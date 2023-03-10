# ThinkPHP6

## 常用命令

### 下载安装

``` shell
# 必须先安装composer
# windowns 直接运行composer-setup.exe
# 更改国内镜像
composer config -g repo.packagist composer https://mirrors.aliyun.com/composer/

# 安装TP
# 命令行运行，先cd到指定安装的目录在运行命令
composer create-project topthink/think tp
# 进入TP目录，更新项目，防止有错误
composer update topthink/framework
```

### 运行

``` shell
# TP6提供命令运行服务
# 进入项目根目录
php think run
# 指定8080端口运行
php think run -p 8080
```

### 安装视图

``` shell
composer require topthink/think-view
```

### 安装视图

错误信息 Driver [Think] not supported.

``` shell
composer require topthink/think-view
```



## url访问

单应用访问模式：

http://serverName/index.php（或者其它入口文件）/控制器/操作/参数/值…

多应用访问模式：

http://serverName/index.php/应用/控制器/操作/参数/值...

注意：

要是想省略index.php要开启apache或nginx的URL重写功能，其他不用修改

## 控制器

### 修改默认控制器

``` php
// 修改 /config/route.php文件
'controller_layer'    =>    '123',
```

### 控制器XXXmodel与XXXcontroller

``` php
/**
 * 若是开启控制器后缀，则控制器必须要改成Acontroller.php
 * 模型必须写Amodel.php
 **/
// /config/route.php
'controller_suffix'     => true,
```



### 定义

``` php
<?php
// 1、命名空间与路径是一致的
namespace app\controller;

// 2、类名与文件名保存一直
class User 
{
    // 当前方法访问的路径为
    // http://localhost/index.php/User/login
    public function login()
    {
        return 'login';
    }
    
    // index方法是默认访问的，可以不添加
    public function index()
    {
        return 'index';
    }
}
```

### 输出\中断

``` php
// TP采用return输出，但只能输出字符串
public function out(){
    $data = array("a"=>1, "b"=>2);
    return json($data);
}

// 中断，推荐使用halt()方法
public function out(){
    $data = array("a"=>1, "b"=>2);
    halt("ceccc");
    return json($data);
}
```

### 基础控制器

``` php
/**
 * 基础控制器仅仅提供了控制器验证功能，
 * 并注入了think\App和think\Request对象，
 * 因此你可以直接在控制器中使用app和request属性调用think\App和 think\Request对象实例
 **/
namespace app\controller;
use app\BaseController;

class Index extends BaseController
{
    public function index()
    {
        // 获取当前方法名
        $action = $this->request->action();
        // 当前实际路径
        $path = $this->app->getBasePath();
    }
}
```

### 空控制器

``` php
// 单应用模式下,提醒错误
namespace app\controller;
class Error
{
    public function index()
    {
        return "sss";
    }
}
```

### 多级控制器

1. 需要在控制器下创建分组

   例如路径:

    /app/controller/group/blog.php

   /app/controller/group/AA.php

2. 访问路径要添加 "."

   http://localhost/index.php/group.blog/index

### 获取POST/GET请求数据

``` php
/**
 * 方法一，函数注入
 **/
use think\Request;

public function __construct(Request $request)
{
    $this->request = $request;
}

public function index(Request $request)
{
    $request->param("key"); // 可获取POST，GET
    $request->get    //获取 $_GET 变量
    $request->post    //获取 $_POST 变量
    $request->put    //获取 PUT 变量
    $request->delete    //获取 DELETE 变量
    $request->session    //获取 SESSION 变量
    $request->cookie    //获取 $_COOKIE 变量
    $request->request    //获取 $_REQUEST 变量
    $request->server    //获取 $_SERVER 变量
    $request->env    //获取 $_ENV 变量
    $request->route    //获取 路由（包括PATHINFO） 变量
    $request->middleware    //获取 中间件赋值/传递的变量
    $request->file    //获取 $_FILES 变量 //这个是比较常用的
}

/**
 * 方法二，静态方法
 **/
use think\facade\Request;
public function index()
{
    return Request::param('name');
}  

/**
 * 方法三，助手函数
 **/
public function index()
{
    return request()->param('name');
}

/**
获取当前请求类型    method()
判断是否GET请求    isGet()
判断是否POST请求    isPost()
判断是否PUT请求    isPut()
判断是否DELETE请求  isDelete()
判断是否AJAX请求    isAjax()
判断是否PJAX请求    isPjax()
判断是否JSON请求    isJson()
判断是否手机访问     isMobile()
判断是否HEAD请求    isHead()
判断是否PATCH请求    isPatch()
判断是否OPTIONS请求    isOptions()
判断是否为CLI执行    isCli()
判断是否为CGI模式    isCgi()
 **/
```



