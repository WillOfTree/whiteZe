#include "fsc/finite_state_machine/ordinary_state.h"


void TOrdinaryState::_bind_methods() {}


/**
 * FSC设置函数
 */
// 调用初始化方法
void TOrdinaryState::t_initiazlie()
{
    // // 切换到一般状态
    // TFSC::change_current_state("TOrdinaryState", "TOrdinaryState");
};


// 每一帧做的事情
void TOrdinaryState::t_update(double delta)
{
    UtilityFunctions::print("update_init");
};

void TOrdinaryState::t_physics_update(double delta)
{
    UtilityFunctions::print("update_init");
};


// 退出时处理的事情
void TOrdinaryState::t_exit()
{
    UtilityFunctions::print("TOrdinaryState::t_exit");
};

// 获取状态
TFSC::TFSC_STATUS TOrdinaryState::t_obtain_state()
{
    return _tfsc_statue;
}; 