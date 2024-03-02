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
     windows.debug.x86_64 = "res://libgodot.debug.x86_64.lib"
     ```

13. 复制“步骤11”生成的.dll文件到example.gdextension文件指定的位置

14. 使用Godot$\to$​ 创建node 即可找到test节点

### 二、vscode配置

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

### 三、像素游戏配置

画面放大3倍

1. 设置窗口

    视口高度：1152/3=384

    视口宽度：648/3=216

2. 打开高级模式

    窗口宽度覆盖：1152

    窗口高度覆盖：648

3. 拉伸模式：canvas_items

## 节点说明

1. Sprited2D：主要用于图片显示
2. Node：可以用于代码逻辑编写
3. AnimatedSprite2D：用于动画播放
4. collisionShape2D：碰撞体积
5. Area2D：能够检测其他节点的进入和退出
6. RayCast2D：根据设置的箭头进行碰撞检测
    - is_colliding()碰撞检测
7. HboxContainer：横向排列的容器，用于制作角色血条等
8. panelcontainer：为图像提供背景
9. Progressbar：进度条，软件常用
10. TextureProgressbar：进度条，游戏常用，可设置背景
11. canvasLayer：可根据屏幕位置显示
12. marker2d：

## 常用类

### 一、_input

- Node节点的方法
- 选哟虚拟键位的映射
- 对于游戏输入，_unhandled_key_input更好

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

### 二、Sprited2D

``` c++
// 加载资源
ResourceLoader *i2 = new ResourceLoader();
Ref<Resource> res = i2->load("res://123.svg");
Ref<Texture2D> i3 = res;

// 获取要修改的节点
// 若查找Node节点，可改成
// Node *root11 = get_node<Node>
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

### 三、Variant

- Godot的万能类型，可以转换为Godot的任意类型

``` c++
// 准备一个Variant类型变量
Variant temp = tg.pop_back();
// 转换类型到Node *
// cast_to<类型>(要转换的变量);
Node *t = cast_to<Node>(temp);
```

### 四、AnimatedSprite2D

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

### 五、AnimationPlay

- 通过单张png，生成动画
- 可以实现更多的效果
- AnimationPlay下添加sprite2d节点



### 六、AudioStreamPlayer

- 全局音效，背景音
- AudioStreamPlayer2D具有距离属性的音效

``` c++
#include <godot_cpp/classes/audio_stream_player.hpp>
// 播放音乐，每次从头开始播放
this->play();
// 继续播放
this->set_stream_paused(false);
// 暂停播放
this->set_stream_paused(true);

/* 代码加载 */
// 加载音频资源
ResourceLoader *R = new ResourceLoader();
Ref<AudioStream> bg = R->load("res://02.mp3","AudioStream");
// 音频类
AudioStreamPlayer *a = new AudioStreamPlayer();
// 加载音频
a->set_stream(k_01);
// 调用播放方法
a->play();
```

## C++

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



### 四、utility_functions

- 包含很多常用方法

``` c++
#include <godot_cpp/variant/utility_functions.hpp>
// 打印方法
UtilityFunctions::print("hello world");
```

### 五、输入设置

#### Ⅰ、鼠标设置

``` c++
#include <godot_cpp/classes/input.hpp>
Test::Test() {
	// 这里可以通过ctrl查看input类
    Input *I = new Input();
    // MOUSE_MODE_HIDDEN：鼠标移入程序隐藏鼠标，同时在编辑器中也会隐藏
    I->set_mouse_mode(Input::MOUSE_MODE_HIDDEN);
};
```

#### Ⅱ、键盘设置

虚拟映射

- 需要配置虚拟按键，不然会出现错误

    菜单栏$\to$ 项目$\to$ 项目设置$\to$ 输入映射$\to$​ 添加键位映射

- 虚拟按键不支持中文

方法一、判断键位按下（不推荐）

``` c++
#include <godot_cpp/classes/input.hpp>

// 方法一
// Input::get_singletion()是一个Input类型的地址
Input &inputsign = *Input::get_singleton();
if(inputsign.is_action_pressed("d")){
	// 判断按键d是否被按下
}
// 方法二
Input *ii = Input::get_singleton();
ii->is_action_pressed("d");
// 方法三
Input::get_singleton()->is_action_pressed("d");

// 按下按键，触发1次
if(ii->is_action_just_pressed("d")) {
    UtilityFunctions::print("按下了虚拟按键");
};
// 松开按键，触发1次
if(ii->is_action_just_released("d")){
    UtilityFunctions::print("松开了虚拟按键");
}
```

方法二、获取XY轴

获取数组

``` c++
// Input实例
Input *ii = Input::get_singleton();
// 获取按键力量
float s = ii->get_action_strength("s");
UtilityFunctions::print(s);
// 获取x，y轴，左-1，右1
float h = ii->get_axis("左", "右");
UtilityFunctions::print(h);
```

获取XY轴

``` c++
Input *ii = Input::get_singleton();
// 获取一个（a，b）
Vector2 dir = ii->get_Vector("左","右","上","下")
```

