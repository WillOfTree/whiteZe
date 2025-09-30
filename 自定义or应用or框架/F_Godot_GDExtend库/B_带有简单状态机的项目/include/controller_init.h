#ifndef __TControllerInit_CPP_H__
#define __TControllerInit_CPP_H__

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


class TControllerInterface;


class TControllerInit : public RefCounted
{
    GDCLASS(TControllerInit, RefCounted);
public:
    static void register_controller(TControllerInterface * p);

protected:
    static void _bind_methods();

private:
    void initialize();

    static std::vector<TControllerInterface *> controller_set;
};
#endif