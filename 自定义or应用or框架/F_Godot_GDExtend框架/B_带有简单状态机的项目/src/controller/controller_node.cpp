#include "controller/controller_node.h"

void TControllerNode::_bind_methods() 
{
    // ClassDB::bind_method(D_METHOD("set_protagonist_name", "r"), &TEnemyManager::set_protagonist_name);
    // ClassDB::bind_method(D_METHOD("get_protagonist_name"), &TEnemyManager::get_protagonist_name);
    // ClassDB::add_property("TEnemyManager",
    // 	PropertyInfo(Variant::STRING, "Protagonist Name"),
    //     "set_protagonist_name",
    //     "get_protagonist_name");
}


/**
 * 父类初始化方法，直接
 */
void TControllerNode::initialize()
{
    UtilityFunctions::print("You Shoud Check 'Controller' Function It Need 'initialize'");
}; 
