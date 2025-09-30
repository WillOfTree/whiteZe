#ifndef __TSignalManager_CPP_H__
#define __TSignalManager_CPP_H__


#include "interface/controller_interface.h"



class TSignalManager : public TControllerInterface
{
    GDCLASS(TSignalManager, TControllerInterface);
    
public:
    virtual void initialize(); // 初始方法，需要再外部访问

    static TSignalManager * get_singleton();
    
protected:
    static void _bind_methods();

private:
    static TSignalManager * singleton;
};
#endif