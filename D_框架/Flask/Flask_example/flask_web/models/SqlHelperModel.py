# --------------------------------------------------------------------
# sqlhelperModel
#
# 单例模式的SQLhelper
# 使用类实现的sqlhelper，利用了数据库连接池的方法、原生pymysql、栈、线程
# 利用栈和线程维护一个栈，这样就可以使用with语句实现不同的连接可关可开
#
# 其他文件直接引入对应的查询方法即可，例
#   index.py文件
#   from flask import current_app
#   db = current_app.DataBase
#   def index():
#       res = db.fetchone("select * from %s", "AAA")
#
# 使用with语句
#   index.py文件
#   from flask import current_app
#   db = current_app.DataBase
#   def index():
#       with db as curse:
#           curse.execute("XXXXXXXXXXXX")
# ----------------------------------------------------------------------
import pymysql
# 老版本1.30以前用法
# from DBUtils.PooledDB import PooledDB
from dbutils.pooled_db import PooledDB
import threading


class SqlHelper(object):
    def __init__(self, HOST, PORT, USER, PASSWORD, DATABASE):
        # 创建一个连接池
        self.POOL = PooledDB(
            creator=pymysql,
            maxconnections=None,
            blocking=True,
            ping=0,

            # 以下正常的数据库连接
            host=HOST,
            port=PORT,
            user=USER,
            password=PASSWORD,
            database=DATABASE,
            charset='utf8'
            # host='127.0.0.1',
            # port=3306,
            # user='root',
            # password='',
            # database='code_miaomu',
            # charset='utf8'
        )
        self.local = threading.local()

    def open(self):
        conn = self.POOL.connection()
        cursor = conn.cursor()
        return conn, cursor

    def close(self, cursor, conn):
        cursor.close()
        # 因为使用了连接池，这不是释放连接，而是放回连接池
        conn.close()

    # 定义一个查询样例
    # def fetchone(self, sql, *args):
    #     result = self.cursor.fetchone(sql, args)
    #     return result

    # with上下文所利用的类
    def __enter__(self):
        conn, cursor = self.open()
        # 获取rv中stack的值
        rv = getattr(self.local, 'stack', None)
        # 如果rv为空，向rv中添加初始化数据
        # 如果rv中有值，向rv中添加新创建的连接信息
        if not rv:
            self.local.stack = [(conn, cursor), ]
        else:
            self.local.stack = rv.append((conn, cursor))
        return cursor

    def __exit__(self, exc_type, exc_val, exc_tb):
        rv = getattr(self.local, 'stack', None)
        # rv为空就删除stack，因为已经什么都没了
        # 如果有，就弹出关闭连接
        if not rv:
            del self.local.stack

        else:
            conn, cursor = rv.pop()
            self.close(conn, cursor)
