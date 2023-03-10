# Flask

## 简单应用

### 一、Hallo word

``` python
from flask import Flask

# 核心启动
app = Flask(__name__)

# 视图
@app.route('/index')
def index():
    return "hallo word"

if __name__ == "__main__":
    app.run()
```

### 二、视图常用return函数

#### 1、模版

``` python
from flask import render_template, jsonify

# 视图函数-返回模版
# 1\模版默认位置为当前目录的templates文件夹
# 2\模版的目录名可以修改
#   app=Flask(__name__, templates="")
@app.route("/index")
def index():
    return render_template('index.html')

# 视图函数-返回模版参数
# 1\直接在render_template后面添加要返回的变量与值
# 2\index.html中要使用 {{}}
#   <h1>{{error}}</h1>
@app.route("/index")
def index():
    return render_template('index.html', error=123, OK=33)
```

#### 2、返回json

``` python
from flask import jsonify

# 视图函数-返回jsonResponse
@app.route("/index")
def index():
    return jsonify({"code":"200", "data":[1,2,3]})

```

### 三、GET、POST请求

``` python
# 视图函数-响应GET，默认响应GET
@app.route("/index", methods=['GET'])
def index():
    return render_template('index.html')

# 视图函数-响应POST
# 若只响应POST，去掉GET即可
@app.route("/index", methods=['GET', 'POST'])
def index():
    return render_template('index.html')

```

### 四、request类

request 请求包含所用HTTP请求的参数

- request.method：请求方法

#### GET请求

参数通过URL传输

1、request.args.get("名称")

- 获取url的传递（get方式）的参数，例: "http://abc.cn?name=22"

2、request.args.to_dict()：

- 转变成可变字典（get方式）

#### POST请求

参数通过body体传输

request.get_json

- 获取Content-Type类型为：**application/json**的数据
- 不需要json.loads()来序列化

request.json.get("名称", None)

- 获取Content-Type类型为：**application/json**的数据
- 不需要json.loads来序列化

request.form

- 获取Content-Type类型为：**multipart/form-data**的数据

- get()方法

  request.form.get("名称", None)；获取指定元素，没有返回None

request.data：接收POST数据，且没有get方法

request.values：

- 获取Content-Type类型为：**application/x-www-form-urlencoded**

- get()方法

  request.values.get("名称", None)

#### 使用样例

``` python
from flask import request

# 视图函数
@app.route("/index")
def index():
    # 判断请求方法
    if request.method == 'POST'：
        user = request.from.get("name")

    return render_template('index.html')
```

### 五、重定向

``` python
from flask import redirect

# 视图函数
# redirect函数后应填写url路径名称
@app.route("/index")
def index():
    return redirect('/index')

# 视图函数-使用url_for
# 
@app.route("/index")
def index():
    return redirect(url_for('index'))
```

### 六、session

1、必须先设置secret_key

- flask的session是存放在用户游览器中的，只要不删除就一直存在
- 首先flask会使用secret_key将用户信息加密，然后返回用户游览器的cooke中，之后用户

``` python
from flask import Flask
app = Flask(__name__)
app.secret_key = "自定义字符串"
```

2、使用session

``` python
from flask import session

# 视图函数
@app.route("/index/<name>")
def index(name):
    # session 数据保存
    session['name'] = name
    # 读取，防止session不存在报错
    name = session.get('name')
    name = session['name']
    # 删除session
    del session['name']
    return redirect('/index')
```

### 七、是否严格URL访问地址

``` python
# 视图函数
# 访问url
# www.xx.com/index/ 
# 与
# www.xx.com/index 都可
@app.route("/index", striet_slashes=False)
def index():
    return 'index'
```

### 八、解析json字符串

``` python
import json

# 将对象转换为json对象
data = {'name': 'lilei', 'age': 30}
json.dumps(data)

# 将字符串转换为json对象
json_str= '{"userId": "1", "id": "1"}'
obj = json.loads(json_str))
```

## 模板

### 一、配置

