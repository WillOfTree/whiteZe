/**
 * 所有类继承的父类，除了资源节点
 */
#ifndef __TMainNode_CPP_H__
#define __TMainNode_CPP_H__

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <map>

using namespace godot;

class TInputManager;
class TGameManager;
class TSceneManager;
class TSignalManager;

class TMainNode : public Node
{
    GDCLASS(TMainNode, Node);
public:
    /**
     * 静态属性，全局静态属性
     */ 
    static TInputManager * s_global_inputmanager; // 输入管理类 
    static TGameManager * s_global_gamemanager; // 游戏管理器
    static TSceneManager * s_global_scenemanager; // 场景管理器
    static TSceneManager * s_global_scenemanager; // 场景管理器
    static TSignalManager * s_global_signalmanager; // 信号管理器

    static Node * s_global_world;      // 世界场景
    static Node * s_global_tfsc;       // 状态机
    
protected:
    static void _bind_methods();

private:
    void sys_initialize(); // 供GDScript调用方法-初始化方法
    
    void verification_main_node(); // 验证方法
    void verification_manager_node(); // 验证管理器方法

};
#endif