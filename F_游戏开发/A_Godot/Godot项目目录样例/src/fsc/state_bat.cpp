#include "state_bat.h"

TBATSTATE::TBATSTATE() {}
TBATSTATE::~TBATSTATE() {}


void TBATSTATE::_bind_methods() {
    // ADD_SIGNAL(MethodInfo());
    ADD_SIGNAL(MethodInfo(
        "BAT_transition",//信号名称
        PropertyInfo(Variant::STRING, "aim_state"),//信号参数
        PropertyInfo(Variant::STRING, "current_state")
        )
    );
}

void TBATSTATE::_ready(){
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    UtilityFunctions::print("ready_bat test");
};
void TBATSTATE::_process(double _delta){
    UtilityFunctions::print("process_bat");
};


void TBATSTATE::initiazlie(){
    UtilityFunctions::print("init_bat");

};
void TBATSTATE::exit(){
    UtilityFunctions::print("exit_bat");
};
void TBATSTATE::update(double delta){
    UtilityFunctions::print("update_bat");
    // send_signal();// test
};

// 发送信号方法
void TBATSTATE::send_signal(){
    emit_signal("MOVE", "BAT");
}