1、templates_dir：默认模版位置参数，默认访问启动文件下的templates目录

``` python
Flask_app= Flask(__name__, templates_dir=None)
```

2、templates_url_path：模版目录参数，默认为当前目录

``` python
Flask_app= Flask(__name__, templates_url_path=””)
```

### 二、模板语法

#### 1、传变量

python文件中设置

``` python
# 视图函数-返回模版参数
# 1\直接在render_template后面添加要返回的变量与值
# 2\index.html中要使用 {{}}
#   <h1>{{error}}</h1>
@app.route("/index")
def index():
    return render_template('index.html', error=123, OK=33)
```

html文件中设置

``` html
<img src=”{{error}}” />
```

#### 2、注释方法

`{# 注释 #}`

#### 3、判断

``` html
{% if name==1 %} 
<html> </html>
{%else%} 
<html> </html>
{% endif %}
```

#### 4、数组遍历

python中设置

``` python
# 视图函数-返回模版参数
data = [1,2,3,4,5]
@app.route("/index")
def index():
    return render_template('index.html', MYDATA=data)
```

html中设置

``` html
/-- 普通循环 --/
{% for item in MYDATA %}
    <span> {{item}} <\span>
{% endfor %}

/-- 循环变量为空的循环 --/
{% for item in MYDATA %}
    <span>{{item}}</span>
{% else %} 
    /-- 为空执行 --/
    <span>没有数据</span> 
{% endfor %}
```

#### 5、遍历字典

python中设置

``` python
# 视图函数-返回模版参数
data = {
    '1':{'name':'A'},
    '2':{'name':'B'}
}
@app.route("/index")
def index():
    return render_template('index.html', MYDATA=data)
```

html中设置

``` html
/-- 普通循环 --/
{% for key, item in MYDATA.items() %}
{% endfor %}

/-- MYDATA为空的循环 --/
{% for key, item in MYDATA.items() %}
    <span>{{key}}</span>
    <span>{{item.name}}</span>
    <span>{{item['name']}}</span>
    <span>{{item.get('name','200')}}</span>
{% else %} 
    <span>没有数据</span> 
{% endfor %}
```

#### 6、模板继承

index.py

- 视图正常调用模板

``` python
from flask import render_template
@app.route("/index")
def index():
    return render_template('index.html')
```

index.html

- view视图调用的模板

``` html
{% extends ‘layout.html’ %}
{% block head %} 
<div>填充到layout的head中</div>
{% endblock %}
```

layout.html:

- 模板会将index的内容放到block模块中
- head是模块的名称，可修改稿

``` html
<html>
    {% block head %}{% endblock %}  
</html>
```

#### 7、模板引入

index.html

``` html
<html>
	{% include 'other.html' %}
</html>
```

other.html

``` html
<body>
    <div>aaa</div>
</body>
```

#### 8、模板函数

在蓝图中定义，只能用于当前蓝图，在启动文件中定义可适用于全局

方法1：直接传函数

``` python
# 视图文件
def func(arg):
    return "haigou" + arg
# 普通的视图函数
@app.route("/index")
def index():
    return render_template('index.html', f=func)
```

方法2：装饰器，模板函数

``` python
# 视图
# 定义全局的模板函数
@app.template_global()
def func(arg):
    return "haigou" + arg

# 全局模板函数，调用方法与global不同
@app.template_filter()
def x1(arg):
    return "xxxx" + arg
```

index.html模板

``` html
<html>
    <div>render_template通过参数传递：{{func()}}</div>
    <div>template_global的调用方法：{{func('xxx')}}</div>
    <div>template_filter的调用方法：{{"xxx"|x1()}}</div>
</html>
```

#### 9、模板过滤器

index.py

``` python

```

index.html

``` html
<html>
    <div>不存在的数显示默认值:{{data.name | default(“默认”) }}
    </div>
	<div>
    支持检查不存在的数据:{{data.name | default(“”, true)}} 
    </div>
    <div>
        {{ data | length() }}
    </div>
</html>
```

