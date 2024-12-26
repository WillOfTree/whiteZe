/**
 * 所有类继承的父类，除了资源节点
 */
#ifndef __TMainNode_CPP_H__
#define __TMainNode_CPP_H__

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

class A_MainNode : public Node
{
    GDCLASS(A_MainNode, Node);
    
public:
protected:
    static void _bind_methods();

private:
};
#endif