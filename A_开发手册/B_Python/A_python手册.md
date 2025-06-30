# Python手册

## 基本语法

### 一、概念

1. python有指针的概念，如果多次初始化一个类，python会指向那个变量，并不会再创建一个相同的对象，使用id()方法即可验证

2. python中一切皆对象，严格意义我们不能说值传递还是引用传递，我们应该说传不可变对象和传可变对象。

3. 可更改(mutable)与不可更改(immutable)对象

   `strings, tuples` 和` numbers `是不可更改的对象

   `list,dict` 等则是可以修改的对象。

4. 不可变类型：

   ``` python
   a=5
   a=10 # 这里实际是新生成一个 int 值对象 10，再让 a 指向它，而 5 被丢弃，不是改变a的值，相当于新生成了a。
   ```

5. 可变类型：

   ``` python
   la=[1,2,3,4] 
   la[2]=5 # la 的第三个元素值更改，本身la没有动，只是其内部的一部分值被修改了。
   ```

6. python 函数的参数传递：

   不可变类型：类似 c++ 的值传递，如 整数、字符串、元组。如fun（a），传递的只是a的值，没有影响a对象本身。比如在 fun（a）内部修改 a 的值，只是修改另一个复制的对象，不会影响 a 本身。

   可变类型：类似 c++ 的引用传递，如 列表，字典。如 fun（la），则是将 la 真正的传过去，修改后fun外部的la也会受影响

7. python不能充分利用多核CPU优势

8. python引用只引用一次（import) 

### 二、输入输出方法

输出：print

``` python
# 连续打印10个x，用于一些需要重复打印的地方
print("x"*10)
# 格式化输出
print("name=%s,age=$d" % (name,age))
print("数字{}".format(a))
# 打印不换行
Print( “****”,end="")；
# 打印换行
Print("")
# 字符串连接新方式
print("===%s==="%(a+b))

# A,b是变量，
# get()与[] :get不会报错
#.Startwith（）以多少开头
#.Endwith()以结尾
Input() # 允许获取输入
```

输入：input 、eval

``` python
# 输入的变量保存在变量a中
# 输入的都是字符串
a = input("请输入：")

# 去掉字符串的引号
# a=1.2，这里的a是浮点数
a = eval("1.2")

# eval经常与input一起使用
a = eval(input("提示文字"))
```

### 三、下标和切片

- 下标从0开始

``` python
Nam = "ABCDEFC。"

# 标点符号也是字符
# a = B
a = Nam[1] 

# 倒叙，下标是从1开始
# a = 。
a = Nam[-1] 

# 截取第2个到第5个
# a = CDEF
a = Nam[2:6]
# a = ABCDEF
a = Nam[:6]
```

### 四、变量

#### Ⅰ、元组

- 元组是不可变的，一旦创建就不能修改其中的元素。如果尝试修改元组中的元素，会引发TypeError异常
- 元组的创建速度比列表快，因为它们不需要动态分配内存

``` python
tup1 = ('physics', 'chemistry', 1997, 2000)
tup2 = (1, 2, 3, 4, 5, 6, 7 )
```

#### Ⅱ、列表

- **列表**是可变的，这意味着你可以修改、添加或删除其中的元素。

``` python
list1 = ['physics', 'chemistry', 1997, 2000]
list2 = [1, 2, 3, 4, 5 ]
list3 = ["a", "b", "c", "d"]
```

#### Ⅲ、字典

``` python
tinydict = {'a': 1, 'b': 2, 'b': '3'}
```

#### Ⅳ、全局变量

1. 函数外定义就是全局变量

2. 函数内使用global，代表要修改全局变量，在函数内不修改变量内容，可直接读取变量

   ``` python
   myval = "111111"
   def myfunction():
       global myvar
       myval = "xxxxxx" # 全局变量
   ```

### 五、不定长参数

``` python
# *args代表传递一个元组
function_name(1,2,3,4,5,6,7)
def function_name(one, two, *args):
    print(args); # (3,4,5,6,7)

# **key代表传递一个字典
function_name(1,2,"aa"=3, "bb"=4)
def function_name(one, two, **keys):
	print(keys) # {"aa"=3, "bb"=4}
```

