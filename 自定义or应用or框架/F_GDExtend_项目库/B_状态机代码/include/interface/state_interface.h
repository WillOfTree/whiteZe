/**
 * @brief 状态机接口类
 * 
 * 此类定义了状态机的基本接口，包括状态的枚举类型和状态相关的虚函数。
 * 
 * 状态枚举 TFSC_STATUS 包含以下状态：
 * - TNULL: 空状态
 * - TBooting: 启动状态
 * - TInit: 初始化状态
 * - TOrdinary: 一般状态
 * - TChanageScence: 场景改变状态
 * - TVerify: 验证状态
 * - TOver: 结束状态
 * 
 * 虚函数说明：
 * - t_initialize(): 进入状态时调用，用于初始化状态。
 * - t_update(double delta): 持续执行的程序，delta为时间间隔。
 * - t_physics_update(double delta): 持续执行的物理相关程序，delta为时间间隔。
 * - t_exit(): 退出状态时调用，用于清理状态。
 * - t_obtain_state(): 获取当前状态，返回 TFSC_STATUS 枚举值。
 */
#ifndef __TStateInterface_CPP_H__
#define __TStateInterface_CPP_H__


class TStateInterface 
{
public:
    // 状态机状态, 空、启动状态、初始化状态、一般状态、场景改变状态、验证状态、结束
    enum class TFSC_STATUS {TNULL, TBooting, TInit, TOrdinary, TChanageScence, TVerify, TOver};

    virtual ~TStateInterface() = default;

    /**
     * 状态机相关方法
     */
    virtual void t_initialize() = 0; /// 进入状态时会调用
    virtual void t_update(double delta) = 0; /// 持续执行的程序
    virtual void t_physics_update(double delta) = 0; // 持续执行的程序
    virtual void t_exit() = 0; // 退出状态会调用

    virtual TFSC_STATUS t_obtain_state() = 0; // 获取状态

};

#endif