from flask import Blueprint

# 创建一个蓝图
# xm是蓝图的自定义名称
api = Blueprint("api", __name__)


@api.route("/index")
def func():
    return "f1"
