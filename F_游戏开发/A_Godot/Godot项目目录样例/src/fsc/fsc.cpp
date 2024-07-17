#include "state_bat.h"
#include "state_move.h"
#include "state_other.h"

#include "fsc.h"


TFSC::TFSC() {}
TFSC::~TFSC() {}


void TFSC::_bind_methods() {
    // 信号接收
    ClassDB::bind_method(D_METHOD("on_transition", "aim_state", "current_state"), &TFSC::on_transition);
}


void TFSC::_ready()
{
    // if(Engine::get_singleton()->is_editor_hint()) {
    //     // 在编辑器中，禁用_process函数
    //     set_process_mode(
    //         Node::ProcessMode::PROCESS_MODE_DISABLED);

    //     UtilityFunctions::print("system set ok");
    // }else{
    //     set_process_mode(
    //         Node::ProcessMode::PROCESS_MODE_ALWAYS);
    // }
    UtilityFunctions::print("TFSC_ready1");
    // 获取所有子节点
    m_bat_state = get_node<TBATSTATE>("TBATSTATE");
    m_move_state = get_node<TMOVESTATE>("TMOVESTATE");
    m_other_state = get_node<TOTHERSTATE>("TOTHERSTATE");

    // 状态数组
    m_game_state["BAT"] =  m_bat_state;
    m_game_state["MOVE"] = m_move_state;
    m_game_state["OTHER"] = m_other_state;
    // 设置默认状态
    m_current_state = m_move_state;

}
// 调用每个状态的更新方法
void TFSC::_process(double _delta) {
    // 每次都调用当前状态类的更新方法
    m_current_state->update(_delta);
    // UtilityFunctions::print("fsc-process");
}

void TFSC::initiazlie(){
    UtilityFunctions::print("fsc-init");
};
void TFSC::exit(){
    UtilityFunctions::print("fsc-exit");
};
void TFSC::update(double delta){
    UtilityFunctions::print("fsc-update");
};

// 
void TFSC::on_transition(String aim_state, String current_state){

    // 退出当前状态
    m_game_state[current_state]->exit();
    // 进入目标状态
    m_game_state[aim_state]->initiazlie();
}