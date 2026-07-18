/**
 * @file keyboard_listener.h
 * @author <叙白> 
 * @brief 键盘监听器控制器类头文件，
 *  注意该监听模块只能监听全局键盘事件，不能监听游戏窗口内的键盘事件，当godot游戏场景获取焦点时，监听就会失效
 * @version 0.1
 * @date 2026-04-16
 */
#ifndef __TKeybordListenerController_CPP_H__
#define __TKeybordListenerController_CPP_H__

// #include "interface/controller.h"
#include <godot_cpp/classes/object.hpp> 

#include <windows.h>



namespace godot
{
	// class Input;
}


class TKeybordListenerController : public godot::Object // 继承接口文件
{
    GDCLASS(TKeybordListenerController, godot::Object); 
    
public:
    // virtual void initialize() override; // 接口文件必须实现方法
    static TKeybordListenerController * get_singleton(); // 获取单例方法

    bool start_listen(); // 开始监听
    void stop_listen(); // 停止监听
    bool is_listening() const; // 是否正在监听

protected:
    static void _bind_methods();

private:
    static HHOOK keyboard_hook; // 全局键盘钩子句柄
    static TKeybordListenerController * singleton; // 单例

    // 钩子回调函数（必须是静态的）
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    

};

#endif