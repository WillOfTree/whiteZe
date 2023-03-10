# 软件安装记录

## 优化系统

### 一、添加普通用户

``` shell
# 添加一个username用户，用户组wheel, -m创建家目录
# 创建完成后，需要登录tree账号并修改一次密码
# 不然可能无法登录
useradd -m -g wheel tree

# 安装sudo,如果安装了就不用安装
pacman -S sudo

# 配置用户可用sudo
vi /etc/sudoers 
# 找到 root ALL=(ALL) ALL 
# 添加 tree ALL=(ALL) ALL
```

### 二、开机启动

systemctl enable NetworkManager

systemctl enable 

### 三、配置archlinuxcn源

配置仓库（/etc/pacman.conf）

``` shell
# 自定义配置格式
[archlinuxcn]
# archlinuxcn-mirrorlist可自定义，但路径一定要正确
Include = /etc/pacman.d/archlinuxcn-mirrorlist
# 官方中国源镜像
Server = https://repo.archlinuxcn.org/$arch
```

配置源地址集合：通过网站https://www.archlinux.org/mirrorlist/ 获取所有中国源

更新源命令：`pacman -Syy`

更新PGP key：`sudo pacman -S archlinuxcn-keyring`  



### 四、更新系统

```shell
# 更新源
$ sudo pacman --sync --refresh
# 更新key
$ sudo pacman --sync --needed archlinux-keyring
# 更新系统
$ sudo pacman --sync --sysupgrade
# 重启
$ sudo reboot
```

### 五、联网

错误：Temporary failure in name resolution

解决：dhcpcd没有开启

#### dhcpcd-必须配置项

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

### 六、声音

``` shell
pacman -S alsa-utils
```

### 七、shell配置安装

``` shell
# 查看当前shell
echo $SHELL
# 查看所有shell
cat /etc/shells
```

#### 1、zsh

①、配置文件：\~/.zshrc（默认）；\~/.zshenv；\~/.zprofile；\~/.zlogin

``` shell
# 安装
pacman -S zsh

# 切换shell，重启后生效
chsh -s /bin/zsh
# 若不知道zsh位置可以使用，进行切换shell
chsh -s `which zsh`
```

②、安装Oh-my-zsh

- 官网：https://ohmyz.sh

使用官网提供的下载安装命令（如果不能下载，可以去github上下载项目）会自动下载安装配置（前提是提前配置了zshrc文件）

③、修改主题，只要名字对，就可正确更好主题

修改ZSH_THEME关键字

可选主题：clond，bira，random  //随机主题

更新source ~/.zshrc 

### 八、修改gamema值

安装软件：`pacman -Sy xorg-xrandr` 

修改命令： `xrandr --gamma 1.3:1.3:1.3`

``` shell
#使用～/.xprofile，允许在会话开始前执行xrandr命令
vim ~/.xprofile
# 查看当前屏幕
xrandr

# 修改指定 edp-1-1显示器的gamma值
xrandr --output eDP-1-1 --gamma 0.5:1.0:0.9
xgamma --output eDP-1-1 --gamma 0.75
```

### 九、调整archlinux亮度

``` shell
# 方式一
# 屏幕亮度调到1000，超过屏幕最亮年度，无法保存
echo 1000 > /sys/class/backlight/intel_backlight/brightness 

# 方式二
# 1最亮  0黑
xrandr --output LVDS --brightness 0.5
```

### 十、输入法

``` shell
# 包含一些框架必须的组件，全选
# 包含fcitx5-qt fxitx5-gtk 输入法模块
# fcitx5-configtool图形配置工具
pacman -S fcitx5-im
# 输入法引擎,包含拼音、双拼、五笔等输入法
pacman -S fcitx5-chinese-addons
# 词库
pacman -S fcitx5-pinyin-moegirl
pacman -S fcitx5-pinyin-zhwiki
# 输入法皮肤-微软外观
pacman -S fcitx5-material-color
```

添加配置，防止某些程序不能正常使用中文输入法

``` shell
# 方式一,使用AUR安装
yay -S fcitx5-input-support

# 方式二
# 文件路径：/etc/environment
# 添加以下代码
GTK_IM_MODULE=fcitx
QT_IM_MODULE=fcitx
XMODIFIERS=@im=fcitx
SDL_IM_MODULE=fcitx
GLFW_IM_MODULE=ibus
```

i3添加执行fcitx5：`exec --u fcitx5`

## 软件安装

### 一、feh桌面背景、图片查看

``` shell
# 安装软件
pacman -S feh
# 设置背景页面
feh --bg-scale “/path/to/image.file”
# 设置随机壁纸
feh --randomize --bg-scale --bg-fill 图片目录
```

### 二、游览器

#### 1、火狐

``` shell
# 安装火狐
pacman -S firefox
# 首先安装中文字体，若还是乱码就安装firefox中文语言包
pacman -S firefox-i18n-zh-cn 
```

配置在全屏浏览模式下保留工具栏和标签栏

