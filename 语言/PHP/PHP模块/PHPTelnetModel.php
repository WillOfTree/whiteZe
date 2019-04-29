<?php
/**
 * PHPTelnetModel(PHP实现Telnet功能的Model)
 *
 * 这个类提供4个方法可以被调用
 * 1.telnet_connect(string $IP):连接方法
 * 2.telnet_auth_password(string $userName, string $password):密码认证方法
 * 3.telnet_exec(string $cmd):命令执行方法
 * 4.telnet_load_validate():跳转验证的方法，在其他地方应该没什么用处，主要是满足配置核查的需求
 * 注：当一次连接，没有被中断的时候可以发送多条命令
 * 注：本Model只有在连接超时或登陆失败的时候才会中断连接，其他情况请手动中断连接（调用close（）方法）
 *
 * @author litao <litao@chinawllc.com>
 * @copyright 2016 chinawllc
 * @version v1.0
 */
class PHPTelnetModel {

    //保存连接对象
    // private $connectOBJ;
    private static $connectOBJ;
    private $validate;
    //保存连接状态的变量
    private static $EnvSu;
    //超时时间
    const TIME_OUT_SEC = 3;
    const TIME_OUT_USEC = 0;

    /**
     * 
     * @return [type] [description]
     */
    public function doTelnetConnect($ip, $port, $user, $pass, $superRootCmd,$rootPass, $cmd){

        if(self::$EnvSu != $IP || empty($EnvSu)){
            //填写新IP
            self::$EnvSu = $IP;

            $this->telnet_connect($ip, $port);
            $this->telnet_auth_password($user, $pass);

            //判断是否需要跳转
            if(!empty($rootPass)){
                //调用root登陆
                $this->telnet_load_validate($superRootCmd, $rootPass);
            }
        }
        
        foreach($cmd as $v){
            $result[] = $this->telnet_exec($v);
        }
         

        return $result;
    }

    /**
     * 创建连接对象，并设置超时时间
     * @param  string  $IP    IP地址
     * @param  int     $PORT  端口
     * @return int 成功返回success，失败返回原因     
     */
    public function telnet_connect($IP, $PORT){
        
        //创建链接
        $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        if (!$socket) {
            $errorcode = socket_last_error();
            $mrk = socket_strerror($errorcode);
            return $mrk;
        }

        //连接
        // $connection = socket_connect($socket, $IP, 23);
        $connection = socket_connect($socket, $IP, $PORT);
        if (!$connection) {
            $errorcode = socket_last_error();
            $mrk = socket_strerror($errorcode);
            return $mrk;
        }

        $timeOut = array(
            "sec"=>self::TIME_OUT_SEC, 
            "usec"=>self::TIME_OUT_USEC
        );

        // 设置超时时间，防止长时间每有数据返回，会卡住 
        socket_set_option($socket,SOL_SOCKET,SO_RCVTIMEO,$timeOut);

        //保存连接对象
        // $this->connectOBJ = $socket;
        self::$connectOBJ = $socket;

        return "success";
    }


    /**
     * 密码验证的方法
     * @param  string  $userName  用户名
     * @param  string  $passWord  密码
     * @return  成功返回success，失败返回原因
     */
    public function telnet_auth_password($userName, $password){
        // $socket = $this->connectOBJ;
        $socket = self::$connectOBJ;
        //判断
        if(empty($socket)){
            return "socket套接字没有被打开或打开失败";
        }

        //开始协商
        //读取字符串
        $readyString = array();
        $nextReadyS = "";
        do{
            $readyString = $this->readyString();
            if(!empty($readyString['data'])){
                break;
            }
            $doString = $this->consultDoString($readyString['consultString']);
            $this->consultSendString($doString);
        }while(true);

        /**
         * 验证登陆是否成功
         */
        $dealWithString = implode("",$readyString['data']);
        //正则匹配字符串
        $dealWith = preg_split("/\n|\r|\r\n/",$dealWithString);
        //将最后一个放出来
        $dealMark = array_pop($dealWith);
        $dealMark = trim($dealMark);
        
        //写入用户名
        $this->sendAndGet($userName);
        
        //写入密码
        $returnResult = $this->sendAndGet($password);
        //用于记录当前登陆成功的返回标志
        $this->validate = $returnResult;

        //超时判断
        if(empty($returnResult)){
            $this->close();
            return "连接超时";
        }

        //判断是否登陆成功
        $junper = preg_match("/^${dealMark}(\s+)?/m",$returnResult);
        
        if($junper > 0){
            $this->close();
            return "认证失败";
        }

        return "success";
    }


    /**
     * 执行名利的方法
     * @param  string $cmd 命令字符串
     * @return string 执行命令返回的结果
     */
    public function telnet_exec($cmd){
        return $this->sendAndGet($cmd);
    }


