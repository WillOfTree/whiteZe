#include "state_bat.h"


void TBatState::_bind_methods() {
    // 进入战斗状态
    ClassDB::bind_method(D_METHOD("change_state_parameter", "a"), &TBatState::change_state_parameter);
    // 退出战斗状态
    ClassDB::bind_method(D_METHOD("exit_bat_state_parameter"), &TBatState::exit_bat_state_parameter);
}


/**
 * FSC设置函数
 */
// 用于判断类是否相同
String TBatState::get_class_name(){
    return m_class_name;
};
// 判断是否进入某种状态
bool TBatState::enter_condition(){

    return m_check_enter_state;
}; 
// 判断退出条件状态
bool TBatState::exit_condition(){
    return m_check_exit_state;
}; 
// 战斗初始化
void TBatState::t_initiazlie(){
    // 加载战斗界面
    m_bat_canvaslayer = s_global_node["Window"]->get_node<CanvasLayer>("BattleWindow");
    m_bat_canvaslayer->show(); 
    // 加载玩家等元素

};
// 战斗退出状态 
void TBatState::t_exit(){
    // 恢复状态
    m_check_enter_state = 0; // 进入状态
    m_check_exit_state = 0;
    // 设置图层隐藏
    m_bat_canvaslayer->hide();
    
    UtilityFunctions::print("exit_bat");
};
// 战斗更新状态
void TBatState::t_update(double delta){
    // UtilityFunctions::print("update_bat");
};


/**
 * 切换状态，更改状态参数
 * 只有m_check_enter_state与m_check_exit_state都为 真 才进入状态切换
 **/ 
void TBatState::change_state_parameter(Variant a){
    m_check_enter_state = 1; // 进入状态
    // m_check_exit_state = 1; // 退出状态
    UtilityFunctions::print("enter bat!!!!!!!!!!");
}; 
void TBatState::exit_bat_state_parameter()
{
    m_check_exit_state = 1;
    UtilityFunctions::print("exit bat!!!!!!!!!!");

}