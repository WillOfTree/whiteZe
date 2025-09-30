#include "controller_init.h"

// #include "controller/game_manager.h"
// #include <godot_cpp/core/class_db.hpp>
#include "interface/controller_interface.h"


using namespace godot;

std::vector<TControllerInterface *> TControllerInit::controller_set {};


void TControllerInit::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("initiazlie"), &TControllerInit::initialize);
    // ClassDB::bind_method(D_METHOD("get_move_down"), &TGameManager::get_move_down);
    // ClassDB::add_property("TGameManager",
    // 	PropertyInfo(Variant::STRING, "Down"),
    //     "set_move_down",
    //     "get_move_down");
}



/**
 * 管理器类初始化
 */
void TControllerInit::initialize()
{
    for (int i=0; i < controller_set.size(); i++)
    {
        controller_set[i]->initialize();
    }
    UtilityFunctions::print("TControllerInit");
}


/**
 * 注册方法
 */
void TControllerInit::register_controller(TControllerInterface * p)
{
    controller_set.push_back(p);
    UtilityFunctions::print("regin ok");
};