from flask import Flask
# 导入视图蓝图
from pro.views.index import api


def create_app():
    app = Flask(__name__)
    app.secret_key = "dfdfaeddfgijii"

    # 注册蓝图到flask
    app.register_blueprint(api)

    return app
