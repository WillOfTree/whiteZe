# Godot C++ 开发框架手册

- Godot命名规范：

  文件名，目录名使用蛇形命名法（例如：start_state）

  类名使用大驼峰命名法

## 节点调用方法说明

- 优先使用信号（解耦设计）
  1. 不同场景中方法调用、场景节点的位置在未来会发生变化、使用Get_Node方法获取的路径过长（超过3个节点）
  1. GDScript调用GDScript方法
  1. GDExtension与GDScript之间的调用，且不要返回值
  1. GDScript调用TFSC中的方法
  1. 一个信号触发多个方法的情况
- 使用get_node方法

  1. GDExtension之间的方法调用，功能性节点（TMainNode、TControl等固定位置节点）
  2. 同一个场景中使用了（%）唯一节点，修改场景中节点不会引起错误
  3. GDExtension与GDScript之间的调用，需要返回值
  4. 在高频调用的方法中（例如_process方法中）

## 常见错误

1. 资源挂载节点，不显示资源位置

   应检查`D_METHOD`的方法与`PropertyInfo`方法是否一致

   应检查`add_property`后的字符是不是当前类名

2. 不显示自定义节点

   应检查节点注册顺序，父类应在子类先注册

## 目录结构

### 一、C++项目目录

``` shell
# 项目根目录
 ├─demo `Godot项目目录`
 ├─bin `存放编译后的可执行文件（Godot引擎或游戏）`
 ├─external `第三方库`
 |	└─godot-cpp
 ├─include `头文件目录` 
 ├─src `C++代码目录` 
 |	├─FSC # 详细查看：一、状态机结构
 |	|	├─finite_state_machine 
 |	|	├─battery_substate 
 |	|	└─fsc.cpp 
 │  ├─manager_controller # 详细查看：二、管理器节点
 │  ├─pickup_object # 详细查看：可拾取物品目录结构
 |	├─resources_data 
 |	|	├─skill_data # 详细查看：三、skill结构
 |	|	└─role_data  `角色数据文件夹`
 |	|		├─protagonist_data.cpp # 主角资源
 |	|		├─enemy_data.cpp # 敌人资源
 |	|		└─role_data.cpp # 角色资源
 |	├─register_types.cpp # 注册文件
 |	└─main_node.cpp # 主节点
 └─SConstruct  # SCons构建脚本
```

### 二、Godot目录说明

``` shell
# Godot项目目录
├─assets # 存放外部原始资源，图像、声音、字体等等
|   ├─textures # 图像，纹理
|   └─fonts    # 文件字体
├─entites `实体（.tscn)，游戏场景中所有可见对象`
|   ├─enemies `敌人` 
|   ├─players `玩家`
|   ├─utils_set `工具集合`
|	|	└─Button.tscn # 按钮场景
|   ├─equipments `装备`
|   ├─skill `技能`
|	|	├─action_skills  `主动技能`
|	|	├─passive_skills `被动技能`
|	|	└─enemy_skill `敌人技能`
|   └─items # 物品
├─components `组件（.tscn)，与不同的对象配合使用，实现不同行为`
|   ├─AI_component # AI组件
│   └─move_component # 移动组件
├─system `系统节点场景集合`
├─json_data `数据文件`
|	├─player.json # 玩家数据
|	└─scene.json # 场景数据
├─scripts `脚本目录`
|	├─teleporter `传送脚本`
|	├─utils_script `工具节点`
|	└─System `系统脚本`
|		└─tfsc.gd # TFSC状态机脚本
├─scenes `游戏场景（.tscn)`
|   ├─One.tscn # 游戏场景一
|   └─twe.tscn # 游戏场景二
├─UI `游戏UI相关`
|	├─login.tscn # 登录界面
|	├─InventoryWindow.tscn # 背包窗口
|   ├─BattleScene.tscn # 战斗场景
|   └─AttributePanel.tscn # 属性面板  
└─resources `所有继承godot resource的资源`
    ├─enemy_date `敌人数据`
    |   ├─enemydate00.tres # 敌人00数据
    |	└─enemydate01.tres # 敌人01数据
    ├─player_date `用户数据`
    |   ├─playerdate00.tres # 玩家00数据
    |	└─playerdate01.tres # 玩家01数据
    └─equipments `装备数据`
```

