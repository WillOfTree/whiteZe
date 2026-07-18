## 待删除/修改/归类内容

### 一、节点操作

#### Ⅱ、Get_node

注意事项：

1. 使用 `%` 标注场景内唯一节点，可以获取场景内任意位置的 `%` 标注的节点

   `get_node<Node>("%sprite"); // 必须携带%标注全局查找` 

2. `get_node()`中必须是`“”`，若是`‘’`，则会发生未知错误

3. `get_node<类型>("")`注意类型，**一般不能填错，填错会找不到节点**

使用方法：

``` c++
/* 获取子节点 */
// 只能获取子节点,不能得到父节点
get_node<Node>("xx");
// 通过相对路径，可以获取子节点的子节点
get_node<Node>("xxx/vvv"); 

/* 获取父节点 */ 
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

#### Ⅲ、节点其他操作

``` c++
is_inside_tree(); // 验证节点是否在树中
```



### 二、位置/全局位置区别

1. `get_positon`：相对于当前节点的父节点为原点，获取的坐标信息

2. `get_global_position`：相对于场景根节点（root节点）

3. 性能差距

   `get_position()`性能消耗极低，只读取节点的position属性

   `get_global_position()`性能消耗稍高

   - 节点链深度 ≤ 3，要慢1.5~2倍
   - 节点链深度 > 10，要慢3~5倍

   解决方法：一般不需要优化（单帧调用小于100次），高频调用可以使用缓存全局坐标，手动计算全局坐标

4. 当设置了Camera2D节点，对get_global_position()与get_position()没有影响

节点位置演示：

``` shell
场景根节点 (0,0)
   └── 父节点 (100,100)
       └── 子节点 position=(50,50)
               ├── get_position() → (50,50)
               └── get_global_position() → (150,150)
```

  获取位置方法

``` c++
/* 设置位置坐标 */ 
// 获取当前位置，相对与父节点
// Node中的方法
Vector2 p = get_position();
/* 获取当前向量速度 */ 
vector2 a = get_velocity();

// 全局节点
Vector2 p = get_global_position();
```

### 三、动画类

#### Ⅰ、AnimatedSprite2D

- 用于动画播放，简单物品动画
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

#### Ⅱ、AnimationPlay

- Godot所有元素都可以使用它来生成动画，包括场景中来回移动的物体，怪物等

### 四、AudioStreamPlayer

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

### 五、Vector2-向量

- 头文件：不需要引用
- Godot坐标系，其坐标原点在屏幕左上点
  - `Vector2(0, 1)` 表示 **向下**。
  - `Vector2(0, -1)` 表示 **向上**。

向量的**加法**计算

``` c++
var a = Vector2(1, 2);
var b = Vector2(3, 4);
print(a + b);  // 输出 (4, 6)
print(a - b);  // 输出 (-2, -2)
```

向量的标量乘除

``` c
var vec = Vector2(2, 4);
print(vec * 2);   // 输出 (4, 8)
print(vec / 2);   // 输出 (1, 2)

print(a.dot(b))  // 输出 1*3 + 2*4 = 11
```

向量乘法

``` c++
// Vector2(x1 * x2, y1 * y2)
print(Vector2(2, 3) * Vector2(4, 5))  // 输出 (8, 15);
```



向量操作方法

``` c++
/* 创建一个向量 */
// Vector(x轴，y轴)
Vector2 a = Vector(100, 100);

/* 获取向量x值、y值 */
Vector2 position = node->get_position();
float x_value = position.x;  // 直接访问x成员
float x_value = position.get_x();  // 使用get_x()方法
float x_value = position[0];  // 获取x值
float y_value = position[1];  // 获取x值

/* 修改向量x值、y值 */
Vector2 position = node->get_position();
position.x = 100.0f; // 方法1：直接设置成员
position.set_x(100.0f);// 方法2：使用set_x方法
position[0] = 50.0f;         // 设置x值
position[1] = 50.0f;         // 设置y值
```

获取方向（从A移动到B的方向）

- 向量A - 向量B = B指向A的向量

  > To find a vector pointing from A to B, use B - A.

``` c++
// 从 A 点指向 B 点的方向向量
Vector2 direction = (pointB - pointA).normalized();
```

向指定方向移动pixel_distance的像素

``` c++
Vector2 direction = (target - current_pos).normalized(); // 获取方向
// 方法一
Vector2 pixel_distance = Vector2(100, 0); // 移动像素，向右移动100像素
Vector2 movement = direction * pixel_distance; // 计算位移

 node->set_position(current_pos + movement);  // 当前移动位置 + 位移  

