# Laravel使用记录

- 版本：8.x

## 前置使用

### 一、安装环境

#### Ⅰ、composer安装

1. windwos安装：直接下载
2. LINUX安装

#### Ⅱ、Homestead 

Homestead是一个类似于python虚拟环境的开发环境，可替换的软件为docker。但Laravel推荐使用Homestead

1. windows安装

### 二、安装Laravel

`composer create-project laravel/laravel[=版本] (项目名称)` 

- create-project：创建项目
- laravel/laravel[=版本]：laravel版本

使用样例：

1. 安装最新版本

   `composer create-project laravel/laravel example-app` 

2. 安装指定版本：

   `composer create-project laravel/laravel=9.* example-app` 

### 三、运行

注意当前命令需要在laravel根目录下运行

1. 配置命令：生成数据库key等密钥

   `php artisan key:generate` 

2. 运行本地项目：

   `php artisan serve` 

3. 了解应用程序的配置、驱动程序和环境

   `php artisan about`

## 环境配置

### 一、目录结构

1. App 目录：app 目录包含应用程序的核心代码。

   - Http：代码主要存在的目录
   - Models：模型类。

2. Bootstrap 目录：

   - app.php ：引导框架。
   - cache：缓存文件。你通常不需要修改此目录中的任何文件

3. Config 目录：配置文件。

4. Database 目录：数据库迁移、模型工厂和种子。

5. Public 目录：资源文件、入口文件

   - index.php：入口文件

6. Resources 目录：视图，模板文件，例如 CSS 或 JavaScript。

7. Routes 目录：所有路由定义。

   Laravel没有默认路由，必须先自定义路由才能访问

   - web.php：中间件组中的路由，该组提供会话状态、CSRF 保护和 cookie 加密。
   - api.php：中间件组中的路由。这些路由旨在是无状态的，因此通过这些路由进入应用程序的请求旨在通过令牌进行身份验证，并且不会访问会话状态。
   - console.php：文件是你可以在其中定义基于闭包的控制台命令的位置。
   - channels.php：文件是你可以在其中注册所有应用程序支持的事件广播 频道的位置。

8. Storage 目录：大文件目录、上传的文件、日志等等

9. Tests 目录：tests 目录包含你的自动化测试。 

10. Vendor 目录： Composer 依赖项。

### 二、配置文件

## 代码编写

### 一、控制器

1. 存在路径：`\app\Http\controllers\`
2. `controllers.php`：主控制器

#### Ⅰ、创建控制器

``` php
<?php
// 1、命名空间，与路径一样
namespace App\Http\Controllers;
// 因为类x与controller类在同一目录下，所以不用使用use
// 2、继承controllers方法
class X extends Controller {
    // 3、自定义方法
    public function show() {
        dump("输出")
    }
}
```

#### Ⅱ、模板渲染

1. 创建控制器、创建方法

2. 在`/resources/views/`下创建视图文件，这里创建`index.blade.php` 

3. 渲染模板

    ``` php
    // 创建控制器
    class X1 extends Controller {
        // 创建方法
        public function index() {  
            /** 渲染模板
            渲染的模板位置：
            /resources/views/index.black.php
            **/
            return view(view: "index");
            /**
            渲染位置：
            /resources/views/diao/index.black.php	
            return view(view: "diao/index")
            */
        }
    }
    ```

4. 设置路由

    ``` php
    // 设置路径url，设置访问方法
    Route::get(uri:'/',  [X1::class, 'index']);
    ```

5. 模板传值

    ``` php+HTML
    <?php
    /* 控制器 */
    class X1 extends Controller {
        public function index() {  
            return view(view: "index", [
                "name"=>"123",
                "age"=>"123",
            ]);
        }
    }
    
    /* 设置路由 */
    Route::get(uri:'/',  [X1::class, 'index']);
    ?>
    
    /-- 模板文件 */
    <html>
        <!-- 不解析变量中的html标签-->
        {{$name}}--{{$age}}
        <!-- 会解析$name中的标签 -->
        {{!! $name !!}}
    </html>
    ```

#### Ⅲ、请求对象

``` php
/* 获取值-控制器 */
use Illuminate\Http\Request;
class X1 extends Controller {
    // 方法1：绑定对象
    public function index(Request $request) { 
        // 获取某一个值
		$name = $request->input("name");  
        // 获取所有值
        $request->all();
        // 获取POST的值
        $request->post();
        // 获取地址栏参数
        $request->query();
    }
}
```



### 二、路由

1. 配置文件web.php：`\routes\web.php` 
2. 省略入口文件

路由实例：

``` php
/* 控制器路由 */ 
// 引入控制器
use App\Http\Controllers\X
// Route::get('url地址', [控制器名, '方法名']);
// 访问路径：http://xxx.com/index.php/my
Route::get(uri:"my", [X::class, 'show']);

