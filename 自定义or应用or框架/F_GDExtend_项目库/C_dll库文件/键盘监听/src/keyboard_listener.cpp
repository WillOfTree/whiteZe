#include "controller/keyboard_listener.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "controller/signal.h"

using namespace godot;


// 静态成员初始化
HHOOK TKeybordListenerController::keyboard_hook = nullptr;
// 单例对象
TKeybordListenerController * TKeybordListenerController::singleton = nullptr;



void TKeybordListenerController::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("start_listen"), &TKeybordListenerController::start_listen);
    ClassDB::bind_method(D_METHOD("stop_listen"), &TKeybordListenerController::stop_listen);
    ClassDB::bind_method(D_METHOD("is_listening"), &TKeybordListenerController::is_listening);

    // ClassDB::bind_method(D_METHOD("get_move_down"), &TKeybordListenerController::get_move_down);
    // ClassDB::add_property("TKeybordListenerController",
    // 	PropertyInfo(Variant::STRING, "Down"),
    //     "set_move_down",
    //     "get_move_down");
}


/**
 * 获取单例
 */
TKeybordListenerController * TKeybordListenerController::get_singleton()
{
    if (singleton == nullptr)
    {
        singleton = memnew(TKeybordListenerController);
    }
    return singleton;
};


/**
 * 钩子回调函数实现
 */
LRESULT CALLBACK TKeybordListenerController::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
    // nCode < 0 时必须传递给 CallNextHookEx
    if (nCode < 0) 
    {
        return CallNextHookEx(keyboard_hook, nCode, wParam, lParam);
    }
    
    if (nCode == HC_ACTION) 
    {
        KBDLLHOOKSTRUCT* pKbStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        
        if (singleton) 
        {
            // 判断按键状态
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) 
            {

                TSignalController::get_singleton()->emit_signal("key_event", static_cast<uint64_t>(pKbStruct->vkCode), "down"); // 发射信号
            } 
            else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) 
            {

                TSignalController::get_singleton()->emit_signal("key_event", static_cast<uint64_t>(pKbStruct->vkCode), "up");
            }
        }
    }
    
    // 始终放行按键，不拦截
    return CallNextHookEx(keyboard_hook, nCode, wParam, lParam);
}


/**
 * 开始监听
 */
bool TKeybordListenerController::start_listen() 
{
    // 检查是否已安装钩子
    if (TKeybordListenerController::keyboard_hook != nullptr) 
    {
        stop_listen();  // 先清理旧的钩子
        UtilityFunctions::print("TKeybordListenerController: Already listening");
        return true;
    }
    
    // 安装低级键盘钩子
    TKeybordListenerController::keyboard_hook = SetWindowsHookExW(
        WH_KEYBOARD_LL,           // 钩子类型：低级键盘钩子
        LowLevelKeyboardProc,     // 回调函数
        GetModuleHandleW(nullptr),// 当前模块句柄
        0                         // 0 表示全局钩子（所有线程）
    );
    
    if (TKeybordListenerController::keyboard_hook == nullptr) 
    {
        UtilityFunctions::print("TKeybordListenerController: Failed to install hook 'keyboard_hook is nullptr'");
        return false;
    }
    
    UtilityFunctions::print("TKeybordListenerController: Hook installed successfully");
    return true;
}


/**
 * 停止监听
 */
void TKeybordListenerController::stop_listen() 
{
    if (TKeybordListenerController::keyboard_hook != nullptr) 
    {
        UnhookWindowsHookEx(TKeybordListenerController::keyboard_hook);
        TKeybordListenerController::keyboard_hook = nullptr;

        UtilityFunctions::print("TKeybordListenerController: Hook removed");
    }
}


/**
 * 是否正在监听
 */
bool TKeybordListenerController::is_listening() const
{
    return TKeybordListenerController::keyboard_hook != nullptr;
}

