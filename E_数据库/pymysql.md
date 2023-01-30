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

## 二、初级方法使用数据库

缺点：每次使用都要连接，断开数据库，浪费资源

``` python
from flask import Flask,pymysql
# 核心启动
app = Flask(__name__)

# 数据库函数
def fetch(sql):
    conn = pymysql.connect(
        host='127.0.0.1', #地址
        port=3306,        #端口
        user='root',      #用户名
        passwd='123',     #秘密
        db='t1'           #数据库名称
    )
    cursor = conn.cursor()
    cursor.execute(sql)
    result = cursor.fetchall()
    cursor.close()
    conn.close()
    return result

# 视图
@app.route('/index')
def index():
    res = fetchall('select * from A')
    return "hallo word"

if __name__ == "__main__":
    app.run()
```

## 三、事务样例

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

## 四、执行sql的命令

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

## 五、查询命令

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

## 六、数据库连接池

原生连接方法推荐使用

### 1、安装

``` shell
pip3 install dbutils
pip3 install pymysql
```

### 2、使用-普通

为每个线程创建一个连接，线程即使调用了close方法，也不会关闭，只是把连接重新放到连接池，供自己线程再次使用。当线程终止时，连接自动关闭。

PersistentDB参数：

- creator：使用链接数据库的模块，一般填写pymysql

- maxconnections：连接池最多的链接数，None、0表示无限制

- mincached：链接池最小的链接数，启动时创建，并等待使用

- blocking：链接池如果没有足够的链接，再来请求连接是阻塞还是报错

  1. True：阻塞
  2. False：报错

- setsession：开始会话前执行的命令列表。如：["set datestyle to ...", "set time zone ..."]

- ping：ping MySQL服务端，检查是否服务可用。例：ping=0

  0 ： 不会ping

  1： 发送请求的时候ping一下（默认选项）

  2： 创建cursor时ping一下

  4： 执行时（execute）ping一下

  7： always

- closeable：

  False：conn.close() 实际上被忽略，供下次使用，再线程关闭时，才会自动关闭链接。

  True：conn.close()则关闭链接，那么再次调用pool.connection时就会报错，因为已经真的关闭了连接（pool.steady_connection()可以获取一个新的链接）

- threadlocal：本线程独享值得对象，用于保存链接对象，如果链接对象被重置

``` python
import pymysql
from DBUtils.PooledDB import PooledDB

# 创建一个连接池
POOL = PersistentDB(
    creator=pymysql, 
    maxconnections=None,
    blocking=True,
    ping=0,
 
    # 以下正常的数据库连接
    host='127.0.0.1',
    port=3306,
    user='root',
    password='123',
    database='pooldb',
    charset='utf8'
)


# 获取一个连接
conn = POOL.connection(shareable=False)
# 创建游标，以下正常
cursor = conn.cursor()
cursor.execute('select * from tb1')
result = cursor.fetchall()
cursor.close()
# 因为使用了连接池，这不是释放连接，而是放回连接池
conn.close()
```

### 3、使用-多线程

``` python
import time
import pymysql
import threading
from DBUtils.PooledDB import PooledDB, SharedDBConnection
POOL = PooledDB(
    creator=pymysql,  # 使用链接数据库的模块
    maxconnections=6,  # 连接池允许的最大连接数，0和None表示不限制连接数
    mincached=2,  # 初始化时，链接池中至少创建的空闲的链接，0表示不创建
    maxcached=5,  # 链接池中最多闲置的链接，0和None不限制
    maxshared=3,  # 链接池中最多共享的链接数量，0和None表示全部共享。PS: 无用，因为pymysql和MySQLdb等模块的 threadsafety都为1，所有值无论设置为多少，_maxcached永远为0，所以永远是所有链接都共享。
    blocking=True,  # 连接池中如果没有可用连接后，是否阻塞等待。True，等待；False，不等待然后报错
    maxusage=None,  # 一个链接最多被重复使用的次数，None表示无限制
    setsession=[],  # 开始会话前执行的命令列表。如：["set datestyle to ...", "set time zone ..."]
    ping=0,
    # ping MySQL服务端，检查是否服务可用。# 如：0 = None = never, 1 = default = whenever it is requested, 2 = when a cursor is created, 4 = when a query is executed, 7 = always
    host='127.0.0.1',
    port=3306,
    user='root',
    password='123',
    database='pooldb',
    charset='utf8'
)


def func():
    # 检测当前正在运行连接数的是否小于最大链接数，如果不小于则：等待或报raise TooManyConnections异常
    # 否则
    # 则优先去初始化时创建的链接中获取链接 SteadyDBConnection。
    # 然后将SteadyDBConnection对象封装到PooledDedicatedDBConnection中并返回。
    # 如果最开始创建的链接没有链接，则去创建一个SteadyDBConnection对象，再封装到PooledDedicatedDBConnection中并返回。
    # 一旦关闭链接后，连接就返回到连接池让后续线程继续使用。
    conn = POOL.connection()

    # print(th, '链接被拿走了', conn1._con)
    # print(th, '池子里目前有', pool._idle_cache, '\r\n')

    cursor = conn.cursor()
    cursor.execute('select * from tb1')
    result = cursor.fetchall()
    conn.close()


func()
```

## 七、关闭数据库连接

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



