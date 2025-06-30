#include "fsc/finite_state_machine/change_scence_state.h"


void TChangeScenceState::_bind_methods() {}


/**
 * FSC设置函数
 */
// 调用初始化方法
void TChangeScenceState::t_initiazlie()
{

    // // 切换到一般状态
    // TFSC::change_current_state("TChangeScenceState", "TChangeScenceState");
};


// 每一帧做的事情
void TChangeScenceState::t_update(double delta)
{
    UtilityFunctions::print("update_init");
};

void TChangeScenceState::t_physics_update(double delta)
{
    UtilityFunctions::print("physice_init");
};

// 退出时处理的事情
void TChangeScenceState::t_exit()
{
    UtilityFunctions::print("TChangeScenceState::t_exit");
};

// 获取状态
TFSC::TFSC_STATUS TChangeScenceState::t_obtain_state()
{
    return _tfsc_statue;
}; 