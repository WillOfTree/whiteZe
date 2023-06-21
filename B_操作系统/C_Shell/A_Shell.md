# shell编程

## 简介

### 一、常见的命令解释器

- 红帽系列：bash
- unix中常用：csh、tcsh

### 二、脚本常用格式

``` shell
# 使用什么命令解释器（一定在第一行）
#!/bin/bash

# 其他脚本
#!/bin/awk
#!/bin/sed
```

### 三、执行脚本

``` shell
# 对于带有执行权限的脚本，直接路径+名称
# 红帽系统常见、系统脚本
./xxx.sh

# 通用使用方
# sh执行-sh是bash的软连接
sh xxx.sh
bash xxx.sh

# 常用于让一些环境变量生效
# 让shell脚本使用类似于include的功能
source xxx.sh
. xxx.sh
```

### 四、重定向

``` shell
# >/dev/null：结果输出文件，/dev/null是直接抛弃
ping -c baidu.com >/dev/null 2>&1
```

### 五、随机数

``` shell
echo $RANDOM
# 生成0-9之间的随机数
echo ($RANDOM%10)
```

## 变量

### 一、变量

#### 1、变量定义

- 只能使用字母数字下划线
- 数字不能开头
- 驼峰命名方法、以下划线连接

``` shell
# 可以使用任意字符定义变量
# old,new都是变量，与C语言类似，但不用声明变量类型
old = 333
new = "xxx"
```

#### 2、变量输出

``` shell
# 使用$表示变量
$old
echo $old

# 使用${}在文本中表示变量
${old}
echo 今天是第${old}天
```

#### 3、变量赋值

``` shell
# 直接赋值
oldboy = 100

# 应用其他结果赋值（esc键下面的啷个键``)
ip = `hostname -l | awk 'print $2'`

#--- 交互式赋值（read）
# 等待用户输入
# addr：变量名称，用户输入信息保存在addr中
read -p "提示信息" addr
```



### 二、环境变量（全局变量）

这些变量由系统定义，全局可用，一般是全大写

永久生效环境变量：`/etc/profile` 

#### 1、常用命令

##### （1）env-查看

查看环境变量：`env`

##### （2）declare

##### （3）export-配置

``` shell
# // 修改临时变量 
# 设置TMOUT命令断开时间为3秒
export TMOUT = 3

# 创建一个环境变量my_shell
export my_shell = 111

# unset命令
# 删除环境变量
```

##### （4）unset-删除

删除一个环境变量：`unset my_shell`

#### 2、常用的环境变量

| 环境变量       | 含义                                    | 备注                                                         |
| -------------- | --------------------------------------- | ------------------------------------------------------------ |
| LANG           | 系统字符集，语言                        | localectl 修改变量<br/>默认文件位置：/etc/sysconfig/i18n（centos） |
| PS1            | 命令格式                                |                                                              |
| PATH           | 命令路径<br/>系统会在PATH路径中查找命令 | 查看PATH中内容：echo $PATH                                   |
| UID            | 记录用户UID信息                         | 脚本中判断用户是否root                                       |
| HOSTNAME       | 主机名称                                |                                                              |
| -------------- | ---------------------                   | ------------------------------------------------             |
| HISTSIZE       | history命令记录的条数（最多）           | history -c/-w/-a/-d                                          |
| HISTFILESIZE   | history文件记录的最多条数               | 文件默认在当前用户家目录 ~/.bash_history                     |
| HISTFILE       | 指定历史记录文件的位置                  | 文件默认在当前用户家目录 ~/.bash_history                     |
| TMOUT          | 不进行操作，自动断开时间                |                                                              |
| HISTCONTROL    | 控制history命令是否记录以空格开头的命令 | export HISTCONTROL=ignorespace<br>以空格开头的命令，不会被记录到history中<br>例如：空格ls -l；这条命令不会被记录 |
| PROMPT_COMMAND | 存放的命令/脚本会在下个命令执行前运行   | export PROMPT_COMMAND=date<br>在下一条命令执行前执行date命令 |

### 三、与变量有关的文件

每次登录都会读取的文件

| 文件名/位置            | 作用                                 | 作用域                            |
| ---------------------- | ------------------------------------ | --------------------------------- |
| /etc/profile           | 环境变量                             | 全局                              |
| /etc/bashrc            | 别名，例如：alias ls -l = ll         | 全局                              |
| ~/.bashrc              | 当前用户的别名（alias）              | 当前用户                          |
| ~/.bash_profile        | 当前用户的环境变量                   | 当前用户                          |
| /etc/profile.d/xxxx.sh | 用户登录系统后，会执行这个目录的脚本 | 注意：一定是.sh结尾的脚本才能执行 |

### 四、特殊变量

#### 1、`$0`：脚本名称

``` shell
# 文件：show.sh
#!/bin/bash
echo $0

# 输出：show.sh
sh show.sh
# 输出：/server/scripts/show.sh
sh /server/scripts/show.sh
```

#### 2、`$n`：参数位置

``` shell
# 文件：show.sh
#!/bin/bash
echo $1, $2

# 输出：start lidao
sh show.sh start lidao oldboy

#-- 多个参数
# 文件：show.sh
#!/bin/bash
echo $1,$2,$3,${10},${11}

# 输出 1,2,3,4,5,6
sh xxx.sh {1..12}
# $n， 输出a1,a2,a3
sh xxx.sh {a..z}
```

#### 3、`$#`：参数个数

不包括文件名