## 蓝图

### 一、目录结构

``` shell
project
	|-- manage.py
	|-- pro_excel
		|-- __init__.py
		|-- views
			|-- index.py
		|-- templates
			|-- index.html 
		|-- statics
```

### 二、基础使用方法

#### 1、manage.py

- 整个项目的启动文件

``` python
from pro_excel import create_app

app = create_app()
if __name__ == "__main__":
    app.run()
```

#### 2、\__init__.py

``` python
from flask import Flask
# 导入视图蓝图
from pro_excel.view.index from api

def create_app():
    app = Flask(__name__)
    app.secret_key = "dfdfaeddfgijii"
    
    # 注册蓝图到flask
    app.register_blueprint(api)
    
    return app
```

#### 3、views/index.py

``` python
from flask import Blueprint

# 创建一个蓝图
# xm是蓝图的自定义名称
api = Blueprint("api", __name__)

@api.route("/index")
def func():
    return "f1"
```

### 二、蓝图前缀/路由分发

``` python
from flask import Flask
# 导入视图中的蓝图模块
from .view.index import api
app = Flask(__name__)

# 访问的路径由
# https://127.0.0.1/index 
# 变成 
# https://127.0.0.1/admin/index
app.register_blueprint(api, url_prefix='/admin')
```

### 三、路由参数

``` python
# 获取路由中page,a的值
# 默认路由值是字符串
@app.route(“/api/<page>/<a>”, methods=[“GET”])
def api(page, a):
    pass  

# 转换路由中的值到指定类型
# 接受int类型的page，str类型的a
@app.route("/api/<int:page>/<string:a>")
def api(page, a):
    pass
```

### 四、中间件+模板函数

``` python
from flask import Blueprint
api = Blueprint("api", __name__)

# 当前中间件只作用于api蓝图
# 注意起始是api不是app
@api.before_request
def f1():
    pass

# 当前模板函数只作用于api蓝图
# 与template_global效果一样
@api.app_template_global()
def f10():
    pass
```

### 五、另一种蓝图系统

#### 1、目录结构

``` shell
bigblue
	|-- manage.py
	|-- config
	+-- bigblue
		|-- __init__.py
		+-- blue_one
			|-- __init__.py
			+-- view
				|-- index.py
			+-- templates
			+-- statics
		+-- blue_two
```

#### 2、使用方法

- 每个蓝图（bigblue）下面的文件都是包，所以blue_one，blue_two都含有__init\_\_.py
- 每个蓝图的都创建对应的包中的\_\_init__.py中
- bigblue下的\_\_init__.py负责集合所有蓝图模块
- 模板、静态文件默认位置是根目录（manage.py所在的目录），设置模板、静态文件参数后会先找根目录，再找对应的蓝图文件下的文件

bigblue\blue_one\\\_\_init__.py

``` python
from flask import Blueprint
# 模板和静态文件参数很重要
ac = Blueprint("ac", __name__)

# 引入当前包的文件index.py文件
from .view import index
```

bigblue\\__init\_\_.py

``` python
from flask import Flask
def create_app():
    app = Flask(__name__)
    app.config.from_object("config.settings")
    # 引入蓝图
    from .blue_one import ac
    # 注册
    app.register_blueprint(ac)
```

manage.py

- 运行程序，入口

``` python
from bigblue import create_app
app = create_app()

if name == "__name__":
    app.run
```

视图文件

bigblue\blue_one\index.py

``` python
# from .是当前目录，只能找到index.py文件
from .. import ac

@ac.route("/index")
def index():
    return "index"
```



## 路由系统

#### 一、路由加载流程

- 将url和函数打包成rule对象
- 将rule对象添加到map对象中
- app.url_map = map对象

#### 二、路由的2种写法

``` python
def index():
    # flask底层调用
    app.add_url_rule('/index', 'index', index)
    
@app.route('/login')
def login():
    return '1'
```

## 配置文件

#### 一、基于全局变量

\_\_init_\_.py

