from flask import Flask
# 导入视图蓝图
from flask_web.views.index import api


def create_app():
    app = Flask(__name__)
    app.secret_key = 'fasjksdfjiejiosjkldfjklk'

    # 从config目录下的settings.py文件导入
    app.config.from_object('configs.setting')

    # 注册蓝图到flask
    app.register_blueprint(api)

    return app
