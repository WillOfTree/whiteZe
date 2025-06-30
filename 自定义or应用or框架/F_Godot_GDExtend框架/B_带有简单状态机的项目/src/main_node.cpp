#include "main_node.h"

// #include <godot_cpp/classes/scene_tree.hpp>

#include "controller/game_manager.h"
#include "controller/input_manager.h"
#include "controller/scene_manager.h"
#include "controller/signal_manager.h"


/**
 * 静态全局变量，供子类直接使用，不用使用Get_Node方法
 **/ 
// 管理器
TInputManager * TMainNode::s_global_inputmanager = nullptr;
TGameManager * TMainNode::s_global_gamemanager = nullptr;
TSceneManager * TMainNode::s_global_scenemanager = nullptr;
TSignalManager * TMainNode::s_global_signalmanager = nullptr;

Node * TMainNode::s_global_world = nullptr; 
Node * TMainNode::s_global_tfsc = nullptr;


void TMainNode::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("sys_initialize"), &TMainNode::sys_initialize);
}


/*****************************************************
 * 供外部GDScrip调用
 * 初始化方法
 *****************************************************/
void TMainNode::sys_initialize() 
{
    /**
     * TMainNode主节点
     */
    TMainNode::s_global_world = get_node<Node>("World"); 
    TMainNode::s_global_tfsc = get_node<Node>("TFSC");
    verification_main_node();


    /**
     * 管理器节点，可以需要添加新的管理器节点
     */
    Node * controller_node = get_node<Node>("TControllerNode");
    ERR_FAIL_NULL_MSG(controller_node, "NO Have Node 'main/TControllerNode'");

    TMainNode::s_global_inputmanager = controller_node->get_node<TInputManager>("TInputManager");
    TMainNode::s_global_gamemanager = controller_node->get_node<TGameManager>("TGameManager");
    TMainNode::s_global_scenemanager = controller_node->get_node<TSceneManager>("TSceneManager");
    TMainNode::s_global_signalmanager = controller_node->get_node<TSignalManager>("TSignalManager");

    verification_manager_node(); // 验证


    /**
     * 管理类初始化方法,
     */
    Array controller = controller_node->get_children();
    for (int i=0; i<controller.size(); i++)
    {
        TControllerNode *p = cast_to<TControllerNode>(controller[i]);
        p->initialize();
    }
}


/**
 * 验证方法
 */
void TMainNode::verification_main_node()
{
    ERR_FAIL_NULL_MSG(TMainNode::s_global_world, "NO Have Node 'main/World'");
    ERR_FAIL_NULL_MSG(TMainNode::s_global_tfsc, "NO Have Node 'main/TFSC'");
}


void TMainNode::verification_manager_node()
{
    ERR_FAIL_NULL_MSG(TMainNode::s_global_inputmanager, "NO Have Node 'Controller/input'");
    ERR_FAIL_NULL_MSG(TMainNode::s_global_gamemanager, "NO Have Node 'Controller/game'");
    ERR_FAIL_NULL_MSG(TMainNode::s_global_scenemanager, "NO Have Node 'Controller/scene'");
    ERR_FAIL_NULL_MSG(TMainNode::s_global_signalmanager, "NO Have Node 'Controller/sinal'");

    // ERR_FAIL_NULL_MSG(TMainNode::s_global_playermanager, "NO Have Node 'Manager/player'");
    // ERR_FAIL_NULL_MSG(TMainNode::s_global_enemymanager, "NO Have Node 'Manager/enemy'");
    // ERR_FAIL_NULL_MSG(TMainNode::s_global_skillmanager, "NO Have Node 'Manager/skill'");
    // ERR_FAIL_NULL_MSG(TMainNode::s_global_batmanager, "NO Have Node 'Manager/bat'");
}