#ifndef __TControllerNode_CPP_H__
#define __TControllerNode_CPP_H__


#include "main_node.h"


using namespace godot;

class TControllerNode : public TMainNode
{
    GDCLASS(TControllerNode, TMainNode);
public:
    virtual void initialize() override; // 初始方法，需要再外部访问

protected:
    static void _bind_methods();

private:
};
#endif