# Linux操作系统

## 目录相关命令

### 一、命令列表

- 切换目录：`cd` 
- 显示上一次目录：`cd -`  
- 显示当前目录：`pwd` 

### 二、mkdir-创建目录

显示目录结构，需要安装tree 

``` shell
# 递归创建目录
mkdir -p xx/aa 
# 创建2个目录(aa,bb)
mkdir aa bb  
```

**rmdir命令**       

rmdir /etc/home      # 删除/etc/home目录

rmdir -p /etc/home    # 递归删除目录

\-------------------------------------------------------------------------------------------

查看命令在哪个目录   which 

## 文件相关命令

创建文件(如果文件已存在则更正文件创建时间)  touch 

**rm命令**

rm -r  # 递归删除目录 

rm -f  # 强制删除

rm -rf  # 递归强制删除

\------------------------------------------------------------------------------------

复制 cp

移动 mv

读取文件（比较小的文件）  Cat 

**tail命令**

Tail -n 5  # 查文件最后5行内容

Tail -f   # 实时显示显示文件添加内容

\----------------------------------------------------------------------------------------

**head命令** 

head /etc/passwd    # 查看前几行 默认显示10行

Head -n 4 /etc/passwd  # 显示4行

\--------------------------------------------------------------------------------------

查看文件（回车一行，空格一页）   more /etc/passwd

查看文件（分屏查看上下方向键）   less /etc/passwd 

## 统计

**wc命令**

wc -l  # 显示有多少条命令

wc -w

wc -c

显示文件信息  du

显示系统空间  df -h 

## 文件权限

\- rw- r-- r-- 1 

文件类型 归属用户 归属组 其他 硬连接数

改变文件权限   chmod

修改文件所属   chown a:b a.out  # 用户a ; b组

chown group file 改变file文件的组为group

chown :user file 改变归属组

chown user: file 改变用户

Chgro 修改用户组权限

 

## 查找命令

**Find命令**

Find / -name  # 按名字查找

Find / -type  # 按类型查找 

-f普通文件 -d目录文件 -l 连接文件 -b设备文件 -c字符设备 -p管道设备 -s本地套接字 

Find / -size +1M -5M   # 按大小查找，不写+-号，就是等于

-maxdepth 1       # 查找深度

## 用户命令

### 一、添加用户

#### 1、adduser

会自动为创建的用户指定主目录、系统shell版本，会在创建时输入用户密码

``` shell
root@iZ2ze9o2g75lce93uglxpdZ:~# sudo adduser tree
Adding user `tree' ...
Adding new group `tree' (1000) ...
Adding new user `tree' (1000) with group `tree' ...
Creating home directory `/home/tree' ...
Copying files from `/etc/skel' ...
New password: 
Retype new password: 
passwd: password unchanged
Try again? [y/N] y
New password: 
Retype new password: 
passwd: password updated successfully
Changing the user information for tree
Enter the new value, or press ENTER for the default
	Full Name []: 
	Room Number []: 
	Work Phone []: 
	Home Phone []: 
	Other []: 
Is the information correct? [Y/n] y
```

#### 2、useradd

自定义添加用户

常用命令行选项：

- -d： 指定用户的主目录
- -m： 如果存在不再创建，但是此目录并不属于新创建用户；如果主目录不存在，则强制创建； -m和-d一块使用。
- -s： 指定用户登录时的shell版本
- -M： 不创建主目录
- -g：指定组

### 二、删除用户

1、`sudo deluser AAAAAA`：只删除用户

2、`sudo deluser --remove-all-files AAAAAAA` ：连同用户拥有的所有文件删除

3、`sudo userdel AAAA`：只删除用户

4、`sudo derlser -r AAAAAA`：连同用户主目录一起删除

- 如果创建时主目录已经存在，即主目录不属于当前要删除的用户，则无法删除主目录。

### 三、用户权限

1、给与普通用户sudo权限

```shell
su root
sudo usermod -a -G sudo AAAAAAA
```

\-----------------------------------------------------------------

添加用户组   groupadd Tree

修改密码    passwd Tree 

## 其他命令

查看历史输入命令  history

查看命令说明    man

**ls命令**

ls -l   # 查看文件详细信息 

ls -a   # 显示所有文件

-r 

ls -lrt   # 按照时间进行排序

ls *.a   # ls 允许输入正则

ls func.?  #

\--------------------------------------------------------------------------------------

**ln命令** 

ln -s软连接

使用ls会看到箭头 可创建目录，

Ln 硬连接，会增加计数，硬连接计数为0，会删除文件夹。不能创建目录硬连接 引用同一块内存（磁盘快）

删除硬连接数   unlink /etc/passwd

\-----------------------------------------------------------------------

返回当前登录的用户  whoami

 

 

-ok 安全模式

-exec

| xargs

| greg 内容过滤

 

Greg -rn

Greg -v 排除

## 网络命令

### 1、netstat

## 程序命令

### Archlinux

`pacman -S XXXX`

### ubuntu

1、`apt install` ：安装命令

2、`apt remove` ：删除命令

## 异常检查检查

### 一、Archlinux

- 检查日志最后10行：`journalctl -xn` 
- **查看系统本次启动的日志：`journalctl -b`
- 检查启动项：`systemctl --type=service` 