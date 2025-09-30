#ifndef __TGameManager_CPP_H__
#define __TGameManager_CPP_H__

#include "interface/controller_interface.h"


class TGameManager : public TControllerInterface
{
    GDCLASS(TGameManager, TControllerInterface); // Godot 必需的宏

public:
    virtual void initialize() override;
    static TGameManager * get_singleton();

    // 测试
    void test();

protected:
    static void _bind_methods();

private:
    static TGameManager * singleton; // 实例

};
#endif