// 方法二
// 每帧移动 100 像素
set_position(get_position() + direction * 100 * delta);
```

一些属性方法


``` c++
/* a向量是否为0向量 */ 
a.is_zero_approx();
/* 向量单位化 */ 
// 得到一个向量的方向，若方向不单位化，移动像素会不准
a.normalized();

/* 设置a走向B的向量 */ 
// B：向量（方向和大小），
// C：每帧的增量
a.move_toward(B, C);

/* 在一个范围内 */ 
Vector2 direction = m_startPosition - position;
if(direction.length() > 200){}
// 返回从该向量指向 to 的归一化向量。相当于使用 (b - a).normalized()。
direction_to(to: Vector2) const
// 返回该向量与 to 之间的距离。
distance_to(to: Vector2);
```

人物移动

``` c++
// 获取输入向量
Vector2 temp_v = m_inputHandler
    ->get_vector("G_LEFT", "G_RIGHT", "G_UP", "G_DOWN").normalized();

temp_v = temp_v.move_toward(temp_v * 1000, external_move_speed * delta) ;
// 设置角色移动
m_player->set_velocity(temp_v);
m_player->move_and_slide();
```

### 六、CharacterBody2D

``` c++
// 设置当前向量
set_velocity(a);
// move_and_collide不能沿着墙滑动
// 根据set_velocity设定，自动进行碰撞体积
move_and_slide();// 可以沿着墙滑动
```

### 七、随机数

- 头文件：`#include <godot_cpp/classes/random_number_generator.hpp>` 

- 文件`utility_functions`同样包含随机方法的静态方法

- `randf_range(0.0,5.0)`：产生浮点数，0.0-5.0之间的数，不包括0.0、5.0

  ``` c++
  // 产生0~5之间的数，不包括5
  int a = utility_functions::randf_range(0.0,5.0);
  // 产生0~5之间的数，不包括0，5
  double a = utility_functions::randf_range(0.0,5.0);
  ```

- `randi_range(1, 3)`：产生整数，1-3之间的数，包括开始（1）和结束值（3）

- `randi()`：产生整数

  ``` c++
  utility_functions::randi(); // 返回0 ~ 2^32-1之间的数
  utility_functions::randi() % 20; // 返回0 ~ 19之间的数
  ```

- `randf()`：产生浮点数

  ``` c
  utility_functions::randf() * 10; //返回0 ~ 10之间的数
  ```

- `randomize()`：产生随机数种子

  ``` c++
  #include <godot_cpp/classes/random_number_generator.hpp>
  
  RandomNumberGenerator *r = new RandomNumberGenerator();
  r->randomize(); // 设置随机数种子
  ```

### 九、utility_functions

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

utilityfunctions::printerr("错误输出")
```

### 十、SceneTree相关方法

1. 头节点：`#include <godot_cpp/classes/scene_tree.hpp>` 

``` c++
// 获取场景树
SceneTree *tree = Node::get_tree();

// get_current_scene():获取当前场景的根节点
Node *root = tree->get_current_scene();
// 获取
SceneTree::get_singleton()->initialize();
```

#### Ⅰ、场景切换

- 只能用于游戏场景切换，因为他会释放所有节点，再新建节点，
- 场景切换要进程场景初始化操作，加载
- 头文件：scene_tree()

``` c
// 获取场景树
SceneTree *t = Node::get_tree();
// 切换场景，使用路径
t->change_scene_to_file("res://game2.tscn");
// 使用pack，节点对象
t->change_scene_to_packed(Node);
// 切换场景方法
t->call_deferred("change_scene_to_file", "res://bat2.tscn");
```

#### Ⅱ、分组

获取分组

``` c++
// 获取场景树
SceneTree * tree = get_tree();
    
// 获取分组中的所有节点
Array a = tree->get_nodes_in_group("组名");
Node * ab = cast_to<Node>(a[0]); // 转换节点，调用a[0]
ab->get_name(); // 获取节点名称
```