``` shell
# 文件：show.sh
#!/bin/bash
echo $#

# 输出：3
sh show.sh start lidao oldboy
# 输出：0
sh show.sh
```

#### 4、`$*`：获取参数

单引号$*与\$@相同

对于加双引号的参数，1个参数1个整体

``` shell
# show.sh
#!/bin/bash
echo $*

# 输出：a b c
sh show.sh a b c

#--- 双引号
#!/bin/bash
# 必须循环输出
for n in "$*"
do
	echo $n
done
# 输出：a b c
sh show.sh a b c
```

#### 5、`$@`：获取参数

加双引号参数，每个参数独立

``` shell
# show.sh
#!/bin/bash
echo $@

# 输出：a b c
sh show.sh a b c

#--- 双引号
# 文件：show.sh
#!/bin/bash
# 必须循环输出
for n in "$@"
do
	echo $n
done

# 执行：
sh show.sh a b c
# 输出-
[root@m1]# a
[root@m1]# b
[root@m1]# c
# 输出-
```

### 五、状态特殊变量

#### 1、$?：返回值

**上一个**脚本的返回值，成功执行返回0，失败（出错）非0

``` shell
# 例子
ping -c baidu.com >/dev/null 2>&1
# ping成功输出,"baidu是通的"
if [$? -eq 0 ];then
	echo "baidu是通的"
fi
```

#### 2、$$：pid

当前脚本的pid

``` shell
#--- 文件：show.sh
#!/bin/bash
echo $$

# 127
sh show.sh
```

#### 3、$!：上个脚本pid

获取上一个脚本的pid

``` shell
ping -c3 www.baidu.com
echo $!
```

#### 4、$_：上个脚本参数

获取上一个脚本的**最后**参数

``` shell
#--- 文件：show2.sh
#!/bin/bash
echo $_

# 第一个命令
sh show.sh a b c
# 运行当前文件，输出：c
sh show2.sh
```

### 六、变量子串

| 形式                 | 含义                                        | 例子                                              |
| -------------------- | ------------------------------------------- | ------------------------------------------------- |
| ${p}                 | 变量                                        | abc${exp}                                         |
| ${#p}                | 返回变量p的长度                             | ${#p}                                             |
| ${p:offset}          | 在变量p中从offset之后提取字符串             | oldboy=996icu<br>#输出：96icu<br>echo ${oldboy:1} |
| ${p:offset:length}   | 在变量p中从offset之后提取length长度的字符串 |                                                   |
| ${p#word}            | 从变量p的开头，删除最短匹配的word子串       |                                                   |
| ${p##word}           | 从变量p的开头，删除最长匹配的word子串       |                                                   |
| ${p%word}            | 从变量p的结尾，删除最短匹配的word子串       |                                                   |
| ${p%%word}           | 从变量p的开头，删除最长匹配的word子串       |                                                   |
| ${p/pattern/string}  | 使用string替换第一个匹配的pattern           |                                                   |
| ${p//pattern/string} | 使用string替换所有的pattern                 |                                                   |

### 七、变量默认值

| 形式       | 含义                                                         | 例子       |
| ---------- | ------------------------------------------------------------ | ---------- |
| ${p:-word} | 如果p没有被赋值或p为空，则值就是word                         | 设置默认值 |
| ${p:=word} | 如果p没有被赋值或p为空，就将word的值赋值给p                  |            |
| ${p:?word} | 如果p没有被赋值或p为空，word为错误输出                       |            |
| ${p:+word} | 如果p没有被赋值或p为空，什么都不做，否则就用word替换变量内容 |            |

## 运算符

### 一、常见的运算符

- +，-，*，%，/
- &&：前一个执行成功在执行后一个
- ||：前一个执行失败再执行后一个
- i++,

### 二、运算方式

``` shell
# 计算2*10
$((2*10))
# 2^10
$((2**10))

#计算2值相加
n1=100
n2=200
$((n1+n1))

# 键结果赋值给n3
((n3=n1+n2))

# let运算后进行赋值
let c=n1+n2
echo $c

# expr
# 必须有空格
expr 1 + 1
expr 1 '*' 1
expr 1 \* 1

# 小数运算
echo 9/6 | bc -l
```

## 条件表达式

### 一、写法/ 格式

- `test <条件>` 
- `[条件]`
- `[[条件]]` ：支持正则
- `((<条件>))` 

``` shell
# 常用的写法
if [ -f /etc/sysconfig/network ]; then
	exit 6
fi
# 常用方法，这里使用的是1个等号
["${NETWORKING}" = "no"] && exit 6
```

常用格式

``` shell
# 满足条件 执行命令
[ 条件 ] && 命令
# 满足条件 执行多条命令
[ 条件 ] && {
	cmd01
	cmd02
}
# 条件不满足执行
[ 条件 ] || 命令
[ 条件 ] || {
	cmd01
	cmd02
}
```

### 二、文件相关

字符串一定要加双引号

| 参数 | 说明                           |
| ---- | ------------------------------ |
| -d   | 判断目录是否存在               |
| -f   | 判断文件是否存在               |
| -e   | 判断exist是否存在              |
| -r   | 判断是否存在，是否有读权限     |
| -w   | 判断是否存在，是否有可写权限   |
| -x   | 判断是否存在，是否有可执行权限 |
| -s   | 判断文件是否存在，是否为空     |
| -L   | 判断文件是否存在，是否为软连接 |

``` shell
# 判断文件是否出存在
[ -f /etc/xxxx.sh]
echo $?
# 字符串表达
[ -n "ssss"]
```





















































































``   







