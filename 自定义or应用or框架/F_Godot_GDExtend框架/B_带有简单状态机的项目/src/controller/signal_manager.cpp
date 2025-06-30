#include "controller/signal_manager.h"

void TSignalManager::_bind_methods() 
{
    // 注册信号
    // ADD_SIGNAL(MethodInfo("change_to_verify"));
}


void TSignalManager::initialize()
{
    // 连接信号
    // Node *p = TMainNode::s_global_tfsc->get_node<Node>("TOrdinaryState");
    // connect("change_to_verify", Callable(p, "signal_to_verify"));
}; 
