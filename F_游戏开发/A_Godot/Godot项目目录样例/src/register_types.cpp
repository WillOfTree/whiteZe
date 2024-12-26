/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

/**
 * 包含自己写的函数类
 */
// 所有节点的基类
#include "../include/main_node.h"


/**
 * 状态机
 */
#include "../include/fsc/fsc.h"
#include "../include/fsc/state_change_scence.h"
#include "../include/fsc/state_open_backpack.h"
#include "../include/fsc/state_init.h"
#include "../include/fsc/state_ordinary.h"
#include "../include/fsc/state_bat.h"
// 战斗子状态
#include "../include/fsc/battery_substate/bat_setup.h" 
#include "../include/fsc/battery_substate/bat_turn.h" // 子状态
#include "../include/fsc/battery_substate/bat_auto_enemy.h" // 子类
#include "../include/fsc/battery_substate/bat_operate_player.h" // 子类
#include "../include/fsc/battery_substate/bat_over.h" // 子类
#include "../include/fsc/battery_substate/bat_verification.h" // 子类


/**
 * 资源挂载节点
 */
// 基类
#include "../include/res_mount_node/res_mount_node.h"

// 父类
#include "../include/res_mount_node/role_node/role.h"
#include "../include/res_mount_node/role_node/role_player.h"
#include "../include/res_mount_node/role_node/role_player.h"
// 玩家实际使用的节点
#include "../include/res_mount_node/role_node/general_enemy.h"
#include "../include/res_mount_node/role_node/general_player.h"

// 容器节点
#include "../include/res_mount_node/container_node/container.h"
// 实际使用的容器节点
#include "../include/res_mount_node/container_node/enemy_container.h"
// #include "../include/res_mount_node/container_node/player_container.h"
#include "../include/res_mount_node/container_node/skill_container.h"


/**
 * 管理器
 */
#include "../include/manager_controller/manager_controller.h"
#include "../include/manager_controller/manager_scene.h"
#include "../include/manager_controller/manager_input.h"
#include "../include/manager_controller/manager_inventory.h"
#include "../include/manager_controller/manager_player.h"
#include "../include/manager_controller/manager_enemy.h"
#include "../include/manager_controller/manager_skill.h"


/**
 * 可拾取物品-
 */
// 基础类
#include "../include/pickable_object/pickable_object.h"
#include "../include/pickable_object/equipments/equipment.h"
#include "../include/pickable_object/items/item.h"
// 装备位置
#include "../include/pickable_object/equipments/body_equipment/body_equipment.h"
#include "../include/pickable_object/equipments/hand_left_equipment/hand_left_equipment.h"
#include "../include/pickable_object/equipments/hand_right_equipment/hand_right_equipment.h"
#include "../include/pickable_object/equipments/helmet_equipment/helmet_equipment.h"
#include "../include/pickable_object/equipments/neck_equipment/neck_equipment.h"

// 可使用物品
#include "../include/pickable_object/items/consumable_item/consumable_item.h" // 主动使用物品
#include "../include/pickable_object/items/dead_effect_item/dead_effect_item.h" // 死亡生效物品

#include "../include/pickable_object/items/consumable_item/big_potion.h" // 大血瓶
#include "../include/pickable_object/items/consumable_item/small_potion.h" // 小血瓶

// 装备
#include "../include/pickable_object/equipments/hand_right_equipment/sword.h"



/**
 * 资源节点
 */
// 父类
#include "../include/resources/t_resources.h"
#include "../include/resources/entites_data/entity_data.h"
#include "../include/resources/entites_data/enemy_data/enemy.h"
#include "../include/resources/entites_data/player_data/player.h"
// 玩家
#include "../include/resources/entites_data/player_data/protagonist_data.h"
// 敌人
#include "../include/resources/entites_data/enemy_data/general_data.h"
// 技能
#include "../include/resources/skill_data/skill.h"
#include "../include/resources/skill_data/action_skills/action_skill_data.h"
#include "../include/resources/skill_data/passive_skills/passive_skills_data.h"

#include "../include/resources/skill_data/action_skills/general_action_skill_data.h"
#include "../include/resources/skill_data/passive_skills/general_passive_skill_data.h"


/**
 * utils功能节点
 */
#include "../include/utils/utils_node.h"
#include "../include/utils/Tbutton.h"
#include "../include/utils/test.h"


/**
 * 组件
 */
#include "../include/enemy_component/component.h"
#include "../include/enemy_component/drop_component.h"
#include "../include/enemy_component/move_component.h"
#include "../include/enemy_component/skill_component.h"



using namespace godot;

/* 初始化注册方法
 * 这里与register_types.h中修改的方法名相同
 */
