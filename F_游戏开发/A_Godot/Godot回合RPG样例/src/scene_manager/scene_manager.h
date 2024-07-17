#ifndef __TSceneManger_CPP_H__
#define __TSceneManger_CPP_H__

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <map>


using namespace godot;


class TSceneManger : public Node
{
    /*
     * 定义一个宏，
     * 	Example：当前你的类名
     * 	Node3D：当前类继承的类名
     */
    GDCLASS(TSceneManger, Node);
    
public:

    void _ready();

    /**
     * 函数
     */
    Ref<PackedScene> * get_scene_collection_path(String s);
    void add_scene_to_world(String s);


    /**
     * 外部属性设置函数
     */


protected:
    static void _bind_methods();

private:
    /* 属性 */
    std::map<String, Ref<PackedScene>> m_scene_map; // 场景资源集合
    Node * m_world_node = NULL; // 世界节点
    std::map<String, Node *> m_main_group = {}; // 主节点
    Node * m_system_node = NULL; // 系统节点

    /* 方法 */ 
    void set_main_group_node();

    
};
#endif