#ifndef __TCommonMethod_CPP_H__
#define __TCommonMethod_CPP_H__

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <map>

using namespace godot;
class TCommonMethod : public Node
{
    /*
     * 定义一个宏，
     * 	Example：当前你的类名
     * 	Node3D：当前类继承的类名
     */
    GDCLASS(TCommonMethod, Node);
    
public:

    bool get_main_group_node(std::map<String, Node *> *a);

protected:
    static void _bind_methods();

private:
};
#endif