## MainNode场景结构

### 一、状态机结构

C++项目

``` shell
├─FSC `状态机目录`
	├─finite_state_machine `状态机文件目录`
	|	├─init_state.cpp
	|	├─bat_state.cpp
	|	├─change_scence_state.cpp
	|	├─open_backpack_state.cpp
	|	└─ordinary_state.cpp
	├─battery_substate `战斗子类`
	|	├─init_substate.cpp 
	|	├─switch_substate.cpp 
	|	├─player_substate.cpp 
	|	├─enemy_substate.cpp 
	|	├─verification_substate.cpp
	|	└─over_substate.cpp 
	└─fsc.cpp #状态机文件
```

回合制RPG

``` shell
TFSM # 无限状态机
├─TInitState # 初始化状态
├─TOrdinaryState # 一般状态，移动和站立 
├─TOpenBackpackState # 背包打开，系统打开状态
├─TChangeScenceState # 切换场景状态
└─TBatState # 战斗状态
    ├─InitialSubState # 子战斗状态-初始化
    ├─SwitchSubState # 子战斗状态-战斗切换
    ├─PlayerSubState # 子战斗状态-玩家操作状态 
    ├─EnemySubState # 子战斗状态-敌人战斗状态
    ├─VerificationSubState # 子战斗状态-验证战斗状态 
    └─OverSubState # 子战斗状态-战斗结束状态
```

横板过关

``` shell
TFSM # 无限状态机
├─TInitState # 初始化状态
├─TMoveState # 移动状态 
├─TIdleState # 站立状态
├─TJumpState # 跳跃状态
└─TChangeScenceState # 切换场景状态
```

### 二、管理器节点

C++项目

``` shell
├─manager_controller `管理类目录`
	├─abstract_manager_node.cpp # 抽象管理器基类
	├─manager_bat.cpp # 战斗管理器
	├─manager_input.cpp # 输入管理器
	├─manager_scene.cpp # 场景管理器
	├─manager_inventory.cpp # 背包管理器
	└─manager_skill.cpp # 技能管理器
```

Godot场景

``` shell
TControllerNode `TControllerNode`
├─`%`TSceneManager     # 场景管理器，用于切换场景，加载玩家，加载敌人等等
├─`%`TInputManager     # 输入管理，将输入信号传送出去，
├─`%`TMapManager       # 随机地图生成
├─`%`TInventoryManager # 物品管理
├─`%`TPlayerManager    # 玩家管理器，技能管理器
└─`%`SignalManager     # 信号管理器，定义信号，连接信号
```

### 三、主场景结构说明

1. 在GDExtension中，使用静态方法存储了当前节点的指针
1. 在Godot编辑器中，使用全局脚本，添加对应位置

``` shell
main `Node2D` # 主循环
├─TFSC `TFSC` # 系统节点
├─TManagermentController `Node` # 管理器控制节点
├─PlayerContainer `Node` # 玩家资源节点
|	├─Protagonist `TPlayerResMount` # 资源节点
|	└─Supporter `TPlayerResMount` # 配角数据
├─Windows `Node` # 一些常用窗口
|	├─InventoryWindow `CanvasLayer` # 装备界面
|	└─BattleWindow `CanvasLayer` # 战斗界面 
├─Camera2D `Camera2D` # 相机节点
└─World `Node` # 世界节点，用于动态加载
```

### 四、world场景结构

- TEnemyContainer：当前场景所有敌人模型容器，保存了当前场景所有可遇见的敌人

