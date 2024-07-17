
#ifndef __TOTHERSTATE_CPP_H__
#define __TOTHERSTATE_CPP_H__

#include "fsc.h"


using namespace godot;


class TOTHERSTATE : public TFSC 
{
    
    GDCLASS(TOTHERSTATE, TFSC);

public:
    TOTHERSTATE();
    ~TOTHERSTATE();
    // 必须要有这个，不然会执行3次
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