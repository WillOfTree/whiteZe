#ifndef __TItemState_CPP_H__
#define __TItemState_CPP_H__



#include "fsc.h"


using namespace godot;

class TItemState : public TFSC 
{
    
    GDCLASS(TItemState, TFSC);

public:

    virtual String get_class_name(); // 用于判断类是否相同
    virtual void t_initiazlie() override; // 进入状态时会调用
    virtual bool enter_condition() override; // 判断是否进入某种状态
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual bool exit_condition() override; // 判断退出条件状态
    virtual void t_exit() override; // 退出状态会调用

    
protected:
    static void _bind_methods();

private:
    String m_class_name = "ITEM";
    bool m_check_enter_state = 0; // 进入状态
    bool m_check_exit_state = 0; // 退出状态

    // std::map<String, Node *> m_main_group_item = {}; // m_main_group
    // Node * m_system_node_item; // m_system_node

    CanvasLayer * m_item_canvaslayer = NULL; // 背包窗口
};

#endif