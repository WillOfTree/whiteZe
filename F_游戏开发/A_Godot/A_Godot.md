# Godot使用说明

## 概述

- 版本：4.21
- GDExtension不支持Godot4以下的版本

### 一、C++环境配置

windows版本的dll文件生成：

1. 下载Godot可执行文件

    注意：Godot可执行文件版本要与godot-cpp版本相同

2. 下载Godot-cpp源文件：[godot-cpp](https://github.com/godotengine/godot-cpp) 

    注意：godot-cpp版本要与Godot可执行文件版本相同

3. 下载安装python

4. 使用python安装SCons

    SCons是由python编写的自动化构建工具

    `pip install SCons` 

5. 创建windows静态链接库（.lib）

    1. 切换到Godot-cpp源代码目录下运行cmd

    2. 运行命令

        ``` shell
        # 默认去寻找VS的编译环境，找不到会寻找MinGW的编译环境
        scons platform=windows  
        # 多线程编译-推荐编译的快-6是6核应与CPU核心相同
        scons -j6 platform=windows  
        scons -j6
        
        #-- 用不到的命令
        # 强制使用mingw编译
        scons platform=windows use_mingw=yes 
        # 软件是64位还是32位置，bits=64 或者 bits=32
        scons platform=windows bits=32        
        ```

    3. 生成的文件目录为：Godot-cpp/bin/

6. 新建项目目录：

    - `Test`：项目根目录
    - `Test/gdextension` 
    - `Test/libgodot.debug.x86_64.lib`：步骤5生成的静态连接库
    - `Test/gdextension/godot-cpp`：Godot源码
    - `Test/gdextension/SConstruct`：SCons构建脚本
    - `Test/gdextension/src`：自定义编写的c++代码位置
    - `Test/gdextension/src/register_types.h`：复制Godot/test/src/register_types.h文件
    - `Test/gdextension/src/register_types.cpp`：复制Godot/test/src/register_types.cpp文件

7. 编写SCons脚本：参考SConstruct注释

    默认dll生成位置为SConstruct文件的上级目录

8. 编写C++代码：

    可参考：代码编写 $\to$ 一、C++ $\to$  Ⅰ、Hello world

9. 注册C++代码：

    参考register_types.h与register_types.cpp注释

10. 使用SCons编译，生成共享库 .dll 文件：

     切换到目录：`Test/gdextension` <SConstruct文件所在目录>

     运行命令：`SCons -Q` 

11. 使用Godot创建新工程A

12. 在A新工程根目录下创建example.gdextension文件：

     example.gdextension名字可以修改；.gdextension不可修改

     可参考文件：

     - `Test/gdextension/godot-cpp/test/example.gdextension` 
     - `Test/gdextension/godot-cpp/test/project/example.gdextension` 

     ``` shell
     [configuration]
     # entry_symbol就是register_types.cpp中example_library_init函数名
     entry_symbol = "example_library_init"
     # Godot4.1版本以上必须有的参数
     compatibility_minimum = "4.1"
         
     [libraries]
     # 步骤5生成的lib路径
     windows.debug.x86_64 = "res://libgodot.debug.x86_64.dll"
     ```

13. 复制“步骤11”生成的.dll文件到example.gdextension文件指定的位置

14. 使用Godot$\to$​ 创建node 即可找到test节点

### 二、extension配置

1. `.gdextension`与`.dll`文件是一一对应关系
2. c++语言的注册文件中，函数名应是在项目中独一无二的

### 三、vscode配置

#### Ⅰ、目录结构

根目录 （官方推荐结构）
├─.vscode `VScode配置文件目录`
├─demo `Godot项目目录`
│  └─bin `dll文件目录` 
│         └─example.gdextension
├─godot-cpp `Godot源码目录`
├─src `C++代码目录` 
│    ├─register_types.cpp
│    ├─register_types.h
│    ├─test.cpp
│    └─test.h
└─SConstruct

#### Ⅱ、修改配置文件

1. 安装插件：codeLLDB
2. 查看launch.json、task.json

#### Ⅲ、配置

1. 安装vscode的C/C++扩展

2. 安装GCC编译器（配置编译器路径，若是没有提示）

   [Releases · niXman/mingw-builds-binaries (github.com)](https://github.com/niXman/mingw-builds-binaries/releases)

3. 安装LLDB扩展（CodeLLDB）

4. 创建task.json文件

   $Ctrl + Shift + P\to输入:configure Task\to 选择:task.json\to 选择:other$​ 

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
               ]
           }
       ]
   }
   ```

5. 运行$Debug\to LLDB$ 创建launch.json

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
               "args": ["--path","C:\\user\\demo"],
               "cwd": "${workspaceFolder}"
            }
       ]
   }
   ```

6. 下断点，调试项目

### 四、像素游戏配置

1. 画面放大3倍

    - 设置窗口

      视口高度：1152/3=384

      视口宽度：648/3=216

    - 打开高级模式

      窗口宽度覆盖：1152

      窗口高度覆盖：648

2. 拉伸模式：canvas_items

3. 画面模糊

    $项目\to 通用(General)\to Rendering\to Default Texture Filter:Nearest$ 

### 五、常见错误

