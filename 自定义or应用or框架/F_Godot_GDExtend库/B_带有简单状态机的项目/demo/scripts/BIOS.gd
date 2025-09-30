## BIOS启动文件
## 主要功能：调用状态机启动、控制器初始化、配置文件的设置
## 
##
## 状态机方法
## var t = ClassDB.instantiate("TFSCMachine") as TFSCMachine
## t.fsc_initiazlie()
##
## 控制器启动启动
## var f = ClassDB.instantiate("TControllerInit") as TControllerInit
## f.initiazlie()
##
## 单例注册
## var k = TMainNode.get_singleton() 获取静态单例
## 
## Godot注册单例
## Engine.register_singleton("xx", k)
##
extends Node


func _ready() -> void:
	pass
	

#---------------------------------------------------
## 输入检测
func _input(_event: InputEvent) -> void:
	pass

## 图形更新
func _process(_delta: float) -> void:
	pass
	
## 物理移动 
func _physics_process(_delta: float) -> void:
	pass