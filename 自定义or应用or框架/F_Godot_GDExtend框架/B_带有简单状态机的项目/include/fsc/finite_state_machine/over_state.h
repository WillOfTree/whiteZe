#ifndef __TOverState_CPP_H__
#define __TOverState_CPP_H__

#include "fsc/fsc.h"


using namespace godot;

class TOverState : public TFSC 
{ 
    GDCLASS(TOverState, TFSC);

public:
    virtual void t_initiazlie() override; // 进入状态时会调用
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual void t_physics_update(double delta) override; // 持续执行的程序
    virtual void t_exit() override; // 退出状态会调用
    virtual TFSC_STATUS t_obtain_state(); // 获取状态

protected:
    static void _bind_methods();

private:
    TFSC::TFSC_STATUS _tfsc_statue = Over;
};

#endif