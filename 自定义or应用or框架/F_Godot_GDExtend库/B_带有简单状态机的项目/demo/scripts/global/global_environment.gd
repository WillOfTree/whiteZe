extends Node

# 全局环境配置
# 主要配置一些基础节点位置，方便其他节点调用
# 需要添加进自动加载中使用：项目 - 项目设置 - 全局

# @onready会等节点树加载完毕，防止出现不在节点树错误
#var default_filedialog_dir = "D:/A_CodeItems/A_Taskbar_program/demo"

## 一定要确定到MainLoop节点，/root节点找不到其他节点
@onready var root_node = get_tree().root.get_node("MainLoop")

## 普通变量
# var current_check_button = "default"