``` shell
World # 场景
├─ FunctionNode # 功能节点
|	└─OtherFunctionNode # 其他功能节点
├─ BG # 背景
|	├─Sprite2D # 背景图片
|	└─Sprite2D # 背景图片
├─ PickableObjectContainer # 场景中可拾取物品，PickupObject对象
|	├─Weapon # 可拾取的物品
|	├─Item # 可拾取的药品
|	└─Equipment # 可拾取装备
├─ Interaction # 交互节点
├─ Teleporter # 传送
|	├─AimPosition_1 `Marker2D` # 目标传送位置
|	└─TriggerArea_1 `Area2D` # 传送碰撞区域、传送触发区域
├─ EnemyPosition # 敌人位置marker2d位置
|	├─Marker2D
|	└─Marker2D
└─ TEnemyContainer[C++] 
```

### 五、战斗场景

``` shell
BattleWindow # 战斗场景canvasLayer
├─ BG # 背景
├─ PositionEnemy # 敌人位置
|	├─EnemyPosition_1 
|	└─EnemyPosition_1 
├─ PositionPlayer # 位置，玩家对象
|	├─PlayerPosition_1 
|	└─PlayerPosition_2 
└─ UI # 控制UI
	├─OptionPanel `PanelContainer` # 操作面板
	|	└─`%`VBoxContainer
	|		└─Button
	└─SkillPanel `PanelContainer` # 技能面板
		└─MarginContainer
			└─`%`GridContainer # 其子节点用于添加技能按钮
```

### 六、过度场景

``` shell
SceneTransition # 战斗场景canvasLayer
└─ Control # 
	├─ ColorRect `` # 
	└─ AnimationPlayer `` # 
```

## 实体结构

### 一、Player结构

| 类型        | 说明   |
| ----------- | ------ |
| Protagonist | 主角   |
| Informers   | 线人   |
| Antaonizers | 对抗者 |
| Subangle    | 副角   |
| Supporter   | 配角   |

场景结构

``` shell
characterBody2D # 玩家
├─ CollisionShape2D # 碰撞体积
├─ Graphic`Node2D` # 图层
|	├─Body `Sprite2D` # 身体
|	├─ChooseIcon `AnimatedSprite2D` #选择图标
|	└─Shadow `Sprite2D` #阴影
├─ AreaNode`Node2D` # 区域节点
|	├─ Body`Area2D` # 身体进入区域
|	|	└─ CollisionShape2D
|	└─ Interactions `Area2D`  # 交互，图层3
|		└─ CollisionShape2D 
├─ ActionAnimation `AnimationPlayer` # 动作动画
|	└─ AnimationTree `AnimationTree` # 动作动画树
├─ SkillAnimation `AnimationPlayer`  # 玩家释放技能动画
└─ ScriptNode<脚本> # 脚本节点 
```

### 二、enemy结构

- DataNode：敌人场景在初始化时，就调用其initialize方法，进行数据初始化

- 敌人加载分为2种模式，一明雷，二暗雷

  明雷：通过json脚本保存人物数据，遇敌后，通过读取json数据实例化

  暗雷：通过godot节点保存场景，遇敌后，通过实例化场景添加敌人
  
- 敌人是自动的，由组件控制

``` shell
characterBody2D # 敌人
├─ CollisionShape2D # 碰撞区域
├─ Graphic`Node2D`
|	├─Body`Sprite2D` # 身体
|	├─ChooseIcon`AnimatedSprite2D` # 选中标识
|	└─Shadow`Sprite2D` # 影子
├─ AreaBox`Node2D` # 回合制不需要
|	├─ HurtBox `Area2D` # 伤害区域，回合制不需要
|	└─ HitBox `Area2D` # 攻击区域，回合制不需要
├─ AnimationPlayer # 动画 
├─ AudioStreamPlayer2D # 音效
├─ AIScriptNode<脚本> `Node` # AI脚本挂载节点-调用组件方法
└─ FunctionNodes`Node2D`
	├─ DataNode `TEnemyResMount` # 资源挂载节点-操作资源节点
    ├─ MoveFunction # 移动组件，控制玩家移动
    ├─ BatFunction # 战斗组件，
    ├─ DropFunction # 掉落
    └─ SkillsComponent `TSkillComponent` # 技能组件
```

