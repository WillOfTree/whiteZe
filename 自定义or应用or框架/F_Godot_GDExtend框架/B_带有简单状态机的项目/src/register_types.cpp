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
 * 注意：要设置默认的#include位置为项目根目录
 */
#include "main_node.h" 

/* 状态机 */
#include "fsc/fsc.h"
#include "fsc/finite_state_machine/init_state.h"
#include "fsc/finite_state_machine/ordinary_state.h"
#include "fsc/finite_state_machine/change_scence_state.h"

/* 管理器 */
#include "controller/controller_node.h"
#include "controller/input_manager.h"
#include "controller/game_manager.h"
#include "controller/signal_manager.h"


using namespace godot;

/* 初始化注册方法
 * 这里与register_types.h中修改的方法名相同
 */
// void initialize_t_game_module(ModuleInitializationLevel p_level) {
void INIT_FUNCTION_NAME(ModuleInitializationLevel p_level)
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
	 * 所有类的基类节点，必须放到最前面
	 */
	// 场景基类节点
	ClassDB::register_class<TMainNode>();


	/**
	 * 状态机类
	 */
	ClassDB::register_class<TFSC>();
	ClassDB::register_class<TInitState>();
	ClassDB::register_class<TOrdinaryState>();
	ClassDB::register_class<TChangeScenceState>();


	/**
	 * 管理器类
	 */
	ClassDB::register_class<TControllerNode>();
	ClassDB::register_class<TGameManager>();
	ClassDB::register_class<TInputManager>();
	ClassDB::register_class<TSignalManager>();

	
}




/* 卸载注册方法
 * 这里与register_types.h中修改的方法名相同
 */
void UNINIT_FUNCTION_NAME(ModuleInitializationLevel p_level)
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
	GDExtensionBool GDE_EXPORT TENTRY_SYMBOL(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		/* 修改参数名称
		 * 这里initialize_t_game_module、uninitialize_t_game_module
		 * 应与register_types.h中自定义方法名相同
		 */
		init_obj.register_initializer(INIT_FUNCTION_NAME);
		init_obj.register_terminator(UNINIT_FUNCTION_NAME);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
