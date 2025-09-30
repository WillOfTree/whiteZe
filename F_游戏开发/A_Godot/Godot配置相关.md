# 配置

## 不同游戏设置数据

#### Ⅰ、Android设置

| Key                                                       | Value                                                        |
| --------------------------------------------------------- | ------------------------------------------------------------ |
| 游戏界面尺寸：19.5：9                                     | 宽度：360<br/>高度：780                                      |
| 游戏界面尺寸（放大）                                      | 宽度：540<br/>高度：1170<br/>窗口宽度覆盖：360<br/>窗口高度覆盖：780 |
| 模式                                                      | 拉伸模式：canvas_items<br/>比例：expand                      |
| 异形屏幕问题                                              | 锚点全屏$\to$Control \ 锚点偏移$\to$ 顶：1170$\times$0.06    |
| 元素居中                                                  | 新建一个control节点$\to$设置锚点 \ 居中 $\to$ 将需要居中的元素（位置xy为0），变成其子节点 |
| 设置app朝向                                               | 项目$\to$显示$\to$窗口$\to$手持设备、朝向：（Landscape横屏，portralt竖屏） |
| 设置APP游戏图标：<.png>格式即可<br>项目$\to$配置$\to$图标 | 导出$\to$启动器图标$\to$Main 192$\times$192<br/>导出$\to$启动器图标$\to$Adaptive Foreground 432x432<br/>导出$\to$启动器图标$\to$Adaptive Background_432x432 |

#### Ⅱ、windows常用配置

| KEy                        | VALUE                                                        |
| -------------------------- | ------------------------------------------------------------ |
| 原图大小                   | 3200 $\times$ 2400                                           |
| 画面分辨率（视口大小）     | 640$\times$360                                               |
| 窗口大小：（窗口覆盖大小） | 1920$\times$1080：640$\times$360的3倍<br>1280$\times$720：640$\times$360的2倍 |
| 拉伸模式                   | canvas_items                                                 |
| 像素画面模糊               | $项目\to 常规\to 渲染\to 纹理\to 画布纹理\to 默认纹理:Nearest$ |

#### Ⅲ、游戏人物大小

星露谷游戏大小

1. 画布：180$\times$320pix
2. 物品植物（基础单位）：16$\times$16pix
3. 角色大小（成人）：14$\times$29pix-2个基础单位大小

风来之国大小

1.  人物大小（成人）：33$\times$65pix
2.  人物大小（小朋友）：33$\times$44pix
3.  树：2倍成人、3倍成人

#### Ⅳ、自动图块

1. 需要64x96像素大小，平铺，内拐角
2. 192\*192=树木 - 画布大小384\*216 ,树木要缩小到05~0.4，0.4是成人大小
3. 0.4=76*76，
4. 人物：64*64
5. 320*240

## 开发环境配置

### 一、win-SCons配置

环境配置

1. 下载Godot可执行文件

   注意：Godot可执行文件版本要与godot-cpp版本相同