### 三、skill结构

技能场景-只用来保存技能动画

``` shell
Skill-ID `Node2D` # 技能ID，用于读取
├─ Property`Node`<脚本> # 保存技能属性，名称用于区分
├─ Graphic`Node2D`
|	├─ Sprite2D `Sprite2D` # 基础图层
|	└─ SkillIcon `` # 技能图标
├─ Area2D # 碰撞体积，根据需要设置碰撞
|	└─ CollisionShape2D # 碰撞体积，disabled属性应选中，取消碰撞体积
└─ AnimationPlayer # 动画节点
```

技能资源

``` shell
`skill_data` # 可拾取对象
├─ action_skill.h # 主动技能
├─ passive_skill.h # 被动技能
└─ base_skill_data.h # 基类，抽象
```



### 四、一些功能场景

#### Ⅰ、位置mark2d

- 做成场景后，可直接添加游戏场景中，并且带有图片显示

- 设置节点开始时不可见

  ``` python
  func _ready() -> void:
      # 可以直接拖拽节点
  	# $ScriptNode.visible = false
      
      var a = parent()->get_node("ScriptNode")
      a.visible = false 
  ```

场景结构

``` shell
mark2d
├─ icon`Sprite2D` # 位置图标，mark2d图标不明显
├─ ScriptNode<脚本>`Node` # 脚本挂载节点
└─ FunctionNode # 脚本挂载节点
```

#### Ⅱ、传送节点

- Area2D设置
  - Monitorable：false
  - Layer：全取消
  - Mask：保留和玩家一样的图层
  
- 因为所有场景都是共享的，所有要取消共享

  `CollisionShape2D\Shap\Resource:Local to Scene` 选中

- 应设置传送区域图块颜色，方便区分传送区域

Area2D脚本

- Area2D触发body_entered信号，触发`_player_entered`方法

``` python
# 导出变量
@export_file(" *.tscn ") var aim_scence # 目标场景，要切换过去的位置
@export var target_transition_area : String = "A" # 传送过去的位置
# 操作变量
@onready var TScenceManager = $TScenceManager # 场景管理器
@onready var collision_shape: CollisionShape2D = $CollisionShape2D #CollisionShape2D节点
# 传送位置方向
enum SIDE { LEFT, RIGHT, TOP, BOTTOM}
@export var side : SIDE = SIDE.LEFT :
    set( _v ):
        side = _v
        _update_area()
 
# 调用管理器中方法
func _player_entered(_p: Node2D)->void:
    TScenceManager.changer_scence(AimScence, target_transition_area)
    pass

# 转换传送区域方向
func _update_area():
    var new_rect: Vector2 = Vector2(32, 32)
    var new_position: Vector2 = Vector2.ZERO
    if side == SIDE.TOP:
        new_rect.x *= size
        new_position.y -=16
    elif side == SIDE.BOTTOM:
        new_rect.x *= size
        new_position.y += 16
    elif side == SIDE.LEFT:
        new_rect.y *= size
        new_position.x -= 16
    else side == SIDE.RIGHT:
        new_rext.y *= size
        new_position.x += 16
    # 防止未找到CollisionShape2D，出现错误
	if collision_shape == null:
        collision_shape = get_node("CollisionShape2D")
    # 设置
    collision_shape.shape.size = new_rect
    collision_shape.position = new_position
```

场景结构

``` shell
Area2D <脚本> # 挂载脚本
└─ CollisionShape2D `` 
```

## 架构

### 一、TMainNode

关于TMainNode循环引用错误：

1. 在TMainNode.cpp中引入管理器类
2. 在使用TMainNode::s_global_manager管理器类时，引入其对应的头文件（在.cpp文件中）

TMainNode中定义的静态变量

