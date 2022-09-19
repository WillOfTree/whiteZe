# CURL网络请求

## 使用方式

``` php
// 1. 初始化
$ch = curl_init();

/**
 * 设置参数
 **/
// 设置URL
curl_setopt($ch, CURLOPT_URL, "http://www.doucube.com");
// 关闭网页输出，可以进行保存到变量
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

// 3. 获取返回结果
$output = curl_exec($ch);

// 4. 释放curl句柄
curl_close($ch);
```

## 调试错误信息。

``` php
/**
 * 返回错误信息
 **/
curl_error($ch);

/**
 * $ch 由curl_init()方法创建的句柄
 * $opt 可选参数
 *		CURLINFO_HTTP_CODE ：最后一个收到的HTTP代码
 **/
curl_getinfo(resource $ch, int $opt = 0)
```

## Curl_setopt参数

``` php

// 指定请求的URL；
curl_setopt($ch, CURLOPT_URL );
// 设置为0表示不返回HTTP头部信息
curl_setopt($ch, CURLLOPT_HEADER );
// 设置0直接输出，1是存入内存(curl_exec的返回值是文本流)
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
// 设置不检查ssl
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
curl_setopt($ch, CURLOPT_URL );
curl_setopt($ch, CURLOPT_URL );
curl_setopt($ch, CURLOPT_URL );
curl_setopt($ch, CURLOPT_URL );
curl_setopt($ch, CURLOPT_URL );
curl_setopt($ch, CURLOPT_URL );
curl_setopt($ch, CURLOPT_URL );
```





## GET请求

如何使用CURL来发送GET请求，发送GET请求的关键是拼装格式正确的URL。

不用特别配置相关参数。

 

## POST请求

主要设置以下2项

\-----------------------------------

//定义要提交的POST数据

$post_data = array(

“sss”=>”sss”,

);

\------------------------------------

// 我们在POST数据哦！

curl_setopt($ch, CURLOPT_POST, 1);

// 把post的变量加上

curl_setopt($ch, CURLOPT_POSTFIELDS, $post_data);

//设置post的下标名称

curl_setopt($ch, CURLOPT_POSTFIELDS, “data=”.$post_data);

## **匹配文本**

//开启

$ch = curl_init();

//配置

curl_setopt($ch, CURLOPT_URL, "http://www.baidu.com/");

//设置exec保存html代码

curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);//不自动输出内容

$aa = curl_exec($ch);

//正则匹配

//$aa中可能会有多行空格或其他字符，使用preg_match可能匹配不到。

//匹配标签比较困难，直接匹配其中的href比较简单。

preg_match_all("/<title.*>(.*)<\/title>/",$aa,$bb);

## **相关正则**

//匹配a标签中的href

/<[a|A].*?href=[\'\"]{0,1}([^>\'\"]*).*?>/

 

# **设置重定向**

可能可以实现登陆限制的网站。如DMM

 



 

# **文件上传**

文件上传与POST过程一样。主要是POST数据不同。

$post_data = array (

// 要上传的本地文件地址。添加@符号。

"upload" => "@C:/doucube/www/test.zip"

);

\-----------------------------

// 我们在POST数据哦！

curl_setopt($ch, CURLOPT_POST, 1);

// 把post的变量加上

curl_setopt($ch, CURLOPT_POSTFIELDS, $post_data);

# **多次请求**

1、创建多个cURL资源

$ch1 = curl_init();

$ch2 = curl_init();

2、分别设置对应配置

Curl_setopt($ch1, CURLOPT_URL, “http://www.aa.com”);

Curl_setopt($ch2, CURLOPT_URL, “http://www.bb.com”);

 ## 常见错误信息

1、**SSL certificate problem: unable to get local issuer certificate**

 解决方法：

（1）curl 取消 ssl 检查

curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);

（2）添加cacert.pem证书

下载证书：[curl - Extract CA Certs from Mozilla](https://curl.se/docs/caextract.html)

修改php.ini添加对cacert.pem支持

[curl]
; A default value for the CURLOPT_CAINFO option. This is required to be an
; absolute path.
curl.cainfo = D:\WAMP\tmp\cacert.pem

 

 

 

 

 

 