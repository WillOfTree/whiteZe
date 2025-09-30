/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#ifndef EXAMPLE_REGISTER_TYPES_H
#define EXAMPLE_REGISTER_TYPES_H

/***********************************************************************/
// Godot的gdextension的entry_symbol，进入信号
// 每一个lib的标识都应不相同
#define TENTRY_SYMBOL library_entry_symbol   

/***********************************************************************/


/** 主要修改位置：函数名称
 * initialize_t_game_module、uninitialize_t_game_module
 * 分别为初始化自定义模块和卸载自定义模块
 * 函数名可以自定义，
 *  例如：initialize_t_game_module修改为initialize_test_module
 */
void initialize_module(ModuleInitializationLevel p_level);
void uninitialize_module(ModuleInitializationLevel p_level);
// 卸载单例-可能以后会修改
void t_unregister_engine_singleton(const godot::String name);


#endif // EXAMPLE_REGISTER_TYPES_H