- 在Firefox地址栏中输入about:config，回车。
- 找到键值 browser.fullscreen.autohide，双击改为 false 。
- 重启浏览器。

### 三、yay安装

``` shell
git clone https://aur.archlinux.org/yay
cd yay
makepkg -si

# go网站无法访问
export GO111MODULE=on
export GOPROXY=https://goproxy.cn

```



# 6、调整目录颜色

~/.bashrc

alias ls=”ls --color” #起别名

# 8、如何查找i3的class

xprop | grep WM_CLASS

然后点击响应的窗口



# 10、安装QT

pacman -S qt5-base qt5-doc

pacman -S qtcreator 

qtcreator启动

pacman -S qt5-translations //中文汉化，需要在设置中设置

 

# 11、安装mysql

**（1****）安装MariaDb****和其客户端工具**

pacman -S mariadb mariadb-clients

**（2****）MariaDb****的数据目录-****按这个来，目录名称没查**

mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql

**（3****）启动MariaDb**

 systemctl start mysqld

**（4****）为root****用户设置一个新密码**

sudo mysqladmin -u root password '' 

**（5****）尝试登录MariaDb****，如果登录成功，说明配置完成了**

mysql -uroot -p  #默认密码为空

**（6****）如果想要MariaDb****开机自动启动，那么就运行以下命令**

sudo systemctl enable mysqld



# 13、切换回终端

ctrl + alt + F2 切换终端

ctrl + alt + esc 退出

# 15、软件

pacman -S yaourt

**pacman -S netease-cloud-music //****网易云**

pacman -S google-chrome //google

pacmans -S shadowsocks-qt5 //代理

pacman -S wps-office ttf-wps-fonts //wps，字体

yaourt -S otf-font-awesome //图标

pacman -S nautilus //打开文件管理器

pacman -S aria2  //xia

### 常用字体

``` shell
# polybar需要的一些字体
pacman -S ttc-iosevka
pacman -S 
# 中文字体
pacman –S wqy-microhei  
pacman –S wqy-zenhei 
```

# 安装播放器mplayer

Pacman -S mplayer smplayer mencoder

mencoder 简单的解码器

Smplayer 是前端页面，并没有播放解码功能，需要mplayer支持

Smplayer需要配置播放器是mplayer还是mpv，在设置里可以看到选项，默认是指定一个第三方路径，没有解码器会播放失败

 

Mplayer 

错误一：

mplayer: could not connect to socket

mplayer: No such file or directory

Failed to open LIRC support. You will not be able to use your remote control

没有远程控制器，一般禁用即可

```
配置文件： ~/.mplayer/config 
加入lirc=no
 
错误二：
接下来需要安装解码器。
从下面的网页下载一个最新的解码器。
http://www1.mplayerhq.hu/MPlayer/releases/codecs/
并且把其中的文件解压之后放入/usr/lib/codecs目录下。
tar xvjf all-20061022.tar.bz2 -C /tmp
cp /tmp/all-20061022/* /usr/lib/codecs
 
```

# AppImage文件

一个新的全平台软件

前提pacman -S fuse

运行直接加./xxxx.appimage

# 蓝牙

[安装](https://wiki.archlinux.org/title/Install) [bluez](https://archlinux.org/packages/?name=bluez)，这个软件包提供蓝牙的协议栈。

[安装](https://wiki.archlinux.org/title/Install) [bluez-utils](https://archlinux.org/packages/?name=bluez-utils)， 其提供 bluetoothctl 工具。 bluetoothctl 蓝牙终端

2款蓝牙图形界面

sudo pacman -S bluedevil

sudo pacman -S blueman

蓝牙音频驱动

pacman -S pulseaudio-bluetooth

 

通用蓝牙驱动是 btusb 内核模块。[检查](https://wiki.archlinux.org/title/Kernel_module_(简体中文)#获取信息) 模块是否加载了。如果没有就先[加载模块](https://wiki.archlinux.org/title/Kernel_module_(简体中文)#手动加载卸载)。

systemctl [Start/enable](https://wiki.archlinux.org/title/Start/enable) bluetooth.service。

 

需要重启系统

blueman-manage启动程序，首次启动会提示开启应用，确定后会退出，应多次启动

连接成功后可退出blueman-manage程序

这个程序默认开机启动。但经常发生开机后能连接音响，却不是用音响输出声音的情况。

执行

```
$ pulseaudio -k
$ ulseaudio --start
```

 

## 常见软件安装错误

## 1、invalid or corrupted package (PGP signature)

``` shell
# 删除gnupg目录及其文件
sudo rm -R /etc/pacman.d/gnupg/ 
sudo pacman-key --init
sudo pacman-key --populate archlinux
sudo pacman-key --populate archlinuxcn
```

## 2、failed to commit transaction (invalid or corrupted package)

``` shell
pacman -Sy archlinux-keyring && pacman -Su
```

## 3、archlinuxcn.gpg不存在

选择PGP signature或者更新指定key

``` shell
pacman -S archlinuxcn-keyring
pacman -Syy
```

## 