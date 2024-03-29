# Archlinux

## 知识点

### 一、UEFI与BIOS说明

#### 1、UEFI

- Unified Extensible Firmware Interface（统一的可扩展固件接口）
- 这种接口用于操作系统自动从预启动的操作环境，加载到一种操作系统上。
- UEFI 系统中使用 GPT，使用[parted](https://wiki.archlinux.org/index.php/Parted_(简体中文))命令

#### 2、BIOS

- Basic Input/Output System（基本输入/输出系统）
- 负责在开机时做硬件启动和检测等工作，并且担任操作系统控制硬件时的中介角色。
- BIOS 系统中使用 MBR，使用fdisk命令

### 二、fstab

文件负责配置Linux开机时自动挂载的分区，某些时候当Linux系统下划分了新的分区后，需要将这些分区设置为开机自动挂载，否则，linux是无法使用新建的分区的。磁盘分区都必须挂载到目录树中的某个具体的目录上才能进行读写操作，而fstab正是负责这一配置。

## 创建启动盘

### 一、启动盘选择

MBR BIOS是大多数系统默认的启动项，可以不配置。

- 硬盘空间不能超过2T，
- GRUB legacy 作为引导程序，必须使用 MBR。
- 使用传统的 BIOS，并且双启动中包含 Windows （无论是 32位版还是 64 位版），必须使用 MBR。

GPT UEFI需要配置BIOS启动项比较复杂，GPT UEFI代表未来，将来一定会替换MBR。

- UEFI支持硬盘大小超过2T

### 二、镜像下载

Archlinux镜像分为网络版（Arch linux Netboot）与ISO文件，这里我们选择ISO文件（magent link 或者 torrent）

### 三、创建启动盘

#### 1、linux系统

使用dd命令

#### 2、Rufus-windos

下载地址：[Rufus - 轻松创建 USB 启动盘](https://rufus.ie/zh/) 

<img src="assets/archlinux/135522.png" style="zoom:55%;" />

#### 2、软碟通

选择RAW方式写入

## 安装前置配置

### 一、设置BIOS启动项

进入系统BOIS中设置启动模式，通过U盘启动

### 二、验证启动模式

``` shell
# 如果命令结果显示了目录且没有报告错误，则系统以 UEFI 模式引导。
ls /sys/firmware/efi/efivars
```

### 三、配置键盘（选作）

默认是英文键盘

### 四、分区

swap分区：swap为内存的2倍

#### 1、分区目标

##### UEFI GPT分区

- swap 分区：2G或者4G
- 主分区（/）：
- EFI分区（/boot）：EFI分区最大512M

<img src="assets/archlinux/141811.png" style="zoom:55%;" />

##### MBR BIOS分区

- swap分区：
- 主分区（/）：

<img src="assets/archlinux/141924.png" style="zoom:55%;" />

#### 2、查看分区信息

`/dev/sdX` 是块设备，依不同物理设备有不同的格式：

- `/dev/sda` 是 SATA 设备（普通磁盘）
- `/dev/nvme0n1` 是 NVMe 设备
- `/dev/mmcblk0` 是 eMMC 设备

```shell
# 可选命令一
parted /dev/sda print
# 可选命令二
fdisk -l /dev/sda
# 命令三
lsblk -f
```

#### 3、分区工具

##### parted：可以划分所有分区

- parted /dev/sdX：进入/dev/sdX磁盘

- mklabel  label_type ：设置分区格式（MBR，GPT）

- mkpart part-type [fs-type] start end(单位Mb)设置分区

- print：查看分区信息

- help [command]：查看命令[command]如何使用

- rm [ num ]：删除一个分区

- set num flag status 

  num：分区序号，print可以查看

  flag：boot，root，

  status：swap状态，可选on或off

- quit：退出

``` shell
#-- 进入分区程序
# 方式一、进入分区程序，默认选择/dev/sda磁盘
root@archiso~# parted 
# 选择磁盘，若默认磁盘不是直接希望得磁盘
(parted) select /dev/sda 
# 方式二、指定磁盘，进入分区程序
root@archiso~# parted 
(parted) parted /dev/sda

#-- 设置分区表
# 1、设置分区格式-GPT分区表
(parted) mklabel gpt 
# 2、设置分区格式-MBR分区表
(parted) mklabel msdos

#-- 开始创建分区
(parted) mkpart ESP fat32 0M 512M
(parted) mkpart swap linux-swap 512M 4.5G 
(parted) mkpart primary ext4 4.5G -1 

#-- 设置boot开关
# 说明： 1 磁盘编号；boot on //设置boot启动标志
(parted) set 1 boot on 

#-- 退出
(parted) q
```

##### cfdisk：图形界面（推荐）

- 设置EFI system分区，大小512M
- 设置Linux swap分区，大小8G
- 设置硬盘空间（Linux filesystem），所有剩余空间
- 光标移动到 write 回车，输出 yes 确定
- 退出

<img src="assets/archlinux/151220.png" style="zoom:55%;" />

### 五、格式化磁盘

1、格式EFI system分区（boot分区）

``` shell
# EFI分区必须是fat格式
mkfs.fat -F 32 /dev/sdaX
# 或者
mkfs.vfat /dev/sdaX
```

2、格式硬盘分区

``` shell
# 一般来讲就是最大的分区，linux filesystem分区
mkfs.ext4 /dev/sdaX
```

3、格式Linux swap分区

``` shell
# 初始交换分区
mkswap /dev/sdaX # 格式化swap分区，
swapon /dev/sdaX # 初始化swap分区(不需要挂载）
```

### 六、检查磁盘类型和分区

命令：`fdisk -l`或`lsblk -f` 

文件系统Type必须是EFI System、Linux swap、Linux filesystem

### 七、挂载

**swap分区不用挂载**

#### 1、挂载根分区

``` shell
# 必须先挂载根目录，才能挂载其他分区
# 将ext4格式的挂载到/mnt
mount /dev/sdaX /mnt
```

#### 2、挂载boot分区

``` shell
# 创建boot目录
mkdir /mnt/boot
# 挂载boot目录，将EFI分区挂载到boot分区
mount /dev/sdaX /mnt/boot 
```

#### 3、挂载其他分区（没有则不挂）

``` shell
#如果有其它分区，分别进行挂载，例如home分区
mkdir /mnt/home
mount /dev/sdaX /mnt/home
```

#### 4、检查挂载是否成功

如果/mnt/boot与/mnt目录大小相同，需要先挂载/mnt再挂载/mnt/boot

``` shell
# 成功样例
lsblk -f
sda1 vfat FAT32  581.9M /mnt/boot
sda2 swap 1             [swap]
sda3 ext4 1.0    431.7G /mnt
```

## 开始系统安装

### 一、连接网络

#### 1、连接wifi

验证能ping通archlinux.com，确保自己能联网，设置动态IP

（1）使用手机USB联网：手机开启USB共享，输入命令dhcpcd

（2）使用wifi-menu：使用wifi-menu命令，进入图形界面联网

（3）使用iwctl（推荐）：

- iwctl：进入命令行
- device list：列出设备名
- station wlan0 scan：扫描网络
- station wlan0 get-networks：列出网络
- station wlan0 connect 名称：连接网络
- station list：连接情况
- exit：退出

#### 2、设置网络同步时间

命令：`timedatectl set-ntp true`

#### 3、添加中国源（非必须）

加快系统安装速度

``` shell
# 禁止更新，不禁止会更新掉自己设施的源地址
systemctl stop reflector.service

# 修改软件源，把中国地址源地址放到前面
# 可以使用nano系统自带编辑器
vi /etc/pacman.d/mirrorlist
```

#### 4、更新源

只同步仓库：`pacman -Syy` 

### 二、安装命令

- 联网软件：

  iwd、dhcpcd（基础）、NetworkManager、iproute2

- 登录的shell：zsh

- linux固件：linux、linux-firmware

- 其他软件：

  bash-completion：命令补全

  man：帮助手册

  git：

  wget：网络下载

  openssh：远程登录

  vim：编辑工具

  sudo：切换root权限

``` shell
# 最小化安装，会缺少基本的软件
pacstrap /mnt base base-devel
# 基础安装
pacstrap /mnt base base-devel linux linux-firmware
# 安装大部分软件-使用dhcpcd\iwd联网（推荐）
pacstrap /mnt base base-devel linux linux-firmware dhcpcd iwd vim sudo bash-completion iproute2 openssh man git wget zsh
# 安装大部分软件-使用networkmanager联网（推荐）
pacstrap /mnt base base-devel linux linux-firmware networkmanager vim sudo bash-completion iproute2 openssh man git wget zsh
```

### 三、生成fstab文件

命令：`genfstab -U /mnt >> /mnt/etc/fstab` 

查看：`cat /mnt/etc/fstab`

- 注意查看swap、vfat、ext4这几个文件类型，以及所有的分区是否都正常存在

### 五、切换系统

命令：`arch-chroot /mnt`  

## 配置系统

### 一、设置时区

```shell
ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
# 设置硬件时间
hwclock --systohc 
```

### 二、配置语言环境

``` shell
vi /etc/locale.gen
# 去掉 ‘#’ 注释
zh-CN utf-8
en-us utf-8

# 执行命令，更新
# locale.conf文件是全局设置，在这里设成中文或者其他非英语环境，桌面环境下会正常显示，但是命令行模式下会变成乱码。中文的问题在后面用其他方法解决。
locale-gen

# 向locale.conf添加语句
echo LANG=en_US.UTF-8 > /etc/locale.conf
```

### 三、修改hosts、hostname

1、创建/etc/hosts文件（不添加localdomain有可能会造成无法联网）

``` shell
127.0.0.1 localhost
::1       localhost
127.0.0.1 localhost.localdomain localhost
```

2、新建主机名

命令：`echo 主机名 > /etc/hostname`

### 五、修改root密码

``` shell
# 修改root密码
passwd root
```

### 六、安装CPU微码

``` shell
# inter的CPU需要安装，cpu微码补丁
pacman -S intel-ucode

# amd的CPU
pacman -S amd-ucode 

# 多系统安装
pacman -S os-prober
```

## 安装引导程序

grub是一个引导器，同时支持UEFI启动、BIOS启动、还支持Windows系统。

### 启动中国源加快程序下载（选用）

参考：联网 $\to$  三、配置中国源

### 一、BIOS（不用）

``` shell
#安装grub命令
pacman -S grub    

# 将引导程序安装到E
# --target=i386-pc 32位系统，默认64位
grub-install /dev/sdaX  

# 配置
grub-mkconfig -o /boot/grub/grub.cfg   
```

### 二、UEFI安装（推荐）

#### 1、安装引导软件

命令：`pacman -S grub efibootmgr` 

#### 2、写入硬盘引导区

**如果提示系统不是EFI需要退出当前系统到U盘中（命令：exit）重写设置磁盘挂载目录**

如果出现错误也可退出当前系统，重新配置（命令：exit）

``` shell
# 参数说明：
# --target=x86_64-efi：安装64位引导文件，efi引导方式
# --efi-directory=/boot：挂载EFI系统分区的目录（根据前面配置设置）
# --bootloader-id=GRUB：UEFI启动菜单选项
grub-install 
	--target=x86_64-efi 
	--efi-directory=/boot 
	--bootloader-id=GRUB
```

#### 3、生成引导文件

`grub-mkconfig -o /boot/grub/grub.cfg`

## 最后-完成

``` shell
# 退出chroot到安装环境
exit 
# 取消挂载 
umount -R /mnt 
# 重启
reboot 
```

## 常见安装错误

### 1、invalid or corrupted package (PGP signature)

``` shell
# 删除gnupg目录及其文件
sudo rm -R /etc/pacman.d/gnupg/ 
sudo pacman-key --init
sudo pacman-key --populate archlinux
sudo pacman-key --populate archlinuxcn
```

### 2、failed to commit transaction (invalid or corrupted package)

``` shell
pacman -Sy archlinux-keyring && pacman -Su
```

### 3、archlinuxcn.gpg不存在

选择PGP signature或者更新指定key

``` shell
pacman -S archlinuxcn-keyring
pacman -Syy
```

## 

## 联网

错误：Temporary failure in name resolution

解决：dhcpcd没有开启

### 一、dhcpcd-必须配置项

``` shell
# 必须使用手机、网线或者其他物理设备
# 安装的软件
pacman -S dhcpcd

# archlinux安装后无法联网，检查解决方法
# 查看网卡名称，如enp4s0或eth0
ip link 
# 启动网卡
ip link set enp4s0 up 
# 自动配置有线网络
dhcpcd 网卡名 
# 配置开机启动有线网络
systemctl enable dhcpcd@网卡名
```

### 二、联网程序

#### 1、iwctl-可选

``` shell
# 安装命令
pacman -S iwd
# 开启iwd服务
systemctl start iwd

# 进入iwd
iwctl
# 列出设备名
device list
# 扫描网络
station wlan0 scan
# 列出网络
station wlan0 get-networks
# 连接网络
station wlan0 connect 名称
# 查看连接状态
station list
#退出
exit

# 开机自启动
systemctl enable iwd
```

常见问题

1、device list 输出的Powered字段为off（断电）

2、device list 输出为空

``` shell
# 检查网卡信息
ip link
# 启动网卡
ip link set 网卡名 up
```

#### 2、NetworkManager-可选

``` shell
# 安装命令
pacman -S NetworkManager

# 启动
NetworkManager 
# 图形界面配置网络
nmtui
# 开机启动
systemctl enable NetworkManager
systemctl start NetworkManager
```

### 三、配置中国源

可去中科大镜像、网易开源镜像、清华开源镜像获取最新地址

``` shell
# vim /etc/pacman.conf
# 1、搜索Color，彩色提示功能
# 2、搜索[multilib],去掉注释
# 3、添加源
[archlinux]
Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
Server = http://mirrors.163.com/archlinux-cn/$arch
```

添加源成功后运行`pacman -Syyu`命令，可以看到archlinux，multilib库在更新

## 
