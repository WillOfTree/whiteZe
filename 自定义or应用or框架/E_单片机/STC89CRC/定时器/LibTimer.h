/*
* Copyright (c) 
* All rights reserved.
* 
* 文件名称：LIB80C52.h
* 型    号：STC89C52RC
* 摘    要：给单片机提供具体功能
* 
* 提供的具体方法简介
*    1、int MatrixKey(); 矩阵键盘
*    2、void Delay(unsigned int xms); 延迟方法 单位ms
*    3、void Timer0Init(); 定时初始化
*
* 当前版本：1.0
* 作    者：WILLOFTREE
* 完成日期：2023年7月30日
*/
#ifndef __LIBTIMER_H__
#define __LIBTIMER_H__

#include <REGX52.H>


// 定时模式 / 计数模式选择，1定时模式，0计数模式
#define TIME_TMOD 1
// 0xFC18到0xffff=>1000us=>1ms
// 0xEC78到0xffff=>5000um=>5ms=>5*200=>1s
#define TIME_TH 0XFC
#define TIME_TL 0X18

/* 时间相关方法 */
void Timer0Init();


#endif