#### Ⅲ、位置设置

- 位置设置需要用到Vector2结构体
- Vector2结构体定义在Node类中

一般设置：

``` c++
// vector2不用引入头文件
// Vector2 new_position = Vector2(X轴, Y轴);
Vector2 new_position = Vector2(100, 100);
// 设置位置坐标，这是父类中的方法
set_position(new_position);
// 设置X坐标
new_position.x = 50;
// 设置Y坐标
new_position.y = 50;
// 获取当前位置,Node中的方法，get_position()
Vector2 p = get_position();

```

使用move_and_slide

- move_and_slide可以自动进行碰撞检测

``` c++
// 设置数据增量
set_velocity(this->m_play_position);
// 开启
move_and_slide();
```



#### Ⅳ、move_and_slide

- 根据set_velocity设定，自动进行碰撞体积

``` c++
// 设置velocty值,velocty是移动增量，每帧都移动
set_velocity(
        Vector2(100, 100)
);
// 设置新位置
move_and_slide();
```

### 六、节点操作

- 注意：节点操作都应在_ready之后的生命周期使用

#### Ⅰ、创建删除

``` c++
#include <godot_cpp/classes/scene_tree.hpp>
// get_tree需要用法scenetree头文件
/* 获取整个节点树 */
// 方法1
Node *root = Node::get_tree()->get_current_scene();
// 方法2
SceneTree *r = Node::get_tree();
Node *root = r->get_current_scene();

/* 删除节点 */
Node *root = Node::get_tree()->get_current_scene();
// 查找节点“Test”
Node *c0 = root->find_child("Test");
// 尝试删除节点Test
c0->queue_free();
```

#### Ⅱ、节点查找

- find_child：可以循环查找节点，但速度比较慢，在节点较多的树中

``` c++
// 只能获取子节点,不能得到父节点
get_node<Node>("xx");
// 通过相对路径，可以获取子节点的子节点
get_node<Node>("xxx/vvv");  
// 获取父节点
get_node<Node>("..");
Node::get_parent();
// find_child会对节点进行遍历，太多节点会影响速度
find_child("xxx");

/* 使用get_node获取指定节点 */
Node *root1 = get_node<Sprite2D>
    ("/root/Node2D/Test/Sprite2D");
```

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



### 七、场景操作

#### Ⅰ、场景切换

``` c++
// 获取场景树
SceneTree *t = Node::get_tree();
// 切换场景
t->change_scene_to_file("res://game2.tscn");
```

#### Ⅱ、资源加载

``` c++
#include <godot_cpp/classes/resource_loader.hpp>
/* 方法一 */ 
// PackedScene：场景资源
// Texture2D：图片纹理，图片资源
ResourceLoader *R = new ResourceLoader();
Ref<PackedScene> scene = R->load(
    "res://game2.tscn","PackedScene");

/* 方法二 */
ResourceLoader *R2 = new ResourceLoader();
Ref<Resource> res = R2->load("res://game2.tscn");
// 转换资源类型
// Ref<PackedScene>：场景资源
// Ref<Texture2D>：图片资源
Ref<PackedScene> scene = res; 
```

#### Ⅲ、预设资源

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



### 九、信号

- 信号主要功能是C++与GDScript脚本交互

#### Ⅰ、自定义信号

- ADD_SIGNAL会在 Godot中创建一个可连接信号

定义一个信号

``` c++
void Test::_bind_methods(){
    // 普通信号，信号为hello_signal
    ADD_SIGNAL(MethodInfo("hello_signal"));
    // 携带参数的信号
    ADD_SIGNAL(MethodInfo(
        "hello_signal"，//信号名称
        PropertyInfo(Variant::STRING, "data"))//信号参数
    )
        
}
```

调用发射信号

``` c++
void Test::xxx(String world){
    // 发射信号-hello_singal
    emit_signal("hello_signal", "xxxxx!");
}
```

#### Ⅱ、bind_method

- 此方法可以将C++编写的函数绑定到GDScript中，在GD脚本中使用

``` c++
#include "test.h"
#include <godot_cpp/variant/utility_functions.hpp>

// 信号可触发方法
void Test::start_test(){
    UtilityFunctions::print("from gdextension");
}
// 绑定方法
void Test::_bind_methods(){
    /* ClassDB::bind_methond(D_METHOD("函数名"), 方法地址)
     * ClassDB::bind_methond(D_METHOD("函数名", "参数1", "参数2"), 方法地址)
     */
    ClassDB::bind_method(D_METHOD("start_test"), &Test::start_test);
}

```



#### Godot设置

1. 使用绑定方法，让触发的方法暴露到Godot中
2. 使用Godot设置信号

### 十、相机

``` c++
tileMap.get_used_rect(); //
tilemap.tile_set.tile_side; //地图大小
camera.limit_top;//相机顶位置
camera.reset_smoothing(); //取消相机移动动画
camera.force_update_scroll();
```

### 十一、攻击框

- 都是继承的Area2D节点，Hurtbox,
- 需要定义图层