``` python
from flask import Flask
app = Flask(__name__) 

# 添加配置文件，从当前目录中读取settings.py
app.config.from_object('settings')
# 从config目录下的settings.py文件导入
app.config.from_object('config.settings')
# 打印
app.config['DB_HOST']
```

config.py

``` python
# 配置样例
xx='123'
DB_HOST='127.0.0.1'
# 当服务其与本地不同时，
# 项目上传到服务器上，只需要删除localsettings文件
# 导入localsettings的参数
try: 
    from .localsettings import *
except ImportError:
    pass
```

#### 二、基于类的方式

不能通过删除文件实现开发服务器、线上服务器，必须手动修改

_\_init\_\_.py

``` python
from flask import Flask
app = Flask(__name__) 

# 从config目录下的settings.py文件导入
app.config.from_object('config.settings.DevSEttings')
# 打印
app.config['DB_HOST']
```

config.py

``` python
class Base(object):
    HOST = '1.1.1.1'

class DevSettings(Base):
    HOST = '1.1.1.1'
    
class LocalSettings(Base):
    HOST = '1.1.1.1'
```

## 装饰器

#### 一、自定义装饰器

- 装饰器可以简单的理解为添加额外功能，运行流程为：@auth、def index()、@app.route
- flask中装饰器一定要在路由装饰器下面
- 由于装饰器的替换效果，多个函数使用同一个装饰器会有函数名重复的错误

``` python
# 装饰器
def auth(func):
    def inner(*arg, **kwargs):
        # 装饰器要运行的代码
        if not user:
            pass
        # end
        return func(*args, **kwargs)
    return inner

# index函数将会替换装饰器中的inner函数
@app.route("/index")
@auth
def index():
    pass
```

#### 二、装饰器名称修改

``` python
import functools

# 装饰器
# @functools.wraps(func)会将当前运行的函数名换成func变量的名称
def auth(func):
    @functools.wraps(func)
    def inner(*arg, **kwargs):
        # 这里添加装饰器要运行的函数
        # end
        return func(*args, **kwargs)
    return inner

# index函数将会替换装饰器中的inner函数
# auth的函数名为index
@app.route("/index")
@auth
def index():
    pass

# index函数将会替换装饰器中的inner函数
# auth的函数名为edit
@app.route("/edit")
@auth
def edit():
    pass
```

#### 三、中间件

before_request：先执行

after_request：最后执行

``` python
from flask import Flask
app = Flask(__name__)

# 不能有返回值，如果有返回值，就会直接停止
@app.before_request
def f1():
    pass

# 必须有参数和返回值
@app.after_request
def f10(response):
    return response

# 运行流程 
# 	f1-> index() ->f10
@app.route("/index")
def index():
    print("index")
```

其他写法

``` python
from flask import Flask
app = Flask(__name__)
def f1():
    pass
def f10(response):
    return response
@app.route("/index")
def index():
    print("index")
    
app.before_request(f1)
app.after_request(f10)
```

## 请求上下文

### 一、原理

current_app 使用了设计模式中的代理模式
request 
session

### 二、LocalProxy对象

session、request、current_app、g都是LocalProxy对象

- current_app：就是Flask（_\_name__）生成的对象
- session：生命周期一直存在
- g变量：在一次请求周期中保存任意数据

### 三、current_app

``` python
from flask import current_app
@app.route("/index")
def index():
    # app在非create_app函数外引用会出错
    # 需要使用current_app代替
```



### 四、g使用方法

``` python
from flask import Flask, g
app = Flask(__name__)

@app.before_request
def f1():
    # g从请求开始就存在
    g.x1 = 123
    
@app.route("/index")
def index():
    print(g.x1)
    return "hello"
```

## 数据库

详见数据库 - pymysql.md

## 信号

flask框架中预留的钩子，可以自定义操作

一、安装

``` python
pip install blinker
```

### 二、flash闪存

flask基于session，特点是只能用1次，存读结束

