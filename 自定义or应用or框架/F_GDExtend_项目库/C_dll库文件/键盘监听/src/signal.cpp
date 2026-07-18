#include "controller/signal.h"

#include <godot_cpp/core/class_db.hpp>  // 关键！ADD_SIGNAL 在这里定义

using namespace godot;


// 单例对象
TSignalController * TSignalController::singleton = nullptr;


void TSignalController::_bind_methods()
{
    //! ADD_SIGNAL(MethodInfo("")); 
    // 
    // ADD_SIGNAL(MethodInfo( 
    //     "not_have_music",//信号名称
    //     PropertyInfo(Variant::STRING, "key")
    // ));

    // 供GDScript调用的信号
    ADD_SIGNAL(MethodInfo("key_event", 
        PropertyInfo(Variant::INT, "keycode"),
        PropertyInfo(Variant::STRING, "keystatus")
    ));
};


/**
 * 初始化方法，用于信号连接
 * 
 * 当GDExtension触发GDScript方法时，需要在GDScript中绑定
 * 只有在GDExtension中触发GDExtension才使用initalize()方法初始化绑定
 */
void TSignalController::initialize()
{
    // 连接信号
    // connect("create_new_layout", Callable(TKeyboardManager::get_singleton(), "create_new_keyboard"));
};


// 获取单例
TSignalController * TSignalController::get_singleton()
{
    if (singleton == nullptr)
    {
        singleton = memnew(TSignalController);
    }
    return singleton;
};

