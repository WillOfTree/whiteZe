#include "fsc/finite_state_machine/init_state.h"


void TInitState::_bind_methods() {}


/**
 * FSC设置函数
 */
// 调用初始化方法
void TInitState::t_initiazlie()
{
    // // 切换到一般状态
    // TFSC::change_current_state("TOrdinaryState", "TInitState");
};


// 每一帧做的事情
void TInitState::t_update(double delta)
{
    UtilityFunctions::print("update_init");
};

// 每一帧做的事情
void TInitState::t_physics_update(double delta)
{
    UtilityFunctions::print("update_init");
};


// 退出时处理的事情
void TInitState::t_exit()
{
    UtilityFunctions::print("TInitState::t_exit");
};


// 获取状态
TFSC::TFSC_STATUS TInitState::t_obtain_state()
{
    return _tfsc_statue;
}; 