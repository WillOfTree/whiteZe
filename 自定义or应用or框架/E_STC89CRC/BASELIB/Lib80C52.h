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
*    3、void BuzzerTime(unsigned int ms); 蜂鸣器
*    4、void DigitalTube(unsigned int location, int n); 数码管
*
* 当前版本：1.0
* 作    者：WILLOFTREE
* 完成日期：2023年7月30日
*/
#ifndef __BASELIB_H__
#define __BASELIB_H__

#include <REGX52.H>


//----- 定时器控制
#define CTRL_DELAY 1
//----- 矩阵键盘
#define CTRL_MATRIXKEY 0
//----- 蜂鸣器
#define CTRL_BUZZER 1
#define BUZZER_PIN P2^5
//----- 数码管
#define CTRL_DTUBE 1
#define DTUBR_PIN0 P2_2
#define DTUBR_PIN1 P2_3
#define DTUBR_PIN2 P2_4
#define DTUBR_PIN_NUM P0 // 显示什么数字
// 注意不同的物理结构，以下数据也应不同）
#define D_NUM01 0x06
#define D_NUM02 0x5b
#define D_NUM03 0x4f
#define D_NUM04 0x66
#define D_NUM05 0x6d
#define D_NUM06 0x7d
#define D_NUM07 0x07
#define D_NUM08 0x7F
#define D_NUM09 0x6F
#define D_NUM00 0x3F
#define D_ERROR 0x79
// a,b,c,d,e,f,g,空
//0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00


#if CTRL_DTUBE
void DigitalTube(unsigned int location, int n);
#endif

#if CTRL_DELAY
void Delay(unsigned int xms);
#endif

#if CTRL_MATRIXKEY
int MatrixKey();
#endif

#if CTRL_BUZZER
sbit BUZZER = BUZZER_PIN;
void BuzzerTime();
#endif

#endif