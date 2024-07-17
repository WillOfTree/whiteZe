#include "state_load.h"


void TLoadState::_bind_methods() {

}


/**
 * FSC设置函数
 */
// 用于判断类是否相同
String TLoadState::get_class_name(){
    return m_class_name;
};
// 判断是否进入某种状态
bool TLoadState::enter_condition(){
    // 判断当前是否可以切换

    return m_check_enter_state;
}; 
// 判断退出条件状态
bool TLoadState::exit_condition(){
    return m_check_exit_state;
}; 

void TLoadState::t_initiazlie(){
    UtilityFunctions::print("init_load");
    // 加载场景
    
};
void TLoadState::t_exit(){
    UtilityFunctions::print("exit_load");
};
void TLoadState::t_update(double delta){
    UtilityFunctions::print("update_load");
};