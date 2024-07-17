
#ifndef __TMOVESTATE_CPP_H__
#define __TMOVESTATE_CPP_H__

#include "fsc.h"

// #include <godot_cpp/classes/input.hpp>

using namespace godot;


class TMOVESTATE : public TFSC 
{
    
    GDCLASS(TMOVESTATE, TFSC);

public:
    TMOVESTATE();
    ~TMOVESTATE();
    
    void _ready();
    void _process(double _delta);
    // 初始化纯虚函数
    void initiazlie();
    void exit();
    void update(double delta);
    
    void send_signal();

protected:
    static void _bind_methods();
    // Input *ii;

private:
};

#endif