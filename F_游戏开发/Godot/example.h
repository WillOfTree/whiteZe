#ifndef TEST_H
#define TEST_H

#include <godot_cpp/classes/Node.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;
class example: public Node {
    /*
    * 定义一个宏，
    * 	Test：当前你的类名
    * 	Node3D：当前类继承的类名
    */ 
    GDCLASS (example, Node);
    // 防止出现意外bug，定义一个方法
    example();
    ~example();
    public:
        void _process(double delta);
    protected:
        static void _bind_methods();
    private:
};
#endif