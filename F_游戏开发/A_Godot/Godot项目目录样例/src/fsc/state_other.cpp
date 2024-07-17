#include "state_other.h"

TOTHERSTATE::TOTHERSTATE() {}
TOTHERSTATE::~TOTHERSTATE() {}


void TOTHERSTATE::_bind_methods() {}

void TOTHERSTATE:: _ready(){
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    UtilityFunctions::print("ready_other");
};
void TOTHERSTATE:: _process(double _delta){
    UtilityFunctions::print("process_other");
};

void TOTHERSTATE::initiazlie(){
    UtilityFunctions::print("init_other");
};
void TOTHERSTATE::exit(){
    UtilityFunctions::print("exit_other");
};
void TOTHERSTATE::update(double delta){
    UtilityFunctions::print("update_other");
};

void TOTHERSTATE::send_signal(){
    UtilityFunctions::print("speak_other");
}