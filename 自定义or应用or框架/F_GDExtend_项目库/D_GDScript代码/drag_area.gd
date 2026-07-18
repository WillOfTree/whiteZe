###
### 拖拽移动场景
### 需要创建Area2D节点，并将本脚本挂载到Area2D节点上
### 需要连接Area2D/input_event信号
### 	input_event信号：专门用来检测鼠标（或手指）是否点击/划过了该节点的碰撞区域
### 
extends Area2D


var is_dragging = false # 是否正在拖拽标识
var drag_offset = Vector2() # 拖拽偏移坐标
var click_position = Vector2i() # 保存鼠标当前点击位置


func  _ready() -> void:
	pass
	

### 
### _input获取在当前Godot界面上的输入事件
### 可以使鼠标移出Area2D区于依然可以移动Godot
### 
func _input(event: InputEvent) -> void:
	
	if is_dragging and event is InputEventMouseMotion:
		get_window().position += Vector2i(event.relative) # 计算移动位置
		
	# 用于判断鼠标左边松开，结束拖拽
	if is_dragging and event is InputEventMouseButton:# 检查是否是鼠标按钮事件
		if event.button_index == MOUSE_BUTTON_LEFT:# 检查是否是左键
			if !event.pressed: # 鼠标松开
				is_dragging = false
				Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
				
				## 设置鼠标位置，可能不同的Godot版本，方法不同
				var screen_pos = get_viewport().get_screen_transform() * click_position
				Input.warp_mouse(Vector2i(screen_pos))
	pass


### 
### 用于触发移动界面的Area2D区域，触发的事件
### 
func _on_input_event(_viewport: Node, event: InputEvent, _shape_idx: int) -> void:
	# 判断是否为鼠标左键的点击事件
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT:
		if event.pressed: # event.pressed为true表示按下，false表示释放
			is_dragging = true # 正在拖拽标识
			click_position = get_viewport().get_mouse_position() # 获取鼠标当前点击的位置
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED) # 开启鼠标模式

	pass # Replace with function body.
