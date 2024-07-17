#include "state_move.h"



TMOVESTATE::TMOVESTATE() {}
TMOVESTATE::~TMOVESTATE() {}


void TMOVESTATE::_bind_methods() {
    // ADD_SIGNAL(MethodInfo());
    ADD_SIGNAL(MethodInfo(
        "MOVE_transition",//信号名称
        PropertyInfo(Variant::STRING, "aim_state"),//信号参数
        PropertyInfo(Variant::STRING, "current_state")
        )
    );
}

void TMOVESTATE::_ready(){
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    UtilityFunctions::print("ready_move");
    // 初始化移动输入
    // Input *ii = Input::get_singleton();
    ;
    
};

void TMOVESTATE::_process(double _delta){
    // if(ii->is_action_pressed("d")){
    //     UtilityFunctions::print("usss_move");
    //     // send_signal();
    // };
};


void TMOVESTATE::initiazlie(){
    UtilityFunctions::print("init_move");
};
void TMOVESTATE::exit(){
    UtilityFunctions::print("exit_move");
};
void TMOVESTATE::update(double delta){
    UtilityFunctions::print("update_move");
    // ii->is_action_just_pressed("d");
    
};

void TMOVESTATE::send_signal(){
    emit_signal("MOVE_transition");
}