添加删除分组

- 需要引入SceneTree头文件

``` c++
t->add_to_group("组名"); // 将节点t添加进分组
t->remove_from_group("组名"); // 将节点t从分组删除
```

其他方法

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

### 十二、Path2D

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

### 十三、RayCast2D

- 射线投射节点，用于检测碰撞不可见射线，根据设置的箭头进行碰撞检测

``` c++
is_colliding(); //检测是否发生碰撞
```

### TileMap

- 5生成地牢-25分
- 设置战争迷雾

``` c++
set_cells_terrain_connect
```

### AStarGrid2D

- AI算法，9期移动AI-05分 



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



### 音乐播放

- 播放，头文件：`#include <godot_cpp/classes/audio_stream_player.hpp>`
- 音乐类型，头文件：`#include <godot_cpp/classes/audio_stream_mp3.hpp>`
- 注意，需要把节点添加到场景树中，才能播放

``` c++
Ref<AudioStream> m = ResourceLoader::get_singleton()->load(path); // 加载音乐资源
Ref<AudioStreamPlayer> t = memnew(AudioStreamPlayer); // 音乐对象

t->set_stream(m); // 设置音乐流
t->play(); //播放，t必须在场景树中，才可以播放
```

### Input

1. 需要配置虚拟按键，不然会出现错误

2. 菜单栏$\to$ 项目$\to$ 项目设置$\to$ 输入映射$\to$​ 添加键位映射

3. 虚拟按键不支持中文

4. 头文件：`#include <godot_cpp/classes/input.hpp>` 

获取单个按钮按下动作

``` c++
// 获取Input静态实例
Input *ii = Input::get_singleton(); 

ii->is_action_pressed("d");// 按下d键，触发多次
ii->is_action_just_pressed("d"));// 按下按键，触发1次
ii->is_action_just_released("d"));// 松开D键
ii->is_anything_pressed();// 任意键按下
```

获取水平方向/垂直方向的动作

``` c++
// 获取Input静态实例
Input *ii = Input::get_singleton(); 

// 获取水平轴（左负右正，自动标准化到 [-1, 1]），不用使用.
float h = ii->get_axis("左", "右");
return Vector2(h, 0);

// 获取垂直轴
float v = ii->get_axis("下", "上");
return Vector2(0, v);
```

获取4个方向的动作

``` c++
Input *ii = Input::get_singleton(); 

// 位置一定对应，不然方向会出错
Vector2 dir = ii->get_vector("左","右","上","下").normalized();
dir.x !=0; // x轴
dir.y !=0; // y轴
```

其他

``` c++
Input *ii = Input::get_singleton(); 

/* 获取按下s的力量 */
float s = ii->get_action_strength("s");
```

InputMap

- 头文件：`#include <godot_cpp/classes/input_map.hpp>`
- 可以解决 this inputmap 不存在bug

``` c++
// 从Godot中的设置加载设置
InputMap* map = InputMap::get_singleton();  
map->load_from_project_settings();
```

## Engine类使用

- 头文件：`#include <godot_cpp/classes/engine.hpp>` 

#### Ⅰ、设置进程模式

- 建议使用GDScript进行update调用
- 注意：不能在CharacterBody2D节点中使用，有些版本会有BUG，编译完成后，需要重新添加节点才有效果

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

#### Ⅱ、获取重力速度

``` c++
#include <godot_cpp/classes/project_settings.hpp>
// 获取重力加速度
Variant g = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
// 保持重力速度
this->m_gravity = (float)g;
```

#### Ⅲ、减速状态

``` c++
#include <godot_cpp/classes/engine.hpp>
# 获取Engine实例，Engine::get_singleton()  
// Engine::get_singleton()->set_time_scale(0.5);
Engine *e = Engine::get_singleton();
e->set_time_scale(3);
```

#### Ⅳ、暂停游戏

``` c++
set_physics_process(false);
get_tree()->paused = true;
// 设置节点属性，Node->pause->mode-> process 设置当前节点和主场景节点不是继承关系
```

#### Ⅴ、注册实例

``` c++
Engine::get_singleton()
    ->add_singleton(Engine::Singleton("YTween", YTween::get_singleton()));
```

#### Ⅶ、程序暂停

``` c++
set_process(FAILED); // 暂停

```

