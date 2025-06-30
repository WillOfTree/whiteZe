/********************************************************
 * 状态机
 * 
 * 1. 由外部GDScript脚本启动，
 * 2. 调用gd_initialize方法进行初始化配置
 * 3. 由 调用t_update方法进行每一帧操作
 * 
 ********************************************************/
#include "fsc/fsc.h"

/**
 * 导入管理器类
 */
// #include "controller/controller_node.h"
// #include "controller/input_manager.h"
// #include "controller/game_manager.h"



/**
 * 静态全局变量，供子类直接使用，不用使用Get_Node方法
 **/ 
std::map<TFSC::TFSC_STATUS, TFSC *> TFSC::s_all_state_machine = {}; // 状态机字节点，所有游戏状态
TFSC * TFSC::s_current_state = nullptr; // 当前状态


/**
 * 绑定方法
 */
void TFSC::_bind_methods() {

    // TFSC方法
    ClassDB::bind_method(D_METHOD("fsc_initiazlie"), &TFSC::t_initiazlie);
    ClassDB::bind_method(D_METHOD("fsc_update", "_delta"), &TFSC::t_update);
    ClassDB::bind_method(D_METHOD("fsc_physics_update", "_delta"), &TFSC::t_physics_update);
    // 供GDScript调用的方法
    ClassDB::bind_method(D_METHOD("change_state", "aim_state", "error_info"), &TFSC::gdscript_change_current_state);
    
    // 绑定变量-供外部调用
    // TNULL, TBooting, TInit, TOrdinary, TChanageScence, TVerify, TOver
    ClassDB::bind_integer_constant("TFSC", "TFSC_STATUS", "TNULL", TFSC_STATUS::TNULL);
    ClassDB::bind_integer_constant("TFSC", "TFSC_STATUS", "TBooting", TFSC_STATUS::TBooting);
    ClassDB::bind_integer_constant("TFSC", "TFSC_STATUS", "TInit", TFSC_STATUS::TInit);
    ClassDB::bind_integer_constant("TFSC", "TFSC_STATUS", "TOrdinary", TFSC_STATUS::TOrdinary);
    ClassDB::bind_integer_constant("TFSC", "TFSC_STATUS", "TChanageScence", TFSC_STATUS::TChanageScence);
    ClassDB::bind_integer_constant("TFSC", "TFSC_STATUS", "TOver", TFSC_STATUS::TOver);
}


/**************************************************
 * GDExtension状态切换方法 
 **************************************************/
void TFSC::change_current_state(TFSC_STATUS aim_state, String error_info)
{
    if (s_all_state_machine.count(aim_state))
    {
        s_current_state->t_exit();
        s_current_state = s_all_state_machine[aim_state]; // 切换状态
        s_current_state->t_initiazlie();
    }
    else
    {
        ERR_FAIL_MSG("Error not find aim_state");
        ERR_FAIL_MSG("Maybe not add node to TFSC or Not write right TFSC_state name");
        ERR_FAIL_MSG(error_info);
    }
}; 


/// 供GDScript调用的切换方法
void TFSC::gdscript_change_current_state(Variable aim_state, Variable error_info)
{
    TFSC_STATUS a = static_cast<TFSC_STATUS>(int(aim_state));
    
    if (s_all_state_machine.count(a))
    {
        s_current_state->t_exit();
        s_current_state = s_all_state_machine[a]; // 切换状态
        s_current_state->t_initiazlie();
    }
    else
    {
        ERR_FAIL_MSG("Maybe your write error enum type name at 'change_state'");
        ERR_FAIL_MSG("Maybe not add node to TFSC or Not write right TFSC_state name");
        ERR_FAIL_MSG("Error in gdscript_change_current_state");
        ERR_FAIL_MSG(error_info);
    }
}; 


/********************************************************
 * FSC 循环结构
 ********************************************************/
// 进入状态时会调用
void TFSC::t_initiazlie()
{
    Array all_children = get_children();
    TFSC_STATUS state_machine_name = TNULL; // 状态机名称
    

    for (int i = 0; i < all_children.size(); i++)
    {
        TFSC *temp = cast_to<TFSC>(all_children[i]); // 转换为FSC类型
        state_machine_name = temp->t_obtain_state(); // 获取当前状态机状态标识

        s_all_state_machine[state_machine_name] = temp;
    }

    // 设置默认的当前状态；
    s_current_state = s_all_state_machine[_default_state_name];

    // 状态机初始化
    if (s_current_state != NULL) {
        s_current_state->t_initiazlie();
    } else {
        ERR_FAIL_MSG("m_current_state init faile! Check default state name,TFSC:128");
    }
}; 


/**
 * 每一帧执行的程序
 */
void TFSC::t_update(double _delta)
{
    if (s_current_state != NULL) {
        s_current_state->t_update(_delta);
    }
}; 


/**
 * 每一物理帧执行的程序
 */
void TFSC::t_physics_update(double _delta)
{
    if (s_current_state != NULL) {
        s_current_state->t_physics_update(_delta);
    }
}; 


/**
 * 退出状态会调用
 **/ 
void TFSC::t_exit() {
    UtilityFunctions::print("t_exit tfsc");
}; 


/**
 * 获取状态
 */
TFSC::TFSC_STATUS TFSC::t_obtain_state()
{
    return TNULL;
}; 