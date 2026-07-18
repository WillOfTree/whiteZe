/*
* Copyright (c) 
* All rights reserved.
* 
* 文件名称：WinGKeyHook.h
* 摘    要：提供捕获全局键盘事件，通过向windows系统中注册钩子函数，当键盘按下时由系统自动调用回调函数
* 
* 具体方法简介
*    1、核心方法有3：
*       SetWindowsHookExW：windows注册钩子方法
*       LRESULT  CALLBACK  HookProc(int  nCode, WPARAM wParam, LPARAM lParam)：钩子的回调函数，HookProc可自定义
*       HHOOK g_hook：定义一个钩子类型变量
*    2、可以将HookProc定义在类内，g_hook变成类内属性，但本例不是
* 
* 使用方法：
*    // 创建WinGkeyHook实例，保存hook实例，用于析构hook，卸载钩子
*    WinGkeyHook *hook = new WinGkeyHook;
*    // 建立静态方法A，并将静态方法写到HookProc内，使键盘回调函数可以触发QT程序中的其他方法
*
* 当前版本：1.0
* 作    者：WILLOFTREE
* 完成日期：2023年8月2日
*/
#ifndef __WINGKEYHOOK_H_
#define __WINGKEYHOOK_H_

#include <windows.h>
//#include "widget.h"


class WinGKeyHook
{
public:
    WinGKeyHook();
    ~WinGKeyHook();

    // 卸载钩子
    void unInstallHook();

};

#endif // __WINGKeyHook_H_
