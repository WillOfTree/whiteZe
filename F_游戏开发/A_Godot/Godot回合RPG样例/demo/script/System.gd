extends Node

@onready var tfsc = $TFSC
@onready var tscene_manager = $TSceneManger

# Called when the node enters the scene tree for the first time.
func _ready():
	tfsc.init() # 状态机初始化方法
	tscene_manager.load_scene_to_world("mountain_seas_village") # 加载基础场景
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	tfsc.update(delta)
	pass
