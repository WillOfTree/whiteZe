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

### 三、配置archlinuxcn源

配置仓库（/etc/pacman.conf）

``` shell
# 自定义配置格式
[archlinuxcn]
# archlinuxcn-mirrorlist可自定义，但路径一定要正确
Include = /etc/pacman.d/archlinuxcn-mirrorlist
```

配置源地址集合：通过网站https://www.archlinux.org/mirrorlist/ 获取所有中国源

在/etc/pacman.d/目录下创建archlinuxcn-mirrorlist文件，并填写中国源

``` shell
# 清华源
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
# 网易源
Server = http://mirrors.163.com/archlinux-cn/$arch
```

更新源命令：`pacman -Syu`

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

查看常见软件错误

#### 1、iwctl-可选

安装dhcpcd

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
# 注意这个命令必须在连接网络后才可以使用，不然会等待网络连接
dhcpcd 网卡名 
# 配置开机启动网络
systemctl enable dhcpcd@网卡名
```

安装iwd

``` shell
# 安装命令
pacman -S iwd
# 开启iwd服务
systemctl start iwd
systemctl enable iwd

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

因为networkmanager版本内置了dhcp，所以不用安装

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

### 六、修改gamema值

安装软件：`pacman -Sy xorg-xrandr` 

修改命令： `xrandr --gamma 1.3:1.3:1.3`

``` shell
#使用～/.xprofile，允许在会话开始前执行xrandr命令
vim ~/.xprofile
# 查看当前屏幕
xrandr

# 修改指定 edp-1-1显示器的gamma值
xrandr --output eDP-1-1 --gamma 0.5:1.0:0.9
xrandr --output eDP-1-1 --gamma 0.9
```

### 七、调整archlinux亮度

#### 1、使用xbacklight

xorg-xbacklight中包含以前的xbacklight软件

安装命令：`pacman -S xorg-xbacklight`

使用命令：（必须使用管理员权限才可以设置）

- 增加亮度：`xbacklight -inc 10`
- 减少亮度：`xbacklight -dec 10` 
- 获取当前亮度：`xbacklight -get`

#### 2、使用light

与xorg-xbacklight功能相同

安装命令：`pacman -S light`  

使用命令：（必须使用管理员权限才可以设置）

- 增加亮度：`light -A 10` 
- 减少亮度：

#### 3、手动控制

``` shell
# 方式一
# 屏幕亮度调到1000，超过屏幕最亮年度，无法保存
echo 1000 > /sys/class/backlight/intel_backlight/brightness 

# 方式二
# 1最亮  0黑
xrandr --output LVDS --brightness 0.5
```

## 配置i3

### 一、alacritty

号称最快的终端模拟器，

①、安装命令：`pacman -S alacritty` 

②、修改i3配置文件中的回车绑定键，将alcritty绑定到回车上

``` shell
bindsym $mod+Enter exec_always --no-startup-id alacritty
```

③、修改配置

