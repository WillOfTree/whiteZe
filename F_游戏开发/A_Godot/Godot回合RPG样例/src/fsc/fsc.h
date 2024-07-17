#ifndef __TFSC_CPP_H__
#define __TFSC_CPP_H__

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/button.hpp>

#include <vector>
#include <map>

#include "../common_methods/common.h"


using namespace godot;

class TFSC : public Node
{
    /*
     * 定义一个宏，
     * 	Example：当前你的类名
     * 	Node3D：当前类继承的类名
     */
    GDCLASS(TFSC, Node);
    
public:
    virtual String get_class_name(); // 返回名称
    virtual void t_initiazlie(); // 进入状态时会调用
    virtual bool enter_condition(); // 判断是否进入某种状态
    virtual void t_update(double delta); // 持续执行的程序
    virtual bool exit_condition(); // 判断退出条件状态
    virtual void t_exit(); // 退出状态会调用

    void check_state_transitions(); // 状态切换方法
    
    // bool get_fsc_main_group(std::map<String, Node *> *a); // 获取map变量 
    // Node * get_fsc_system_node(); // 获取Node节点

    // 测试：
    // std::map<String, Node *> m_main_group = {}; // main分组中所有节点
    // Node * m_system_node = NULL; // system 节点

    // static Node * s_system_node; // 
    static std::map<String, Node *> s_global_node; // 静态节点，所有可用的其他节点
protected:
    static void _bind_methods();


private:
    String m_class_name = "TFSC"; // 类名
    TFSC * m_current_state = NULL; // 当前状态
    std::vector<TFSC *> m_game_state = {};  // 游戏状态
    

    /**
     * 私有方法
     */
    void set_inital_state(TFSC * z); // 设置初始化状态
};
#endif