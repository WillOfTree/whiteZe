# MySQL

## **一、命令**

mysql -uroot -p 进入数据库

create database ---name---创建数据库

use ---datebaeseName--使用数据库

show tables 显示表

show databases 显示数据库

truncate table 你的表名 #索引从0开始

## 二、运行sql文件**

1/创建数据

2/进入库

3/source /opt/mysql.sql

# **三、导出** 

mysqldump -u用戶名 -p密码 -d 数据库名 表名 > 脚本名;

导出整个数据库结构和数据
mysqldump -h localhost -uroot -p123456 database > dump.sql

导出单个数据表结构和数据
mysqldump -h localhost -uroot -p123456 database table > dump.sql

导出整个数据库结构（不包含数据）
mysqldump -h localhost -uroot -p123456 -d database > dump.sql

导出单个数据表结构（不包含数据）
mysqldump -h localhost -uroot -p123456 -d database table > dump.sql

# **四、MySQL-python**

 

import MySQLdb

 

\# 打开数据库连接

db = MySQLdb.connect(

host="localhost",

user="root",

port="3306",

password="humingfei212697~",

db="codelion",

charset='utf8'

)

\# 使用cursor()方法获取操作游标

cursor = db.cursor()

\#执行

cursor.execute("")

\# 使用 fetchone() 方法获取一条数据

\# data = cursor.fetchone()

print "Database version : %s " % data

\# 关闭数据库连接

db.close()

 

execute(sql)

　　可接受一条语句从而执行

executemany(templet,args)

　　能同时执行多条语句，执行同样多的语句可比execute()快很多，强烈建议执行多条语句时使用executemany

　　templet : sql模板字符串,

​         例如   'insert into table(id,name) values(%s,%s)'

　　args: 模板字符串的参数，是一个列表，列表中的每一个元素必须是元组！！！ 

​        例如： [(1,'小明'),(2,'zeke'),(3,'琦琦'),(4,'韩梅梅')] 

# **远程访问MySQL**

use mysql;

select host,user,password from user;

可以看到在user表中已创建的root用户。host字段表示登录的主机，其值可以用IP，也可用主机名，

  (1)有时想用本地IP登录，那么可以将以上的Host值改为自己的Ip即可。

## **实现远程连接(授权法)**

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

## **实现远程连接（改表法）**

use mysql;

update user set host = '%' where user = 'root';

这样在远端就可以通过root用户访问Mysql.

# **sql语法**

## **add**

## **delect**

## **update**

## **select**

 

 