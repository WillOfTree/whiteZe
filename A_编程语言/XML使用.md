# XML手册

# python

## 1、导入

import xmltodict

## 2、使用

\# 将xml字符串转换为对象（字典）

\# xml_str xml字符串

xml_dict = xmltodict.parse(xml_str) 

 

\# 将字典转换为 xml字符串

\# dict  字典

\# pretty 打印xml变量是否有格式

\# dict 样例：{ “xml”:{“a”:1,”b”:2} }

xml_str = xmltodict.unparse（dict, pretty=true） 

# PHP

## 1、加载-保存

/**

 \* 通过DOMDocument加载文档

 */

$dom = new DOMDocument();

$dom -> load(“./firstStairMenu.xml”);

/**

 \* 将DOMDocument文档转化为Xpath

 */

**$xpath** = new DOMXPath($dom);

/**

 \* 保存

 */

$dom -> save('test1.xml'); // save as file

\-----------------------------------------------------------------

/**

 \* 通过DOMDocument加载文档

 */

$dom = new DOMDocument();

$dom -> load(“./firstStairMenu.xml”);

 

/**

 \* 将DOMDOcument转换为Xpath

 */

**$xpath** = simplexml_import_dom($dom)

 

/**

 \* 保存

 */

$dom -> save('test1.xml'); // save as file

## 2、使用xpath语法

//获取所有节点数,用于获得一共有多少节点

$query = "/root/*";

$entries = **$xpath** -> query($query); //执行xpath语句

 

查询语句一般为 //*

用于选择查到的节点

Item(@parent)是必有的对于多个查询结果其参数是对应的不同的选项，对于单个选项其值为0即可

Item()

选值是从0开始

//查找节点属性的值  使用item标识第几个 使用nodeValue等取值

attributes->item(2)

所有节点

/root/mark[1]是从1开始，不是0开始

 

nodeValue选中节点的值

nodeName选中节点的名字

 