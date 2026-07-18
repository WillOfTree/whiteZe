#include "controller/game_manager.h"


using namespace godot;

TGameManager * TGameManager::singleton = nullptr;


void TGameManager::_bind_methods() 
{
    // ClassDB::bind_method(D_METHOD("set_move_down", "r"), &TGameManager::set_move_down);
    // ClassDB::bind_method(D_METHOD("get_move_down"), &TGameManager::get_move_down);
    // ClassDB::add_property("TGameManager",
    // 	PropertyInfo(Variant::STRING, "Down"),
    //     "set_move_down",
    //     "get_move_down");
}



/**
 * 加载按键映射
 */
void TGameManager::initialize()
{
    UtilityFunctions::print("TGameManager");
}


/**
 * 单例
 */
TGameManager * TGameManager::get_singleton()
{
    if (singleton == nullptr)
    {
        singleton = memnew(TGameManager);
    }
    return singleton;
};


void TGameManager::test()
{
    UtilityFunctions::print("test_TGame");
}