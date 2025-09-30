#include "finite_state_machine/over_state.h"

using namespace godot;

/**
 * FSC设置函数
 */
// 调用初始化方法
void TOverState::t_initialize()
{

    // // 切换到一般状态
    // TFSC::change_current_state("TOverState", "TOverState");
};


// 每一帧做的事情
void TOverState::t_update(double delta)
{
    // UtilityFunctions::print("update_init");
};

void TOverState::t_physics_update(double delta)
{
    // UtilityFunctions::print("update_init");
};

// 退出时处理的事情
void TOverState::t_exit()
{
    // UtilityFunctions::print("TOverState::t_exit");
};

// 获取状态
TStateInterface::TFSC_STATUS TOverState::t_obtain_state()
{
    return _tfsc_statue;
}; 