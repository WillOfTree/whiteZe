/**
 * 因为Object类不能获取场景树，所有需要TMainNode进行操作
 */
#ifndef __TSignalController_H__
#define __TSignalController_H__

// #include "interface/controller.h"
#include <godot_cpp/classes/object.hpp>


namespace godot
{
    // class Node;
}


class TSignalController : public godot::Object
{
    GDCLASS(TSignalController, godot::Object);

public:
    // virtual void initialize() override; // 初始化方法
    void initialize(); // 初始化方法
    static TSignalController * get_singleton(); // 获取单例方法

protected:
    static void _bind_methods();

private:
    static TSignalController * singleton; // 单例
};
#endif