2. 下载Godot-cpp源文件：[godot-cpp地址](https://github.com/godotengine/godot-cpp) 

   注意00：要下载godot-cpp项目，不是Godot的源码

   注意01：godot-cpp版本要与Godot可执行文件版本相同

3. 下载安装python（不建议使用微软商店安装）

   设置环境变量

4. 使用python安装SCons 

   > SCons是由python编写的自动化构建工具

   安装命令：`pip install SCons`  

   测试命令：`scons -v` 

5. 下载安装MSYS2

   下载路径：[Releases · niXman/mingw-builds-binaries (github.com)](https://github.com/niXman/mingw-builds-binaries/releases) 

   | 版本参数 | x86_64       | win32       | seh                         | msvcrt                                     | ucrt                                 | posix      |
   | -------- | ------------ | ----------- | --------------------------- | ------------------------------------------ | ------------------------------------ | ---------- |
   | 说明     | 64位操作系统 | windows程序 | 异常处理模型，无脑选seh即可 | 是一个过时的C++运行库，主要是C99之前的标准 | 是一个通用的C运行库，支持最新C++语法 | 可移植版本 |

6. 运行程序：MSYS2 MSYS

   更新：`pacman -Syu`

   安装GCC和make：`pacman -S --needed base-devel mingw-w64-x86_64-toolchain` 

   设置环境变量，GCC位置：`msys64\mingw64\bin` 

   验证命令：`gcc -v` 

新建项目目录

```shell
godot_project/
├── bin/                  # 编译后的可执行文件
├── src/                  # 项目源码
│   ├── core/             # 核心逻辑（与引擎无关的代码）
│   │   ├── math/         # 数学工具类
│   │   ├── utils/        # 通用工具类
│   │   └── core.cpp      # 核心逻辑实现
│   ├── game/             # 游戏逻辑
│   │   ├── entities/     # 游戏实体（角色、敌人等）
│   │   ├── levels/       # 关卡逻辑
│   │   └── game.cpp      # 游戏主逻辑
│   ├── ui/               # 用户界面
│   │   ├── widgets/      # 自定义UI组件
│   │   └── ui.cpp        # UI逻辑
│   ├── modules/          # Godot C++模块
│   │   ├── my_module/    # 自定义模块
│   │   │   ├── SCsub     # 模块构建配置
│   │   │   ├── register_types.cpp  # 模块注册
│   │   │   └── my_class.cpp        # 自定义类实现
│   │   └── other_module/ # 其他模块
│   ├── third_party/      # 第三方库
│   │   └── some_lib/     # 第三方库源码或头文件
│   └── main.cpp          # 程序入口
├── assets/               # 游戏资源
│   ├── textures/         # 纹理
│   ├── sounds/           # 音效
│   ├── fonts/            # 字体
│   └── scenes/           # Godot场景文件
├── docs/                 # 项目文档
│   ├── design/           # 设计文档
│   ├── api/              # API文档
│   └── README.md         # 项目说明
├── tests/                # 单元测试
│   ├── core/             # 核心逻辑测试
│   ├── game/             # 游戏逻辑测试
│   └── ui/               # UI测试
├── scripts/              # 构建脚本或其他脚本
│   ├── build.sh          # 构建脚本
│   └── deploy.sh         # 部署脚本
├── .gitignore            # Git忽略文件
├── SConstruct            # Godot构建配置
└── README.md             # 项目说明
```

最简单项目目录

``` shell
# 项目根目录
 ├─ demo `Godot项目目录`
 │  └─bin `dll文件目录` 
 │     └─example.gdextension #扩展启动文件
 |
 ├─Godot-cpp `Godot源码目录`
 ├─src `C++代码目录` 
 │  ├─register_types.cpp # 注册文件
 │  ├─register_types.h   # 注册文件
 │  ├─test.cpp # 开发代码
 │  └─test.h   # 开发代码
 └─SConstruct  # SCons构建脚本
```

编写代码

1. 参考SConstruct注释
2. 编写C++代码

生成动态链接库（.dll）

1. 切换到目录：SConstruct文件所在目录
2. 运行命令：`SCons -j6 -Q platform=windows`  

修改.gdextension

1. 复制生成的.dll文件到example.gdextension文件指定的位置

   若SConstruct中已经设置好路径，则不用复制

2. example.gdextension

   example名字可以修改

   .gdextension不可修改

3. 可参考文件：

   - `godot-cpp/test/example.gdextension` 
   - `godot-cpp/test/project/example.gdextension` 

``` shell
[configuration]
# entry_symbol就是register_types.cpp中example_library_init函数名
entry_symbol = "example_library_init"
# Godot4.1版本以上必须有的参数
compatibility_minimum = "4.1"

[libraries]
# 步骤5生成的lib路径
windows.debug.x86_64 = "res://libgodot.debug.x86_64.lib"
```

### 二、vscode编辑器设置

安装软件

1. 安装vscode的C/C++扩展

2. 安装LLDB扩展（CodeLLDB）

3. 安装Task Explorer：用于只编译不运行并不是必须项

4. 安装GCC编译器（配置编译器路径，若是没有提示）

   下载路径：[Releases · niXman/mingw-builds-binaries (github.com)](https://github.com/niXman/mingw-builds-binaries/releases) 

   验证命令：`gcc --version` 

配置构建任务文件：task.json

- 创建task.json文件：$Ctrl + Shift + P\to输入:configure Task\to 选择:task.json\to 选择:other$ 

``` json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build", // launch.json中配置对应
            "type": "shell", // 在shell中启动
            "command": "scons", //执行命令
            "args": [ // 命令参数
                "-j12",
                "target=template_debug", //debug设置
                "debug_symbols=yes"//debug设置
                "no_run=yes" // 只编译不运行
            ]
        }
    ]
}
```

配置运行和调试文件：launch.json

- 运行$Debug\to LLDB$ 创建launch.json
- 若不使用调试，可以不配置launch.json

``` json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug", // debug中显示的名称
            "type": "lldb",
            "preLaunchTask":"build",// 执行上一步的操作task.json
            "request": "launch",
            // Godot可执行文件的位置，C:\\User\\Godot.exe
            "program": "${workspaceFolder}/<executable file>",
            // 要编译的项目目录
            "args": ["--editor","--path","C:\\user\\demo"],
            "cwd": "${workspaceFolder}"
         }
    ]
}
```

配置文件导入目录：VSCode的IntelliSense

- VSCode 的 IntelliSense 依赖于 `c_cpp_properties.json` 文件来配置头文件搜索路径。
- 文件位置：`.vscode/c_cpp_properties.json` 

``` c++
{
    "configurations": [
        {
            "name": "Win32",  // 根据你的操作系统选择
            "includePath": [ // 设置头文件默认打开路径
                "${workspaceFolder}/**",  // 默认包含项目根目录
                "${workspaceFolder}/include",  // 绝对路径
            ],
           "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "D:\\Program Files\\msys64\\mingw64\\bin\\gcc.exe",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

配置完成后，就可使用了

1. 设置Godot主场景

2. 下断点，调试项目

### 三、SCons使用

``` shell
# 推荐
# 多线程编译-6是6核应与CPU核心相同
SCons -j12 platform=windows  

# 默认去寻找VS的编译环境，找不到会寻找MinGW的编译环境
scons platform=windows  

# no_run参数：编译，不运行
scons platform=windows no_run=yes 

#-- 用不到的命令
# 强制使用mingw编译
scons platform=windows use_mingw=yes 
# 软件是64位还是32位置，bits=64 或者 bits=32
scons platform=windows bits=32 
```

## 