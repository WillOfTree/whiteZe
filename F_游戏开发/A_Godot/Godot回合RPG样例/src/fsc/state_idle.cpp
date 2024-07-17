#include "state_idle.h"


void TIdleState::_bind_methods() {}


/**
 * FSC设置函数
 */
// 用于判断类是否相同
String TIdleState::get_class_name(){
    return m_class_name;
};
// 判断是否进入某种状态
bool TIdleState::enter_condition(){
    bool temp = Input::get_singleton()->is_anything_pressed();
     
    if (temp) {
        m_check_enter_state = 0;
    } else {
        m_check_enter_state = 1;
    }
    // return m_check_enter_state;
    // m_check_enter_state = Input::get_singleton()->is_anything_pressed();
    return m_check_enter_state;
}; 

// 判断退出条件状态
bool TIdleState::exit_condition(){
    m_check_exit_state = 1;
    return m_check_exit_state;
}; 

void TIdleState::t_initiazlie(){
    UtilityFunctions::print("init_idle");
};
void TIdleState::t_exit(){
    // 恢复状态
    m_check_enter_state = 0;
    m_check_exit_state = 0;
    UtilityFunctions::print("exit_idle");
};
void TIdleState::t_update(double delta){
    UtilityFunctions::print("update_idle");
};


/**
 * 切换状态，更改状态参数
 * 只有m_check_enter_state与m_check_exit_state都为 真 才进入状态切换
 **/ 
void TIdleState::change_state_parameter(){
    m_check_enter_state = 1; // 进入状态
    m_check_exit_state = 1; // 退出状态
}; 
