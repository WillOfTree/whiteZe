/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#ifndef EXAMPLE_REGISTER_TYPES_H
#define EXAMPLE_REGISTER_TYPES_H

/***********************************************************************/

#define INIT_FUNCTION_NAME initialize_module      // 进入函数名称
#define UNINIT_FUNCTION_NAME uninitialize_module  // 释放函数名

// Godot的gdextension的entry_symbol，进入信号
// 每一个lib的标识都应不相同
#define TENTRY_SYMBOL library_entry_symbol    

/***********************************************************************/


#include <godot_cpp/core/class_db.hpp>

using namespace godot;

/** 主要修改位置：函数名称
 * initialize_t_game_module、uninitialize_t_game_module
 * 分别为初始化自定义模块和卸载自定义模块
 * 函数名可以自定义，
 *  例如：initialize_t_game_module修改为initialize_test_module
 */
// void initialize_t_game_module(ModuleInitializationLevel p_level);
// void uninitialize_t_game_module(ModuleInitializationLevel p_level);
void INIT_FUNCTION_NAME(ModuleInitializationLevel p_level);
void UNINIT_FUNCTION_NAME(ModuleInitializationLevel p_level);

#endif // EXAMPLE_REGISTER_TYPES_H