> register_types.windows.template_debug.x86_64.obj : error LNK2019: 无法解析的外部符号 "private: \_\_cdecl Test::Test(void)" (??0Test@@AEAA@XZ)，函数 "private: static void * \_\_cdecl godot::ClassDB::_create_instance_func<class Test>(void *)" (??$_create_instance_func@VTest@@@ClassDB@godot@@CAPEAXPEAX@Z) 中引用了该符号
> demo\bin\libcpp.dll : fatal error LNK1120: 1 个无法解析的外部命令
> scons: *** [demo\bin\libcpp.dll] Error 1120

- 必须.cpp中文件必须实现

> core/extension/gdextension.cpp:629 - No GDExtension library found for current OS and architecture (windows.x86_64) in configuration file: res://bin/a.gdextension
> Failed loading resource: res://bin/a.gdextension. Make sure resources have been imported by opening the project in the editor at least once.

- 若确定.lib文件存在，则可能是编译环境错误，Godot的提示并不准确

- scons

- 需要编译godot-cpp文件

- 没有gcc编译环境

- [为 Windows 平台编译 — Godot Engine (4.x) 简体中文文档](https://docs.godotengine.org/zh-cn/4.x/contributing/development/compiling/compiling_for_windows.html)

- ```
  pacman -S mingw-w64-x86_64-python3-pip mingw-w64-x86_64-gcc  \
      mingw-w64-i686-python3-pip mingw-w64-i686-gcc make
  ```

- 安装GCC ，[Win7 / Win10 下 msys64 安装 MinGW-w64 工具链 - Milton - 博客园 (cnblogs.com)](https://www.cnblogs.com/milton/p/11808091.html)

- 验证GCC，gcc -v

## 游戏框架设计

- Godot命名规范：

  文件名，目录名使用蛇形命名法（例如：start_state）

  类名使用大驼峰命名法

### 一、游戏目录

``` shell
# 项目目录
├─assets # 存放外部原始资源，图像、声音、字体等等
|   ├─textures # 图像，纹理
|   └─fonts    # 文件字体
├─entites # 实体，游戏场景中所有可见对象
|   ├─characters # 
|   |   ├─enemies
|   |   └─player
|   └─pickable_object # 可拾取对象
|       ├─equipments
|       └─items
├─components # 组件，与不同的对象配合使用，实现不同行为
|   ├─AI_component # AI组件
│   └─move_component # 移动组件
├─managers # 抽象功能集合
|   ├─fsm # 有限状态机
|   ├─input_handler # 输入处理器，
|   ├─map_manager # 地图管理器，自动生成地图等
│   └─assets
├─scenes # 游戏场景
|   ├─scens_two
│   └─scenes_one
├─UI # 游戏UI相关
|   ├─inventory_window # 背包窗口
|   └─attribute_panel # 属性面板
└─resources # 所有继承godot resource的资源
    ├─map_date # 地图数据
    ├─tile_set # 瓦片集目录
    └─characters # 角色数据
```

### 二、状态机

#### Ⅰ、虚函数状态机

- 使用虚函数实现

``` c++
/*
*
*/
// fsc.h

// state_move.h
```



#### Ⅱ、纯虚函数状态机

- 使用纯虚函数实现

``` c++

```



## 生命周期

1. `_ready`方法，优先初始化子类，再初始化父类
2. 其他生命周期方法，都是优先运行父类再运行子类

## 特殊节点说明

## 一、NodePath

1. NodePath节点是一个特殊的节点

``` c++

```



## 二、Ref<>类

1. Ref<>类可以直接使用

``` c++
```



1. Sprited2D：主要用于图片显示
2. Node：可以用于代码逻辑编写
3. AnimatedSprite2D：用于动画播放，简单物品动画
4. AnimationPlay：Godot所有元素都可以使用它来生成动画，包括场景中来回移动的物体，怪物等
5. collisionShape2D：碰撞体积
6. Area2D：能够检测其他节点的进入和退出，不与其他节点封装
    - worldBoundaryShape2D：可以在一个方向上无线延长的节点
7. RayCast2D：根据设置的箭头进行碰撞检测
    - is_colliding()碰撞检测
8. HboxContainer：横向排列的容器，用于制作角色血条等
9. panelcontainer：为图像提供背景
10. Progressbar：进度条，软件常用
11. TextureProgressbar：进度条，游戏常用，可设置背景
12. canvasLayer：可根据屏幕位置显示
13. marker2d：



## 基本的数据类型

- 不用引用文件，直接使用即可

### 一、Variant

- Godot的万能类型，可以转换为Godot的任意类型
- Variant可以直接转换为其他类型，只有节点使用cast_to方法

``` c++
// 准备一个Variant类型变量
Variant temp = tg.pop_back();

/* 转换样例，cast_to方法 */
// 转换类型到Node *，
// cast_to<目标类型>(待转换的变量);
Node *t = cast_to<Node>(temp);
```

### 二、Dictionary 

``` c++
Dictionary a{
    "xx":12,
}

Dictionary datetime;
datetime[YEAR_KEY] = 2014;
datetime[MONTH_KEY] = 2;
```

### 三、数组

#### Ⅰ、Array

- 普通数组

``` c++
Array args;
args.push_back(p_arg1);
// 升序排列
args.sort();
// 获取数组大小
args.size();
// 从后弹出元素
args.pop_back();
// 从前面弹出元素
args.pop_front();
```

#### Ⅱ、List

- 双链表

``` c++
// Convert arguments to Godot's command-line.
List<String> args;
args.push_back();
```

#### Ⅲ、Vector

- 可变数组

``` c++
Vector<uint8_t> buffer;
buffer.resize(stereo ? wav_count * 2 : wav_count);
Vector<String> drivers;
		drivers.push_back("dummy");
```

### 四、MAP

``` c++
/* Equal to: RBMap<String, Vector<Vector<Variant>>> */
HashMap<String, Array> _signals;

BitMap
```

### 五、JSON

1. Godot内置呢JSON解析方法，不用使用jsoncpp
2. 头文件：`#include <godot_cpp/classes/json.hpp>`

``` c++
/**
 * ModeFlags 
 * FileAccess::READ = 1
 * FileAccess::WRITE = 2
 * FileAccess::READ_WRITE = 3
 * FileAccess::WRITE_READ = 7
**/
FileAccess *f = new FileAccess();
String a = f->open("res://workdiloge/work.json", FileAccess::READ)->get_as_text();

/* json这是字符串类型，可以转换为字符串 */ 
Variant json_s = JSON::parse_string(a);

/* 解析json */
JSON *json_o = new JSON();
// 解析json文本，
json_o->parse(a);
/* 获取json数据 */ 
// 这里temp可以使用array类型
// json的数据类型：
// 		[ {"name":"mali","text":"今天夜色真美"} ]
Array temp = json_o->get_data();
// 这里可以将{}文本转换为指点类型
Dictionary c = b[0];
// 调用字典方法，NULL是默认数据
c.get("name", NULL));
   
```

## 对象类

### 一、Sprited2D

``` c++
// 获取要修改的节点
Sprite2D *root11 = get_node<Sprite2D>
    ("/root/Node2D/Test");
// 设置新纹理
root11->set_texture(i3);
// 设置中心点
root11->set_centered(false);
// 平移
Vector2 p = Vector2(100, 100);
root11->set_offset(p);
```

### 三、AnimatedSprite2D

- 动画播放类
- 在Godot添加自定义动画类，设置动画效果

``` c++
// 获取节点，注意是Animatedsprite2d类型
AnimatedSprite2D *a_s = get_node<AnimatedSprite2D>("/root/Node2D/A_node2d");
// 调用播放动画方法，a是Godot已经设置好的动画
a_s->play("a");
a_s->pause();//暂停
a_s->stop();//停止
a_s->is_playing();//状态
```

### 四、AnimationPlay

- 通过单张png，生成动画
- AnimationPlay下添加sprite2d节点

### 五、AnimationTree

- 头文件

    `#include <godot_cpp/classes/animation_tree.hpp>` 

    `#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>` 

- AnimationRootNode：动画树节点的基本资源。通常，它不会直接使用，

- AnimationNodeBlendTree:：包含多个混合类型节点，

- AnimationNodeBlenderSpace1D: 1D空间混合

- AnimationNodeBlenderSpace2d: 在2D空间中旋转根节点

- AnimationNodeStateMachine：动画节点状态机

- AnimationNodeAnimation: 从列表中选择一个动画播放，这是最简单的根节点类型，通常不直接作为Tree Root根节点使用。

- 注意：AnimationPlay不能设置自动播放，但要设置循环

- 注意：状态机（连接线）要设置enable，如果设置auto会出现意外情况，使用travel控制播放动画

``` c++
/* 获取节点 */
// 获取动画节点
AnimationPlayer *m_animatePL = get_node<AnimationPlayer>("AnimationPlayer");
// 获取动画树节点
AnimationTree m_animateTr = get_node<AnimationTree>("../../AnimationTree");

/* 获取AnimationNodeStateMachineplayback属性 */
// 这个属性地址，可以在Godot界面查找
Variant b = m_animateTr->get("parameters/playback");
// 转为AnimationNodeStateMachineplayback
m_animationState = cast_to<AnimationNodeStateMachinePlayback>(b);

/* 启动动画树 */
// 字符串可在godot界面查找
// aoix是Input向量
m_animateTr->set("parameters/idle/blend_position", aoix);
m_animateTr->set("parameters/run/blend_position", aoix);
// 设置播放动画
m_animationState->travel("run");
```



### 六、AudioStreamPlayer

- 音频流播放器
- AudioStreamPlayer2D具有距离属性的音效

``` c++
#include <godot_cpp/classes/audio_stream_player.hpp>
/* 代码加载 */
// 加载音频资源
ResourceLoader *R = new ResourceLoader();
Ref<AudioStream> bg = R->load("res://02.mp3","AudioStream");
// 音频类
AudioStreamPlayer *a = new AudioStreamPlayer();
// 加载音频
a->set_stream(k_01);
// 播放音乐，每次从头开始播放
a->play();
// 继续播放
a->set_stream_paused(false);
// 暂停播放
a->set_stream_paused(true);
```

### 七、Vector2

- 头文件：不需要引用

- 向量A - 向量B = B指向A的向量

    > To find a vector pointing from A to B, use B - A.


``` c++
/* 创建一个向量 */
// Vector(x轴，y轴)
Vector2 a = Vector(100, 100);
// 设置x，y向量
a.x = 50;
a.y = 50;

/* a向量是否为0向量 */ 
a.is_zero_approx();
/* 向量单位化 */ 
// 得到一个向量的方向
a.normalized();

/* 设置a走向B的向量 */ 
// 向量（方向和大小），每帧的增量
a.move_toward(B, C);

/* 在一个范围内 */ 
Vector2 direction = m_startPosition - position;
if(direction.length() > 200){}
// 返回从该向量指向 to 的归一化向量。相当于使用 (b - a).normalized()。
direction_to(to: Vector2) const
// 返回该向量与 to 之间的距离。
distance_to(to: Vector2);
```

### 八、CharacterBody2D

``` c++
// 设置当前向量
set_velocity(a);
// move_and_collide不能沿着墙滑动
// 根据set_velocity设定，自动进行碰撞体积
move_and_slide();// 可以沿着墙滑动
```

### 九、Random

- 头文件：`#include <godot_cpp/classes/random_number_generator.hpp>` 
- 文件utility_functions同样包含随机方法的静态方法

``` c++
/* Utility_functions */

// 随机方向
RandomNumberGenerator *r = new RandomNumberGenerator();
// 随机取得-1，0，1
float x = r->randf_range(-1, 1);
float y = r->randf_range(-1, 1);
```



### 十、Area2D

1. 层（Collision/Layer）：隶属层级（显示图像、遮盖等效果）
2. 遮罩（Collision/Mask）：碰撞层级（物理碰撞）

``` c++
```

攻击框

- 都是继承的Area2D节点，Hurtbox,
- 需要定义图层

### 十一、utility_functions

- 包含很多常用方法
- 头文件：`#include <godot_cpp/variant/utility_functions.hpp>`

``` c++
// 打印方法
UtilityFunctions::print("hello world");
UtilityFunctions::print("hello world");
// double
UtilityFunctions::randf();
// int64_t
UtilityFunctions::randi_range(int64_t from, int64_t to);
// double
UtilityFunctions::randf_range(double from, double to);
// double
UtilityFunctions::randfn(double mean, double deviation);
// Variant
UtilityFunctions::type_convert(const Variant &variant, int64_t type);
```

### 十二、Node

1. 大部分节点的父节点，Node的方法一般可用直接使用

2. 注意：

    节点操作都应在_ready之后的生命周期使用

    get_node()中必须是“”，若是‘’，则会发生未知错误

``` c++
/* 设置位置坐标 */ 
// 获取当前位置
// Node中的方法
Vector2 p = get_position();
/* 获取当前向量速度 */ 
vector2 a = get_velocity();

/* 查找节点 */
// 只能获取子节点,不能得到父节点
get_node<Node>("xx");
// 通过相对路径，可以获取子节点的子节点
get_node<Node>("xxx/vvv");  
// 获取父节点
get_node<Node>("..");
get_parent();
// find_child会对节点进行遍历，太多节点会影响速度
Node *c0 = find_child("Test");

/*得到当前所有子节点*/ 
Array b = get_children();
UtilityFunctions::print(b[0].get_type());

/* 获取节点 */
// 获取所有节点数量
get_child_count();
get_child("节点序号");

/* 删除节点 */
c0->queue_free();
```

### 十三、SceneTree

1. 头节点：`#include <godot_cpp/classes/scene_tree.hpp>`

获取整个节点数：

``` c++
/* 获取整个节点树 */
// 方法1
Node *root = Node::get_tree()->get_current_scene();
// 方法2
SceneTree *r = Node::get_tree();
Node *root = r->get_current_scene();
//
SceneTree::get_singleton()->initialize();
```

场景切换

``` c
// 获取场景树
SceneTree *t = Node::get_tree();
// 切换场景
t->change_scene_to_file("res://game2.tscn");
```



### 十五、Object

1. 所以类的基类，这意味Object中的方法可以直接调用

``` c
Object *obj = memnew(Object);
INFO(obj);

/* 连接方法
connect("信号名称", Callable(类, "触发方法"));
*/ 
connect("game_stop", Callable(this, "game_stop_met"));
// get_parent父类方法
connect("enemy_default_weapon_attack", Callable(get_parent(), "enemy_bee_attack"));
```

### 十六、Path2D

- 使用PATH2d在地图上画出路径
- 创建Pathfollow2d节点，pathfollow2d节点会根据path2d设置的路径行走

``` c
PathFollow2D *p = get_node<PathFollow2D>("/root/Node2D/Path2D/PathFollow2D");
// 设置移动距离，单位像素
p->set_progress(500);

// 获取当前移动坐标
Vector2 v = p->get_position();
Sprite2D *s = get_node<Sprite2D>("/root/Node2D/Sprite2D");
// 将坐标设置给精灵
s->set_position(v);
```

### 十七、RayCast2D

- 射线投射节点，用于检测碰撞不可见射线

``` c++
is_colliding(); //检测是否发生碰撞
```

### Engine

- 头文件：`#include <godot_cpp/classes/engine.hpp>` 

#### Ⅰ、设置进程模式

- 设置这个，会解决按键bug
- 注意：不能在CharacterBody2D节点中使用

``` c++
#include <godot_cpp/classes/engine.hpp>
Test::Test(){
    if(Engine::get_singleton()->is_editor_hint()) {
        // 在编辑器中，禁用_process函数
        set_process_mode(
            Node::ProcessMode::PROCESS_MODE_DISABLED);

        UtilityFunctions::print("set ok");
    }
}

```

#### Ⅱ、从项目中读取配置

- 可以解决 this inputmap 不存在bug

``` c++
#include <godot_cpp/classes/input.hpp>
// 从Godot中的设置加载设置
InputMap* map = InputMap::get_singleton();  
map->load_from_project_settings();
```

#### Ⅲ、获取重力速度

``` c++
#include <godot_cpp/classes/project_settings.hpp>
// 获取重力加速度
Variant g = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
// 保持重力速度
this->m_gravity = (float)g;
```

#### Ⅳ、减速状态

``` c++
#include <godot_cpp/classes/engine.hpp>
# 获取Engine实例，Engine::get_singleton()  
// Engine::get_singleton()->set_time_scale(0.5);
Engine *e = Engine::get_singleton();
e->set_time_scale(3);
```



## 功能实现

### 一、Hello world

头文件

``` c++
#ifndef TEST_H
#define TEST_H

#include <godot_cpp/classes/sprite2d.hpp>
using namespace godot;
class Test: public Sprite2D {
    /*
    * 定义一个宏，
    * 	Test：当前你的类名
    * 	Node3D：当前类继承的类名
    */ 
    GDCLASS (Test, Sprite2D);
    Test();
    ~Test();
    // 防止出现意外bug，定义一个方法
    protected:
    	static void _bind_methods();
}
#endif
```

.cpp文件

``` c++
#include "test.h"
#include <godot_cpp/variant/utility_functions.hpp>
void Test::_bind_methods(){}
Test::Test(){
    UtilityFunctions::print("hello world");
}
Test::~Test(){
    UtilityFunctions::print("bye");
}
```

### 二、生命周期

- 不好用

- Node节点的方法

- 选哟虚拟键位的映射

- _process每一帧都运行；delta = 1/帧数

  移动距离$\times$delta可以使移动距离与帧率无关；1$\times$delta可以简单理解为每秒移动1像素

``` c++
void T_AudioStreamPlayer::_input(const Ref<InputEvent> &event){
    //UtilityFunctions::print("_input");
	// 判断p是否按下
    if(event->is_action_pressed("p")){
        UtilityFunctions::print("stop");
    }  
    //C++示例方法，转换inputevent
    const InputEventKey *key_event = Object::cast_to<const InputEventKey>(*event);
    
}

/* _unhandled_key_input */
void T_CharacterBody2D::_unhandled_key_input(const Ref<InputEvent> &event){}
```



- 本身是Node节点的属性

``` c++
public:
// C++的方法与GD脚本的方法函数名相同
/* 节点添加到节点树时调用
 * 每一个节点加入树都会调用
 */ 
void _EnterTree();
/* 所有节点加载完成后调用
 * 从最后一个节点的Ready方法依次调用
 * 初始化一般写在这里
 */
void _Ready(); 
/* 每一帧都调用这个方法
 * delta：帧与帧间隔的时间
 */ 
void _Process(double delta); 
/* 物理计算一次调用
 * 一般调用物理引擎时使用
 */
void _physicProcess(double delta);
void _exitTree(); //节点销毁调用
/* 只要键盘或鼠标按动，就触发当前方法 */
void _input(const Ref<InputEvent> &event);//输入按键调用
```

### 三、绑定方法

#### Ⅰ、自定义节点属性

- 需要重新打开Godot，才能显示属性
- 中文会乱码

设置自定义节点属性名称

``` c++
/* ClassDB::add_property("类名",
 *     PropertyInfo(Variant::FLOAT, "属性名称"),
 *     "触发的设置方法名",
 *     "触发的获取方法名");
 * PropertyInfo有额外的参数
 *     PropertyInfo(Variant::FLOAT, 
 *     		"属性名称",
 *          PROPERTY_HINT_RANGE,// 限定范围
 *			"最小值, 最大值, 步长")
 */
void Test::_bind_methods(){
    ClassDB::add_property("Test",
        PropertyInfo(Variant::FLOAT, "radius")),
        "set_radius",// Radius属性触发的set方法
    	"get_radius");// Radius属性触发的get方法
}
```

绑定自定义属性的触发方法

``` c++
void Test::_bind_methods(){
    ClassDB::bind_methond(
        D_METHOD("set_radius","radius"), 
        &Test::set_radius); // set_radius触发Test中的方法
}
```

设置属性修改逻辑

``` c++
/* .h文件 */ 
public:
	void set_radius(double radius);
	double get_radius() const;
private:
	double radius;
	
/* .cpp */
Test::Test(){
    radius = 10; //在构造方法中初始化
}
// 设置radius属性值
void Test::set_radius(double radius) {
    // radius是从godot界面获取的值
    this->radius = radius;
}
// 获取属性
double Test::get_radius() const {
    return this->radius;
}
```

#### Ⅲ、为属性添加分组



### 五、人物移动

#### Ⅰ、键盘设置

1. 虚拟映射设置

2. 需要配置虚拟按键，不然会出现错误

3. 菜单栏$\to$ 项目$\to$ 项目设置$\to$ 输入映射$\to$​ 添加键位映射

4. 虚拟按键不支持中文

#### Ⅱ、常用函数

1. 头文件：

    `#include <godot_cpp/classes/input.hpp>` 

2. Input实例化

    方法一

    ``` c++
    // Input::get_singletion()是一个Input类型的地址
    Input &inputsign = *Input::get_singleton();
    // 判断按键d是否被按下
    inputsign.is_action_pressed("d");
    ```

    方法二

    ``` c++
    Input *ii = Input::get_singleton();
    ii->is_action_pressed("d");
    ```

    方法三

    ``` c++
    Input::get_singleton()->is_action_pressed("d");
    ```

``` c++
// 按下d键，触发多次
ii->is_action_pressed("d");
// 按下按键，触发1次
ii->is_action_just_pressed("d"));
// 松开D键
ii->is_action_just_released("d"));
/* 获取按下s的力量 */
float s = ii->get_action_strength("s");
/* 获取x，y轴 */
// 左-1，右1
float h = ii->get_axis("左", "右");
/* 获取向量 */
Vector2 dir = ii->get_Vector("左","右","上","下");
dir.x !=0; // x轴
dir.y !=0; // y轴
```

#### Ⅲ、移动样例

``` c++
Input m_ii = Input::get_singleton();
// 当前键盘输入，方向
Vector2 aoix = m_ii->get_vector("left", "right", "up", "down");
// 向量归一化
aoix = aoix.normalized();
// 当前向量值,get_velocity
Vector2 currentAoix = get_velocity();
// 判断是否向量aoix是否为0
if(!aoix.is_zero_approx()){
    /*实现加速度, 方法一
    */ 
    // currentAoix += aoix * 100 * delta;
    // // 限制最大速度
    // // limit_length限制向量最大长度
    // currentAoix = currentAoix.limit_length(10000 * delta);

    /* 加速度实现，方法二*/
    // 向第一个向量移动固定的detla，不会超过最大值
    // move_toward（目标数值，每帧的增量）
    currentAoix = currentAoix.move_toward(aoix * 200, 200* delta) ;
} else {
    currentAoix = currentAoix.move_toward(Vector2(0,0), 400 * delta);
}
set_velocity(currentAoix);
// move_and_collide不能沿着墙滑动
move_and_slide();// 可以沿着墙滑动
```

### 鼠标设置

``` c++
#include <godot_cpp/classes/input.hpp>
Test::Test() {
	// 这里可以通过ctrl查看input类
    Input *I = new Input();
    // MOUSE_MODE_HIDDEN：鼠标移入程序隐藏鼠标，同时在编辑器中也会隐藏
    I->set_mouse_mode(Input::MOUSE_MODE_HIDDEN);
};
```

### 六、分组操作

#### Ⅲ、删除分组

- 通过Godot创建分组

``` c++
/*获取场景树*/ 
SceneTree *t = get_tree();
/*获取场景中的组empy*/ 
// TypedArray类型继承于Array
// TypedArray<Node> tg = t->get_nodes_in_group("empy");
// empy是分组名，在Godot界面中设置
Array tg = t->get_nodes_in_group("empy");

// is_empty,数组为空时返回true
while (!tg.is_empty())
{
    // 弹出一个节点，注意是Variant类型
    Variant temp = tg.pop_back();
    // 转换类型到Node
    Node *t = cast_to<Node>(temp);
    t->queue_free();
}
```

#### Ⅲ、分组操作

``` c++
/* 调用分组中公共方法 */
// 获取场景树
SceneTree *t = get_tree();
// 调用分组empy的脚本中ttt1方法
t->call_group("empy", "ttt1");

/* 动态添加分组 */
/* 使用get_node获取指定节点 */
Sprite2D *root1 = get_node<Sprite2D>
    ("/root/Node2D/Test/Sprite2D");
root1->add_to_group("empy");
```

### 七、预设资源

- load是直接加载
- preload是使用时加载

方式一：（简单命令）

``` c++
#include <godot_cpp/classes/resource_loader.hpp>
// 资源加载
ResourceLoader *R = new ResourceLoader();
Ref<PackedScene> scene = R->load(
    "res://game2.tscn","PackedScene");
        
if (scene.is_valid()) {
    // 实例化资源
    Node *n = scene->instantiate();
    // 实例化的资源n添加进当前场景
    Node::get_tree()->get_current_scene()->add_child(n);
    UtilityFunctions::print("y");
}
```

方式二：

``` c++
ResourceLoader *R2 = new ResourceLoader();
Ref<Resource> res = R2->load("res://game2.tscn");
// will simply become NULL if not a PackedScene.
Ref<PackedScene> scene = res; 
if (scene.is_valid()) {
    Node *n = scene->instantiate();
    Node::get_tree()->get_current_scene()->add_child(n);
    UtilityFunctions::print("y");
}
```

### 八、设置

#### Ⅰ、设置进程模式

- 设置这个，会解决按键bug
- 注意：不能在CharacterBody2D节点中使用

``` c++
#include <godot_cpp/classes/engine.hpp>
Test::Test(){
    if(Engine::get_singleton()->is_editor_hint()) {
        // 在编辑器中，禁用_process函数
        set_process_mode(
            Node::ProcessMode::PROCESS_MODE_DISABLED);

        UtilityFunctions::print("set ok");
    }
}

```

#### Ⅱ、从项目中读取配置

- 可以解决 this inputmap 不存在bug

``` c++
#include <godot_cpp/classes/input.hpp>
// 从Godot中的设置加载设置
InputMap* map = InputMap::get_singleton();  
map->load_from_project_settings();
```

#### Ⅲ、获取重力速度

``` c++
#include <godot_cpp/classes/project_settings.hpp>
// 获取重力加速度
Variant g = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
// 保持重力速度
this->m_gravity = (float)g;
```

#### Ⅳ、减速状态

``` c++
#include <godot_cpp/classes/engine.hpp>
# 获取Engine实例，Engine::get_singleton()  
// Engine::get_singleton()->set_time_scale(0.5);
Engine *e = Engine::get_singleton();
e->set_time_scale(3);
```



### 九、信号

#### Ⅰ、ADD_SIGNAL

1. 发射信号方法
2. Variant::STRING类型可参考Variant
3. 这能在Godot面板中的信号设置信号发出

不带参数的信号

``` c++
void Test::_bind_methods(){
    // 普通信号，信号名称为：hello_signal
    ADD_SIGNAL(MethodInfo("hello_signal"));
}
void Test::xxx(String world){
    // 发射信号，hello_singal
    emit_signal("信号名称");
}
```

调用发射信号

``` c++
void Test::_bind_methods(){
    // 携带参数的信号
    ADD_SIGNAL(MethodInfo(
        "hello_signal"，//信号名称
        PropertyInfo(Variant::STRING, "data"))//信号参数
    )
}
void Test::xxx(String world){
    // 发射信号，hello_singal
    emit_signal("信号名称", "参数1");
}
```





``` 
#include "Enemy.h"
void cast_damage(Enemy * target);

ClassDB::bind_method(
			D_METHOD("cast_damage_met", "target"), &DefaultBullet::cast_damage);
void DefaultBullet::cast_damage(Enemy * target) {
	target->being_attacked(damage);
	emit_signal("default_bullet_hit", get_position());
	queue_free();
}

```



#### Ⅱ、bind_method

- 信号的接收方法

- 操作方法

    连接信号方法$\to$ 连接到脚本（选中自定义类）$\to$​ 接受方法旁的“选取”

    <img src="assets/111183620.png" style="zoom:55%;" />

不带参数的方法

``` c++
void Test::_bind_methods(){
    /* ClassDB::bind_methond(D_METHOD("函数名"), 方法地址) */
    ClassDB::bind_method(D_METHOD("start_test"), &Test::start_test);
}
```

带参数的方法

1. Godot一些发射的信号带有参数，接收函数使用Variant

``` c++
void Test::_bind_methods(){
    /***
     * ClassDB::bind_methond(D_METHOD("函数名", "参数1", "参数2"), 方法地址)
     */
    ClassDB::bind_method(D_METHOD("start_test", "a", "b"), &Test::start_test);
}

// 带有参数的接收函数
void Test::start_test(Variant a, Variant b){
   	// 使用cast_to转换为适合类型 
    // cast_to<类型>(要转换的变量);
	Area2D *t = cast_to<Area2D>(a);
}
```

#### Ⅲ、添加属性

- 注意：ClassDB::bind_method方法一定要在 ClassDB::add_property之前

基本用法：

``` c++
void Test::_bind_methods(){
    /* 将Godot界面属性与C++方法绑定 */
    // 要先定义绑定方法
    ClassDB::bind_method(D_METHOD("set_radius", "r"), &Test::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &Test::get_radius);
    
    /* 添加界面接口
    ClassDB::add_property("类名",
    	PropertyInfo(参数类型, "参数名称"),
        "参数设置方法", 
        "获取参数数值");
    */
    ClassDB::add_property("Test",
    	PropertyInfo(Variant::FLOAT, "xxxx"),
        "set_radius",
        "get_radius");
}
/* 设置get_radius、set_radius方法 */
double Test::get_radius(){
    return radius;
}
void Test::set_radius(double r){
    this->radius = r;
}
```

给属性添加分组

``` c++
/* 
ADD_GROUP("分组名称","分组标识");
ADD_SUBGROUP("分组名称", "分组标识");
*/
// 设置分组表示，
ADD_GROUP("Group01","first_");
// 设置分组标识，二级分组
ADD_SUBGROUP("Group02", "first_second_");

/* 添加属性到分组中 */
ClassDB::add_property("Test",
    // 添加分组标识
    PropertyInfo(Variant::FLOAT, "first_second_xxxxx"),
    "set_radius",
    "get_radius");
```

### 十、相机

``` c++
tileMap.get_used_rect(); //
tilemap.tile_set.tile_side; //地图大小
camera.limit_top;//相机顶位置
camera.reset_smoothing(); //取消相机移动动画
camera.force_update_scroll();
```

### 十二、设置Y层

1. 根节点设置Y启用
2. Tilemap设置Y启用
3. Tilemap -> “层”设置Y启用
4. player节点设置Y启用
5. 设置Player层与“层”的z坐标处同一层
6. 修改贴图“选择”-“Y排序原点”
7. 修改player节点下的“Animationbody2D”节点的锚点

### 对话框dialogue

1. 创建一个control节点

2. 创建一个子节点NinePatchRect

3. 创建文本子节点（

    富文本：NinePatchRect/RichTextLabel

    普通文本：NinePatchRect/Lebel

4. 这些方法都是基于，富文本节点，LEbel节点

``` c++
set_text(); // 设置文本，每次都是新的
add_text(); // 添加文本
```



### 资源加载

#### Ⅰ、游戏资源加载

1. 头文件：`#include <godot_cpp/classes/resource_loader.hpp>` 

2. 类型头文件：

    场景资源：`#include <godot_cpp/classes/packed_scene.hpp>`

``` c++
/* 方法一 */ 
// PackedScene：场景资源
// Texture2D：图片纹理，图片资源
ResourceLoader *R = new ResourceLoader();
Ref<PackedScene> scene = R->load(
    "res://game2.tscn","PackedScene");
// 把资源初始化，然后就可以调用了
Node *b = scene->instantiate();

/* 方法二 */
ResourceLoader *R2 = new ResourceLoader();
Ref<Resource> res = R2->load("res://game2.tscn");
// 转换资源类型
// Ref<PackedScene>：场景资源
// Ref<Texture2D>：图片资源
Ref<PackedScene> scene = res; 
// 把资源初始化，然后就可以调用了
Node *b = scene->instantiate();
```

#### Ⅱ、文本资源加载

1. 头文件：`#include <godot_cpp/classes/file_access.hpp>`

``` c++
FileAccess *f = new FileAccess();
String a = f->open("res://workdiloge/work.json", FileAccess::READ)->get_as_text();
```

### 实现黑夜透镜效果

1. 添加CanvasLayer节点：相当于图层，

   Layer属性：改成大的，遮盖全部

   Mouse / Filter属性：阻止点击穿透，建议stop

2. 添加子节点ColorRect节点：改变颜色

3. 可以使用 SceneTree.create_tween() 或 Node.create_tween() 创建 Tween（“即用即弃”）

``` c++
/* 创建补间动画 tween类 */

```



### 回合制人员加载

1. 设置Marker2D节点，表贼元素位置

``` c++
// 得到定位节点
m1 = get_node<Marker2D>("m1");
m2 = a->get_node<Marker2D>("m2");
m3 = a->get_node<Marker2D>("p3");
// 加载敌人素材
ResourceLoader *R = new ResourceLoader();
Ref<PackedScene> wolf = R->load("res://units/enemy_wolf.tscn","PackedScene");

// 初始化，元素初始化
Node *b = wolf->instantiate();
Node *c = tree->instantiate();
// marker2d加载敌人素材
m1->add_child(b);
m2->add_child(c);
```

### 调用子类方法

``` c++
#incldue "Player"
_player = get_node<Player>("Player");
_player->set_movement_limit(_scene_size);

```

### 常见错误

> error C2504: “\*\*\*\*”: 未定义基类

- 

> 父类：father.h；子类:child.h；

1. 在father.h文件中声明`class child;`
2. 在father.cpp中引入头文件：`#include "child.h"` 

> 成功编译，但编译后子类不存在节点中

- `register.cpp`中要保证，父类在子类前面进行注册

> error LNK2001: 无法解析的外部符号 "public: virtual void __cdecl TFSC::initiazlie(void)" (?initiazlie@TFSC@@UEAAXXZ)

- 若是在使用多态的时候出现错误，父类虚函数没有默认方法

> error C2039: "speak": 不是 "TMOVESTATE" 的成员

- 子类不能写virtual关键字

> 节点未找到

- 由于Godot的节点加载顺序

> error C2065: “TFSCINTERFACE”: 未声明的标识符
>
> error C2027: 使用了未定义类型“TMOVESTATE”

- 检测头文件的引用顺序

### 场景继承

### UI设置

### Gdextension说明文档

### 平台跳跃移动

``` c++
int SPEED = 130;
int JUMP_VELOCITY = -400;

#include <godot_cpp/classes/project_settings.hpp>
Variant g = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");

if not  is_on_floor():
	velocity.y += g * delta;

if input.is_action_just_pressed("ui_accept") and is_on_floor():
	velocity.y = JUMP_VELOCITY
```

### 注册实例

``` c++
Engine::get_singleton()->add_singleton(Engine::Singleton("YTween", YTween::get_singleton()));
```

### 补间动画

- C++使用没有效果，只进行记录

  ```c++
  #include <godot_cpp/classes/tween.hpp>
  #include <godot_cpp/classes/property_tweener.hpp>
  
  Ref<Tween> tw = Node::create_tween()->set_loops();
  bool b = tw->is_valid();// 验证是否存活
  bool a = tw->is_running();// 验证是否运行
  
  Sprite2D *sp01 = get_node<Sprite2D>("../sp2");
  // 属性补间
  tw->tween_property(cr, NodePath("color:a"), 255.0, 4.0);
  ```

- 使用GD脚本编写

  `.set_delay(x)`：延迟x秒执行补间动画

  `.set_loop()`：设置补间动画循环

  `.from_current(x)`：从x状态执行到目标状态

  `.set_ease()`：设置变化曲线

  `.set_trans()`：带有物理属性

``` python
# 获取节点，4.0以上版本需要使用@字符
@onready var ax = $sp2
# 创建一个补间动画
var tween = create_tween()
# 创建属性补间动画
# ax:欲添加补间动画的对象
# "position"：初始状态
# Vector2(1000, 500)：目标状态
# 5：持续时间
tween.tween_property(ax, "position",Vector2(1000, 500), 5)
tween.interval(1.0); # 循环的补间动画的间隔
```

### 动画播放实现场景移动

1. 创建场景A（任意）
2. 创建子节点AnimationPlayer（A节点的子节点）
3. 创建新动画
4. 在指定位置创建一个关键帧，在目标位置再创建一个关键帧
5. 设置播放模式，可以修改播放方式（实现往返播放）

### 自定义继承

1. 注册（`register_types.cpp`）时顺序很重要，父类一定要先注册
2. 若自定义节点没有出现，可以重启Godot软件

``` c++
// 父类
class TFSC : public Node {
    GDCLASS(TFSC, Node);
}
// 子类
class TMOVESTATE : public TFSC {
    GDCLASS(TMOVESTATE, TFSC);
}
```