### 六、拆包

``` python
# 创建进程，线程时使用
# 形参传递元组里的内容
# *args 传递的是一个元组
# **kwargs 传递的是一个字典
A=(1,2,3,4,5)
B=("a"=1,"b"=2)
function_name(*A,**B)

def function_name(*args, **kwargs)
	pass
```

### 七、匿名函数

### 八、集合（set）

1. `A&B`交集 A有B也有的
2. `A|B` 并集 所有不重复的
3. `A-B` 差集
4. `A^B` 对称差集只存在其中

``` python
A=[1,2,3,4,5,6,1,2,3]
B = set(A) #去重
A = list(B)#转换为列表

A="bcde"
B = Set(A) #将字符串转换为集合
```



### 枚举

``` python
class Padding(Enum):
	aa = 1 
	bb = 2
```

### 偏函数

重写函数的参数方法

``` python
import functools
def func(a1, a2):
    print(a1, a2)

# 重写了func函数为new_func，并且将a1赋值为123，
# 新函数不需要写2个参数
new_func = functools.partial(func, 123)
new_func(2)
```

## 面向对象

### 一、定义

1. 对象中的self指的是当前类本身，self名字可便

``` python
class Employee:
   	def function_name(self): # 公有方法
      	pass
   	def __private_method(self): # 私有方法，带有2个_
   		pass
    
Tom = Employee() # 创建类
Tom.function_name() # 调用类中的方法

# 带有参数的类
class Employee:
    def __init__(self, name)
    	pass
emp = Employee("zara")
```

### 二、魔术方法

1. `__new__`
2. `__str__`
3. `__main__`
4. `__add__`
5. `__dict__`
6. `__all__` 
7. `__name__`
8. `__doc__`
9. `__module__`

new

``` python
#__new__在init之前调用，类的实例化方法，并返回该实例
#__init__初始化时运行，实例的构造方法，接受类的实例(self)并对其进行构造
Class = one(one,two):
  def __init__(self,one,two) 
```

str

``` python
#str__对象的描述信息,打印对象调用
class Flask():
    def __str__(self):
        return “ssss”
```

main

add：重载+号方法

dict：序列化时调用

dict：类的序列化方法，只能序列化实列属性,无法序列化类属性

name：执行文件的名称

all：禁止调用all以外的函数，对类也有效

slots：限定类中只能有几个属性

slots__ = [“name”,”age”]

### 三、继承

1. **继承**会继承父类的`__init__`方法，继承就会执行父类的`__init__`
2. 如果父类定义了`__init__`，子类要使用`super().__init__()`方法，确保`__init__`方法执行，防止父类`__init__`方法中初始化一些变量

定义：

``` python
class Anmal(object): #新式类
    pass

class Dog(Anmal): #继承Anmal类
	def index(self):
    	pass
```

在子类调用父类方法

``` python
Anmal.drak(self)  #self不可少
Super().drak()  #super一个方法指向父类
```

### 六、实例属性、类属性

- 类属性不用实例化，就能调用
- 实例属性必须实例化
- 类外部修改类属性需要这样修改className.name=”123”
- 不然修改的是实例属性

类属性是共享的，例如

``` python
class AA();
a=1 # A=AA(); A.a的值都是1
a=datatime.new() #这个值永远是类创建的时候的时间
```

实例化属性是初始化后赋值的，属性值不同

类变量不会存在`__dict__`方法中；实例变量会在`__dict__`方法中

 修改：

self修改的只会是实例属性

**className.name=”123” #****修改类属性**

 调用：**

**类属性与实例属性同名时，先读取实例属性，没有则找类属性**

**<****实例属性优先级高，同时存在相同名称的类属性和实例属性，只读取实例属性

类属性：

Class Tool(object):

name=“one” 

实例属性：

Class Tool(object):

def __init__(self):

self.nameo = “one”

### 将方法变成属性

``` python 
class test:
	@property
	def intro(self):
    	pass
```

### 类方法

1. 类方法与静态方法主要区别在于参数
2. 类方法可以访问类的属性和方法，但不能访问实例的属性和方法。
3. 静态方法不能访问类的属性和方法，也不能访问实例的属性和方法。

