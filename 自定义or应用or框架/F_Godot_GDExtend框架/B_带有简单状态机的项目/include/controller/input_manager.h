#ifndef __TInputManager_CPP_H__
#define __TInputManager_CPP_H__


#include "controller/controller_node.h"



namespace godot
{
	class Input;
}

using namespace godot;

class TInputManager : public TControllerNode
{
    GDCLASS(TInputManager, TControllerNode);
public:
    virtual void initialize() override;

    Vector2 input_move_axis_direction(); // 输入方向
    Vector2 input_move_vector_direction(); // 输入方向

protected:
    static void _bind_methods();

private:
    Input *ii = nullptr; 
    
    // 普通设置
    // int _move_speed = 8000;

    String _move_left = "G_LEFT";
    String _move_right = "G_RIGHT";
    String _move_up = "G_UP";
    String _move_down = "G_DOWN";
    
    // String _pick_up = "G_PICKUP";
    // String _backpack = "G_ITEM";
};
#endif