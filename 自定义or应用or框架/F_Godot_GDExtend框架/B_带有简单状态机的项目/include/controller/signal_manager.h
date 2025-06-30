#ifndef __TSignalManager_CPP_H__
#define __TSignalManager_CPP_H__


#include "controller/controller_node.h"


using namespace godot;

class TSignalManager : public TControllerNode
{
    GDCLASS(TSignalManager, TControllerNode);
public:
    virtual void initialize(); // 初始方法，需要再外部访问

protected:
    static void _bind_methods();

private:
};
#endif