# Keyboard Listener键盘监听

注意：

- 当Godot软件获取焦点时，本dll无法获取键盘输入，因为Godot接手了键盘输入

``` python
# 开始监听
TKeybordListenerController.start_listen() 
# 停止监听
TKeybordListenerController.stop_listen() 
# 验证监听
TKeybordListenerController.is_listen() 

# 连接信号，只有一个信号key_event
KeybordListenerSignal.connect("key_event", xxxx)
# keycode:按键代码ASCII码，Keystatus:按键状态，分为down,up2个状态
func xxxx(keycode, keystatus) -> void:
	pass
```