## CURD

1. 在 app 目录下创建一个 model 目录，并创建 User.php 的模型类；

### 创建mode类

``` php
namespace app\model; 
// 必须使用model
use think\Model; 
// 必须继承model
class User extends Model { 
    // 而受保护的字段$connection，则是切换到 demo 数据库；
    protected $connection = 'demo'; 
    // 类中的查询方法
	public function getUser() { 
        $user = User::select(); 
        return json($user); 
    }
}
```

### 查询方法 

``` php
// 控制器中必须使用use才可以使用Db类
use think\facade\Db; 

/**
 * 一些特殊的查询方法
 **/
// 可以得到最近一条 SQL 查询的原生语句；
Db::getLastSql()
    
/**
 * 
 **/
// 生产静态实例查询方法
$userQuery = Db::table("tp_user")
$userQuery->where('id', 27)->find();    
// 清除上一次查询添加where
->removeOption('where')
    
/**
 * DB类的链式查询
 * Db::table()中 table 必须指定完整数据表（包括前缀）
 **/
// 初始化Db类，'tp_user'为表名
Db::table('tp_user')  
// 指定条件,where("字段", 值)
->where("id", 1)
    
// return: 没有返回空，有返回数组
// 只查询一条数据，需指定 where 条件； 
->find()
// 获取数据多条数据
->select()
// 可以查询username字段的的值（单个），没有数据返回 null；
->value('username');    
// 指定字段(username字段/列），没有数据返回空数组；
->column('username');
// 指定字段(username字段/列)并修改key为id，没有数据返回空数组；
->column('username', "id");

/**
 * 结果返回的数据形式
 **/
// 没有查询到数据抛出异常
->findOrFail()    
// 在没有数据时返回一个空数组
->findOrEmpty();
// 数据集对象转化为数组；
->toArray();
// 获取多列数据
->select();
// 抛出异常；
->selectOrFail();


```

### 查询极大数据

``` php
// 列用chunk方法批量处理数据
// 每次查询3条，直到查询完成
Db::table('tp_user')->chunk(3, function($users) { 
    foreach ($users as $user) {
        dump($user); 
    }
});

// 利用游标查询功能，php特性，性能要好点
$cursor = Db::table('tp_user')->where("id", 1)->cursor(); 
foreach($cursor as $user){ 
    dump($user); 
}
```

### 链式查询方法

#### where详解

``` php
/**
 * 表达式查询，就是 where()方法的基础查询方式；
 * where('字段名','查询表达式','查询条件')
 **/ 
// 比较查询 
Db::name('user')->where('id', 80)->find(); 
//使用=、<>、>、<、>=、<=可以筛选出各种符合比较值的数据列表； 
Db::name('user')->where('id','<>',80)->select();
Db::name('user')->where('id','=',80)->find();
//使用 like 表达式进行模糊查询；
Db::name('user')->where('email','like','xiao%')->select();

//like 表达式还可以支持数组传递进行模糊查询；
// (`email` LIKE 'xiao%' OR `email` LIKE 'wu%')
Db::name('user')->where('email','like',['xiao%','wu%'], 'or')->select();

//like 表达式具有两个快捷方式 whereLike()和 whereNoLike()；
Db::name('user')->whereLike('email','xiao%')->select(); 
Db::name('user')->whereNotLike('email','xiao%')->select();

//between 表达式具有两个快捷方式 whereBetween()和 whereNotBetween()； 
Db::name('user')->where('id','between','19,25')->select(); 
Db::name('user')->where('id','between',[19, 25])->select(); 
Db::name('user')->whereBetween('id','19,25')->select(); 
Db::name('user')->whereNotBetween('id','19,25')->select();

//in 表达式具有两个快捷方式 whereIn()和 whereNotIn()； 
Db::name('user')->where('card','in', '19,21,29')->select();
Db::name('user')->where('card','in', [19, 21, 29])->select();
Db::name('user')->whereIn('card','19,21,29')->select(); 
Db::name('user')->whereNotIn('card','19,21,29')->select();

//null 表达式具有两个快捷方式 whereNull()和 whereNotNull()； 
Db::name('user')->where('uid','null')->select(); 
Db::name('user')->where('uid','not null')->select(); 
Db::name('user')->whereNull('uid')->select(); 
Db::name('user')->whereNotNull('uid')->select();

// 使用 exp 可以自定义字段后的 SQL 语句； 
Db::name('user')->where('id','exp','IN (19,21,25)')->select(); 
Db::name('user')->whereExp('id','IN (19,21,25)')->select();

//关联数组查询，通过键值对来数组键值对匹配的查询方式； 
$user = Db::name('user')->where([ 
    'gender' => '男', 
    'price' => 100  
])->select();

//索引数组查询，通过数组里的数组拼装方式来查询； 
$user = Db::name('user')->where([ 
    ['gender', '=', '男'], 
    ['price', '=', '100'] 
])->select();

// whereRaw()支持复杂字符串格式
Db::name('user')->whereRaw('gender="男" AND price IN (60, 70, 80)')->select();

// SQL 查询采用了预处理模式，比如 id=:id，也能够支持；
Db::name('user')->whereRaw('id=:id', ['id'=>19])->select();


```

