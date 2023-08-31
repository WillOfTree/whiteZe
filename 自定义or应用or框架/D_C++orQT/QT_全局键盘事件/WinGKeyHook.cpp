
#include "keyhook.h"
//#include <QDebug>

HHOOK g_hook;

// 钩子回调函数
/* HookProc可自定义名字
 * LRESULT  CALLBACK  HookProc(int  nCode, WPARAM wParam, LPARAM lParam)
 *  int  nCode: 挂钩过程用于确定如何处理消息的代码。如果nCode小于零，则挂钩过程必须将消息传递给 CallNextHookEx 函数而不进行进一步处理，并且应返回CallNextHookEx返回的值
 *  wParam：信号类型：WM_KEYDOWN、WM_KEYUP、WM_SYSKEYDOWN或WM_SYSKEYUP
 *  lParam：KBDLLHOOKSTRUCT结构体指针
*/
LRESULT CALLBACK callBackKeyHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    // 定义键盘事件，用于获取按下的是哪个键
    KBDLLHOOKSTRUCT *Key_Info = (KBDLLHOOKSTRUCT *)lParam;
    // 键盘按下事件
    if (wParam == WM_KEYDOWN)
    {
        /* 这里按键事件的具体处理方法
         * static void s_keyhookSend(int Key_info);
         * Key_Info->vkCode获取键盘的按键，ASCII码，int类型
         **/
        //Widget::s_keyhookSend(Key_Info->vkCode);
    }

    // 调用下一个钩子
    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}


KeyHook::KeyHook()
{
    /*
     * HHOOK SetWindowsHookEx(int idHook, HOOKPROC lpfn, HINSTANCE hMod, DWORD dwThreadId)
     *  int idHook: 它是和钩子函数类型一一对应的。常用钩子函数类型如下：
     *      WH_KEYBOARD 键盘钩子
     *      WH_KEYBOARD_LL，不用新建dll即可捕获全局消息
     *      WH_MOUSE 表示是鼠标钩子
     *      WH_MOUSE_LL 是低级鼠标钩子;
     *  HOOKPROC lpfn: 钩子回调函数的地址，名字可自己定义见1.2
     *  HINSTANCE hMod：钩子函数所在的实例的句柄。对于线程钩子，该参数为NULL；对于系统钩子，该参数为钩子函数所在的DLL句柄。
     *  DWORD dwThreadId：指定钩子所监视的线程的线程号。对于全局钩子，该参数为NULL。
    */
    g_hook=SetWindowsHookExW(WH_KEYBOARD_LL, callBackKeyHook, nullptr, 0);

}

/**
* 析构方法，使用delete
*/
KeyHook::~KeyHook()
{
    UnhookWindowsHookEx(g_hook);
    g_hook = nullptr;
    //qDebug() << "end2";
}

/**
    钩子卸载方法
*/
void KeyHook::unInstallHook()
{
    if(g_hook){
        UnhookWindowsHookEx(g_hook);
        g_hook = nullptr;
        //qDebug() << "end1";
    }

    //qDebug() << "end1";
}