- `TMainNode::s_global_world `：世界节点

- `TMainNode::s_global_batmanager`：战斗管理器

- `TMainNode::s_global_playermanager`：玩家节点

- `TMainNode::s_global_inventorymanager`：仓库管理器

- `TMainNode::s_global_scenemanager`：场景管理器

- `TMainNode::s_global_inputmanager`：输入输出管理器

- `TMainNode::s_global_inventorywindow`：背包窗口

- `TMainNode::s_global_battlewindow`：战斗窗口

TMainNode可调用方法

- `sys_initialize()`：TMainNode初始化方法

TMainNode的GDScript脚本设置

``` shell
extends TMainNode

@onready var tfsc = $TFSC # 状态机核心节点引入
func _ready() -> void:
	sys_initialize(); # 系统初始化
	tfsc.fsc_initiazlie(); # 状态机初始化
	pass # Replace with function body.
	
func _process(delta: float) -> void:
	tfsc.fsc_update(delta) # 状态机每帧运行
	pass
```

### 二、TFSC状态机

提供给GDScript调用的方法

1. `fsc_initiazlie()`：状态机初始化方法 
2. `fsc_update(_delta)`：状态机update方法 

### 三、管理器类

- 管理器类要使用TMainNode中设置的s_global_manager方法，需要引入其对应的头文件，为了防止循环引入错误

Ⅰ、InputManager

Ⅲ、SceneManager

### 四、物品相关

#### Ⅰ、物品Resource类

- `pickable_object`继承Resource类

- 使用最后的子类，创建对应对象

  例如：使用`consumable_item`资源创建`big_potion.tres`（大血瓶）物品资源
  
- 资源类并没有镶嵌到任何场景中

``` shell
`pickable_object` # 可拾取对象
├─`items` # 物品
|	├─ item.h # 基类，抽象
|	|	## obtain_item_type()：获取物品类型（虚）
|	├─ dead_effect_item.h  # 死亡影响物品
|	└─ consumable_item.h   # 可消耗物品
├─`equipments` # 装备
|	├─equipments.h # 基类，抽象
|	|	## obtain_equipment_type():获取装备类型（虚）
|	├─body_equipments.h       # 身体位置 
|	├─hand_left_equipments.h  # 左手位置
|	├─hand_right_equipments.h # 右手位置
|	├─helmet_equipments.h     # 帽子位置
|	└─neck_equipments.h       # 项链位置
├─slot_data.h # 插槽类，存放资源和个数
└─pickable_object.h # 基类，抽象
	## obtain_pickup_type()`: 获取是装备还是物品（虚）
	## use()使用方法（虚），其具体子类重写此方法
```

`pickable_object`类的主要属性

- `name # String`：名称
- `description # String`：描述
- `texture # Texture2D`：物品纹理

#### Ⅱ、Res类与库存管理器关系

- 【节点】InventoryManager：库存管理器器

  `item # SlotData`，用于存放SlotData资源

  `equipment # SlotData`，用于存放SlotData资源

- 【资源】SlotData：物品插槽数据

  `data # pickup_object`，用于存放资源类

  `quantity # Int`，物品数量

- 【资源】pickup_object对象，使用其子类生成具体对象

  ConsumableItem：物品数据，用于生成具体的物品，例如`大血瓶.tres`

  DeadEffectItem：物品数据，用于生成具体的物品，例如`复活甲.tres`

  BodyEquipments：物品数据，用于生成具体的物品，例如`胸甲.tres`

  HandLeftEquipments：物品数据，用于生成具体的物品，例如`盾牌.tres` 

#### Ⅲ、库存

装备菜单场景

``` shell
Menu`CanvasLayer` # 菜单
└─ Control # 可以不添加代码，就使用方向键移动焦点
    └─ PanelContainer`PanelContainer` # 图标 
        └─ GridContainer`GridContainer` # 九宫格，物品存放的
            └─ InventorySlot`Button`【场景】 # 物品插槽要做成场景，方便使用
            	├─ TextureRect # 物品图标,获取资源的texture属性
            	├─ ScriptNode`node`<脚本1> # 脚本节点
				└─ Label # 数量个数
```