#### field-指定字段查询

``` php
//使用 field()方法，可以指定要查询的字段； 
Db::name('user')->field('id, username, email')->select(); 
Db::name('user')->field(['id', 'username', 'email'])->select();

//使用 field()方法，给指定的字段设置别名；
Db::name('user')->field('id, username as name')->select();
Db::name('user')->field(['id', 'username'=>'name'])->select();

//查询获取所有字段，而不是*；
Db::name('user')->field(true)->select();

//屏蔽掉想要不显示的字段
Db::name('user')->withoutField('details')->select();

//使用 field()方法在新增时，验证字段的合法性；
Db::name('user')->field('username, email, details')->insert($data);
```

#### 起别名查询

``` php
//使用 alias()方法，给数据库起一个别名； 
Db::name('user')->alias('a')->select();
```

#### limit-分页

``` php
//使用 limit()方法，限制获取输出数据的个数； 
Db::name('user')->limit(5)->select(); 
//分页模式，即传递两个参数，比如从第 3 条开始显示 5 条 limit(2,5)；
Db::name('user')->limit(2, 5)->select(); 

//实现分页，需要严格计算每页显示的条数，然后从第几条开始；
//第一页 
Db::name('user')->limit(0, 5)->select(); 
//第二页 
Db::name('user')->limit(5, 5)->select();

//page("第几页", "一页显示几条") 
//第一页 
Db::name('user')->page(1, 5)->select(); 
//第二页 
Db::name('user')->page(2, 5)->select();
```

#### order-排序

``` php
///使用 order()方法，可以指定排序方式，没有指定第二参数，默认 asc； 
Db::name('user')->order('id', 'desc')->select(); 
//支持数组的方式，对多个字段进行排序； 
Db::name('user')->order([
    'create_time'=>'desc', 
    'price'=>'asc'
])->select(); 

//使用 orderRaw()方法，支持排序的时候指定 MySQL 函数； 
Db::name('user')->orderRaw('FIELD(username,"樱桃小丸子") DESC')->select();
```

#### group-分组

``` php
///使用 group()方法，给性别不同的人进行 price 字段的总和统计；
Db::name('user')->fieldRaw('gender, SUM(price)') ->group('gender')->select();
//多字段分组统计； 
Db::name('user')->fieldRaw('gender, SUM(price)') ->group('gender,password')->select();

//使用 group()分组之后，再使用 having()进行筛选； 
$result = Db::name('user') 
    ->fieldRaw('gender, SUM(price)') 
    ->group('gender') 
    ->having('SUM(price)>600') 
    ->select();
```



### 增加数据