``` python
from flask import Flask, render-template
# 导入flash
from flask import flash, get_flash_messages

app = Flask(__name__)
# 设置secret_key
app.secret_key = "111111111111"

@app.before_request
def f1():
    # 保存数据
    flash(123)
    
@app.route("/index")
def index():
    # 获取数据
    messages = get_flashed_messages()
    return "hello"

if __name__ == '__main__':
    app.run()
```

### 三、可扩展的地点

#### 1、中间件扩展

意义不大，因为没有session，g，request等变量，尚未进入flask请求

``` python
from flask import Flask, render-template
app = Flask(__name__)
    
@app.route("/index")
def index():
    return "hello"

class MyMiddleware(object):
    def __init__(self, old_app):
        self.wsgi_app = old_app.wsgi_app
        
    def __call__(self, *args, **kwargs):
        # 添加自定义语句
        print("自定义位置")
        result = self.wsgi_app(*args, **kwargs)
        print("自定义位置")
        return result
    
app.wsgi_app = MyMiddleware(app)
if __name__ == '__main__':
    app.run()
```

#### 2、appcontext_pushed信号

当app_ctx被push到local中栈之后，会触发appcontext_pushed信号，之前注册到这个信号的方法会被触发

``` python
from flask import Flask, render-template
# 引入信号
from flask import signals

app = Flask(__name__)

# 注册到信号中的代码会被执行
@signals.appcontext_pushed.connext
def f1(arg):
    pass


if __name__ == '__main__':
    app.run()
```

#### 3、before_first_request信号

``` python
from flask import Flask
app = Flask(__name__)

# 注册到信号中的代码会被执行
@app.before_first_request
def f1():
    pass

@app.route("/index")
def index():
    return "aaa"

if __name__ == '__main__':
    app.run()
```

#### 4、request_started信号

``` python
from flask import Flask, render-template
# 引入信号
from flask import signals

app = Flask(__name__)

# 注册到信号中的代码会被执行
# 这里的arg就是app对象
@signals.request_started.connext
def f1(arg):
    pass

if __name__ == '__main__':
    app.run()
```

#### 5、url_value_preprocessor

``` python
from flask import Flask, render-template
app = Flask(__name__)

# 注册到信号中的代码会被执行
# 这个信号在视图前，befor_request之前调用
# endpoint路由，args是url参数
@app.url_value_preprocessor
def f1(endpoint, args):
    pass

@app.route("/index")
def index():
    return "aaa"
if __name__ == '__main__':
    app.run()
```

#### 6、before_request

#### 7、before_render_template

模板（render_template）渲染之前

``` python
from flask import Flask, render-template
# 引入信号
from flask import signals
app = Flask(__name__)

# 注册到信号中的代码会被执行
@signals.before_render_template.connect
def f1(app, template, context):
    pass

@app.route("/index")
def index():
    return "aaa"
if __name__ == '__main__':
    app.run()
```

#### 8、template_rendered

模板（render_template）渲染之后

``` python
from flask import Flask, render-template
# 引入信号
from flask import signals
app = Flask(__name__)

# 注册到信号中的代码会被执行
@signals.template_rendered.connect
def f1(app, template, context):
    pass

@app.route("/index")
def index():
    return "aaa"
if __name__ == '__main__':
    app.run()
```

#### 9、after_request

#### 10、request_finished信号

``` python
from flask import Flask, render-template
# 引入信号
from flask import signals
app = Flask(__name__)

# 注册到信号中的代码会被执行
@signals.request_finished.connect
def f1(app, request):
    pass

@app.route("/index")
def index():
    return "aaa"
if __name__ == '__main__':
    app.run()
```

#### 11、got_request_exception

请求异常的信号，并不是视图函数出问题，而是flask框架运行时出问题

``` python
from flask import Flask, render-template
# 引入信号
from flask import signals
app = Flask(__name__)

# 注册到信号中的代码会被执行
@signals.got_request_exception.connect
def f1():
    pass

@app.route("/index")
def index():
    return "aaa"
if __name__ == '__main__':
    app.run()
```