脚本1：参考

``` python
# 获取节点
# 每当SlotData数据修改时调用set_slot_data方法
var slot_data:SlotData: set = set_slot_data
@onready var texture_rect: $TextureRect #物品图标节点
@onready var label: $Label #标签节点

func _ready() -> void:
    texture_rect.texture = null
    label.text = ""
    
func set_slot_data(value: SlotData) -> void:
    slot_data = value
    if slot_data == null:
        return
    texture_rect.texture = Slot_data.data.texture # 设置物品纹理
    label.text = str(slot.data.quantity) # 设置数量
```

#### Ⅳ、可拾取物品场景

- FunctionNode节点：就1个功能，**保存SlotData类**，供其他C++方法调用SlotData类
- 掉落物品场景一般使用`Node2D`，但一些物品会有移动动作，应使用`characterBody2D`节点

掉落物品场景

``` shell
PickUpObject `Node2D`|`characterBody2D`
├─ Icon`Node2D` # 图标 
|	├─ItemIcon`Sprite2D` # 物品图标
|	└─CueIcon`Sprite2D` # 提示图标 
├─ Area2d # 拾取物品范围
|	└─ CollisionShape2D 
├─ AudioStreamPlayer2D # 拾取音效
├─ ScriptNode<脚本1> # 挂载脚本的节点，响应Area区域进入响应方法
└─ FunctionNode `SlotNode` # 功能节点
```

脚本1

``` python
@export var item_data : ItemData : set = _set_item_data

@onready var sprite_2d: Sprite2D = $ItemIcon # 获取精灵节点
# 修改可拾取物品节点数据
func _set_item_data( value: ItemData ) -> void:
    item_data = value
    if item_data and sprite_2d:
        sprite_2d.texture = item_data.texture
    pass
```

#### Ⅴ、掉落物品

1. 掉落物品，掉落的是`SlotData`资源
2. 其使用的结构是<可拾取物品场景>
3. 当物品掉落时，应初始化`PickUpObject`场景，并设置`FunctionNode`中的数据保存对应的数据节点
4. 若游戏中不显示具体的物品，可以不实例化`PickUpObject`场景，直接交换数据即可

### 五、场景交互

#### Ⅰ、可交互场景

宝箱：

``` shell
Treasure-chest`Node2D`
├─ Skin  `Sprite2D` # 宝箱皮肤
├─ Items `Sprite2D` # 宝箱内物品皮肤
├─ AnimationPlayer  # 动画
├─ AudioStreamPlayer2D        # 音频播放
├─ StaticBody2D`StaticBody2D` # 静态的碰撞形状
|	└─ CollisionShape2D `` 
├─ Area2D # 交互区域，玩家交互图层相同
|	└─ CollisionShape2D
├─ ScriptNode`Node`<脚本> # 交互区域，玩家交互图层相同
└─ FunctionNode
```

解密按钮

``` shell
Treasure-chest`Node2D`
├─ Skin  `Sprite2D` # 宝箱皮肤
├─ Area2D  # 
|	└─ CollisionShape2D  # 
├─ AudioStreamPlayer2D #音频
├─ ScriptNode`Node`<脚本>
└─ FunctionNode ``
```



#### Ⅱ、谜题





## 属性说明

#### Ⅰ、通用属性

| 属性              | 作用                           | 其他说明                                  |
| ----------------- | ------------------------------ | ----------------------------------------- |
| Collision / Layer | Layer当前对象所在的层          | `General/Layer Name/2D Phystcs`可设置名称 |
| Collision / Mask  | Mask当前对象可以交互、碰撞的层 | `General/Layer Name/2D Phystcs`可设置名称 |
|                   |                                |                                           |

#### Ⅱ、Area2D

