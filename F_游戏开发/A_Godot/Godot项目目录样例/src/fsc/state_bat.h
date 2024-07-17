
#ifndef __TBATSTATE_CPP_H__
#define __TBATSTATE_CPP_H__

#include "fsc.h"


using namespace godot;


class TBATSTATE : public TFSC 
{
    
    GDCLASS(TBATSTATE, TFSC);

public:
    TBATSTATE();
    ~TBATSTATE();

    void _ready();
    void _process(double _delta);
    // 初始化纯虚函数
    void initiazlie();
    void exit();
    void update(double delta);
    
    void send_signal();

protected:
    static void _bind_methods();

private:
};

#endif