``` python
Class Name(object):
  	Name = “ss”

  	@classmethod #类方法定义
  	def function_name(cls): #cls代表类
  		cls.name
        pass

	@staticmethod
	def function_static(): #这里不用填写self,cls
        pass

#静态方法
Name.function_static() #直接调用
one = Name()
one.function_static() # 通过类调用

#类方法调用,直接调用
Name.function_name() 
#类方法调用,通过实例化调用
One = Name()
One.function_name() //实例方法调用
```

### dict序列化字典

当dict()序列化一个类时，会触发如下方法

1. 先出发类中的keys方法，获取所有允许序列化的类
2. 触发`__getitem__`方法，根据keys()返回的值获取类中的类属性

``` python
class YY(object):
	name = “aaa” # 不会因为
	def keys(self):
		return (‘name’,’age’)  # dict只会序列化name,age字段

 	def __getitem__(self, item):
		return getattr(self, item) #当YY[‘name’]触发
```

### 单例模式

``` python
Class dog(object):
	__interface = none
	def __new__(cls):
		If cls.__interface == none:
			Cls.__interface = object.__new__(cls)
			return cls.__interface
		else:
			return cls.__interface
        

# 类方法创建**
@classmethod
def instance(cls, *args, **kwargs):
	if not hasattr(dog, “_instance”):
	dog._instance = dog()
	return dog._instance

#创建多次，但操作的都是一个对象
## 只初始化1次__init__
class dog(object):
	__first_init = True
	def __init__(self):
	if self.__first_init:
		SesActive.__first_init = False
```

### namedtuple快速定义类

``` python
from collections import namedtuple

my_class = nametuple(“className”, [‘count’, “age”])
my_class(11, 33) //对其赋值
```



## 异常处理

``` python
try:
	#.....
except 错误类型:
except 错误类型:
except (NameError, filenotfounderror):
except exception as xxx:
  	#捕获所有异常xxx原来的变量名
else：
	#没有异常打印
finally：
	#没有错打印
	#错误类型是特定的
```

## 模块导入

### 一、普通 Python 模块的导入规则

- python包导入只能导入**子目录**中的**模块**（必须定义为包），若一个目录被定义成包，则这个目录内的文件都应看成这个包的一部分，导入从包名开始

- 像django、flask、tornado等一些框架能**不同包**之间**随意**导入，是因为他的**入口文件**server.py（项目启动文件）在**目录顶层。**

- 搜索路径：

  1. 在当前模块所在路径中搜索导入模块
  2. 在环境变量 PYTHONPATH 指定的路径列表中搜索导入模块
  3. 在 sys.path 指定的路径列表中搜索导入模块

- 绝对导入

  绝对导入的格式为 import A.B 或 from A import B

- 相对导入：

  `.` 代表当前模块，`..` 代表上层模块，`...` 代表上上层模块，依次类推。

  相对导入格式为` from .A import B` 或 `from ..X import Y` 

### 二、同级目录导入

``` python
# 目录结构
|--server.py
|--Bao
	|--__init__.py
	|--Module_one.py

# server.py 文件导入包
from Bao import Module

# Module_one.py
from server import api
```

### 三、包内同级导入

``` python
# 目录结构
|--Bao
	|--__init__.py
	|--Module_one.py
	|--Module_two.py
    
# Module_one.py文件
# 在一个包中可以导入同一个包中的文件
import Module_two
# 导入Module_two所以函数
from Module_two impor *
# 从当前包（module_one所在的包）导入
from . import Module_two
```

### 四、包之间的导入

``` python
# 目录结构
|--Bao1
	|--__init__.py
	|--Module_one.py
|--Bao2
	|--__init__.py
	|--Module_two.py

# /Bao2/Modeule_one.py
from Bao2 import Module_two
from .Bao2 import Module_two
```

### 五、不可导入

```python
# 目录结构
|--Bao1
	|--__init__.py
	|--Module_two.py
|--Bao2
	|--__init__.py
	|--Module_one.py

# 注意：Module_one与Module_two不能互相导入
# 例：import Module_one 
# 解决方案1：添加同级目录
import sys 
sys.path.append("绝对路径")
# 解决方案2：修改成同级目录导入的目录结构
```

