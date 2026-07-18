# GDScript

## 语法相关

### 一、类型转换

``` python
String a = str(level) # Level是int类型，转换为字符串
Variant str_to_var(string: String );  // 将string转换为variant
String var_to_str(variable: Variant); // 将variant转化为String
```

### 二、语法

``` python
extends Area2D # 继承节点Area2D
class_name TKeyBoardInterface # 声明一个类名称，在其他位置可以继承
signal ssss # 自定义信号

@export var player_date: Resource # 资源类型变量
@export_file(".tson") var leve # 
@export var level: int # 界面可修改，int类型

@onready var tfsc = $TFSC # 定义变量tfsc为拖拽的节点TFSC
@onready var tfsc = get_node("/root/main/System/TFSC") # 获取节点

var score = 100  # 传统写法（动态类型）
var score: int = 100 # # 类型注解写法，显式声明为 int 类型
var score := 100     # # 类型推断写法（:=）自动推断为 int 类型，等效于 var score: int = 100

# 假设场景节点位置为：/root/TMainNode/TFSC/InitState
get_tree().current_scene # 获取的路位置为：/root/TMainNode
```

set与get使用

``` python
## 注意：默认值后有：
var 变量名 = 默认值:
    set(新值):
        # 自定义赋值逻辑
        if 条件:
            变量名 = 新值
            # 可触发其他操作
    get:
        # 自定义读取逻辑
        return 变量名
```

信号

``` python
#
func _ready():
	var timer = get_node("Timer")
    # 节点.信号名称.connect(处理方法) 
    # 处理方法，不用添加“”
	timer.timeout.connect(_on_timer_timeout)
    pass

func _on_timer_timeout():
    pass
```



## 常用的功能

### 一、自动设置资源内容

- 使用`set(value)`，当变量keyboard_res后就会自动进行变量修改
- 在`set(value)`，不能使用`@onread`定义的变量（因为此时尚未进入场景树）

``` python
@export var keyboard_res: KeyBoradRes:
	set(value):
        # 必不可少
		keyboard_res = value 
        
		# 在set方法中不能获取节点，可能是当前节点树未建立
		# 使用call_deferred方法可以设置
		call_deferred("auto_set_info")
		pass
    
# 回调函数
func auto_set_info():
    pass
```

### 二、脚本继承

- 主要用于大量代码重复出现在不同的场景中
- `self`：与JavaScript中的this类似，指代当前运行的脚本
- `super`：在子类中调用父类

父类定义

``` python
extends Control ## 可以是任何类
class_name TKeyBoardInterface ## 声明当前类可以被继承，new等

## 外部资源，其子类都会有
@export var keyboard_res: KeyBoradRes

## 在子类_ready之前调用
func _ready() -> void:
	pass

## 自定义方法
func _on_down() -> void:
    ## self指向的是当前运行的脚本，一般是子类
    ## filedialog是子类中的变量
	self.filedialog.show()
	pass 
```

子类定义

``` python
## 继承父类
extends TKeyBoardInterface
## 特有的方法
@onready var filedialog = $FileDialog

func _ready() -> void:
	# 调用父类方法
	super._on_down()
	pass
```

### 三、场景实例化

- `load()`：在代码执行到该行时才会从磁盘加载资源。
- `preload()`：**仅GDScript**，在脚本加载时就会完成资源的加载。如果资源不存在，会在**编辑阶段**报错。这适用于那些你确定会使用且路径不会改变的场景

实例化场景

``` python
# /* 2种加载方式，2选一 */
# 在运行时加载，代码执行到这行时加载
var scene_a_resource = load("res://path_to_your_scene_A.tscn") 
# 静态加载，当场景加载时，就加载资源
var scene_a_resource = preload("res://path_to_your_scene_A.tscn")

# 实例化场景
var scene_a_instance = scene_a_resource.instantiate()

# 添加场景
add_child(scene_a_instance)


```

删除场景

``` python
# 场景指针，可以放到全局变量中
scene_a_instance.queue_free()

# 若只能获取父类节点，只删除子节点
 for child in $B.get_children():
     child.queue_free()
    
# 如果知道场景A的节点名
if $B.has_node("SceneA"):  # 假设场景A的节点名叫"SceneA"
   $B.get_node("SceneA").queue_free()
```



