#include "state_item.h"


void TItemState::_bind_methods() {}


/**
 * FSC设置函数
 */
// 用于判断类是否相同
String TItemState::get_class_name(){
    return m_class_name;
};

// 判断是否进入某种状态
bool TItemState::enter_condition(){
    m_check_enter_state = Input::get_singleton()->is_action_just_pressed("G_ITEM");
    return m_check_enter_state;
}; 

// 判断退出条件状态
bool TItemState::exit_condition(){
    return m_check_exit_state;
}; 
void TItemState::t_initiazlie(){
    UtilityFunctions::print("init_other");
    // 获取基本节点
    // m_system_node_item = get_node<Node>("../.."); // 获取System节点
    // m_system_node_item->get_node<TCommonMethod>("TCommonMethod")->get_main_group_node(&m_main_group_item); // 获取main分组节点
    // 为什么不能获取父类属性
    // Node * a = TFSC::get_fsc_system_node();
    // UtilityFunctions::print(a);
    // UtilityFunctions::print(TFSC::m_system_node);
    
    // 打开成本
    m_item_canvaslayer = TFSC::s_global_node["Window"]->get_node<CanvasLayer>("InventoryWindow"); 
    m_item_canvaslayer->show();
};

void TItemState::t_exit(){
    // TODO:: 关闭窗口，更改m_check_exit_state
    UtilityFunctions::print("exit_other");
    // 设置状态为原始状态
    m_check_enter_state = 0;
    m_check_exit_state = 0;
};

void TItemState::t_update(double delta){

    if (Input::get_singleton()->is_action_just_pressed("G_ITEM")) {
        m_check_exit_state = 1;
        m_item_canvaslayer->hide();
    }
};