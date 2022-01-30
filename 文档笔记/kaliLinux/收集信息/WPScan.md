# WPScan

WPScan专门用于扫描WordPress网站中的多种安全漏洞，其中包括主题漏洞、插件漏洞和WordPress本身的漏洞

# 语法

```shell
wpscan [options] --url URL
```

常用选项

```shell
wpscan --update #更新
wpscan -h #帮助菜单
wpscan --force | -f  #不检查网站运行的是不是WordPress, 没啥用
wpscan --version #输出当前版本
```

# options参数

## 1 、--enumerate | -e [OPTS]

```shell
# -------------------------------------
# 如果没有指定选项，默认选项为："vt,tt,u,vp"
#--------------------------------------

"[OPTS] 参数列表:"
t    # Popular themes 使用的主题
p    # Popular plugins 使用的插件

vp   # Vulnerable plugins 有漏洞的插件
vt   # Vulnerable themes 有漏洞的主题

ap   # All plugins 安装的所以插件
at   # All themes 所以主题

u    # User Name 枚举用户名
     # u[10-20]  枚举用户ID从10到20

tt   # Timthumbs 列举缩略图相关的文件
cb   Config backups
dbe  Db exports
m  


```

## 2、 暴力破解得到密码

```shell
# --------------------
#--wordlist | -w <path>
# 例：
wpscan -e u --url XXX --wordlist "字典文件路径"
```

## 3、指定爆破的用户名

```shell
#----------------
# 使用指定用户名
# --username | -U
# 例：
wpscan --wordlist pass.txt --username admin --url XXX 

#-------------------
# 指定爆破用户名字典
# --usernames <path>
# 例：
```

## 其他

```shell
--config-file | -c <config file使用指定的配置文件
--user-agent | -a <User-Agent指定User-Agent
--cookie <String指定cookie
--random-agent | -r 使用随机User-Agent
--follow-redirection 如果目标包含一个重定向，则直接跟随跳转
--batch 无需用户交互，都使用默认行为
--no-color 不要采用彩色输出
--wp-content-dir <wp content dirWPScan会去发现wp-content目录，用户可手动指定
--wp-plugins-dir <wp plugins dir指定wp插件目录，默认是wp-content/plugins
--proxy <[protocol://]host:port设置一个代理，可以使用HTTP、SOCKS4、SOCKS4A、SOCKS5，如果未设置默认是HTTP协议
--proxy-auth <username:password设置代理登陆信息
--basic-auth <username:password设置基础认证信息
--threads | -t <number of threads指定多线程
--cache-ttl <cache-ttl设置 cache TTL
--request-timeout <request-timeout请求超时时间
--connect-timeout <connect-timeout连接超时时间
--max-threads <max-threads最大线程数
--throttle <milliseconds当线程数设置为1时，设置两个请求之间的间隔
--verbose | -v 输出Verbose
```




