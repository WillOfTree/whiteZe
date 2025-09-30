/**
 * @class TChangeScenceState
 * @brief 表示有限状态机中的场景切换状态。
 * 
 * 该类继承自 TStateInterface，实现了初始化、更新、物理更新、退出和获取当前状态的方法。
 * 
 * @note 状态由 TFSC_STATUS 枚举值 TChanageScence 标识。
 * 
 * @author 作者: 叙白
 * @date   日期: 20250715
 */
#ifndef __TChangeScenceState_CPP_H__
#define __TChangeScenceState_CPP_H__

#include "interface/state_interface.h"


class TChangeScenceState : public TStateInterface
{ 
public:
    virtual void t_initialize() override; // 进入状态时会调用
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual void t_physics_update(double delta) override; // 持续执行的程序
    virtual void t_exit() override; // 退出状态会调用
    virtual TFSC_STATUS t_obtain_state(); // 获取状态


private:
    TFSC_STATUS _tfsc_statue = TFSC_STATUS::TChanageScence;
};

#endif