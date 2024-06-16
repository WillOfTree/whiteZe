#ifndef __TEXAMPLE_CPP_H__
#define __TEXAMPLE_CPP_H__

#include <godot_cpp/classes/Node.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
class TExample : public Node
{
    /*
     * 定义一个宏，
     * 	Example：当前你的类名
     * 	Node3D：当前类继承的类名
     */
    GDCLASS(TExample, Node);
    // 防止出现意外bug，定义一个方法
    TExample();
    ~TExample();

public:
    void _process(double delta);
    void _ready();

protected:
    static void _bind_methods();

private:
};
#endif