#ifndef __TIdleState_CPP_H__
#define __TIdleState_CPP_H__


#include "fsc.h"


using namespace godot;

class TIdleState : public TFSC 
{
    
    GDCLASS(TIdleState, TFSC);

public:
    virtual String get_class_name(); // 用于判断类是否相同
    virtual void t_initiazlie() override; // 进入状态时会调用
    virtual bool enter_condition() override; // 判断是否进入某种状态
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual bool exit_condition() override; // 判断退出条件状态
    virtual void t_exit() override; // 退出状态会调用
   
    void change_state_parameter(); // 切换状态，更改状态参数
    

protected:
    static void _bind_methods();

private:
    /**
     * 元素
     */
    String m_class_name = "IDLE";
    bool m_check_enter_state = 0; // 进入状态
    bool m_check_exit_state = 0; // 退出状态

    // TInputHandler * m_inputHandler; // 输入句柄
    // Ref<PackedScene> m_protagonist;

    /**
     * 方法
     */
};

#endif