# MySQL

## 常用命令

``` mysql
# 进入数据库
mysql -uroot -p 
# 创建数据库
create database 数据库名 
# 选择数据
use 数据库名称
# 显示表
show tables 表名
# 显示数据库
show databases 数据库
# 索引从0开始
truncate table 表名 #
# 修改密码
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '新密码';
# 设置为空密码
mysql> set password for root@localhost=password('');
# 授权用户tree拥有demoDB库的所以权限
grant all privileges on demoDB.* to tree@localhost
# 创建用户tree,密码是1233
create user 'tree'@'localhost' identified '1233'
# 允许tree远程访问
grant all privileges on *.* to 'tree'@'%' with grant option
```

## 忘记密码

``` shell
# 方法一，跳过密码检验
# 打开mysql的配置文件，添加skip-grant-tables
[mysqld]
skip-grant-tables

# 方法二，修改密码
# 前提要先跳过密码，后进入mysql控制台
mysql > use mysql;
mysql > update user set authentication_string=password('123456') where user='root';
mysql > flush privileges;

# 出现的错误
# ERROR 1820 (HY000): You must reset your password using ALTER USER statement before executing this statement.
alter user 'root'@'localhost' identified by 'youpassword';

# 出现的错误
# ERROR 1819 (HY000): Your password does not satisfy the current policy requirements
set global validate_password_policy=0;
```

### 运行sql文件

``` mysql
# 创建数据
# 进入库
source /opt/mysql.sql
```

### 导出 

``` mysql
mysqldump -u用戶名 -p密码 -d 数据库名 表名 > 脚本名;

#导出整个数据库结构和数据
mysqldump -h localhost -uroot -p123456 database > dump.sql

#导出单个数据表结构和数据
mysqldump -h localhost -uroot -p123456 database table > dump.sql

#导出整个数据库结构（不包含数据）
mysqldump -h localhost -uroot -p123456 -d database > dump.sql

#导出单个数据表结构（不包含数据）
mysqldump -h localhost -uroot -p123456 -d database table > dump.sql
```

## window使用

### 常用

必须是系统管理员权限

``` shell
# 启动mysql
net start mysql
# 关闭mysql
net stop mysql
```

### 错误-无法启动

检查mysql.ini文件中路径是否正确

## 错误-缺少data

``` shell
# 缺少data文件
mysql --initialize --user=mysql --console
# 
```

## 远程访问MySQL

use mysql;

select host,user,password from user;

可以看到在user表中已创建的root用户。host字段表示登录的主机，其值可以用IP，也可用主机名，

  (1)有时想用本地IP登录，那么可以将以上的Host值改为自己的Ip即可。

### 实现远程连接(授权法)

  将host字段的值改为%就表示在任何客户端机器上能以root用户登录到mysql服务器，建议在开发时设为%。  
  update user set host = ’%’ where user = ’root’;

  将权限改为ALL PRIVILEGES

mysql> use mysql;
Database changed
mysql> grant all privileges on *.* to root@'%' identified by "password";
Query OK, 0 rows affected (0.00 sec)

mysql> flush privileges;
Query OK, 0 rows affected (0.00 sec)

mysql> select host,user,password from user;
+--------------+------+-------------------------------------------+
| host     | user | password                 |
+--------------+------+-------------------------------------------+
| localhost  | root | *A731AEBFB621E354CD41BAF207D884A609E81F5E |
| 192.168.1.1 | root | *A731AEBFB621E354CD41BAF207D884A609E81F5E |
| %      | root | *A731AEBFB621E354CD41BAF207D884A609E81F5E |
+--------------+------+-------------------------------------------+
3 rows in set (0.00 sec)

这样机器就可以以用户名root密码root远程访问该机器上的MySql.

### 实现远程连接（改表法）

use mysql;

update user set host = '%' where user = 'root';

这样在远端就可以通过root用户访问Mysql.

 

 