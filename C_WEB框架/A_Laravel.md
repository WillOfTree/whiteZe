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

   - Broadcasting：包含应用程序的所有广播频道类。这些类是使用 make:channel 命令生成的。 此目录默认不存在
   - Console：应用程序的所有自定义 Artisan 命令。
   - Events：此目录默认不存在，但会由 event:generate 和 make:event Artisan 命令为你创建。
   - Exceptions：包含应用程序的异常处理程序
   - Http：目录包含你的控制器、中间件和表单请求。 
   - Jobs：该目录默认不存在，但如果你执行 make:job Artisan 命令，则会为你创建。 Jobs 目录包含你的应用程序的 队列作业。 
   - Listeners：此目录默认不存在，但如果你执行 event:generate 或 make:listener Artisan 命令，则会为你创建。
   - Mail：该目录默认不存在，但如果你执行 make:mail Artisan 命令，则会为你创建。 
   - Models：Eloquent 模型类
   - Notifications：默认情况下，此目录不存在，但如果你执行 make:notification Artisan 命令时会自动生成。
   - Policies：默认情况下，此目录不存在，但如果你执行 make:policy Artisan 命令会生成。 
   - Providers：包含程序中所有的服务提供者。
   - Rules：默认情况下，此目录不存在，但如果你执行 make:rule Artisan 命令后会生成。

2. Bootstrap 目录：

   app.php ：引导框架。

   cache：缓存文件。你通常不需要修改此目录中的任何文件

3. Config 目录：所有应用程序的配置文件。

4. Database 目录：数据库迁移、模型工厂和种子。

5. Public 目录：资源文件、入口文件

   index.php：所有进入应用程序的请求的入口点并配置自动加载。

6. Resources 目录：视图，模板文件，例如 CSS 或 JavaScript。

7. Routes 目录：所有路由定义。

   web.php：中间件组中的路由，该组提供会话状态、CSRF 保护和 cookie 加密。

   api.php：中间件组中的路由。这些路由旨在是无状态的，因此通过这些路由进入应用程序的请求旨在通过令牌进行身份验证，并且不会访问会话状态。

   console.php：文件是你可以在其中定义基于闭包的控制台命令的位置。

   channels.php：文件是你可以在其中注册所有应用程序支持的事件广播 频道的位置。

8. Storage 目录：大文件目录、上传的文件、日志等等

9. Tests 目录：tests 目录包含你的自动化测试。 

10. Vendor 目录： Composer 依赖项。

### 二、配置文件










