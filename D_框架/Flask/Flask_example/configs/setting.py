# 本地配置
#
debug = False
# 端口
# port = 8080
# 主机
# host = '127.0.0.1'

# 数据库连接配置


# 当服务其与本地不同时，
# 项目上传到服务器上，只需要删除localsettings文件
# 导入localsettings的配置，
try:
    from localsetting import *
except ImportError:
    pass