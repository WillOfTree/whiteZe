/********************************************************
 * 状态机
 * 
 * 1. 由外部GDScript脚本启动，
 * 2. 调用gd_initialize方法进行初始化配置
 * 3. 由 调用t_update方法进行每一帧操作
 * 
 ********************************************************/
#include "fsc_machine.h"

#include <godot_cpp/core/class_db.hpp>

//# 引入的子状态类，需要在这里添加子类
#include "finite_state_machine/init_state.h"
#include "finite_state_machine/ordinary_state.h"
#include "finite_state_machine/over_state.h"

using namespace godot;

/**
 * 绑定方法
 */
void TFSCMachine::_bind_methods() 
{
    // TFSCMachine方法
    ClassDB::bind_method(D_METHOD("fsc_initiazlie"), &TFSCMachine::t_initiazlie);
    ClassDB::bind_method(D_METHOD("fsc_update", "_delta"), &TFSCMachine::t_update);
    ClassDB::bind_method(D_METHOD("fsc_physics_update", "_delta"), &TFSCMachine::t_physics_update);
    // 供GDScript调用的方法
    ClassDB::bind_method(D_METHOD("change_state", "aim_state", "error_info"), &TFSCMachine::gd_change_current_state);
    
    // 绑定变量-供外部调用
    //# 使用静态转换经enum class类型转换为GDExtensionInt类型
    //# TNULL, TBooting, TInit, TOrdinary, TChanageScence, TVerify, TOver
    ClassDB::bind_integer_constant("TFSCMachine", "TStateInterface::TFSC_STATUS", "TNULL", static_cast<GDExtensionInt>(TNULL) );
    ClassDB::bind_integer_constant("TFSCMachine", "TStateInterface::TFSC_STATUS", "TBooting", static_cast<GDExtensionInt>(TBooting));
    ClassDB::bind_integer_constant("TFSCMachine", "TStateInterface::TFSC_STATUS", "TInit", static_cast<GDExtensionInt>(TInit));
    ClassDB::bind_integer_constant("TFSCMachine", "TStateInterface::TFSC_STATUS", "TOrdinary", static_cast<GDExtensionInt>(TOrdinary));
    ClassDB::bind_integer_constant("TFSCMachine", "TStateInterface::TFSC_STATUS", "TChanageScence", static_cast<GDExtensionInt>(TChanageScence));
    ClassDB::bind_integer_constant("TFSCMachine", "TStateInterface::TFSC_STATUS", "TOver", static_cast<GDExtensionInt>(TOver));
}


/**************************************************
 * GDExtension状态切换方法 
 **************************************************/
void TFSCMachine::change_current_state(TStateInterface::TFSC_STATUS aim_state, String error_info)
{
    if (all_state_machine.count(aim_state))
    {
        // 获取当前类状态
        TStateInterface::TFSC_STATUS a = m_current_state->t_obtain_state();
        // 判断当前all_state_machine[a]是否为空，不为空错误
        if (all_state_machine[a] == nullptr)
        {
            // 退出状态
            m_current_state->t_exit();
            // 复原指针
            all_state_machine[a] = std::move(m_current_state);
            // 切换状态
            m_current_state = std::move(all_state_machine[aim_state]) ; 
            m_current_state->t_initialize();
        }
        else
        {
            ERR_FAIL_MSG("Error 10000: find it");
        }
    }
    else
    {
        ERR_FAIL_MSG("Error not find aim_state");
        ERR_FAIL_MSG("Maybe not add node to TFSCMachine or Not write right TFSCMachine_state name");
        ERR_FAIL_MSG(error_info);
    }
}; 


/// 供GDScript调用的切换方法
void TFSCMachine::gd_change_current_state(Variant aim_state, Variant error_info)
{
    // 类型转换
    TStateInterface::TFSC_STATUS a = static_cast<TStateInterface::TFSC_STATUS>(int(aim_state));
    String b = error_info;

    change_current_state(a, b);
}; 


/********************************************************
 * FSC 
 ********************************************************/
// 进入状态时会调用
void TFSCMachine::t_initiazlie()
{
    // 初始化类 
    //! 未来可能改成工厂类
    all_state_machine[TInit] = std::make_unique<TInitState>();
    all_state_machine[TOrdinary] = std::make_unique<TOrdinaryState>();
    all_state_machine[TOver] = std::make_unique<TOverState>();


    // 设置默认的当前状态
    // 移动指针，all_state_machine[TInit] = null
    m_current_state = std::move(all_state_machine[TInit]);

    // 状态机初始化
    if (m_current_state != NULL) {
        m_current_state->t_initialize();
    } else {
        ERR_FAIL_MSG("m_current_state init faile! Check default state name,TFSCMachine:128");
    }

    // 检查
}; 



/**
 * 每一帧执行的程序
 */
void TFSCMachine::t_update(double _delta)
{
    if (m_current_state != NULL) {
        m_current_state->t_update(_delta);
    }
}; 


/**
 * 每一物理帧执行的程序
 */
void TFSCMachine::t_physics_update(double _delta)
{
    if (m_current_state != NULL) {
        m_current_state->t_physics_update(_delta);
    }
}; 


// TFSCMachine::~TFSCMachine()
// {

// };