#include "controller/input_manager.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>


using namespace godot;

TInputManager * TInputManager::singleton = nullptr;

void TInputManager::_bind_methods() 
{
    // ClassDB::bind_method(D_METHOD("set_move_down", "r"), &TInputManager::set_move_down);
    // ClassDB::bind_method(D_METHOD("get_move_down"), &TInputManager::get_move_down);
    // ClassDB::add_property("TInputManager",
    // 	PropertyInfo(Variant::STRING, "Down"),
    //     "set_move_down",
    //     "get_move_down");
}

/**
 * 单例
 */
TInputManager * TInputManager::get_singleton()
{
    if (singleton == nullptr)
    {
        singleton = memnew(TInputManager);
    }
    return singleton;
};



/**
 * 加载按键映射
 */
void TInputManager::initialize()
{
    InputMap * _map_ii = InputMap::get_singleton();
    _map_ii->load_from_project_settings();

    ii = Input::get_singleton();
}


// 输入方向
Vector2 TInputManager::input_move_axis_direction()
{
    float h = ii->get_axis(_move_left, _move_right);
    return Vector2(h, 0);
}; 


// 输入方向
bool TInputManager::input_move_vector_direction()
{
    Vector2 d = ii->get_vector(_move_left, _move_right, _move_up, _move_down).normalized();

    // 没有输入（0，0）返回true，这里需要返回假，当有输入时返回真
    return !(d.is_zero_approx());
}; 

// 输出打印信息
// void TInputManager::input_print_info()
// {
 
//     // 有按键为真，没有按键为假
//     ii->is_action_just_pressed("G_F1");
// }; 