## 打包

1. 创建setup.py文件，复制代码
2. Setup.py文件中添加py_modules添加模块文件名
3. 运行命令`python3 setup.py build `生成build文件目录
4. 运行命令`python3 setup.py sdist` 打包文件

包的安装

1. 解压包
2. 进入解压目录，运行`python3 setup.py install` 

包内导入需要填写包名模块名详细阅读有道云笔记包内容

## 迭代器and生成器

1. 共有方法：`next() , send() , __next__() , __iter()__ `

### 一、列表生成式

``` python
A = [ X for x in range(10) ] #列表
A =(x for x in range(10)) #列表生成式
```

### 二、函数生成器(特殊的迭代器）

生成方式比较复杂，可以填写一个函数

但函数中出现yield就代表这个函数是一个生成器

``` python
def create():
  A,b = 0,1
  for I in range(50):
   	yield b #一开始要打印的数字，根据这个数进行累积
  A,b = a,a+b
```

当生成器不能再生成数据时，会产生一个异常stoplteration错误

``` python
# 使用for循环生成器可以避免这个错误

for bb in a:
	print(bb) #不使用next，直接打印
```

### 三、迭代器

可迭代对象（iterable）：可以直接作用于 for 循环的对象统称为可迭代对象

1. 一类是集合数据类型，如 list 、 tuple 、 dict 、 set 、 str 等；
2. 一类是 generator ，包括生成器和带 yield 的generator function。

迭代器：任何实现了`__iter__`和`__next__()`（python2中实现next()）方法的对象都是迭代器

1. `__iter__`返回迭代器自身
2. `__next__`返回容器中的下一个值

``` python
class Fib:
	def __init__(self):
 		self.prev = 0
		self.curr = 1

  	def __iter__(self):
		return self

 	def __next__(self):
		value = self.curr
		self.curr += self.prev
		self.prev = value
		return value
 
# 输出结果
#>>> f = Fib()
#>>> list(islice(f, 0, 10))
#[1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
```

### 四、send使用

如果yield的值返回给一个变量，例

``` python
Def create()
	A = 0
	for bb in range(5)
		Tem = yield bb
		print Tem #这里打印不出来，要使用send(“值”)这样的方法进行打印

A = create()
a.send(“xxx”) ##这里会打印生成器的值，还会打印send的值
#第一次使用send会造成程序崩溃，后几次运行才可以，或者第一次传值none;a.send(“none”)
```

### 五、生成器有什么用呢

1. 协程（多任务其中一种，进程，线程，协程最快）

``` python
def t1():
	while True:
		print(“1”)
        yiled None #暂停

def t2():
	while True:
	print(“2”)
	yiled none #暂停

Te = t1()
Tt = t2()
while True:
  Te.__next__()
  Tt.__next__()
```

## 闭包 and 装饰器

### 一、闭包

1. 函数中包含一个函数
2. 被包含的**函数用到了**外面函数的变量

``` python
def line_conf(a, b): #定义闭包
  	def line(x): 
		return a*x + b #使用了函数外的参数，资源不会被释放
	return line #返回了line函数的指针

#调用方法
line1 = line_conf(1, 1) #调用闭包 return line
print(line1(5)) #调用闭包 return a*x +b
```

### 二、装饰器

1. 当一个函数加载装饰器的时候，执行流程就是装饰器定义
2. 装饰器要么是函数，要么是一个类，不可能是一个类中的函数。

如何定义一个自定义装饰器

``` python
# 自定义装饰器创建
import functools
def timefun(func): #timefun装饰器名称，
	
    # wrappedfunc名称可自定义
    # wrappedfunc 自定义函数名,*args,**kargs是foo的参数
    @functools.wraps(func) # func指向foo函数，foo是要装饰的函数
	def wrappedfunc(*args, **kargs): 
        # ...
    	# func(*args,**kargs) 在装饰器中调用foo函数
        
		return func(*args, **kwargs) #执行一次foo函数
	return wrappedfunc #wrappedfunc这个名称要与自定义名称一样

#调用，会立刻调用
@timefundef 
foo(a, b, c):
	print(a+b+c)
```

### 三、带有参数的装饰器