#### 12、teardown_request

请求结束时，不论请求成功还是失败，都会运行到

``` python
from flask import Flask, render-template
from flask import signals
app = Flask(__name__)

# 注册到信号中的代码会被执行
@app.teardown_request
def f1(exc):
    pass

# 额外的一个信号
@signals.request_tearing_down
def f1(app, exc):
    pass

@app.route("/index")
def index():
    return "aaa"
if __name__ == '__main__':
    app.run()
```

#### 13、appcontext_popped

``` python
from flask import Flask, render-template
from flask import signals
app = Flask(__name__)

# 注册到信号中的代码会被执行
# 这个信号在最后
@signals.appcontext_popped.connect
def f1(exc):
    pass

@app.route("/index")
def index():
    return "aaa"
if __name__ == '__main__':
    app.run()
```

## 静态文件

### 一、配置

static_folder参数：

- 静态文件目录

static_url_path参数：

  - 设置url访问路径（当设置这个，static_dir将失去效果）

  - 默认值是：'/static'

  - 例：static_url_path=“/ss/cc” ，

    访问url由：

    http://localhost/static

    变为

    http://localhost/ss/cc

    访问的物理位置为是static_folder中设置的文件目录

static_dir参数：

- 如果不配置static_dir参数，则默认访问启动文件下的static目录

- static_dir默认位置是以Flask视图所在的目录，配置static_dir后url路径也会变成文件名

  例如:

  static_dir=”view/aaa”,

  这里访问路径将变成

  http://localhost/aaa/image.jpg


``` python
from flask import Flask

app = Flask(
	__name__,
    # 静态文件目录名称
    static_folder='static',
)

Flask_app= Flask(__name__, static_dir=None)
```

### 二、HTML中样例

``` html
<!--一般写法-->
<img src="/staic/mm.jpg" />

<!--优点：当static_url_path的参数发生变化，url_for会自动修改-->
<img src="{{url_for('static', filename='mm.jpg')}}"
```

### 三、蓝图中配置静态文件

``` python
from flask import Blueprint

# 配置蓝图级别静态文件
api = Blueprint('web', __name__, static_folder="", static_url_path="")

@api.route("/index")
def func():
    return "f1"
```

## 上传文件

#### 一、前端

#### 二、后端

``` python
image = []
for file in files:
	if file and allowed_file(file.name):
		fileTime = str(int(time.time() * 1000))
		filename - fileTime + os.path.splitext(file.filename)[1]
		file.save(os.path.join(UPLOAD_Folder, filename))
		imagesName.append(filename)
```

#### 三、错误信息

1、路由错误：最后写着got an unexpected keyword argument ‘method’ 路由配置允许访问的方法参数错误

限制用户访问静态文件
@api.route()
def download(“/download”):
判断用户信息
send_static_file() // FLask处理静态文件的方法

## WSGI

### 一、原理

``` python
from werkzeug.serving import run_simple

def func(environ, start_response):
    print("请求来了")
    
if __name__ == "__main__":
    run_simple('127.0.0.1', 5000, func)
```

### 二、threadlocal实现

## flask-script

flask组件，用于运行flask程序

### 一、安装

``` python
pip install flask-script
```

### 二、使用

app.py

``` python
from flask import Flask
from flask_script import Manager

manager = Manager(app)

if __name__ == "__main__":
    manager.run()
```

shell命令

``` shell
python app.py runserver -H 127.0.0.1 -p 8000
```

### 三、自定义命令

``` python
from flask import Flask
from flask_script import Manager

manager = Manager(app)
# 自定义任务
# 命令：python manage.py custom 123
# custom是自定义任务的函数名
# 123是参数，会传递到arg中
@manager.command
def custom(arg):
    pass

# 另外的方式
@manager.option('-n', '-name', dest='name')
@manager.option('-u', '-user', dest='user')
def cmd(name, user):
    pass

if __name__ == "__main__":
    manager.run()
```

