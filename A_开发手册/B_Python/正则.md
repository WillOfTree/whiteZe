# python正则

import re

.group() #分组后取组

.span()

\-----------------------------------

## 生成一个正则匹配

pattern = re.compile(r” 正则规则 ”,[x])

--r：可以匹配转义字符

--u：匹配unicode字符

--x：[

re.I：忽略大小写

re.S：全文匹配

]

## 匹配方法

**1****、pattern.match(str[, bigin, end])**

从文本头部开始匹配

--str：要匹配的字符串

--bigin：指定开始匹配的位置（0开始，包含）

--end：指定结束的字符串

--返回值：对象

 

**2****、pattern.search(str[,bigin,end])**

从任意位置开始匹配

--str：要匹配的字符串

--bigin：指定开始匹配的位置（0开始，包含）

--end：指定结束的字符串

--返回值：

 

**3****、pattern.findall(str)**

匹配全部字符串，获取文本中所有符合规则

--str：字符串

--返回值：数组

 

**4****、pattern.finditer(str)**

匹配全部字符串，获取文本中所有符合规则

--str：字符串

--返回值：m<迭代器>

 

**5****、pattern.split(r’str’)**

切割字符串

--r：按字符匹配（compile这不用加r）

--str:要切割的字符串

--返回值：m<数组>

 

**6****、pattern.sub(r”str”,des_str)**

将str替换，des_str中符合正则的字符串

--r：匹配转义字符

--str：原字符串

--des_str：要替换的字符串

 