    /**
     * telnet跳转验证方法
     * 
     *
     * @param  string  $superCmd  切换特权账户的命令
     * @param  string  $rootPass  特权账户的密码
     * @return [type] [description]
     */
    public function telnet_load_validate($superCmd, $rootPass){
        
        // //普通用户登陆
        // $result = $this->telnet_auth_password($userName, $password);
        //获取普通用户登陆的标识
        $validate = $this->validate;
        $sendReult = "";

        //发送跳转命令
        $sendReult = $this->sendAndGet($superCmd);
        //发送用户密码
        if(!empty($rootPass)){
            $sendReult = $this->sendAndGet($rootPass);
        }
        //对登陆进行判断
        $result = $this->judgeString($validate,$sendReult);

        if($result){
            return "success";
        } else {
            return 0;
        }
    }

    /**
     * 处理跳转验证的方法
     * 
     * @param  string $firstMark 普通用户登陆成功后返回的数据，eg：[test1@localhost ~]$
     * @param  string $twoMark   输入跳转命令后返回的数据，eg：[root@localhost test1]#
     * @return [type]            [description]
     */
    private function judgeString($firstMark,$twoMark){
        $mark = array(
            $firstMark,
            $twoMark
        );

        $result = array();
        for($i=0;$i<2;$i++){
            //正则分割字符串
            $dealWith = preg_split("/\n|\r|\r\n/",$mark[$i]);
            //将最后一个放出来
            $dealMark = array_pop($dealWith);
            $result[] = trim($dealMark);
        }

     
        if($result['0'] == $result['1']){
            //登陆失败
            return 0;
        }
        //登陆成功
        return 1;

        // $junper = preg_match("/^${dealMark}(\s+)?/m",$twoMark);
        //正则匹配字符串
        // $dealWith = preg_split("/\n|\r|\r\n/",$twoMark);
        // //将最后一个放出来
        // $dealMarkTwo = array_pop($dealWith);
        // $dealMarkTwo = trim($dealMark);

        // //如果匹配到标识，说明登陆失败
        // if($junper > 0){
        //     return 0;
        // }
        // return 1;
    }

    /**
     * 读取字符串
     */
    private function readyString(){
        $IAC = chr(255);

        // $socket = $this->connectOBJ;
        $socket = self::$connectOBJ;

        $getData = array();
        do{
            $out = socket_read($socket, 1, PHP_BINARY_READ);

            /**
             * 对获取的数据进行筛选，
             * 将协商相关的字符全部放到特定的位置。
             */
            if($out == chr(255)){

                $getData['consultString'][] = $out;
                for($i=0;$i<2;$i++){
                    $string = socket_read($socket, 1, PHP_BINARY_READ);
                    $getData['consultString'][] = $string;
                }
                continue;
            }
            
            //标识结束
            if($out == chr(0)){
                break;
            }

            //没有再返回结果
            if($out == ""){
                break;
            }

            /**
             * 保存可以输出的数据
             */
            $getData['data'][] = $out;

        }while(true);

        return $getData;
    }


    /**
     * 协商-处理命令
     * 
     * @param  array  $getData  获取的协商的命令
     * @return string 经过处理，用来回应协商结果的命令
     */
    private function consultDoString($getData){
        $IAC = chr(255);
        $DO = chr(253);
        $DONT = chr(254);
        $WILL = chr(251);
        $WONT = chr(252);
        $SB = chr(250);
        $SE = chr(240);

        $sendMark = array();
        $count = count($getData);
        for($i=0;$i<$count;$i++){
            if($getData[$i] == $IAC){
                //可以拒绝的
                if($getData[$i+1] == $DO){
                    $sendMark[] = $IAC.$WONT.$getData[$i+2];
                    continue;
                }
                if($getData[$i+1] == $WILL){
                    $sendMark[] = $IAC.$DONT.$getData[$i+2];
                    continue;
                }
                //必须同意的
                if($getData[$i+1] == $WONT){
                    $sendMark[] = $IAC.$DONT.$getData[$i+2];
                    continue;
                }
                if($getData[$i+1] == $DONT){
                    $sendMark[] = $IAC.$WONT.$getData[$i+2];
                    continue;
                }
            }
        }

        return $sendMark;
    }


    /**
     * 协商-发送的字符串
     *
     * @param  array  $sendMark  用来回应协商的命令
     * @var string
     */
    private function consultSendString($sendMark){
        // $socket = $this->connectOBJ;
        $socket = self::$connectOBJ;

        $aa = "";
        foreach($sendMark as $v){
            $aa = $aa.$v; 
        }

        socket_write($socket,$aa);
    }


    /**
     * 发送命令 并获取返回值
     * 
     * @param  string $cmd 命令
     * @return string 命令执行的结果
     */
    private function sendAndGet($cmd){
        // $socket = $this->connectOBJ;
        $socket = self::$connectOBJ;

        //添加换行
        $cmd = $cmd."\n";

        socket_write($socket,$cmd);
        $result = $this->readyString();

        //拼接字符串
        $string = implode("",$result['data']);

        return $string;
    }


    /**
     * 中断连接
     */
    private function close(){
        // $socket = $this->connectOBJ;
        $socket = self::$connectOBJ;

        socket_close($socket);
    }
}