# --------------------------------------------------------------------
# sqlhelper
# 数据库操作的相关方法集合，利用了数据库连接池的方法、原生pymysql
# 其他文件直接引入对应的查询方法即可，例
#   index.py文件
#   from sqlhepler import fetchone
#   def index():
#       res = fetchone("select * from %s", "AAA")
#----------------------------------------------------------------------
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

# 定义一个查询样例
def detchone(sql, *args):
    conn = POOL.connection()
    cursor = conn.cursor()
    # 注意这里，主要修改位置,sql语句一定要在单引号中
    cursor.execute(sql, args)
    result = cursor.fetchall()
    cursor.close()
    # 因为使用了连接池，这不是释放连接，而是放回连接池
    conn.close()
    return result