| 属性        | 作用                                                         | 适用场景                           |
| :---------- | :----------------------------------------------------------- | :--------------------------------- |
| monitorable | 控制 `Area2D` 是否可以被其他 `Area2D` 或 `PhysicsBody2D` 检测到。 | 隐藏的陷阱区域或不可见的触发区域。 |
| monitoring  | 控制 `Area2D` 是否检测其他 `Area2D` 或 `PhysicsBody2D`。     | 关闭检测功能、优化性能。           |

### 关于如何修改Button样式

1. TextureButton：专为图片按钮设计，支持多状态贴图
2. StyleBoxTexture：将图片作为按钮背景，支持九宫格拉伸

直接使用 `TextureButton`（直接替换为图片按钮）

使用普通 `Button` + 图片样式（自定义 StyleBox）

1. 创建 Button 节点
2. 用图片替换背景样式
   -  `Theme Overrides` → `Styles` $\to$  `Normal` 旁边的 `[空]` → 选择 `New StyleBoxTexture`
   - 在新弹出的 `StyleBoxTexture` 属性中：
     - `Texture`：拖入你的按钮图片
     - `Margin`（边距）：调整图片九宫格切分（避免拉伸变形）
3. 为其他状态添加图片（可选）：对 `Hover`、`Pressed` 等状态重复上述步骤，替换不同图片



## 功能

### 一、攻击概率计算

闪避率计算

- 功能头文件：`#include <godot_cpp/variant/utility_functions.hpp>` 
- 由父类：role计算

``` c++
float f = UtilityFunctions::randf_range(0, 1); // 获取随机数

// 判断攻击者的闪避率是否大于当前随机数
// Dodge：玩家闪避率
// 玩家的闪避率越高，大于f的概率就越大
if (Dodge >= f)
{
    return 1; //成功闪避
}
return 0; // 闪避失败
```

暴击率计算

- 功能头文件：`#include <godot_cpp/variant/utility_functions.hpp>`

``` c++
float f = UtilityFunctions::randf_range(0, 1); // 获取随机数

// 判断攻击者的暴击率是否大于当前随机数
// critical：暴击率
// 玩家的暴击率越高，暴击概率越大
if (critical >= f)
{
    return 1; // 触发暴击
}
return 0; // 没有触发暴击
```

伤害计算

### 二、敌人加载方法

1. **固定敌人**：简单场景直接在场景中放置关键敌人（如Boss）。
2. **动态敌人**：通过 `Marker2D` 动态生成小怪或随机敌人。复杂场景优先使用 `Marker2D` 动态生成，提高灵活性和可维护性。
3. **配置文件支持**：使用JSON或Godot的 `Resource` 系统定义敌人类型和生成规则。

### 三、相机设置

