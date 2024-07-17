#include "scene_manager.h"

#include "../common_methods/common.h"


/**
 * 设置方法
 */
void TSceneManger::_bind_methods() {
    ClassDB::bind_method(D_METHOD("load_scene_to_world", "s"), &TSceneManger::add_scene_to_world);
}

void TSceneManger::_ready(){

    // 获取system节点
    m_system_node = get_node<Node>("..");
    set_main_group_node(); // 设置main分组节点
    // 设置世界节点，必须在设置set_main_group_node之后才可以使用
    m_world_node = m_main_group["World"];


    // 加载战斗场景节点 
	ResourceLoader * R = ResourceLoader::get_singleton();
    m_scene_map["main"] = R->load("res://main.tscn", "PackedScene");
    m_scene_map["login"] = R->load("res://scene/LoginInterface.tscn", "PackedScene");

    m_scene_map["mountain_seas_village"] = R->load("res://scene/mountains_seas_village.tscn", "PackedScene");
}

/**
 * 设置场景管理器 参数相关方法
 */
Ref<PackedScene> * TSceneManger::get_scene_collection_path(String s){
    return &m_scene_map[s];
};


/**
 * 加载节点
 */
void TSceneManger::add_scene_to_world(String s) 
{
    Node * temp = m_scene_map[s]->instantiate(); // 实例化
    m_world_node->add_child(temp); // 添加节点
}


/**
 * 将main分组节点定义到本身
 */
void TSceneManger::set_main_group_node()
{
    TCommonMethod * t = m_system_node->get_node<TCommonMethod>("TCommonMethod");
    t->get_main_group_node(&m_main_group);
};