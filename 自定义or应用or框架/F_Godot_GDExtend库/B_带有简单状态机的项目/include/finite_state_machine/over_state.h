/**
 * @file over_state.h
 * @brief 定义了 TOverState 类，表示有限状态机中的“结束”状态。
 * 
 * TOverState 继承自 TStateInterface，重写了状态生命周期相关的虚函数，包括初始化、更新、物理更新和退出等方法。
 * 提供获取当前状态的方法，并包含静态方法用于绑定类方法。
 * 
 * @author 作者: 叙白
 * @version 1.0
 * @date 2025年7月
 */
#ifndef __TOverState_CPP_H__
#define __TOverState_CPP_H__

#include "interface/state_interface.h"


class TOverState : public TStateInterface
{ 
public:
    virtual void t_initialize() override; // 进入状态时会调用
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual void t_physics_update(double delta) override; // 持续执行的程序
    virtual void t_exit() override; // 退出状态会调用
    virtual TFSC_STATUS t_obtain_state(); // 获取状态

protected:
    static void _bind_methods();

private:
    TFSC_STATUS _tfsc_statue = TFSC_STATUS::TOver;
};

#endif