/* 基本路由 */
Route::get(uri:'/', function(){
    return "xxxxxxxxx";
});

/* 参数路由 */
Route::get(uri:"my/{id}", [X::class, 'show']);
// 控制器中使用
/*
class X1 extends Controller {
    // $id 就是url中传递的参数
    public function index($id) { }
}
*/
```

### 三、视图

1. 目录位置：`/resources/views/` 

2. 视图文件后缀必须为：`.blade.php` 

3. 模板`.blade.php`中就是html的内容

4. 为了方便管理视图文件，一般根据控制器名创建视图文件夹

5. 视图路由

    ``` php
    /* 非传值 */
    // 只返回一个视图
    Route::view('/', 'welcome');
    //
    Route::get(uri:'/', function(){
    	// view(view: '视图名称');
        return view(view: 'welcome');
    });
    
    /* 传值 */ 
    // 只返回一个视图
    Route::view('/', 'welcome', [
        'name'=>'123',
        'age'=>'123',
    ]);
    
    Route::get(uri:'/', function(){
    	// view(view: '视图名称');
        return view(view: 'welcome', [
            'name'=>'123',
        	'age'=>'123',
        ]);
    });
    ```

6. 传值到模板`.blade.php`中解析变量

    ``` html
    <html>
        <!-- 不解析变量中的html标签-->
        {{$name}}--{{$age}}
        <!-- 会解析$name中的标签 -->
        {{!! $name !!}}
        <!-- 使用函数 -->
        {{md5(12345)}}
        {{date("Y-m-d h:i:s", time())}}
        <!-- 如果$aa为空，显示空-->
        {{$aa??''}}
        <!-- 带有查询参数withQueryString，一般用于分页 -->
        {{$list->withQueryString()->link()}}
        <!-- 删除时url会更新，保持以前的参数-->
        <a href="/del/{{$id}}?{{http_build_query($gets)}}"
    </html>
    ```

7. 视图方法

    ``` HTML
    <!-- 判断方法 -->
    @if( $a>22 )
    @else 
    @elseif( $a>31 )
    @endif
    <!-- a是否设置 -->
    @isset( $a )
    	<!-- 不为空运行 -->
    @endisset
    
    <!-- 判断时候为空 -->
    @empty( $a )
    	<!-- a为空 -->
    @endempty
    ```


### 四、数据库

1. 配置文件：`\config\database.php` 
2. env配置文件（开发时使用）：`\.env` 

#### Ⅰ、查询方法 

- 注意返回的一般是一个对象，应使用`->`访问

``` php
// 必须引入DB类
use Illuminate\Support\Facades\DB;

/* 使用原生SQL语句 */
DB::select(query: "select * from A");
DB::raw(value:"count(*)");
    
/* 获取所有数据 */ 
// table()设置表名，无前缀
DB::table(table:"User")->get();
/* 获取第一条数据 */ 
DB::table(table:"User")->first();
/* 表达式查询 */ 
DB::table(table:"User")
    ->where(column:"id", operator: '=', value: "1233")
    // 简写：字段，操作符，值
    ->where("id", '=', "1233")
    ->get();
