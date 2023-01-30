# --------------------------------------------------------------------
# sqlhelperModel
# 使用类实现的sqlhelper，利用了数据库连接池的方法、原生pymysql
# 其他文件直接引入对应的查询方法即可，例
#   index.py文件
#   from sqlheplerModel import db
#   def index():
#       res = db.fetchone("select * from %s", "AAA")
#----------------------------------------------------------------------
import pymysql
from DBUtils.PooledDB import PooledDB

class DqlHelper(object):
    def __init__(self):
        # 创建一个连接池
        self.POOL = PersistentDB(
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

    def open(self):
        conn = self.POOL.connection()
        cursor = conn.cursor()
        return conn, cursor

    def close(self, cursor, conn)
        cursor.close()
        # 因为使用了连接池，这不是释放连接，而是放回连接池
        conn.close()

    # 定义一个查询样例
    def detchone(self, sql, *args):
        conn, cursor = self.open()
        # 注意这里，主要修改位置,sql语句一定要在单引号中
        cursor.execute(sql, args)
        result = cursor.fetchall()
        self.close(conn, cursor)
        return result

db = SqlHelper()