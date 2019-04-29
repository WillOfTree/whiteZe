<?php
/**
 * PHP偷偷运行的羞耻play(PHPAppStartingModel)
 * 
 * 简单的实现了ＰＨＰ后台运行，对比任务ＩＰ并将相同的ＩＰ的Ｋｅｙ值插入数据库
 * 注：请求需是异步请求（例:Ajax)
 *
 * @author litao <litao@chinawllc.com>
 * @copyright 2016 chinawllc
 * @version v1.0
 */
class PHPAppStartingModel {
    /**
     * 数据库名
     * @var string
     */
    private $table = "sss";
    /**
     * 设置信息，以后可能添加新的信息
     * @var array
     */
    private $setValue = array(
      "echo"=>"what's the fuck!",
    );

     /**
     * 开始方法
     *
     * @param array $aggregate 　集合ＩＰ数组
     * @param array $loophole    漏洞ＩＰ集合
     * @param int   $AID         分析任务名称
     */
    public function start($aggregate, $loophole,$AID){

        //设置
        $this->_set();
    
        $valueTMP = "";
        $valueTMP = $this->TWOsearch($aggregate,$loophole);
     
        //得到插入的数据
        $valueBIG = "";
        foreach($valueTMP as $v){
          $valueBIG = "( ${AID},". $aggregate[$v]['id'] . "," . $loophole[$v]['id'] ." ),".$valueBIG;
        }
        $valueBIG = rtrim($valueBIG, ",");
        // sleep(10);//测试效果
        $this->insterDB($valueBIG);
        exit;
    }


    /**
     * 执行ｓｑｌ
     * 
     * @param  string $valueBIG 要插入的数据
     */
    private function insterDB($valueBIG){
        //添加数据到数据库
        $dbA = new Zend_db_Table;
        $db = $dbA->getAdapter();

        $table = $this->table;
        $prepareSQL = "INSERT INTO ${table} (aid,nass_IP_id,vrms_IP_id) VALUES ${valueBIG}";
        
        $db->query($prepareSQL);
    }

    private function _set(){
        $set = $this->setValue;
         echo $set['echo'];
        //得到缓存区的大小
        $size = ob_get_length();
        //发送关闭连接到前台
        header("Content-Length: $size");
        header('Connection: close');
        ob_end_flush();//与下面的缓存操作重复
        ob_flush();
        flush();

        //开启PHP后台运行
        ignore_user_abort(true);
        //脚本超时设置
        set_time_limit(0);
    }

    /**
     * 数值查找
     * 
     * @param array $aggregate 集合IP
     * @param array $loophole 漏洞IP
     * @param array 相同IP的集合
     */
    private function TWOsearch($aggregate,$loophole){
        $result = array();
        //查找
        foreach($aggregate as $k=>$v){
            foreach($loophole as $kk=>$vv){
                if($v['IP'] == $vv['IP']){
                    $result[] = $k;
                    //删除已查找过的数据
                    unset($loophole[$kk]);
                }
            }
        }

        return $result;
    }
}