### 四、禁止关闭

设置：$项目\to项目设置\to常规\to配置（高级设置）\to自动接受退出（取消）$ 

``` python
# 设置关闭失效
get_tree().set_auto_accept_quit(false) 
# 响应关闭通知
func _notification(what):
	if what == NOTIFICATION_WM_CLOSE_REQUEST:
		get_tree().quit() # default behavior
```

### 五、信号

内置信号

``` python
extends Control

func _ready():
    # 获取按钮节点（假设场景中有一个名为 Button 的按钮）
    var button = $Button

    # 连接按钮的 pressed 信号到自定义方法
    button.pressed.connect(_on_button_pressed)

# 当按钮背按下时调用的方法
func _on_button_pressed():
    print("按钮被点击了！")
```

自定义信号

``` python
extends Node

# 1. 定义自定义信号
signal player_scored(points)
signal game_over

func _ready():
    # 2. 连接自定义信号到处理方法
    player_scored.connect(_on_player_scored)
    game_over.connect(_on_game_over)

# 3. 在某个条件下发射信号
func add_score(amount):
    print("获取分数：", amount)
    player_scored.emit(amount)   # 发射信号并传递参数

func end_game():
    game_over.emit() # 发射无参数信号

# 4. 处理信号的方法
func _on_player_scored(points):
    print("玩家获得了 %d 分" % points)

func _on_game_over():
    print("游戏结束！")

```

### 六、关于鼠标无法点击按钮

**`CenterContainer`默认会"拦截"鼠标事件**。作为`Control`类节点，它的`mouse_filter`属性默认为`MOUSE_FILTER_STOP`，这意味着：

- 它会接收鼠标事件
- 事件不会继续向下传递给被它覆盖的节点A 

即使这个容器是透明的、没有背景，它仍然会阻挡事件传递。这就是为什么节点A变得无法点击。

**解决方案**

**方案一：设置Mouse Filter为Ignore（最推荐）**

1. 选中你的`CenterContainer`节点
2. 在检查器（Inspector）中找到 **"Mouse Filter"** 属性
3. 将其从默认的 **"Stop"** 改为 **"Ignore"**

或者通过代码设置：

```python
$CenterContainer.mouse_filter = Control.MOUSE_FILTER_IGNORE
```

**方案二：设置Mouse Filter为Pass**

如果你希望`CenterContainer`本身也能接收某些事件（比如鼠标进入/退出的效果），但又不想阻挡下层，可以设置为 **"Pass"** 模式。

gdscript

```
$CenterContainer.mouse_filter = Control.MOUSE_FILTER_PASS
```

这种模式下：

- 容器会先接收到事件
- 事件会继续向下传递给节点A 
- 如果容器和节点A都想响应同一个点击，两者都会触发

方案三：调整节点层级

如果因为某些原因你不能修改`CenterContainer`的`mouse_filter`，可以考虑调整节点结构：

- 将`CenterContainer`和节点A放在同一层级，而不是覆盖在上面
- 但根据你的描述（"在A界面上添加centercontainer"），方案一明显更符合你的原始设计意图

验证是否生效

设置完成后，你可以：

1. 运行场景
2. 点击原本被容器覆盖的区域
3. 节点A应该能正常响应点击了

原理小贴士

Godot的`mouse_filter`有三种模式：

| 模式             | 行为               | 适用场景                     |
| :--------------- | :----------------- | :--------------------------- |
| **STOP**（默认） | 接收事件，停止传递 | 按钮、输入框等交互控件       |
| **PASS**         | 接收事件，继续传递 | 透明遮罩、需要同时响应的上层 |
| **IGNORE**       | 完全忽略事件       | 纯装饰性元素、布局容器       |

你现在的需求就是典型的"布局容器应该忽略事件"场景，所以**方案一最合适**。

### 七、实例化场景没有背景

- 需要用药Panel控件设置背景颜色
- 需要设置场景的顶级父类`custom Minimum Size`属性，不能为空
- 需要保存场景

### 八、按钮不更新

``` python
# 更新按钮
self.button.queue_redraw() 
await get_tree().process_frame # 等待1帧
```

