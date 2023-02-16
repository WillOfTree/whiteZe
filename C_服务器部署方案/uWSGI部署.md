# uWSGI配置安装

## 一、部署流程

$\frac{上传项目}{上传数据库}\to 安装python虚拟环境\to 配置nginx服务\to 配置uwsgi\to 测试$

## 二、安装虚拟环境

详见-虚拟环境

## 三、安装uwsgi

``` shell
# 首先进入创建的虚拟环境，env是自己创建的虚拟环境
source /env/bin/active
# 在虚拟环境中安装uwsgi
pip install uwsgi
```

## 四、运行

### 1、通过命令行运行（不推荐）

``` shell
# http：端口
# wsgi-file：启动文件
uwsgi --http :80 --wsgi-file app.py --callable app 
```

### 2、通过配置文件运行

#### （1）创建文件uwsgi.ini

touch uwsgi.ini

#### （2）修改文件

``` toml
[uwsgi]
# 通过socket方式启动
socket=127.0.0.1:8001 

# 项目根目录
chdir=** 
# virtualenv虚拟环境目录，不必要写到bin/active,写到bin所在的目录即可
virtualenv=**
# pid保存的文件
pidfile=**/pid.pid 
disable-logging=false
# 日志文件，这个很重要，500错误时，错误信息会记录在这个位置
daemonize=**/daemonize.log

# manager -> 启动文件manager.py
# 指定启动文件
wsgi-file = /var/www/flask/manager.py 

# app -> app = Flask(__name__)
# flask实例化的类名称
callable = app
# 后台启动
master=true 

# 这个配置项一般与服务器配置相关
# 4个进程
processes=4 
# 2个线程
threads=2  
```

#### （3）修改nginx配置文件

``` shell
server{
	# 主要配置，ssl，静态文件见nginx部署方案
	location / {
		include uwsgi_params;
		uwsgi_pass 127.0.0.1:8001;
	}
}
```

## 命令

``` shell
# 关闭
uwsgi --stop pid.pid 
# 启动,uwsig.ini是uwsig的配置文件
uwsgi --ini uwsgi.ini 
# 以后台的模式运行
uwsgi --ini uwsgi.ini &
```

## 坑

1、如果日志记录no python application ,可能是flask或djano项目业务代码有错，这些错误不会被记录，uwsgi会记录一个no python application