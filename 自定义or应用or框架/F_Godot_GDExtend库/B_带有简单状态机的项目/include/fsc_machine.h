/**
 * @class TFSCMachine
 * @brief 游戏状态机类，继承自 Godot 的 Object 类。
 *
 * 该类用于管理游戏中的状态切换，支持通过 C++ 和 GDScript 进行状态变更。
 *
 * 公有方法：
 * - change_current_state: 切换当前状态，传入目标状态和错误信息。
 * - gd_change_current_state: 供 GDScript 调用的状态切换方法，参数为变量类型。
 *
 * 保护方法：
 * - _bind_methods: Godot 绑定方法，用于注册类方法到 Godot 引擎。
 *
 * 私有成员：
 * - s_current_state: 当前状态指针，指向 TStateInterface。
 * - _default_state_name: 默认状态名称，初始化为 TStateInterface::TInit。
 *
 * 注意事项：
 * - 该类设计用于 Godot 游戏引擎，需配合 TStateInterface 使用。
 * - 部分静态成员已注释，若需要管理所有状态机实例可取消注释并实现相关逻辑。
 * 
 * @author 作者: 叙白
 * @date   日期: 20250715
 */
#ifndef __TFSCMachine_CPP_H__
#define __TFSCMachine_CPP_H__

#include <godot_cpp/classes/object.hpp>

#include <map>
#include <memory>

#include "interface/state_interface.h"


using namespace godot;

class TFSCMachine : public Object
{
    GDCLASS(TFSCMachine, Object);

public:
    
    // 切换状态
    void change_current_state(TStateInterface::TFSC_STATUS aim_state, String error_info);
    // 供GDScript调用的切换方法
    void gd_change_current_state(Variant aim_state, Variant error_info); 
    // 注册状态机方法
    // void register_state_machine(TStateInterface *state_machine, TStateInterface::TFSC_STATUS state_name);

    // ~TFSCMachine();

protected:
    static void _bind_methods();

private:
    //!  仅引入枚举值（如 VALUE1, VALUE2 等）,并不引入TStateInterface::TFSC_STATUS类型
    using enum TStateInterface::TFSC_STATUS;

    ////  TInit, TOrdinary, TChanageScence, TVerify, TOver,
    //// std::vector<TStateInterface::TFSC_STATUS> tfsc_state_vector 
    //// {
    ////     TNULL, 
    //// TBooting,
    ////     TInit,
    ////     TOrdinary
    //// }; // 状态地图

    // 智能指针，可以不 设置=0
    std::unique_ptr<TStateInterface> m_current_state = nullptr; // 当前状态
    // TStateInterface::TFSC_STATUS _default_state_name = TInit; // 默认游戏状态名称-类的名称
    std::map<TStateInterface::TFSC_STATUS, std::unique_ptr<TStateInterface>> all_state_machine;  // 状态机字节点，所有游戏状态

    void t_initiazlie(); // 状态机初始化方法
    // void state_factory();

    /**
     * 每一帧执行的程序
     */
    void t_update(double _delta);
    void t_physics_update(double _delta);

};
#endif