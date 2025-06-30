#include "fsc/finite_state_machine/over_state.h"


void TOverState::_bind_methods() {}


/**
 * FSC设置函数
 */
// 调用初始化方法
void TOverState::t_initiazlie()
{

    // // 切换到一般状态
    // TFSC::change_current_state("TOverState", "TOverState");
};


// 每一帧做的事情
void TOverState::t_update(double delta)
{
    UtilityFunctions::print("update_init");
};

void TOverState::t_physics_update(double delta)
{
    UtilityFunctions::print("update_init");
};

// 退出时处理的事情
void TOverState::t_exit()
{
    UtilityFunctions::print("TOverState::t_exit");
};

// 获取状态
TFSC::TFSC_STATUS TOverState::t_obtain_state()
{
    return _tfsc_statue;
}; 