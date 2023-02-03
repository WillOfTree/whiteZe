# uWSGI配置安装

## 一、适用

django\flask等项目部署

## 二、安装虚拟环境

详见-虚拟环境

## 三、安装uwsgi

``` shell
# 首先进入创建的虚拟环境
source /env/bin/active
# 在虚拟环境中安装uwsgi
pip install uwsgi
```

## 四、通过命令行运行

``` shell
# http：端口
# wsgi-file：启动文件
uwsgi --http :80 --wsgi-file app.py --callable app 
```

### 五、通过配置文件运行

### 1、创建文件uwsgi.ini

touch uwsgi.ini

### 2、修改文件

``` toml
[uwsgi]
# 通过socket方式启动
socket=127.0.0.1:8001 
# 项目根目录
chdir=/home/www/flask 
# manager -> 启动文件manager.py
# app -> flask实例化的类， app=flask(__name__)
# 指定启动文件
wsgi-file = /var/www/flask/manager.py 
# 指定Flask(__name__)的变量名称
# eg：app = Flask(__name__)
callable = app
# 后台
master=true 
# virtualenv虚拟环境目录，不必要写到bin/active
virtualenv=/envs/nb/
# 4个进程
processes=4 
# 2个线程
threads=2  
# pid保存的文件
pidfile=/home/www/flask/conf/pid.pid 
disable-logging=false
# 日志文件
daemonize=/home/www/flask/conf/daemonize.log
```

### 3、修改nginx配置文件

``` shell
server{
	location / {
		include uwsgi_params;
		uwsgi_pass 127.0.0.1:8001;
	}

	location /static {
	# 静态文件
		alias /home/www/flask/static/; 
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