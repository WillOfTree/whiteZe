# 系统函数

## round()

四舍五入

## len()

长度

 

# dict字典

dict = {“x”:123}

## dict.len()

键值对个数

## dict.keys()

返回所有键

## dict.values()

返回所有值

## dict.items()

返回所有键值

dict

# string字符串

## str.split(“”)

分割

## str.splitext(‘’)

## str.rstrip(‘str’)/str.lstrip(‘str’)

# time时间

import time

## time.time()

浮点型时间戳

## time.strptime(str, “%Y-%m-%d”)

将字符串转换为时间格式

## time.mktime(time)

将指定时间变量转换为时间戳

 

# OS系统

## os.path.split()

获取文件名及路径

--（path）

path, file_name = os.path.split(“/etc/o.py”)

path：/etc

file_name：o.py

## os.path.join()

拼接路径

path = os.path.join(ph, name)

path：/etc/o.py

## os.path.splitext()

分割后缀名

a = "/opt/ext/o.py"

b,c = os.path.splitext(a)

b：/opt/ext/o

c：py

## os.rename()

重命名

os.rename(“目标源文件”, ”文件名”)

## os.remove()

删除文件

Os.remove(“文件名”)

## os.mkdir()

创建文件夹

os.mkdir(“文件夹名称”)

 

## os.rmdir()

删除文件夹

os.rmdir(“文件名”)

## os.chdir()

改变当前路径

Os.chdir(“../”)

## os.listdir()

获取目录列表

Os.listdir(“../”)

 

# re正则

import re

# json

import json

import jsonpath #jsonpath

 

## json.loads(html)

加载json格式

--html：json形式的字符串转换为python的json（unicode）

--return：unicodestr

## jsonpath.jsonpath(unicodestr, “node”)

获取指定节点的文本

--unicodestr：json

## json.dumps(str, ensure_ascii=True)

将python的json格式转换为json格式的字符串

jsondump默认转化为ascii编码

--str：json字符串

--ensure_ascii：转换为ascii编码（unicode是通用格式）

# threading线程

# queue队列

# request请求

# random随机

import random

## random.choice(array)

随机选择

# base64

## base64.b64encode(“str”)

# pymongo 数据库

import pymongo

## pymongo.MongoClient(host, port)

--return client

## client[dbname]

选择数据库

## db[sheetname]

选择表

## sheet.insert(data)

插入数据

# datetime/time时间

## datetime.utcnow()

获取unicode时间戳

## time.time()

10位时间戳

int(time.time() * 1000)