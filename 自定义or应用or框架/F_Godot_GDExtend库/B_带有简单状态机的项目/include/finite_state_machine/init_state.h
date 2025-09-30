/**
 * @class TInitState
 * @brief 初始化状态类，继承自 TStateInterface。
 * 
 * 该类用于表示有限状态机中的初始化状态，包含进入、更新、物理更新、退出等状态相关的接口方法。
 * 
 * 方法说明：
 * - t_initialize()：进入状态时调用，用于初始化相关操作。
 * - t_update(double delta)：持续执行的程序，每帧调用一次。
 * - t_physics_update(double delta)：物理相关的持续执行程序，每帧调用一次。
 * - t_exit()：退出状态时调用，用于清理或保存状态。
 * - t_obtain_state()：获取当前状态。
 * 
 * 私有成员：
 * - _tfsc_statue：当前状态，初始为 TInit。
 * 
 * @author 作者: 叙白
 * @date   日期: 20250715
 */
#ifndef __TInitState_CPP_H__
#define __TInitState_CPP_H__

#include "interface/state_interface.h"


class TInitState : public TStateInterface 
{
public:
    virtual void t_initialize() override; // 进入状态时会调用
    virtual void t_update(double delta) override; // 持续执行的程序
    virtual void t_physics_update(double delta) override; // 持续执行的程序
    virtual void t_exit() override; // 退出状态会调用
    virtual TFSC_STATUS t_obtain_state() override; // 获取状态


private:
    TFSC_STATUS _tfsc_statue = TFSC_STATUS::TInit;
};

#endif