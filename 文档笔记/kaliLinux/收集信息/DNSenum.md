# 枚举服务

# 一、DNSenum

尽可能收集一个域的信息，它能够通过谷歌或者字典文件猜测可能存在的域名，以及对一个网段进行反向查询。它可以查询网站的主机地址信息、域名服务器、mx record（函件交换记录），在域名服务器上执行axfr请求，通过谷歌脚本得到扩展域名信息（google hacking），提取自域名并查询，计算C类地址并执行whois查询，执行反向查询，把地址段写入文件



## 1、命令

```shell
dnsenum [ADDR]
```

# 二、fierce

该工具是一个域名扫描综合性工具。它可以快速获取指定域名的DNS服务器，并检查是否存在区域传输（Zone Transfer）漏洞。如果存在该漏洞，会自动执行暴力破解，以获取子域名信息。对获取的IP地址，它还会遍历周边IP地址，以获取更多的信息。该工具会将IP地址进行分段统计，以便于后期其他工具扫描

## 1、命令

```shell

```

# 三、Snmpwalk

snmpwalk是SNMP的一个工具，它使用SNMP的GETNEXT请求查询指定OID（SNMP协议中的对象标识）入口的所有OID树信息，并显示给用户。

## 1、命令

```shell
snmpwalk [OPTION] <addr>
```

## 2、OPTION参数

```shell
–h：显示帮助。

–v：指定snmp的版本, 1或者2c或者3。

–c：指定连接设备SNMP密码。

–V：显示当前snmpwalk命令行版本。

–r：指定重试次数，默认为0次。

–t：指定每次请求的等待超时时间，单为秒，默认为3秒。

–l：指定安全级别：noAuthNoPriv|authNoPriv|authPriv。

–a：验证协议：MD5|SHA。只有-l指定为authNoPriv或authPriv时才需要。

–A：验证字符串。只有-l指定为authNoPriv或authPriv时才需要。

–x：加密协议：DES。只有-l指定为authPriv时才需要。

–X：加密字符串。只有-l指定为authPriv时才需要。
```

# 四、Snmp-check

可获取

+系统信息，如主机名、操作系统类型及架构等：

注：snmpcheck 版本不同用法不同，命令格式也不同，在 kali 中甚至是两个软件，一个使用 `snmpcheck` 命令，一个使用 `snmp-check` 命令。

## 1、BASE

```shell
snmp-check [OPTION] <目标地址>
```

## 2、OPTION参数

# 五、smtp-user-enum

它是针对 SMTP 服务器的 25 端口，进行用户名枚举的工具，用来探测服务器已存在的邮箱账户。

## 1、BASE

```shell

```
