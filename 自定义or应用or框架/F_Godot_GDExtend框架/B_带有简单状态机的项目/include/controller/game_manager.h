#ifndef __TGameManager_CPP_H__
#define __TGameManager_CPP_H__


#include "controller/controller_node.h"


using namespace godot;

class TGameManager : public TControllerNode
{
    GDCLASS(TGameManager, TControllerNode);
public:
    virtual void initialize() override;

protected:
    static void _bind_methods();

private:

};
#endif