# --------------------------------------------------------------------
# sqlhelperModel
#
# 非单例模式的sqlHelper，每次使用必须自己实例化对象
# 使用类实现的sqlhelper，利用了数据库连接池的方法、原生pymysql
# 利用栈和线程维护一个栈，这样就可以使用with语句实现不同的连接可关可开
#
# 必须自己创建对象，例
#   index.py文件
#   from SqlHelperEasyModel import SqlHelper
#   def index():
#       db = SqlHelper()
#       with db as cursor:
#           cursor.execute('xxxxxxxxxxxx')
#
#       with SqlHelper() as cursor:
#           cursor.execute('xxxxxxxxxxxx')
# ----------------------------------------------------------------------
import pymysql
# 老版本1.30以前用法
# from DBUtils.PooledDB import PooledDB
from dbutils.pooled_db import PooledDB


# 共用方法，连接池唯一
POOL = PooledDB(
    creator=pymysql,
    maxconnections=None,
    blocking=True,
    ping=0,

    # host=create_app.config['host'],
    # port=create_app.config['port'],
    # user=create_app.config['user'],
    # password=create_app.config['password'],
    # database=create_app.config['database'],
    # charset='utf8'
    # 以下正常的数据库连接
    host='127.0.0.1',
    port=3306,
    user='root',
    password='123',
    database='pooldb',
    charset='utf8'
)


class SqlHelper(object):
    def __init__(self):
        # 每一个conn，cursor对每一类来说是唯一的
        self.conn = None
        self.cursor = None

    def open(self):
        """
        conn, cursor数据通过 __enter__方法保存到self
        """
        conn = POOL.connection()
        cursor = conn.cursor()
        return conn, cursor

    def close(self):
        self.cursor.close()
        # 因为使用了连接池，这不是释放连接，而是放回连接池
        self.conn.close()

    # 定义一个查询样例
    def fetchone(self, sql, *args):
        # 注意这里，主要修改位置,sql语句一定要在单引号中
        self.cursor.execute(sql, args)
        result = self.cursor.fetchone()
        return result

    # with上下文所利用的类
    def __enter__(self):
        """
        返回的cursor用于with调用
        """
        self.conn, self.cursor = self.open()
        return self.cursor

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()
