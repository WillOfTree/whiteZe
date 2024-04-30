/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#ifndef EXAMPLE_REGISTER_TYPES_H
#define EXAMPLE_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

/** 主要修改位置：函数名称
 * initialize_example_module、uninitialize_example_module
 * 分别为初始化自定义模块和卸载自定义模块 
 * 函数名可以自定义，
 *  例如：initialize_example_module修改为initialize_test_module
 */
//void initialize_example_module(ModuleInitializationLevel p_level);
//void uninitialize_example_module(ModuleInitializationLevel p_level);
void initialize_tree_godot_module(ModuleInitializationLevel p_level);
void uninitialize_tree_godot_module(ModuleInitializationLevel p_level);

#endif // EXAMPLE_REGISTER_TYPES_H
