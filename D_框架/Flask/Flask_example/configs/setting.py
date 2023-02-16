# 本地配置
# ------
DEBUG = False
SECRET_KEY = 'fasjk11111111111111'


# 数据库连接配置
# ------------
# 端口
# DB_PORT = 8080
# 主机
# DB_HOST = '127.0.0.1'

# 当服务其与本地不同时，
# 项目上传到服务器上，只需要删除localsettings文件
# 导入localsettings的配置，
try:
    from configs.localsetting import *
except ImportError:
    pass