- 默认配置文件位置（默认不会创建）：`$HOME/.config/alacritty/alacritty.yml`
- 使用主题，参考Github：[alacritty主题库](https://github.com/alacritty/alacritty-theme) 

``` shell
#引入样例，‘-’ 是必须的语法结构，不能省略
import:
  - ~/.alacritty-colorscheme/themes/breeze.yaml
# 注意，windows参数，只有重启才能看到效果
window:
	# 透明度
	opacity: 0.5
	# 终端内边距
	padding:
		x: 10
		y: 5
```

### 二、picom

默认配置文件位置（默认不会创建）：`~/.config/picom/picom.conf` 

``` shell
# i3配置启动
exec --no-startup-id picom -b
```

### 三、状态栏polybar

#### 1、配置文件

默认配置文件（默认不会创建）：` ~/.config/polybar/config.ini` 

polybar带有一个样例配置文件，位置在：` /usr/share/doc/polybar/examples/config.ini` 

#### 2、修改i3配置文件

- 注释自带的bar 或者i3blocks
- 添加命令：`exec_always --no-startup-id polybar -c 配置文件路径` 

#### 3、polybar-theme配置

``` shell
# 下载主题，或者去github上参考polybar-themes
$ git clone --depth=1 https://github.com/adi1090x/polybar-themes.git
$ cd polybar-themes
$ chmod +x setup.sh
$ ./setup.sh

# 选择主题
cd ~/.config/polybar/
# 运行launch.sh程序
./launch.sh --forest
```

#### 4、配置bar

- 屏幕亮度模块：ls -1 /sys/class/backlight

- 设置背景透明：修改参数background #000000

- 电池模块：

- 边框距离 / 
  border-top-size = 5
  border-left-size = 5
  border-right-size = 5
  
- 内边距:
  
  ; padding-{left,right}
  ; 内边距
  padding = 5

### 四、背景feh

``` shell
# 设置随机壁纸
exec_always --no-startup-id feh --randomize --bg-scale --bg-fill 图片目录
```

### 五、rofi

默认配置文件：`~/.config/rofi/config.rasi` 

使用方法

- **run**: `$PATH`下的应用程序
- **drun**: 桌面程序，一般对应目录`/usr/share/applications`下的`.desktop`文件.
- **window**: 窗口
- **ssh**: 通过ssh链接远程服务器
- **file-browser**: 简单的文件浏览器.
- **keys**: 快捷键.
- **combi**: 混合模式.

``` shell
# 添加进i3
bindsym $mod+d exec --no-startup-id rofi -show drun
```

### 六、网络托盘图标

nm-applet需要networkmanager支持，而且与dhcpcd互斥

命令：`pacman -S network-manager-applet`

启动命令：`nm-applet`

i3wm配置：`exec --no-startup-id nm-applet`

## 系统工具

### 一、shell配置安装

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

可选主题：clond，bira，funky、agnoster //随机主题

更新source ~/.zshrc 

### 二、输入法

1、安装命令

``` shell
# 包含一些框架必须的组件，
# 安装项说明：
# fcitx5-qt：对于qt程序不可用安装
# fxitx5-gtk：对gtk不可用安装
# fcitx5-configtool：图形配置工具
pacman -S fcitx5

# 输入法引擎,包含拼音、双拼、五笔等输入法
pacman -S fcitx5-chinese-addons

# 词库
pacman -S fcitx5-pinyin-zhwiki

# 输入法皮肤
pacman -S fcitx5-material-color
```

2、添加配置

①、防止某些程序不能正常使用中文输入法

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

②、i3添加执行fcitx5：`exec --no-startup-id fcitx5` 

③、运行`fcitx5-configtool`配置中文输入键盘

### 三、蓝牙安装

1、安装方法

``` shell
# 提供蓝牙的协议栈。
pacman -S bluez
# 提供 bluetoothctl 工具。 bluetoothctl 蓝牙终端
pacman -S bluez-utils
# 蓝牙音频驱动
pacman -S pulseaudio-bluetooth
# 开机启动蓝牙服务
systemctl Start bluetooth
systemctl enable bluetooth
```

2、蓝牙图形界面

``` shell
# 图形界面一
# 安装命令
sudo pacman -S bluedevil
# 进入图像界面
bluedevi-wizard

# 图形界面二
sudo pacman -S blueman
```

### 四、声音

i3中修改语音控制参数

``` shell
pacman -S alsa-utils
```

### 六、安装播放器mplayer

安装：`pacman -S mplayer smplayer mencoder`

- mencoder：简单的解码器
- Smplayer：是前端页面，并没有播放解码功能，需要mplayer支持
- mplayer：需要配置播放器是mplayer还是mpv，在设置里可以看到选项，默认是指定一个第三方路径，没有解码器会播放失败

Mplayer 

错误一：

mplayer: could not connect to socket

mplayer: No such file or directory

Failed to open LIRC support. You will not be able to use your remote control

没有远程控制器，一般禁用即可

配置文件： ~/.mplayer/config 
加入lirc=no

错误二：
接下来需要安装解码器。
从下面的网页下载一个最新的解码器。
http://www1.mplayerhq.hu/MPlayer/releases/codecs/
并且把其中的文件解压之后放入/usr/lib/codecs目录下。
tar xvjf all-20061022.tar.bz2 -C /tmp
cp /tmp/all-20061022/* /usr/lib/codecs

## 常用软件

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

### 四、常用软件集合

- pacman -S yaourt
- 网易云
  1. 官方：`pacman -S netease-cloud-music`
  2. 号称最好看的第三方：`yay -S yesplaymusic` 
- 基于Blink引擎的google：`pacman -S chromium`
-  chromium引擎的游览器
  1. edge：`yay -S microsoft-edge-stable-bin`
  2.  google：`pacman -S google-chrome` 
- 代理：`pacmans -S shadowsocks-qt5` 
- 下载器：`pacman -S aria2`

## 常用功能设置项

### 1、调整目录颜色

``` shell
vim ~/.bashrc
# 起别名，使用显示颜色的命令
alias ls=”ls --color”
```

### 2、如何查找i3的class

``` shell
# 运行命令，然后选中想要知道class的窗口
xprop | grep WM_CLASS
```

### 3、切换回终端

- 切换终端：ctrl + alt + F2 
- 退出：ctrl + alt + esc 

### 4、复制粘贴

粘贴软件安装命令：`pacman -S copyq`

- 粘贴：ctrl + shift + v
- 复制：ctrl + shift + c

## 运行第三方程序

### 一、运行windons程序

安装：`pacmac -S wine`

配置，运行命令：`winedfg`

运行：

- 32位运行：`wine xxxx.exe`
- 64位运行：`wine64 xxxxx.exe`

若文字乱码，可以将windows中字体复制到`\usr\share\wine\fonts`目录下，安装文件默认即可

错误二：输入框不显示

`pacman -S winetricks`

执行：`winetricks riched20`

```shell
winetricks corefonts 
winetricks cjkfonts
winetricks msxml6 
winetricks riched20
winetricks riched30
winetricks vcrun6
```

### 二、运行.deb

``` shell
# 安装debtab
yay -S debtap
# 更新debtab库
sudo debtap -u
# 将deb包转换为pkg包
debtap XXXX.deb
# 安装pkg包
pacman -S XXXXXX.pkg
```

### 三、运行.AppImage

``` shell
# 错误，需要安装的软件
pacman -S fuse
# 添加可执行权限
chmod a+x XXXXXX.AppImage
# 运行
./XXXXXXX.AppImage
```

## 开发环境

### 一、安装QT

``` shell
# 可直接使用
# 然后选择base、doc包（qt分为qt5、qt6）
pacman -S qt

# 中文汉化，需要在设置中设置 
pacman -S qt5-translations 
pacman -S qt6-translations 
# 安装IDE
pacman -S qtcreator

# 启动命令
qtcreator启动
```

### 二、使用代理服务

#### 1、clash for windows

图像界面，终端中无法使用

也可以github上的项目进行安装，

``` shell
# 安装命令-没有这个库
pacman -S clash-for-windows-bin

# 方式二、通过github进行下载
# 项目名称：clash-for-windows-pfk
# 下载64位解压运行cfw即可
```

开启clash后还应开启系统代理服务（终端使用代理）

``` shell
# 这个应写成proxy.sh脚本文件，方便运行
# 设置代理：
proxy_set(){
	export http_proxy='http://127.0.0.1:7890'
	export https_proxy='https://127.0.0.1:7890'
	export all_proxy='socks5://127.0.0.1:7890'
	# 并不是必须项
	export ftp_proxy=""
	export no_proxy=""
}


# 同样写成脚本文件
# 取消代理：
proxy_off(){
	unset http_proxy
	unset https_proxy
	unset all_proxy
}

# github设置代理
proxy_git_on(){
	git config --global http.proxy http://127.0.0.1:7890 
	git config --global https.proxy http://127.0.0.1:7890 
}

proxy_git_off(){
	git config --global --unset http.proxy
	git config --global --unset https.proxy
}

# 修改.zshrc文件
# 在文件最后添加source ~/sys_files/proxy.sh
# 运行文件source .zshrc
```

验证：使用ping无法验证，使用wget www.google.com

#### 2、v2raya

``` shell
# 安装命令
pacman -S xray 
pacman -S v2raya
# 启动v2raya
systemctl enable v2raya
```

打开游览器配置v2raya，地址：127.0.0.1：2017

将“全局透明代理”和“规则端口的分流模式”都设置为GFWList，其他设置默认，点击保存并应用，回到主界面，点击导入订阅或节点链接

### 三、安装mysql

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

## 常用字体

### 字体格式说明

- TTF：常用字体类型
- OTF：ttf的升级版本（对于pc来说，有otf用otf，没有就选ttf）
- ttc：微软字体
- EOT：微软的web字体
- SVG：基本是苹果专用字体

### 英文字体集合

#### Iosevka

安装命令：`pacman -S ttc-iosevka`

常用字体名称

- Iosevka / Iosevka Normal：正常字体
- Iosevka Extended：加宽字体
- Iosevka Light：细字体
- Iosevka Bold / Iosevka ExtraBold：正常粗 / 特粗
- Iosevka Italic：斜体

#### Fira code

安装命令：`yay -S otf-fira-code-git`

字体名称：otf-fira-code

#### 微软字体

安装命令：`yay -S ttf-ms-fonts` 

字体名称：ttf-font

### 中文字体集合

#### wqy-microhei

安装命令：`pacman –S wqy-microhei`

#### wqy-zenhei

安装命令：`pacman -S wqy-zenhei ` 

#### wps字体

安装命令：`pacman -S wps-office ttf-wps-fonts` 

### 图标集合

安装命令：yaourt -S otf-font-awesome

## 常见软件错误

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

### 4、Temporary failure in name resolution

原因是域名不能解析或者DNS配置错误

- 添加域名解析：`127.0.0.1 localhost.localdomain localhost` 
- 添加DNS服务：`DNS=8.8.8.8`

## 应急启动

1、准备好archlinux的安装盘，开机时设置u盘启动

2、进入live CD，配置好网络

3、mount /dev/sda3 /mnt

4、arch-chroot /mnt