``` php
/**
 * insert()方法，插入一条数据
 * return： 成功返回1， 失败抛出异常
 **/ 
$data = [ 
    'username' => '辉夜', 
    'password' => '123', 
];
Db::name('user')->insert($data);
//忽略异常
Db::name('user')->strict(false)->insert($data);

//mysql，可以支持 replace 写入；
//insert 和 replace 写入的区别，前者表示表中存在主键相同则报错，后者则修改；
Db::name('user')->replace()->insert($data);

// 新增成功后返回当前数据 ID
Db::name('user')->insertGetId($data);

/**
 * 插入多条数据
 **/
$data = [ 
    ['username' => '辉夜'], 
    ['password' => '123'],
];
Db::name('user')->insertAll($data);
//持 replace()方法
Db::name('user')->replace()->insertAll($data);

/**
 * 以自行判断是新增还是修改(更新)数据
 **/
Db::name('user')->save($data);
```

### 修改数据

``` php
/**
 * 修改成功返回影响行数，没有修改返回 0；
 **/ 
$data = [ 
    'username' => '李白' 
];
Db::name('user')->where('id', 38)->update($data); 

//使用 save()方法进行修改数据，这里必须指定主键才能实现修改功能； 
Db::name('user')->where('id', 232) ->save(['username'=>'李黑']);

//如果修改数据包含了主键信息，比如 id，那么可以省略掉 where 条件； 
$data = [ 
    'id' => 231, 
    'username' => '李白' 
];
Db::name('user')->update($data); 

// 如果想让一些字段修改时执行 SQL 函数操作，可以使用 exp()方法实现； 
Db::name('user')->where('id', 232) ->exp('email', 'UPPER(email)') ->update();

//如果要自增/自减某个字段，可以使用 inc/dec 方法，并支持自定义步长； 
Db::name('user')->where('id', 232) ->inc('price') ->dec('status', 2) ->update(); 

//一个更加简单粗暴灵活的方式，使用::raw()方法实现 3，4 点的内容； 
Db::name('user')->where('id', 232) ->update([ 
        'email' => Db::raw('UPPER(email)'), 
        'price' => Db::raw('price + 1'), 
        'status' => Db::raw('status - 2')
]); 
```

### 删除数据

``` php
//极简删除可以根据主键直接删除，删除成功返回影响行数，否则 0； 
Db::name('user')->delete(51); 
//根据主键，还可以删除多条记录； 
Db::name('user')->delete([48,49,50]); 
//正常情况下，通过 where()方法来删除； 
Db::name('user')->where('id', 47)->delete(); 
//通过 true 参数删除数据表所有数据； 
Db::name('user')->delete(true);
```

### 聚合查询

``` php
//使用 count()方法，可以求出所查询数据的数量；
Db::name('user')->count(); 
//count()可设置指定 id，比如有空值(Null)的 uid，不会计算数量； 
Db::name('user')->count('uid'); 
//使用 max()方法，求出所查询数据字段的最大值； 
Db::name('user')->max('price'); 
//如果 max()方法，求出的值不是数值，则通过第二参数强制转换； 
Db::name('user')->max('price', false); 
//使用 min()方法，求出所查询数据字段的最小值，也可以强制转换； 
Db::name('user')->min('price'); 
//使用 avg()方法，求出所查询数据字段的平均值； 
Db::name('user')->avg('price'); 
//使用 sum()方法，求出所查询数据字段的总和； 
Db::name('user')->sum('price');
```

### 子查询

``` php
// 使用 fetchSql()方法，可以设置不执行 SQL，而返回 SQL 语句，默认 true； 
Db::name('user')->fetchSql(true)->select(); 
//使用 buildSql()方法，也是返回 SQL 语句，不需要再执行 select()，且有括号； 
Db::name('user')->buildSql(true); 
//结合以上方法，我们实现一个子查询； 
$subQuery = Db::name('two')->field('uid')->where('gender', '男')->buildSql(true); 
$result = Db::name('one')->where('id','exp','IN '.$subQuery)->select();
//使用闭包的方式执行子查询； 
$result = Db::name('one')->where('id', 'in', function ($query) { 
    $query->name('two')->where('gender', '男')->field('uid'); 
})->select()
```

### 原生查询

``` php
//使用 query()方法，进行原生 SQL 查询，适用于读取操作，SQL 错误返回 false； 
Db::query('select * from tp_user'); 
//使用 execute 方法，进行原生 SQL 更新写入等，SQL 错误返回 false； 
Db::execute('update tp_user set username="孙悟空" where id=29');
```

