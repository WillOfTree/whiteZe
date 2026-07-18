/*
* Copyright (c) 
* All rights reserved.
* 
* 文件名称：LIBUART.h
* 型    号：STC89C52RC
* 摘    要：提供串口使用方法
* 
* 提供的具体方法简介
*    1、void UARTInit(); 串口初始化
*    2、void UARTSend(unsigned char byte); 串口发送信息
*
* 当前版本：1.0
* 作    者：WILLOFTREE
* 完成日期：2023年7月30日
*/
#ifndef __LIBUART_H__
#define __LIBUART_H__

#include <REGX52.H>


// 单片机同时接收和发送
#define UART_SCON 0x50
#define UART_ET 1
// 单片机只发送数据，不接收数据
//#define UART_SCON 0x40
//#define UART_ET 0

// 电源控制
#define UART_PCON 0x80

// 定时器初始值
// 9600波特率：TL=0xFA; TH=0xFA
// 4800波特率：TL=0xF3; TH=0xF3
#define UART_TL 0xF3
#define UART_TH 0xF3

/* 串口相关方法 */
void UARTInit();
void UARTSend(unsigned char byte);

#endif