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
var scene_a_resource = load("res://path_to_your_scene_A.tscn") # 在运行时加载
var scene_a_resource = preload("res://path_to_your_scene_A.tscn") # 在脚本解析时预加载

// 实例化场景
var scene_a_instance = scene_a_resource.instantiate()

# 添加场景
add_child(scene_a_instance)

# 卸载
scene_a_instance.queue_free()
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

