# pymysql

## 一、基本流程

``` python
# 导入库
import pymysql

# 连接数据库
conn = pymysql.connect(
	host='192.168.9.99', #数据库主机名.默认是用本地主机
	port=3306, #MySQL服务使用的TCP端口.默认是3306
	user='root', #数据库登陆名.默认是当前用户
	password='123', #数据库登陆的秘密.默认为空
	db = 'dbname', #要使用的数据库名.没有默认值
	charset='utf8', #数据库编码
)

# 获取cursor
cursor = conn.cursor()

# sql命令
sql = 'insert into userinfo(username,pwd) values (%s,%s)'
# 执行sql命令，username,pwd是%s的变量
cursor.execute(sql, (username, pwd))

# 提交
conn.commit() # 提交后才会真的执行
```

## 二、事务样例

``` python
import pymysql 
#建立连接
db = pymysql.connect(...) 
#拿到游标
cursor = db.cursor() 
# sql语句
sql = 'insert into userinfo(username,pwd) values (%s,%s)'

try:
	#rows变量得到数据库中被影响的数据行数。
	rows = cursor.execute(sql, (username, pwd))
	#如果没有commit()，库中字段已经向下移位但内容没有写进，可是自动生成的ID会自动增加。
	# 向数据库提交
	db.commit() 
except:
	# 发生错误时回滚
	db.rollback()

#关闭（游标、数据库）
cursor.close()
db.close()
```

## 三、执行sql的命令

``` python
#sql:sql语句，args:参数
# 显示sql语句是怎么写的
cursor.mogrify(sql,args) 
# select返回值是受影响行数
cursor.execute(sql,args) 
# 执行多条数据
cursor.executemany(sql,args) 
#
callproc(procname, args)
#用来执行存储过程,移动到下一个结果集
nextset(self)
```

## 四、查询命令

``` python
# 前置添加：执行execute/方法
# 返回一条结果，包含所有字段，通过元组截取
cursor.fetchone()
# 返回所有结果
cursor.fetchall()
# 返回多条数据,size是返回条数
cursor.fetchmany(size)
# 获取自增ID
cursor.lastrowid 
# 移动指针到某一行.如果mode='relative',则表示从当前所在行移动value条,如果mode='absolute',则表示从结果集的第一行移动value条
scroll(self, value, mode='relative'):
```

## 五、数据库连接池

原生连接方法推荐使用

## 六、关闭数据库连接

``` python
# 需要分别的关闭指针对象和连接对象.他们有名字相同的方法 
cursor.close()
conn.close()
```

## 注意

``` python
#使用sql语句,这里要接收的参数都用%s占位符.要注意的是,无论你要插入的数据是什么类型,占位符永远都要用%s
sql="insert into cdinfo values(%s,%s,%s,%s,%s)"

#param应该为tuple或者list
param=(title,singer,imgurl,url,alpha)

#执行,如果成功,n的值为1
n=cursor.execute(sql,param)

#如果需要批量的插入数据,就这样做 
sql="insert into cdinfo values(0,%s,%s,%s,%s,%s)"

#每个值的集合为一个tuple,整个参数集组成一个tuple,或者list
param=((title,singer,imgurl,url,alpha),(title2,singer2,imgurl2,url2,alpha2))

#使用executemany方法来批量的插入数据.这真是一个很酷的方法! 
n=cursor.executemany(sql,param)
```



