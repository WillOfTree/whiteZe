#include "state_move.h"


void TMoveState::_bind_methods() {
   
    /**
     * 外部属性
     */
    // 设置移动种子
    ClassDB::bind_method(D_METHOD("set_move_speed", "r"), &TMoveState::set_move_speed);
    ClassDB::bind_method(D_METHOD("get_move_speed"), &TMoveState::get_move_speed);
    ClassDB::add_property("TMoveState",
    	PropertyInfo(Variant::INT, "Move Speed"),
        "set_move_speed",
        "get_move_speed");
}


/**
 * FSC设置函数
 */
// 用于判断类是否相同
String TMoveState::get_class_name(){
    return m_class_name;
};
// 进入移动状态
bool TMoveState::enter_condition(){
    
    // 如果有输入，则返回真
    Input * temp = Input::get_singleton();
    Vector2 temp_v = temp->get_vector("G_LEFT", "G_RIGHT", "G_UP", "G_DOWN").normalized();
    if (temp_v == Vector2(0,0)) {
        m_check_enter_state = 0;
    } else  {
        m_check_enter_state = 1;
    }
    
    return m_check_enter_state;
}; 
// 退出条件状态
bool TMoveState::exit_condition(){
    m_check_exit_state = 1;
    return m_check_exit_state;
}; 

void TMoveState::t_initiazlie(){
    UtilityFunctions::print("initiazlie_move"); 
 
    // 获取角色
    m_player = TFSC::s_global_node["Player"]->get_node<CharacterBody2D>("Protagonist");

};

void TMoveState::t_exit(){
    UtilityFunctions::print("exit_move");
};

void TMoveState::t_update(double delta){
    UtilityFunctions::print("move_update");

    /**
     * 角色移动
     */
    Vector2 temp_v = m_inputHandler->get_vector("G_LEFT", "G_RIGHT", "G_UP", "G_DOWN").normalized();
    temp_v = temp_v.move_toward(temp_v * 1000, external_move_speed * delta) ;

    m_player->set_velocity(temp_v);
    m_player->move_and_slide();

};


/**
 * 外部属性设置方法
 */
// 设置背包图层路径
void TMoveState::set_move_speed(int a){
    external_move_speed = a;
};
int TMoveState::get_move_speed(){
    return external_move_speed;
};