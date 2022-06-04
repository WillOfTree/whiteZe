# nginx部署

## 一般部署

### 基于域名配置（默认方法）

``` nginx
# 访问方法 web.testpm.com
# 此方法可以使用ip访问
http {
    # 主要配置server块，而一般server会被拆分到vhost文件夹下
    server {
        listen       80; # 监听端口
        server_name  web.testpm.com; # 监听域名
        location / {
            # 这两个必须配置，其他可选
            root   /var/www/nginx/;
            index  index.html index.htm;
            }
        }
}
```

### 基于ip配置

``` nginx
# 访问方法： 10.0.105.199:8080
http {
    include       mime.types;
    default_type  application/octet-stream;

    server {
        listen       10.0.105.199:8080; # 填写IP
        server_name  web.testpm.com; # 填写域名
        location / {
            root   /var/www/nginx/;
            index  index.html index.htm;
        }
     
     # 多个域名，一般会写道vhost文件夹下
     server {
        listen       10.0.105.201:80;
        server_name  web.testpm.com;
        location / {
            root   /1000phone/html/;
            index  index.html index.htm;
            }
        }
}
```

## 部署项目常见问题

首先：你应该配置nginx的error_log选项，并将最后一个参数设为debug，这样可以输出更多错误信息，或者请求信息

### 404 not find

1. 检查 **root参数** ，root 建议放在server里面，因为若是在location中，则只对当前location起效

2. 对于 PHP项目

   ``` nginx
   # 检查 location 项中的 root 参数，
   # 并且保证server，其他location 中没有 root参数。
   location ~ .+\.php($|/) { 
       	# 这项确保路径与项目路径对应
   		root        /var/www/html/website;  
       	........
   } 
   ```

### welcome to nginx 却没有出现项目页面

**对于 PHP项目**

1. 检查location中index选项是不是将index.html写在了前面（优先级高），修改为index.php。

### 403 Forbidden

1. nginx没有项目目录的操作权限 -> 修改目录权限
2. 目录下没有 **index参数** 定义的文件，例如 index index.html，若是没有index.html也会出现403

### PHP无法解析（File not found.）;

查看日志文件确定是php-fpm与nginx交互问题

检查fastcgi_pass 127.0.0.1:9000，确定与php-fpm中的配置相同，php-fpm位置在php的文件夹中。

### 500 服务器错误

代码有错误

**对于PHP**

直接进入php.ini 配置display_error=On显示错误信息，然后修改错误。

### 其他较长错误信息

Fatal error: Uncaught Error: Failed opening required

``` nginx
# 位置：/usr/local/nginx/fastcgi.conf 文件
# 参数： fastcgi_param PHP_ADMIN_VALUE
# $document_root/ 修改为 $document_root/../:
fastcgi_param PHP_ADMIN_VALUE "open_basedir=$document_root/../:/tmp/:/proc/";
```

## 实例配置

### 负载均衡

``` nginx
# 1、配置组
#  tornadoes是自定义名称
upstream tornadoes {  
    server 127.0.0.1:8000
    server 127.0.0.1:8001
    server 127.0.0.1:8002
}

#2、配置location
# //cat路径是自定义的
location /cat { 
	proxy_pass http://tornadoes;  # //这是最主要命令
}
```

### 响应websocket

``` nginx
# 1、配置组（这不是必须的)
upstream websocket {
	server 127.0.0.1:8000
}

# 配置响应websocket的 locateion
location /chat {
    # websocket指定是nginx中的一个组
    proxy_pass http://websocket;
    proxy_http_version 1.1
	# 将http请求升级为websocket
    proxy_set_header Upgrade $http_upgrade;
    proxy_set_header connection "upgrade"; 
}
```

### 反向代理

 

### 解析 PHP

``` nginx
# 需要libxml2支持
# ./configure --prefix=/usr/local/php7 --enable-fpm
# ----------------------------------------------------------------
# 配置nginx
# nginx/conf/rewrite 有写好的配置文件 (特别是lnmp）
server
{
    	# // 必须配置项
        listen 8080;
        server_name www.taskRemand.com ;
    	## 以下必须在server项中配置
		index index.php index.html;  
        root /home/www/task_remand_tp6/public;
    
    	# // 引入配置好的文件，针对php
		include rewrite/thinkphp.conf; # thinkphp的配置文件
        include enable-php.conf; # 开启php支持的文件
}

# 其他常用参数
location ~ *\.php$ {
    fastcgi_index index.php;
    fastcgi_pass  127.0.0.1:9000;
    include       fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
    fastcgi_param SCRIPT_NAME $fastcgi_script_name;
}
```

### 配置解析url参数

``` nginx
#url：[https://abc.dc.com/image?url=https://vpic.v.com/1641213/p0685fxrwij.png](https://abc.dc.com/image?url=https://vpic.video.qq.com/1641213/p0685fxrwij.png)
location ~/image {
   if ($query_string ~ ^(.)url=(.*)$){
		# 设置$imageUrl 等于if语句中的第二个数据
      	set $imageUrl $2;
      	proxy_pass $imageUrl; #转发
   }
 }
```

### 配置解析ssl

1. 申请证书，

   阿里云提供证书申请，可申请免费证书 ( SSL证书->免费证书->创建证书 ）

2. 检查nginx是否有 http_ssl_module 模块

   ``` shell
   # 使用命令，查看是否有 --with-http_ssl_module
   nginx -V
   ```

3. SSL证书部署

``` nginx
# 目录：/usr/local/nginx
# 创建证书文件夹 cert
# 上传证书到目录

server{
    listen 443 ssl;
    # 绑定证书的域名
    server_name miaomu.willoftree.cn;
    
    # ssl on;
    # 如果一站点既要80 http访问，又要443https访问。
    # 不能在配置文件中使用ssl on，配置listen 443 ssl;
    
    #证书信息
    ssl_certificate ssl/miao/....crt;
    ssl_certificate_key ssl/....key;
        
    #私钥名称
    ssl_session_timeout 5m;
    ssl_ciphers ECDHE_RSA_AES128-GCM-SHA256:HIGH:!aNULL:!MD5:!RC4:!DHE;
    ssl_prefer_server_ciphers on;
    
    location / {
        proxy_pass http://xxxx.com:port;
    }
}
```



