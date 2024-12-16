# wireshark网络分析

## 概述

- 官网地址：www.wireshark.org
- 网络模拟eNSP：

## 说明

### Packet Details Pane(数据包详细信息)

在数据包列表中选择[指定数据包](https://zhida.zhihu.com/search?content_id=233475982&content_type=Article&match_order=1&q=指定数据包&zhida_source=entity)，在数据包详细信息中会显示数据包的所有详细信息内容。数据包详细信息面板是最重要的，用来查看协议中的每一个字段。各行信息分别为

（1）Frame:物理层的[数据帧](https://zhida.zhihu.com/search?content_id=233475982&content_type=Article&match_order=1&q=数据帧&zhida_source=entity)概况

（2）EthernetII:[数据链路层](https://zhida.zhihu.com/search?content_id=233475982&content_type=Article&match_order=1&q=数据链路层&zhida_source=entity)以太网帧头部信息

（3）Internet Protocol Version 4:互联网层[IP包](https://zhida.zhihu.com/search?content_id=233475982&content_type=Article&match_order=1&q=IP包&zhida_source=entity)头部信息

（4）Transmission Control Protocol:传输层T的数据段头部信息，此处是TCP

（5）Hypertext Transfer Protocol:应用层的信息，此处是HTTP协议

## Berkeley Packet Filter过滤规则

### 一、语法规则

1、type：表示对象

- 例如：ip地址，子网，端口

2、dir：表示数据包的传输方向

- src源地址，dst目标地址

3、proto：表示与数据包匹配的协议类型

- 例如：ether，tcp，ip，arp

### 二、具体使用样例

1、查找指定IP为192.168.0.1的数据

- `ip.addr == 192.168.0.1`  
- `ip.addr == 192.168.0.1/24` 

2、查找源地址为192.168.0.1的数据：`ip.src == 192.168.0.1` 

3、查找目标地址为192.168.0.1的数据：`ip.dst == 192.168.0.1` 

4、查找端口为80的数据：

- `tcp.port == 80` 
- `udp.port == 80` 

5、多条查找条件：`tcp.port == 80 and ip.dst == 192.168.0.1` 

## 捕获过滤器

在抓包前设置，根据规则抓取指定数据包

capture $\to$ capture filter for selected interfaces 设置规则

- `tcp dst port 80`：抓取目标端口80的数据包
- `dst host 192.168.0.1`：目标地址为192.168.0.1的数据包

## 筛选过滤器

抓包后，对数据进行选择

逻辑运算符：|| and not && ! or

## 远程数据包捕获

- 通过远程桌面，进行抓包分析，缺点在登录过程中会产生无关的数据流量
- 远程抓包

远程主机启动winpcap 运行命令rpcapd -n

wireshark配置

capture $\to$ Manage Interfaces $\to$ Remote Interfaces $\to$ ➕ 添加远程接口

## 本地数据抓取

RawCap抓取本地环回网卡

## ARP欺骗

KailLinux里面有软件`arpspoof -i 网卡名 -t 目标IP 欺骗的内容` 

arp.opcode == 0x0001 请求arp

arp.opcode == 0x0002 响应arp

arp.src.hw_mc == mac地址 具体mac地址

## MAC地址泛洪

隐藏自己的mac地址：`macchanger -m MAC地址 网卡名` 

命令：macof

## 泪滴安全测试

导致系统崩溃和无法服务

## TCP SYN flooding

重复发送建立连接的请求，

hping3 -q -n --rand-source -S -p 80 IP地址

## 网络取证

从数据包

暴力破解软件medusa

`medusa -h ip地址 -u 用户名 -M ssh -P 密码字典`

