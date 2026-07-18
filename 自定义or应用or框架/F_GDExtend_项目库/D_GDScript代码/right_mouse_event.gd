###
### 实现鼠标右键
### 将本脚本，挂载到节点上，即可使用，需要连接信号 right_clicked ，并在 right_clicked 信号触发方法_on_right_clicked方法中进行下一步操作
###
extends Control

# 信号
signal right_clicked(keycode:String) 

func _ready() -> void:
	# 连接信号
	# 多个节点用了同一个脚本，需要一个一个连接信号，但是使用代码就不用管了
	right_clicked.connect(_on_right_clicked)
	pass

## 专门用来处理发送给该控件的GUI输入事件（鼠标点击、移动、滚轮、触摸屏等）。
## _gui_input:仅当前控件，_input是整个场景书
func _gui_input(event: InputEvent) -> void:
	
	## 判断是否为鼠标右键
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_RIGHT:
		## 鼠标右键按下
		if event.pressed:
			var t = get_parent().keyboard_res.costom_id # 获取父类属性的key
			right_clicked.emit(t) # 发射信号
			accept_event()  # 事件被消费，不会继续传递给父控件
			pass


## right_clicked信号处理方法
func _on_right_clicked(keycode: String) -> void:
	print(keycode)
	pass # Replace with function body.
