#ifndef __TMoveState_CPP_H__
#define __TMoveState_CPP_H__


#include "fsc.h"

using namespace godot;


class TMoveState : public TFSC 
{
    
    GDCLASS(TMoveState, TFSC);

public:
    virtual String get_class_name(); // 用于判断类是否相同
    virtual void t_initiazlie() override; // 进入状态时会调用
    virtual bool enter_condition() override; // 判断是否进入某种状态
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual bool exit_condition() override; // 判断退出条件状态
    virtual void t_exit() override; // 退出状态会调用

    // void change_state_parameter(); // 切换状态，更改状态参数
    
    /**
     * 外部属性方法
     */

    // // 设置背包图层路径
    

protected:
    static void _bind_methods();


private:
    /**
     * 属性
     */
    String m_class_name = "MOVE";
    bool m_check_enter_state = 0; // 进入状态
    bool m_check_exit_state = 0; // 退出状态

    CharacterBody2D * m_player = NULL;
    Input * m_inputHandler = Input::get_singleton(); // 输入句柄

    // Node * m_system_node_move = NULL; // system节点
    // std::map<String, Node *> m_main_group_move = {}; // main中节点
    
    // 测试
    int external_move_speed = 100000; // 移动种子

    /**
     * 方法
     */
    void set_move_speed(int a);
    int get_move_speed();
};


#endif