``` python
import functools
def func_arg(arg = 'hello'): # 装饰器函数的参数，默认值为:hello
	def func (funNume): #funNume代指 f1 函数
		def func_in(*args,**kargs): # f1 函数的参数
            # ...
			return funNume(*args,**kargs) # f1函数的返回值
		return func_in
	return func

#1.先执行func_arg('world')函数，这个函数return的结果是func这个函数的引用
#3.使用@func对f1进行装饰
@func_arg('world')
def f1(a,b):
	return 'haha'
```

### 四、类装饰器

 

## 元类

创建类的东西-》元类，type()

Type(“名称”,(继承),{方法:函数}

## 动态语言

## 垃圾回收（GC）

1. 大整数对象池，小整数对象池

2. 小整数：-5到256在内存中早定义完好

3. 大整数：python对其开启新内存

4. intern机制：相同的字符串指向同一块变量

5. 引用计数：Python垃圾处理机制的主要方式

   缺点：循环引用内存不能被释放；python使用隔代回收进行解决

6. 隔代回收：Python将对象都挂在链表中，每当计数达到预定的时候，就会进行一次清理

注意：类中默认的`__del__`方法是垃圾回收机制，如果要重写`__del__`方法需要调用父类的`__del__`方法进行清除垃圾

## 内建属性

在获得属性时进行调用，返回值时返回类中的属性

调用过程，先将字符串

``` python
def __getattribute__(self, obj)
	return ….. #自定义返回值
	return object.__getattribute__(self,obj) #系统默认返回的属性
```

## 内建函数：

``` python
lambda x:x+x,[1,2,3]
X = 1+1,x=2+2,x=3+3

lambda x,y:x+y,[1,2,3],[3,2,1]
X,y = 1+3,xy=2+2,xy=3+1
```

Map：对指定方法进行映射

Filter：对指定的数据进行过滤

Filter（函数，数据）：对filter数据进行过滤，经函数判断为真的时候才保留

Reduce：对函数进行累积

## Functools

Wraps显示以前的help信息

#### Ⅰ、with语句

``` python
# with的指向顺序
# 先执行Foo类中的__enter__方法，其返回值放到变量f中，最后再指向__exit__方法
class Foo(object):
    def __enter__(self):
        return 123
    def __exit__(self, exc_type, exc_val, exc_tb):
        pass
    
obj = Foo()
with obj as f:
    print(f)
```

## 第三方库

### 一、网络爬虫

1. requests：简洁的处理HTTP请求的库，基于urllib3库
2. scrapy：是python开发的快速的、高层次的web获取框架，本身包含成熟网络爬虫系统具有的部分公共功能

### 二、数据分析

1. numpy：用于处理数据类型相同的多维数组，可以存储和处理大型矩阵
2. scipy：在numpy库上增加了数学、科学以及工程计算的常用函数
3. pandas：基于numpy库，为了解决数据分析任务

### 三、文本处理方向

1. pdfminer：从pdf文档提取信息库
2. openpyxl：处理Excel文本的库
3. python-docx：处理Word的库
4. beautifulsoup4：解析处理HTML与XML的库

### 四、数据可视化

1. matplotlib：提供数据绘图的库，主要进行二维图数据展示、科学计算数据可视化
2. TVTK：三维可视化工具
3. mayavi：基于VTK开发三维可视化库

### 五、用户界面

1. PyQt5：QT5的python版本
2. wxPython：GUI库
3. PyGTK：基于GTK+的python语言封装，具有跨平台性，

### 六、机器学习方向

1. scikit-learn：数据挖掘和数据分析库
2. TensorFlow：谷歌开发的第二代人工智能学习系统
3. Theano：深度学习大规模神经算法的运算设计

### 七、Web开发方向

1. Django：Web框架，全面
2. Pyramid
3. Flask：Web框架，微框架

### 八、游戏开发方向

1. Pygame：SDL库基础上进行封装
2. Panda3D：开源快平台的3D渲染和游戏开发库
3. cocos2d：2D游戏开发库

### 九、其他

1. PIL：图像处理库
2. SymoPy：全功能计算机代数系统
3. NLTK：自然语言处理库
4. WeRoBot：微信公众号开发框架
5. MyQR：生成二维码库
