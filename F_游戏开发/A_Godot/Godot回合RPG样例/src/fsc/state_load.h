#ifndef __TLoadState_CPP_H__
#define __TLoadState_CPP_H__


#include "fsc.h"


using namespace godot;

class TLoadState : public TFSC 
{
    
    GDCLASS(TLoadState, TFSC);

public:

    virtual String get_class_name() override; // 用于判断类是否相同
    virtual void t_initiazlie() override; // 进入状态时会调用
    virtual bool enter_condition() override; // 判断是否进入某种状态
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual bool exit_condition() override; // 判断退出条件状态
    virtual void t_exit() override; // 退出状态会调用
    

protected:
    static void _bind_methods();

private:
    String m_class_name = "LOAD";
    bool m_check_enter_state = 0; // 进入状态
    bool m_check_exit_state = 0; // 退出状态

    void change_scene(); // 改变场景
};

#endif