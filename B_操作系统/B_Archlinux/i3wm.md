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
pacman -S xf86-video-intel 
# NVIDIA卡：
pacman -S xf86-video-nouveau 
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

#### 方式二：通过显示管理器（推荐）

详见：四、显示管理器

## 三、安装I3

``` shell
# i3 包含所有可安装软件，i3gaps与i3wm在2021年前是有区别额，
# 但2021年7月左右，i3gaps被整合到i3wm中，i3gaps不在可用，archlinux中记录如此
# 安装i3wm
pacman -S i3
```

## 四、显示器管理器

安装启动器后即可在登录界面选择i3进行登录

GDM、LightDM、SDDM、LXDM会调用.xprofile和.xinitrc文件

### 1、GDM

GDM会自动安装Gome桌面，**登录时选择i3桌面**

``` shell
pacman -S gdm
```

设置开机自启动：`systemctl enable gdm.service`

### 2、lightDM（推荐）

启动i3时不用做任何操作，默认进入i3

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

### 3、sddm（不好用）

``` shell
# 安装命令
pacman –S sddm
```

设置sddm开机启动：`systemctl enable sddm.service` 

### 4、其他启动器

gdm3和KDM

## 配合i3的软件

这里只记录安装命令，详细软件配置请看archlinux使用.md

### 一、安装终端模拟器

alacritty号称最快的终端模拟器，

1、alacritty（推荐）：`pacman -S alacritty` 

2、urxvt：

### 二、透明软件

alacritty、polybar自带背景透明，特别是alacritty，他自己的透明效果不会透明文本

1、compton：`pacman -S compton `

2、picom（推荐）：`pacman -S picom`

### 二、状态栏

1、polybar：`pacman -S polybar` 

### 三、桌面背景

1、feh：`pacman -S feh` 

### 四、软件启动器

1、rofi（推荐）：`pacman -S rofi` 

2、dmenu_run：

## i3配置

### 一、配置文件

全局配置文件位置：/etc/i3/config 。 

个人配置文件： 

- ~/.config/i3/config（修改这个文件）
- ~/.i3/config

 ### 二、参数说明

``` shell
# 当启动了某些并不支持启动提醒的某脚本或程序时，鼠标指针会逗留在忙碌状态六十秒以上。
# 为防止此现象，凡是 exec 命令都均加 --no-startup-id 后缀，
--no-startup-id

# ----------------------
# exec : 只在开机时执行1次命令
# 例子：
exec --no-startup-id feh

# -----------------------
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

### 四、配置界面

#### 1、边距设置

``` shell
# 内边距
gaps inner 10
# 外边距
gaps outer 10
```

#### 2、可移动窗口

移动浮动窗口。你可以选择其中一个方式，1拖动标题栏，2配置可以通过按键和鼠标点击窗口来移动窗口的浮动调节器

`floating_modifier <Modifier>`

#### 3、浮动窗口大小

``` shell
# -1不限制大小
floating_maximum_size -1 x -1
```

#### 4、边框样式

``` shell
# 无边框
new_window none

# 浮动窗口无边框
new_float none

# 隐藏靠近屏幕边缘的边框
# smart，只有一个窗口隐藏边框，多个不隐藏
hide_edge_borders none|vertical|horizontal|both|smart
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