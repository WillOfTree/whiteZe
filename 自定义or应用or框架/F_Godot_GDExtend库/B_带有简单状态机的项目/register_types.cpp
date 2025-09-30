/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include <godot_cpp/classes/engine.hpp>

using namespace godot;


//-----------------------------------------------------------
//--- 头文件引入 ----------------------------------------------
//-----------------------------------------------------------
/* 抽象类 */
#include "interface/controller_interface.h"


/* 状态机 */
#include "fsc_machine.h"
// #include "fsc/finite_state_machine/init_state.h"
// #include "fsc/finite_state_machine/ordinary_state.h"
// #include "fsc/finite_state_machine/change_scence_state.h"


/* 管理器 */
#include "controller_init.h"

#include "controller/input_manager.h"
#include "controller/game_manager.h"
#include "controller/signal_manager.h"


//-----------------------------------------------------------
//--- 注册 ---------------------------------------------------
//-----------------------------------------------------------
void initialize_module(ModuleInitializationLevel p_level)
{
	/* 如果需要在编译器中初始化类
	 * 将 MODULE_INITIALIZATION_LEVEL_SCENE 修改为 MODULE_INITIALIZATION_LEVEL_EDITOR
	 */
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
	/*****************************
	 * 抽象类注册
	 * ClassDB::register_abstract_class<>();
	 *****************************/
	ClassDB::register_abstract_class<TControllerInterface>();

	
	/*******************************
	 * 状态机类
	 * ClassDB::register_class<>();
	 ******************************/
	ClassDB::register_class<TFSCMachine>();
	

	/******************************
	 * 管理器类注册
	 ****************************/
	ClassDB::register_class<TControllerInit>();

	ClassDB::register_class<TGameManager>();
	ClassDB::register_class<TInputManager>();
	ClassDB::register_class<TSignalManager>();

	// 初始化方法注册
	TControllerInit::register_controller(TGameManager::get_singleton());
	TControllerInit::register_controller(TSignalManager::get_singleton());
	TControllerInit::register_controller(TInputManager::get_singleton());


	/**************************
	 * 供GDScript调用的单例 
	 *! 注意：要填写反注册单例
	 **************************/ 
	Engine::get_singleton()->register_singleton(
		"TGameManager", 
		TGameManager::get_singleton()
	);
}


//-----------------------------------------------------------
//--- 卸载 ---------------------------------------------------
//-----------------------------------------------------------
void uninitialize_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	/**
	 *! 反注册单例
	 */
	t_unregister_engine_singleton("TGameManager");
}


//-----------------------------------------------------------------
//--- 其他 ---------------------------------------------------------
//-----------------------------------------------------------------
/* 卸载自定义类 */
void t_unregister_engine_singleton(const godot::String name)
{
	if (Engine::get_singleton()->has_singleton(name)) 
	{
		// 获取单例对象指针，以便后续处理
		godot::Object *singleton = Engine::get_singleton()->get_singleton(name);
		// 从引擎中注销单例
		Engine::get_singleton()->unregister_singleton(name);
		// 如果单例对象是由你分配内存的，并且你负责它的生命周期，记得在这里释放内存
		memdelete(singleton);
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
		init_obj.register_initializer(initialize_module);
		init_obj.register_terminator(uninitialize_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
