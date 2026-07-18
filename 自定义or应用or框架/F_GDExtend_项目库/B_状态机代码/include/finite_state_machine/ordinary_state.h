
/**
 * @file ordinary_state.h
 * @brief 普通状态类的定义，继承自状态接口类 TStateInterface。
 * 
 * 该类用于实现有限状态机中的普通状态，包含状态的初始化、更新、物理更新、退出和获取状态等方法。
 *
 * 主要功能：
 * - t_initialize(): 进入状态时调用，用于初始化状态。
 * - t_update(double delta): 持续执行的程序逻辑。
 * - t_physics_update(double delta): 持续执行的物理相关逻辑。
 * - t_exit(): 退出状态时调用，用于清理或保存状态。
 * - t_obtain_state(): 获取当前状态信息。
 *
 * 保护成员：
 * - _bind_methods(): 绑定方法，用于反射或脚本系统。
 *
 * 私有成员：
 * - _tfsc_statue: 当前状态，初始化为 TOrdinary。
 * 
 * @author 作者: 叙白
 * @date   日期: 20250715
 */
#ifndef __TOrdinaryState_CPP_H__
#define __TOrdinaryState_CPP_H__

#include "interface/state_interface.h"


class TOrdinaryState : public TStateInterface
{ 
public:
    virtual void t_initialize() override; // 进入状态时会调用
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual void t_physics_update(double delta) override; // 持续执行的程序
    virtual void t_exit() override; // 退出状态会调用
    virtual TFSC_STATUS t_obtain_state() override; // 获取状态

protected:
    static void _bind_methods();

private:
    TFSC_STATUS _tfsc_statue = TFSC_STATUS::TOrdinary;
};

#endif