#ifndef __TInputManager_CPP_H__
#define __TInputManager_CPP_H__


#include "interface/controller_interface.h"


namespace godot
{
	class Input;
}


class TInputManager : public TControllerInterface
{
    GDCLASS(TInputManager, TControllerInterface);

public:
    virtual void initialize() override;
    static TInputManager * get_singleton();

    Vector2 input_move_axis_direction(); // 输入方向
    bool input_move_vector_direction(); // 输入方向

protected:
    static void _bind_methods();

private:
    godot::Input *ii = nullptr; 
    static TInputManager * singleton;
    
    // 普通设置
    // int _move_speed = 8000;

    godot::String _move_left = "G_LEFT";
    godot::String _move_right = "G_RIGHT";
    godot::String _move_up = "G_UP";
    godot::String _move_down = "G_DOWN";
    
    // String _pick_up = "G_PICKUP";
    // String _backpack = "G_ITEM";
};
#endif