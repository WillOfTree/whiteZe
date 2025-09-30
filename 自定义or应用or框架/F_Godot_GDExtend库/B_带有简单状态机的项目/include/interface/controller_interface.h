#ifndef __TControllerInterface_CPP_H__
#define __TControllerInterface_CPP_H__

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>



class TControllerInterface : public godot::RefCounted
{
    GDCLASS(TControllerInterface, RefCounted); // Godot 必需的宏

protected:
    static void _bind_methods(){};
    
public:
    virtual void initialize() = 0; // 初始方法，需要再外部访问

    virtual ~TControllerInterface() = default; // 默认析构函数
};
#endif