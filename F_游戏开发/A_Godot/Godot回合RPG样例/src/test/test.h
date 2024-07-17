#ifndef __TMainTscn_CPP_H__
#define __TMainTscn_CPP_H__

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

class TTest : public Node
{
    /*
     * 定义一个宏，
     * 	Example：当前你的类名
     * 	Node3D：当前类继承的类名
     */
    GDCLASS(TTest, Node);
    
public:

    void _ready();
    void test();
    void main_start(); // 开始按键，触发方法

protected:
    static void _bind_methods();

private:
};
#endif