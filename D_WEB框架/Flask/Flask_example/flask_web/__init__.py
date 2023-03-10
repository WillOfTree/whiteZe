from flask import Flask
# 导入视图蓝图
from flask_web.views.index import api
# 数据库连接, 导入连接model
# from flask_web.models.SqlHelperModel import SqlHelper


def create_app():
    app = Flask(__name__)
    # 从config目录下的settings.py文件导入
    app.config.from_object('configs.setting')

    # 数据库创建连接
    # app.DataBase = SqlHelper(app.config['DB_HOST'], app.config['DB_PORT'], app.config['DB_USER'], app.config['DB_PASSWORD'], app.config['DB_NAME'])

    # 注册蓝图到flask
    app.register_blueprint(api)

    return app
