# Ubuntu操作系统

## 一、添加用户

1、adduser：会自动为创建的用户指定主目录、系统shell版本，会在创建时输入用户密码

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

2、useradd：为用户指定参数

常用命令行选项：

- -d： 指定用户的主目录
- -m： 如果存在不再创建，但是此目录并不属于新创建用户；如果主目录不存在，则强制创建； -m和-d一块使用。
- -s： 指定用户登录时的shell版本
- -M： 不创建主目录

## 二、删除用户

1、`sudo deluser AAAAAA`：只删除用户

2、`sudo deluser --remove-all-files AAAAAAA` ：连同用户拥有的所有文件删除

3、`sudo userdel AAAA`：只删除用户

4、`sudo derlser -r AAAAAA`：连同用户主目录一起删除

- 如果创建时主目录已经存在，即主目录不属于当前要删除的用户，则无法删除主目录。

## 三、权限

1、给与普通用户sudo权限

```shell
su root
sudo usermod -a -G sudo AAAAAAA
```

## 四、网络命令

### 1、netstat

## 五、程序命令

1、`apt install` ：安装命令

2、`apt remove` ：删除命令