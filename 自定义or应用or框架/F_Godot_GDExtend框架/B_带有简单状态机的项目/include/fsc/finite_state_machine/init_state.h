/***************************************
 *  场景切换时的状态
 * 
 * 
 * 
 * 
 *****************************************/
#ifndef __TInitState_CPP_H__
#define __TInitState_CPP_H__

#include "fsc/fsc.h"


using namespace godot;

class TInitState : public TFSC 
{
    GDCLASS(TInitState, TFSC);
public:
    virtual void t_initiazlie() override; // 进入状态时会调用
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual void t_physics_update(double delta) override; // 持续执行的程序
    virtual void t_exit() override; // 退出状态会调用
    virtual TFSC_STATUS t_obtain_state() override; // 获取状态

protected:
    static void _bind_methods();

private:
    TFSC::TFSC_STATUS _tfsc_statue = Init;
};

#endif