- 视频参考：[Godot教程使用 Godot 4 制作 2D 动作冒险类 RPG](https://www.bilibili.com/video/BV1sB2NYLEwj/?p=8&share_source=copy_web&vd_source=ccf6eacaac851ed567f6ba47c8fda545)

``` c++
tileMap.get_used_rect(); //
tilemap.tile_set.tile_side; //地图大小
camera.limit_top;//相机顶位置
/* 重置相机位置，取消过度动画 */
camera.reset_smoothing(); 
camera.force_update_scroll();
camera.limit_left = int() // 设置相机大小
```

### 四、玩家重叠问题

启用Y排序

1. 根节点（游戏场景）设置`Y Sort Enabled`启用
2. Tilemap设置Y启用
3. Tilemap -> “层”设置Y启用
4. player节点设置Y启用
5. 设置Player层与“层”的z坐标处同一层
6. 修改贴图“选择”-“Y排序原点”
7. 修改player节点下的“Animationbody2D”节点的锚点

### 五、遇敌脚本

``` python
extends Node
# 战斗状态机位置
@onready var batstate = get_tree().get_current_scene().get_node("TFSC/TBatState");
# 遇敌类型\soldier小兵 infernal精英 boss
var monster_type = "soldier"

func _on_area_2d_body_entered(body):
	# 从场景中Enemy添加
	batstate.enter_bat_state(monster_type);
	pass # Replace with function body.
```

### 六、追逐敌人

### 七、对话框dialogue

创建NPC说话的气泡框

- 若是像素需要修改 CanvasItem / Texture / Filter $\to$ Nearest属性

``` shell
PanelContainer
	├─ NinePatchRect # 对话框背景
	└─ MarginContainer # 边距
		└─Label / RichTextLabel # 文本标签，显示说话文字
```

### layer physics

1. Layer：block_movement 阻挡移动
2. Layer：

### 

### 碰撞检测

1. 检测碰撞需要 `Area2D` 节点，被碰物体（敌人）与碰撞物体（玩家）都需要添加 `Area2D` 节点
2. 使用玩家（敌人）的信号 `area_entered` 进行碰撞后代码运行

本例是玩家 `CharacterBody2D` 中的 `Area2D` 发出信号

``` shell
# Player节点构造
Player # CharacterBody2D 类型
├─ CollisionShape2D `碰撞结构`
├─ temp # 其他节点
└─ Area2D `碰撞体检测节点` 
	└─ CollisionShape2D `碰撞结构`
```

多场景使用C++步骤流程

1. 接收信号类（对信号进行处理），暴露信号方法

   ``` c++
   ClassDB::bind_method(
       // change_state_parameter：信号
       // &TBatState::change_state_parameter：信号触发方法
       D_METHOD("change_state_parameter", "a"), &TBatState::change_state_parameter
   );
   ```

2. 连接信号

   ``` c++
   // 任意类，获取到指定 Area2D 节点，进行信号连接
   Player
       ->get_node<Area2D>("Area2D")
       // area_entered：区域进入信号Godot官方信号
       // ba_s：类，战斗节点
       // change_state_parameter：ba_s中的方法
       // 注意：这里链接的是 Area2d 节点中area_entered信号
       ->connect("area_entered", Callable(ba_s, "change_state_parameter"));
   ```



### 补间动画

- C++使用没有效果，只进行记录

  ```c++
  #include <godot_cpp/classes/tween.hpp>
  #include <godot_cpp/classes/property_tweener.hpp>
  
  Ref<Tween> tw = Node::create_tween()->set_loops();
  bool b = tw->is_valid();// 验证是否存活
  bool a = tw->is_running();// 验证是否运行
  
  Sprite2D *sp01 = get_node<Sprite2D>("../sp2");
  // 属性补间
  tw->tween_property(cr, NodePath("color:a"), 255.0, 4.0);
  ```

- 使用GD脚本编写

  `.set_delay(x)`：延迟x秒执行补间动画

  `.set_loop()`：设置补间动画循环

  `.from_current(x)`：从x状态执行到目标状态

  `.set_ease()`：设置变化曲线

  `.set_trans()`：带有物理属性

``` python
# 获取节点，4.0以上版本需要使用@字符
@onready var ax = $sp2
# 创建一个补间动画
var tween = create_tween()
# 创建属性补间动画
# ax:欲添加补间动画的对象
# "position"：初始状态
# Vector2(1000, 500)：目标状态
# 5：持续时间
tween.tween_property(ax, "position",Vector2(1000, 500), 5)
tween.interval(1.0); # 循环的补间动画的间隔
```

### 焦点移动

1. 应设置主题元素 focus 效果，这是当节点（一般是Button）获取焦点显示的效果，不然没有变化
2. 当使用手柄时应设置 Input Map$\to$ Show Built in Actions选项，然后设置ui_left、ui_rigth、ui_up、ui_bottom等按键映射，这样就可以使用手柄移动焦点
3. 要移动焦点，需要有一个控件获取焦点

GDScript脚本-获取焦点

``` python
@onready var b = $Button
func _ready() -> void:
    b.grab_focus() # 按钮Button获取焦点
```