/* 查询一个值 */ 
DB::table(table:"User")
    // 条件
    ->where(column:"id", operator: '=', value: "1233")
    ->value(column: "name");
/* 获取一列的值 */
DB::table(table:"User")
    ->where(column:"sex", operator: '=', value: "1")
    ->pluck(column: "name");
/* 排序、限制、分组 */
DB::table(table:"User")
    // 设置字段
    ->select("id", "name")
    // 条件
    ->where(column:"sex", operator: '=', value: "1")
    // 排序，age-列名，desc-逆序
    ->orderBy("age", "desc")
    // 查询条数
    ->limit(10)
    // 分组，并计算个数，使用having对分组查询
    ->groupBy(groups: "name")
    ->select(column: "id",DB::raw(value:"count(*) as num"))
    ->having(column:"num", operator: '>', value: "5");

/**/
```

#### Ⅱ、使用模型

1. 创建模型，在项目根目录运行

    `php artisan make:model 模型名` 

2. 模型位置：`/app/Models` 

3. 返回的数据一般是数组，使用`[]`访问

模型中使用

``` php
<?php
namespace App\Models;
class Example extends Model {
    // 主键不是整数
    protected $keytype = 'string';
    // 自动时间戳，默认开启
    protected $timestamps = false;
    /* 必须设置的 */
    // 主键
    protected $primarykey = 'id';
    // 表名
    protected $table = 'Student';
    // 设置表名并起别名
    protected $table = "Student as s";
    
    /* 查询方法 */
    public function select() {
        return self::select("id", "name")->get(); 
    }
    
    /* 分页方法 */
    public function select() {
        return self::select("id", "name")
            ->pageinate(10); 
    }
}
```

控制器中调用

``` php
// 使用模型
use App\Models\Student;
// 模型起别名
use App\Models\Student as StudentModel;

class X1 extends Controller {
    public function index() {
        // 调用model中的方法
        Student::select();
    }
}
```

#### Ⅲ、删除方法

``` php
namespace App\Models;
class Example extends Model {
    /* 必须设置的 */
    // 主键
    protected $primarykey = 'id';
    // 表名
    protected $table = 'Student';
    /* 删除 */
    public function del() {
        self::destroy(1);
        self::destroy(1,2,3);
        self::destroy([1,2,3]);
    }
}
```

#### Ⅳ、添加数据

``` php
namespace App\Models;
class Example extends Model {
    // 设置不允许添加字段
    protected $guarded = [];
    
    // 添加方法
    public function add($post) {
        try {
            // 添加多个数据，
           	self::create($post);
            // 方法二
            self::create([
                'name' => "2134",
                "age" => "sdf"
            ])
        }catch (\Exception $e) {
            
        }
    }
}
```



### 五、其他

#### Ⅰ、异常

``` php
try {
    self::destroy($id);
    $arr = ['error'=>0,'msg'=>"成功"];
}catch (\Exception $e) {
    $arr = ['error'=>0,'msg'=>"错误", 'emsg'=>$e];
}
return $arr;
```

#### Ⅱ、表单验证

1. 新建请求类命令：`php artisan make:request 表单验证类名称` 

2. 请求类位置：`\app\Http\Requests\`  

3. 使用方式

    ``` php
    // 假设创建的验证类为studentRequest
    // php artisan make:request studentRequest
    /* 控制器类 */
    use App\Models\Student as StudentModel;
    
    class X1 extends Controller {
        // 使用自定义的request类
        public function index(studentRequst $re) {
        }
    }
    ```

4. 验证失败时，会产生一个302重定向

配置验证request类

``` php
// 开启验证
public function authorize() {
    return false; // 返回改成true
}

// 验证规则
public function rules() {
    // name：规则字段名
    // 详细规则，查看手册
    // required 不能为空
    return [
        'name'=>'required | between:2,10'
    ]
}

/* 提示信息 */
public function messages() {
    return [
        'name.required'=>'不能为空',
        'name.between'=>"字符长度必须在2到10"
    ]
}
```

#### Ⅲ、验证码

#### Ⅳ、文件上传





