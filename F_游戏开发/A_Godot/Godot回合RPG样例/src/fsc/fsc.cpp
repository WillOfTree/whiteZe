#include "fsc.h"

#include "state_idle.h"
#include "state_move.h"
#include "state_item.h"
#include "state_bat.h"
#include "state_load.h"


// 静态全局变量
std::map<String, Node *> TFSC::s_global_node = {};


/**
 * 绑定方法
 */
void TFSC::_bind_methods() {
    ClassDB::bind_method(D_METHOD("update", "_delta"), &TFSC::t_update);
    ClassDB::bind_method(D_METHOD("init"), &TFSC::t_initiazlie);

}


/**
 * FSC 循环结构
 */
// 进入状态时会调用
void TFSC::t_initiazlie()
{
    /**
     * 加载按键映射
     */
    InputMap * _map_ii = InputMap::get_singleton();
    _map_ii->load_from_project_settings();

    /**
     * 获取一些需要使用的节点
     */
    Node * system_node = get_node<Node>(".."); // 获取System节点
    system_node->get_node<TCommonMethod>("TCommonMethod")->get_main_group_node(&s_global_node); // 获取main分组节点
    // s_global_node = m_main_group;
    s_global_node["System"] = system_node;


    /**
     * 加载状态节点
     */
    TIdleState * id_s = get_node<TIdleState>("TIdleState");
    TMoveState * mo_s = get_node<TMoveState>("TMoveState");
    TBatState * ba_s = get_node<TBatState>("TBatState");
    TItemState * it_s = get_node<TItemState>("TItemState");
    TLoadState * lo_s = get_node<TLoadState>("TLoadState");

    m_game_state.push_back(id_s);
    m_game_state.push_back(mo_s);
    m_game_state.push_back(ba_s);
    m_game_state.push_back(it_s);
    m_game_state.push_back(lo_s);

    /**
     * 初始状态更新
     */
    set_inital_state(id_s);

    /**
     * 信号连接
     */
    // 进入战斗信号链接-测试
    s_global_node["Player"]
        ->get_node<CharacterBody2D>("Protagonist")
        ->get_node<Area2D>("Area2D")
        ->connect("area_entered", Callable(ba_s, "change_state_parameter"));
    // 退出信号链接 - 测试
    s_global_node["Window"]
        ->get_node<Button>("BattleWindow/test_out")
        ->connect("button_down", Callable(ba_s, "exit_bat_state_parameter"));

    // ->connect("enemy_crash", Callable(ba_s, "change_state_parameter"));
    // 测试
    // check_state_transitions();
    // for (int i = 0; i<m_game_state.size(); i++) {
    //     UtilityFunctions::print(m_game_state[i]);
    // }

}; 

// 判断是否进入某种状态
bool TFSC::enter_condition()
{
    UtilityFunctions::print("TFSC::enter_condition");
    return 1;

}; 

// 持续执行的程序
void TFSC::t_update(double _delta)
{
    
    if (m_current_state != NULL) {
        m_current_state->t_update(_delta);
        check_state_transitions();
    }
}; 

// 判断退出条件状态
bool TFSC::exit_condition()
{
    UtilityFunctions::print("TFSC::exit_condition");
    return 1;
}; 

// 退出状态会调用
void TFSC::t_exit()
{
    UtilityFunctions::print("TFSC::t_exit");
}; 


/**
 * 获取类的名称
 */
String TFSC::get_class_name(){
    return m_class_name;
};


/**
 * 初始化方法
 * */
void TFSC::set_inital_state(TFSC * z){
    m_current_state = z;
    
    if (m_current_state != NULL) {
        m_current_state->t_initiazlie();
    } else {
        UtilityFunctions::print("m_current_state init faile! TFSC:128");
    }
}


/**
 * 状态切换方法
 */
void TFSC::check_state_transitions() {
    String current_name = m_current_state->get_class_name();
    
    for (int i=0; i<m_game_state.size(); i++) {
        String aim_name = m_game_state[i]->get_class_name(); // 获取目标类的名称，用于类的判断
        
        if (current_name != aim_name) { // 验证当前类与目标类是否相同
            
            if (m_game_state[i]->enter_condition()) { // 目标状态是否满足进入条件
                
                if(m_current_state->exit_condition()) { // 当前类是否满足退出条件
                    
                    m_current_state->t_exit();
                    m_current_state = m_game_state[i]; // 切换状态
                    m_current_state->t_initiazlie();
                }
            } 
        }
    }
}


/**
 * 提供给子类，变量
 * m_main_group与m_system_node
 */
// // 获取map变量 
// bool TFSC::get_fsc_main_group(std::map<String, Node *> *a)
// {

//     a = &m_main_group;
//     return 1;
// }; 
// 获取Node节点
// Node * TFSC::get_fsc_system_node()
// {
//     return m_system_node;
// }; 