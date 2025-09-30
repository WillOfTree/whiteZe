extends Node

# 全局环境配置
# 主要配置一些基础节点位置，方便其他节点调用
# 需要添加进自动加载中使用：项目 - 项目设置 - 全局

# @onready会等节点树加载完毕，防止出现不在节点树错误
@onready var GlobalMain = get_node("/root/TMainNode")

# 状态机
@onready var GlobalTFSC = get_node("/root/TMainNode/TFSC")

# 管理器
@onready var GlobalController = get_node("/root/TMainNode/TControllerNode")
@onready var GlobalSignal = get_node("/root/TMainNode/TControllerNode/TSignalManager")
@onready var GlobalGame = get_node("/root/TMainNode/TControllerNode/TGameManager")
