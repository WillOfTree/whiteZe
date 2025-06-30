#ifndef __TFSC_CPP_H__
#define __TFSC_CPP_H__

#include "main_node.h"


using namespace godot;

class TFSC : public TMainNode
{
    GDCLASS(TFSC, TMainNode);

protected:
    // 状态机状态, 空、启动状态、初始化状态、一般状态、场景改变状态、验证状态、结束
    enum TFSC_STATUS {TNULL, TBooting, TInit, TOrdinary, TChanageScence, TVerify, TOver};

    static void _bind_methods();

public:
    /**
     * 状态机相关方法
     */
    virtual void t_initiazlie(); /// 进入状态时会调用
    virtual void t_update(double delta); /// 持续执行的程序
    virtual void t_physics_update(double delta); // 持续执行的程序
    virtual void t_exit(); // 退出状态会调用
    virtual TFSC_STATUS t_obtain_state(); // 获取状态
    void change_current_state(TFSC_STATUS aim_state, String error_info); // 切换状态
    void gdscript_change_current_state(Variable aim_state, Variable error_info); /// 供GDScript调用的切换方法

    /**
     * 供子节点使用的属性，必须是public属性
     */
    static std::map<TFSC_STATUS, TFSC *> s_all_state_machine;  // 状态机字节点，所有游戏状态
    static TFSC * s_current_state; // 当前状态

private:
    TFSC_STATUS _default_state_name = Init; // 默认游戏状态名称-类的名称
  
};
#endif