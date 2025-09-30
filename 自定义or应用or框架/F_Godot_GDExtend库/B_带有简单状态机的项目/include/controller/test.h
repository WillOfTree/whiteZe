/**
 * 
 */
#ifndef __TControllerNode_CPP_H__
#define __TControllerNode_CPP_H__

// 继承了需要引入头文件
#include <godot_cpp/classes/node.cpp>

// 向前声明，Godot的类需要声明
namespace godot
{
    class Input;
}

// 使用godot::明确godot的类
class TControllerNode : public godot::Node
{
    GDCLASS(TControllerNode, godot::Node);

public:
    virtual void initialize() override; // 初始方法，需要再外部访问

protected:
    static void _bind_methods();

private:
};
#endif