// void initialize_t_game_module(ModuleInitializationLevel p_level) {
void initialize_tree_game_module(ModuleInitializationLevel p_level)
{
	/* 如果需要在编译器中初始化类
	 * 将 MODULE_INITIALIZATION_LEVEL_SCENE 修改为 MODULE_INITIALIZATION_LEVEL_EDITOR
	 */
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	/* 这里注册自己写的函数类
	 *
	 * ClassDB::register_class：注册我们自己编写的类
	 * 例如：自定义头文件test.h，自定义类TEST
	 * ClassDB::register_class<类名>();
	 * ClassDB::register_class<Example>();
	 */
	// 所有类的基类节点，必须放到最前面
	ClassDB::register_abstract_class<A_MainNode>();
	// --- 测试
	ClassDB::register_class<TTest>();

	/**
	 * 状态机相关类
	 */
	// ClassDB::register_class<TSystemNode>();
	ClassDB::register_class<TFSC>();
	ClassDB::register_class<TOrdinaryState>();
	ClassDB::register_class<TOpenBackpackState>();
	ClassDB::register_class<TChangeScenceState>();
	ClassDB::register_class<TBatState>();
	ClassDB::register_class<TInitState>();
	// 战斗子类
	ClassDB::register_class<BatSetup>(); 
	ClassDB::register_class<BatTurn>(); // 战斗子类
	ClassDB::register_class<BatAutoEnemy>(); // 战斗子类
	ClassDB::register_class<BatOperatePlayer>(); // 战斗子类
	ClassDB::register_class<BatVerification>(); // 战斗子类
	ClassDB::register_class<BatOver>(); // 战斗子类


	/**
	 * 管理器相关
	 **/
	ClassDB::register_class<TManagerController>();
	ClassDB::register_class<TSceneManger>();
	ClassDB::register_class<TInputManager>();
	ClassDB::register_class<TInventoryManager>();
	ClassDB::register_class<TPlayerManager>();
	ClassDB::register_class<TEnemyManager>();
	ClassDB::register_class<TSkillManager>();



	/**
	 * 资源挂载节点
	 */
	ClassDB::register_class<TResMountNode>();// 资源挂载节点的基础父类
	
	// 容器节点
	ClassDB::register_class<TContainerNode>(true);// 基础父类
	ClassDB::register_class<TEnemyContainer>();
	ClassDB::register_class<TSkillContainer>();

	// 角色资源节点
	ClassDB::register_class<TRoleNode>(true); // 父类
	ClassDB::register_class<TPlayerRole>(true);// 玩家资源
	ClassDB::register_class<TEnemyRole>(true);// 敌人资源 
	
	ClassDB::register_class<TGeneralPlayer>(); // 一般玩家节点
	ClassDB::register_class<TGeneralEnemy>(); // 一般敌人节点


	/**
	 * 组件 
	 **/ 
	ClassDB::register_class<TEnemyComponent>(); // 基类

	ClassDB::register_class<TDropComponent>();
	ClassDB::register_class<TMoveComponent>();
	ClassDB::register_class<TSkillComponent>();


	/**
	 * 可拾取物品节点
	 */
	ClassDB::register_abstract_class<TPickableObject>();// 基础父类
	ClassDB::register_abstract_class<TEquipmentObject>();// 装备基类
	ClassDB::register_abstract_class<TItemObject>(); // 物品基类
	// 装备位置
	ClassDB::register_class<TBodyEquipment>();
	ClassDB::register_class<TLeftEquipment>();
	ClassDB::register_class<TRightEquipment>();
	ClassDB::register_class<THelmetEquipment>();
	ClassDB::register_class<TNeckEquipment>();
	// 物品分类
	ClassDB::register_class<TConsumableItem>();
	ClassDB::register_class<TDeadEffectItem>();
	// 可拾取物品-装备
	ClassDB::register_class<ESword>();
	// 可拾取物品-物品
	ClassDB::register_class<ISmallPotion>(); // 小血瓶
	ClassDB::register_class<IBigPotion>();
	

	/**
	 * utils功能节点
	 */
	ClassDB::register_abstract_class<TUtilsNode>();// 基础父类
	// 功能节点
	ClassDB::register_class<TButton>();


	/**
	 * 资源节点注册
	 */
	// 父类
	ClassDB::register_class<A_TResourcesData>();// 资源节点-父类
	
	// 实体资源节点
	ClassDB::register_class<TEntityData>(); // 实体基类
	ClassDB::register_class<TPlayerData>(); // 玩家基类
	ClassDB::register_class<TEnemyData>(); // 敌人基类
	// 实际使用的节点
	ClassDB::register_class<TProtagonistData>(); // 主角
	ClassDB::register_class<TEnemyGeneralData>(); // 一般的敌人资源

	// 技能资源
	ClassDB::register_class<TSkillData>();// 
	ClassDB::register_class<TPassiveSkillData>(); // 被动技能
	ClassDB::register_class<TActionSkillData>();  // 主动技能
	
	ClassDB::register_class<GeneralActionSkillData>();
	ClassDB::register_class<GeneralPassiveSkillData>();
}

/* 卸载注册方法
 * 这里与register_types.h中修改的方法名相同
 */
void uninitialize_tree_game_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}

extern "C"
{
	/* 这里需要记住函数名example_library_init
	 * 这个函数名可以修改，后面需要将这个函数名传给Godot作为我们模块入口
	 */
	GDExtensionBool GDE_EXPORT tree_game_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		/* 修改参数名称
		 * 这里initialize_t_game_module、uninitialize_t_game_module
		 * 应与register_types.h中自定义方法名相同
		 */
		init_obj.register_initializer(initialize_tree_game_module);
		init_obj.register_terminator(uninitialize_tree_game_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
