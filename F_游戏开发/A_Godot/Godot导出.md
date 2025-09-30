# 导出设置

## 下载构建模板

- 方式一：项目$\to$安装Android构建模板$\to$管理模板$\to$下载安装

- 方式二：从官网下载导出模板（Godot无法下载情况）

  [模板下载地址](https://godotengine.org/download/windows/) $\to$编辑器$\to$管理导出模板$\to$导入下载好的模板文件

- 方式三：编辑器$\to$管理导出模板$\to$下载安装

## Android

一些注意事项

1. 若正常导出软件，安装后无法使用，闪退，可能是架构参数错误，

   优先使用armeabi-v7a选项，

2. 导出模板位置：`C:\Users\binar\AppData\Roaming\Godot\export_templates\4.3.stable`

### 一、基础配置

> 一般只配置一次即可

#### Ⅰ、Java SDK

Java SDK下载安装（安装到C盘可能会出现权限不够问题），建议与Android_SDK安装在统一目录下，例如：D:\Program Files

下载参数说明

- 地址：[Latest Releases | Adoptium](https://adoptium.net/zh-CN/temurin/releases/?variant=openjdk17) 
- 平台：windows 
- 版本：17长期支持版，LTS

#### Ⅱ、Android_SDK

Android_SDK有2种安装方式

1. 使用命令行安装
2. 使用Android Studio安装

使用命令行安装

1. 下载：[Android Studio](https://developer.android.com/studio?hl=zh-cn) 命令行工具（下拉页面，到最后有下载地址）
2. 在D盘根目录创建文件夹Android_SDK（Android_SDK目录不能有空格，不然会产生错误）
3. Android_SDK$\to$将**Android Studio命令行工具**解压到Android_SDK目录

使用Android Studio安装

#### Ⅲ、设置签名

设置签名，使用的是Android_SDK软件

- 切换到Android_SDK目录，打开cmd，运行命令：注意sdkmanager的位置
- ` ./cmdline-tools/bin/sdkmanager --sdk_root="." "platform-tools" "build-tools;34.0.0" "platforms;android-34" "cmdline-tools;latest" "cmake;3.10.2.4988404" "ndk;23.2.8568313"`

#### Ⅳ、配置Godot设置，打开编辑器

1. 编辑器$\to$编辑器设置$\to$导出$\to$Android，Java SDK Path：添加Java_SDK的根目录
2. 编辑器$\to$编辑器设置$\to$导出$\to$Android，Android SDK Path：设置为Android_SDK的根目录

#### Ⅴ、设置环境变量

1. 用户变量 / Path项：添加Java_SDK的bin目录
2. `JAVA_HOME`：Java_SDK的安装目录（填写<Java_SDK> / bin目录即可）
3. `ANDROID_HOME`：其位置为 Android_SDK的根目录（GDExtension 导出模板需要的变量）

重启系统、打开cmd，验证是否正常运行，测试命令：java

### 二、生成.so库文件

#### Ⅰ、运行命令，生成指定的.so扩展

> scons  platform=android  target=目标  arch=架构

- 目标可选：

  template_release：不会有输出信息 

  template_debug：会有输出信息，错误提示

- 架构可选：arm32 / arm64 / x86_64 / x86_32

- 调试常用：

  x86_64生成：`scons platform=android target=template_debug arch=x86_64` 

- 发布常用：

  x86_64：`scons platform=android target=template_release arch=x86_64`

  arm64：`scons platform=android target=template_release arch=arm64`

#### Ⅱ、配置.gdextension文件

- 注意：生成的.so库文件要与 x86_64 / x86_32 / arm64 / arm32标识对应

- 如果要是对应版本错误，有可能会出现以下问题，包括但不限于

  在导出时，Godot可能会崩溃

  安装后无法运行

  安装后闪退

- 安卓参数参数对应

  android.x86_64 $\leftrightarrow$ x86_64架构 、android.x86_32 $\leftrightarrow$ x86_32架构 、

  android.arm32 $\leftrightarrow$ armeabi-v7a架构 、android.arm64 $\leftrightarrow$ arm64-v8a架构

- 优先使用64位架构，32位多数为老机型设计

``` python
[libraries]
# 模拟器版本
android.x86_64 = "res://bin/android/lib.android.template_release.x86_64.so"
android.x86_32 = "res://bin/android/lib.android.template_release.x86_32.so"
# 手机版本
android.arm64 = "res://bin/android/lib.android.template_release.arm64.so"
android.arm32 = "res://bin/android/lib.android.template_release.arm32.so"
```

### 三、导出配置

#### Ⅰ、架构选择

**若用于windows模拟器调试使用**：x86、x86_64架构

| 已生成的.so库的名称                | Godot架构的参数 |
| ---------------------------------- | --------------- |
| android.template_release.x86_32.so | x86             |
| android.template_release.x86_64.so | x86_64          |
| android.template_release.arm32.so  | armeabi-v7a     |
| android.template_release.arm64.so  | arm64-v8a       |

#### Ⅱ、密钥库配置

1. 打开`Jave_JDK/bin`目录下运行命令

   > keytool -v -genkey -keystore tree.keystore -alias tree -keyalg RSA -validity 10000 -dname "CN=tree,O=Android,C=CN" 

   ``-alias`：填写用户名（**默认：tree** ）

   `-validity`：密钥有效期，单位天

   `-keystore`：密钥文件文件名，若不使用此项，也会要求输入密码

   `-storepass`：密码（**默认：tree0000**）

   `-dname`：cn-开发者名称，O-组织名称，C-国家或组织代码

2. 运行命令后，会在当前目录生成**tree.keystore**文件（可将其剪切到其他目录）

3. 在＂$密钥库\to 发布$＂中填写信息

   发布：填写tree.keystore的位置

   发布密码 / 发布用户：填写生成.keystore文件的密钥

   `当前密钥位置：D:\Program Files (x86)\Godot\tree.keystore`

4. 导出即可

### 四、导出常见错误

1. 安装了 **模板** 但是还是显示模板不存在，应检查模板版本，其 **版本号** 应与Godot完全相同才可

2. Godot在导出时崩溃，可能是生成的.so文件与库不对应，应检查名称

3. 导出的程序在实机调试运行时，没有TMainNode节点
   1. 检查.gdextension文件中对应的库是否加载成功

   2. godot-cpp版本、Godot版本、导出模板版本三者是否一致

      Godot编辑器菜单栏$\to$编辑器$\to$管理导出模板$\to$查看当前版本

4. 没有配置密钥库

   > editor/export/editor_export_platform.h:179 - 代码签名: 找不到密钥库，无法导出。

### 五、安卓远程调试

不同安卓模拟器有不同的设置方式（这里使用网易的MuMu模拟器）

> 可查看MuMu模拟器开发者指南
>
> MuMu模拟器$\to$常见问题$\to$开发者指南$\to$ADB连接$\to$MuMu模拟器12如何连接adb

1. 查看ADB端口：设置$\to$问题诊断$\to$ADB诊断

2. 执行连接ADB，进入MuMu目录$\to$shell$\to$adb.exe

   命令：`adb.exe connect 127.0.0.1:<ADB端口>`

3. 回到Godot，Godot右上角$\to$运行旁边的远程调试就可以使用了

### 六、修改Android启动页面

1. 首先应安装导出模板

2. 使用Gradle构建

   删除Godot项目目录下的android目录：`\demo\android`

   安装Android构建模板：任务栏$\to$项目$\to$安装Android构建模板

3. 修改文件：`\demo\android\build\res\values\themes.xml` 

4. 额外的使用“压缩原生库”可减小App大小

style name = "GodotAppMainTheme"选项

``` xml
<!-- 禁用系统状态栏背景绘制（避免与 Godot 界面冲突） -->
<item name="android:windowDrawsSystemBarBackgrounds">false</item>
<!-- 禁止通过滑动关闭应用（防止误操作退出） -->
<item name="android:windowSwipeToDismiss">false</item>
```

style name = "GodotAppSplashTheme" 选项

- @mipmap可以修改res/mipmap目录下的图片
- @mipmap/icon_background：背景层，提供图标的底色或图案。
- @mipmap/icon_foreground：是自适应图标的前景层，通常用于启动画面或应用图标。
- #AARRGGBB：颜色编码，BB为00是透明，FF为不透明（待确定）

``` xml
<!-- 闪屏背景色（必须设置）
  - 可以填写内容：@color/xxx、#AARRGGBB、@mipmap -->
<item name="android:windowSplashScreenBackground">#000000</item>

<!-- 图标  
  - 可以填写内容：@mipmap、@null -->
<item name="windowSplashScreenAnimatedIcon">@mipmap/icon_foreground</item>

<!-- 默认即可 -->
<item name="postSplashScreenTheme">@style/GodotAppMainTheme</item>

<!--（可选）闪屏动画时长（毫秒）
  - 默认值：1000ms -->
<item name="windowSplashScreenAnimationDuration">500</item>
```



## Windows

### 基础配置

1. 下载RC：[Releases · electron/rcedit](https://github.com/electron/rcedit/releases) 
2. 配置RC：编辑器$\to$编辑器设置$\to$Export \ Windows $\to$ rcedit，设置rcedit路径位置