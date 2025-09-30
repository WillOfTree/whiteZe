#include "controller/signal_manager.h"
#include "controller/game_manager.h"

using namespace godot;

TSignalManager * TSignalManager::singleton = nullptr;


void TSignalManager::_bind_methods() 
{
    // 注册信号
    // ADD_SIGNAL(MethodInfo("change_to_verify"));
}


void TSignalManager::initialize()
{
    UtilityFunctions::print("TSingManager");
    TGameManager * p = TGameManager::get_singleton();
    p->test();
    // 连接信号
    // Node *p = TMainNode::s_global_tfsc->get_node<Node>("TOrdinaryState");
    // connect("change_to_verify", Callable(p, "signal_to_verify"));
}; 


// 单例
TSignalManager * TSignalManager::get_singleton()
{
    if (singleton == nullptr)
    {
        singleton = memnew(TSignalManager);
    }
    return singleton;
}
