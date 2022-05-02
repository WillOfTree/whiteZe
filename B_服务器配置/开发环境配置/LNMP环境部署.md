# LNMP下载

[安装 - LNMP一键安装包](https://www.lnmp.org/install.html)

[LNMP添加、删除虚拟主机及伪静态使用教程 - LNMP一键安装包](https://lnmp.org/faq/lnmp-vhost-add-howto.html)

安装步骤

1. 下载LNMP，进入软件目录，运行 install.sh

2. 选择MySQL版本、PHP版本 
   
   > 注意：mysql 密码问题
   > 
   > 1.5之前版本如果安装时不输入直接回车，密码为root，
   > 
   > 1.5及之后版本为 lnmp.org#随机数字，如没有输入密码会立即显示，安装完成后也会再次显示，也可以查询安装日志。
   
   添加数据库命令：lnmp database add
   
   编辑数据库用户密码命令：lnmp database edit
   
   删除数据库命令：lnmp database del
   
   列出所有数据库命令：lnmp database list

3. 等待安装成功

# LNMP常用命令

配置虚拟主机：**lnmp vhost add**

列出虚拟主机：**lnmp vhost list**

删除虚拟主机：**lnmp vhost del**

### 默认网站(虚拟主机)

LNMP默认网站配置文件：/usr/local/nginx/conf/nginx.conf  

LNMPA默认网站配置文件：

    /usr/local/nginx/conf/nginx.conf      

    /usr/local/apache/conf/extra/httpd-vhosts.conf  

LAMP默认网站配置文件：/usr/local/apache/conf/extra/httpd-vhosts.conf
