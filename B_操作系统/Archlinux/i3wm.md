# i3安装配置

## 一、x说明

liunx图形界面（X系统）主要的几个部分包括

- xorg-server：

  配置文件：/etc/X11/xorg.conf

- 显示器管理器：GDM、lightDM等

- 窗口管理器：i3等桌面

## 二、图形界面

### 1、安装xorg软件包

xorg-server需要配合窗口管理器（i3）或桌面环境（Gnome）来使用

安装命令：`pacman -S xorg-server` 

### 2、驱动安装

``` shell
# 执行如下命令查询显卡类型：
$ lspci | grep -e VGA -e 3D
# 安装对应的驱动，输入下面命令，查看所有开源驱动：
$ pacman -Ss xf86-video

# intel卡：
pacman -S xf86-video-intel #首选
# NVIDIA卡：
pacman -S xf86-video-nouveau #这个是错误的
# AMD卡：
pacman -S xf86-video-ati

# 安装笔记本触摸驱动：
# pacman -S xf86-input-synaptics
```

### 3、启动xorg

常见的文件：

- .xinitrc：xinit和startx会调用这个文件
- .xprofile：在x桌面启动后，窗口管理器运行前调用，xinit和startx会调用这个文件。

#### 方式一：xinit

用途：运行窗口管理器或者桌面环境，可以手动启动xorg

安装命令：`pacman -S xorg-xinit`

相关的配置文件：

- 默认执行的文件为：`~/.xinitrc`
-  找不到执行文件：`/etc/X11/xinit/xinitrc` 

配置流程：

``` shell
# 复制启动文件到当前用户家目录
# xinitrc启动器默认执行文件
cp /etc/X11/xinit/xinitrc ~/.xinitrc、

#-----------------
# .xinitrc中添加命令
#-----------------
# 运行i3
exec i3
# 运行虚化效果
exec compon -b &
# 运行输入法

# 进入桌面
startx
```

#### 方式二：通过显示管理器

详见三、显示管理器（推荐）

## 三、安装I3

``` shell
# i3 包含所有可安装软件，i3gaps与i3wm在2021年前是有区别额，
# 但2021年7月左右，i3gaps被整合到i3wm中，i3gaps不在可用，archlinux中记录如此
pacman -S i3
```

## 四、显示器管理器

安装启动器后即可在登录界面选择i3进行登录

GDM、LightDM、SDDM、LXDM会调用.xprofile和.xinitrc文件

### 1、GDM

GDM会自动安装Gome桌面，登录时选择i3桌面

``` shell
pacman -S gdm
```

设置开机自启动：`systemctl enable gdm.service`

### 2、lightDM（推荐）

``` shell
# 安装启动器
pacman -S lightdm 
# 用于输入密码
pacman -S lightdm-gtk-greeter
```

配置命令：

- `systemctl enable lightdm` ：设置开机启动
- `systemctl start lightdm`：启动
- `systemctl disable lightdm`：关闭
- `systemctl status lightdm`：状态

### 3、sddm

``` shell
# 安装命令
pacman –S sddm
```

配置命令：

- `systemctl enable sddm.service`：设置sddm开机启动

### 4、其他启动器

gdm3和KDM

## 安装终端模拟器

### 1、alacritty

号称最快的终端模拟器，修改i3配置文件中的回车绑定键，将alcritty绑定到回车上

安装命令：`pacman -S alacritty` 

默认配置文件位置（默认不会创建）：`$HOME/.config/alacritty/alacritty.yml`

配置项，参考[alacritty主题库]([GitHub - alacritty/alacritty-theme: Collection of Alacritty color schemes](https://github.com/alacritty/alacritty-theme)) 

``` shell
windown:
	padding:
		x: 10
		y: 5
font:
	size: 15
	normal:
		family:
		style: Regular
	bold:
		family:
```

### 2、urxvt

## 配合i3的软件

### 一、透明软件

可以不装透明软件，因为alacritty、polybar自带背景透明，效果可以

#### 1、compton

``` shell
pacman -S compton 
# 启动
exec --no-startup-id compton -b
# 带有配置文件启动
exec --no-startup-id compton -b --config 路径
```

#### 2、picom

``` shell
# 执行pacman -S compton也会选择
pacman -S picom 
# 启动
# --experimental-backends实验参数，配置文件中填写，这可不写
exec --no-startup-id  -b picom
# 带有配置文件启动
exec --no-startup-id --experimental-backends -b picom --config 路径
```

### 二、状态栏polybar

安装命令：`pacman -S polybar` 

默认配置文件目录：` ~/.config/polybar/config.ini` 

- 这个目录需要自己创建
- polybar带有一个样例配置文件，位置在：` /usr/share/doc/polybar/examples/config.ini` 

修改i3配置文件

- 注释自带的bar 或者i3blocks
- 添加命令：`exec_always --no-startup-id polybar` 

使用polybar-theme配置

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

# 不显示错误
export DISPLAY=:0
```

error:moule/mpd:connect refused

需要安装mpd：`pacman -S mpd` 

配置bar

配置屏幕亮度，ls -1 /sys/class/backlight

设置背景透明：修改参数background #000000

### 三、背景feh

``` shell
# 设置随机壁纸
exec_always --no-startup-id feh --randomize --bg-scale --bg-fill 图片目录
exec_always --no-startup-id feh --bg-scale "/home/background.jpg"
```

### 四、软件启动器

#### 1、rofi

安装命令：`pacman -S rofi` 

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
rofi -show drun

# 添加进i3
bindsym $mod+d exec --no-startup-id rofi -show drun
```

#### 2、dmenu_run

## i3配置

### 一、配置文件

全局配置文件位置：/etc/i3/config 。 

个人配置文件： 

- ~/.config/i3/config（修改这个文件）
- ~/.i3/config

 ### 二、参数说明

``` shell
# ---------------------------------------------------------------------
# 当启动了某些并不支持启动提醒的某脚本或程序时，鼠标指针会逗留在忙碌状态六十秒以上。
# 为防止此现象，凡是 exec 命令都均加 --no-startup-id 后缀，
# ---------------------------------------------------------------------
--no-startup-id

# ----------------------
# exec : 只在开机时执行1次命令
# 例子：
exec --no-startup-id feh

# exec_always：每次重启i3，使用该命令启动的程序都会重新执行一次
# 例子：
exec_always --no-startup-id feh
```

### 三、功能配置

``` shell
# 工作区1:web输出到LVDS1,并重定义名字1:web
# 代表笔记本的 LVDS1, 或是 VGA1, HDMI1, HDMI2
workspace "1:Web" output LVDS1

# 绑定快捷键$mod+1 打开1:web
bindsym $mod+1 workspace 1:Web
bindsym $mod+1 workspace number $ws2

# 将urxvt绑定到工作区2
assign [class="URxvt"] 2
assign [class="URxvt"] $ws2

#设置工作区模式
tabbed 叠加的tab状态
workspace_layout default|stacking|tabbed

# 绑定工作区
for_window [workspace=1] layout default //设置工作区1为默认布局

#生成布局配置
i3-save-tree --workspace your-workspace-name > ~/.config/i3/workspace.json

#配置 i3 conf
exec --no-startup-id "i3-msg '$your-workspace-name; append_layout ~/.config/i3/workspace.json'"
```

## i3命令

``` shell
$mod+enter 开启新窗口
$mod+shift+q 退出
$mod+f 全屏
$mod+Shift+r 重启i3
$Mod+e 默认正常分列  
$Mod+w 标签式布局
$Mod+s 堆叠布局
$mod+v 垂直分割窗口
$mod+h 水平分割窗口
```

## BUG错误

### 问题：i3-sensible-terminal could not find a terminal emulator. Please install one.

解决：没有模拟终端