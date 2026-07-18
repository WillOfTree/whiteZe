#include "LIBUART.h"

/**
 * @brief  串口初始化方法
 * @param  
 * @retval 
 **/
void UARTInit(){
    /* serial control（串行接口控制）
    -  SM0/SM1: 工作方式选择
            00：方式0，移位寄存器，波特率f/12
            01: 方式1，10位异步收发器，波特率可变（常用）
            10: 方式2，11位异步收发器，f/64或f/32
            11：方式3，11位异步收发器，波特率可变
    -  SM2：
            0不管RB8的数据，收到信息放入SBUF中，激活RI
            1，RB8=0，丢弃信息
            1，RB8=1，收到信息放入SBUF中，激活RI
    -  REN： 
            1启用串口接收数据
            0关闭串口接收数据（只发不收）
    -  TB8：在方式2、3中起奇偶校验、地址帧、数据帧
    -  RB8：工作方式1中需要接受数据1，不需要接收数据0
    -  TI：发送数据中断
    -  RI：接受数据中断
    */
    SCON = UART_SCON;
    
    /* Power control（电源控制）*/ 
    PCON = UART_PCON;
    
    /* 设置波特率 
    -  串口定时器只能使用T1
    -  串口使用双8位自动重装计时器
    */ 
    TMOD &= 0x0F;
    // 0010 0000:8位自动重装
    TMOD |= 0x20;
    
    /* 定时器初始值设置 */
    //给定时器赋初值，定时 1ms
    TL1 = UART_TL;
    TH1 = UART_TH;
    
    /* 其他配置 */
    // 默认为0，不需要中断函数
    ET1 = 0;
    // 启动定时器1
    TR1 = 1;  
    
#if UART_ET
    EA = 1;
    ES = 1;
#endif
}

/**
 * @brief  发送数据
 * @param  byte发送的16进制数据
 * @retval 
 **/
void UARTSend(unsigned char byte){
    // SBUF是数据缓冲区，只要往里写就可以
    SBUF = byte;
    // 判断是否发送成功，1发送完成，0尚未完成
    while(TI == 0);
    // 必须手动设置TI=0
    TI = 0;
}

/*
// 单片机接收函数样例
void 自定义名() interrupt 4
{
  
}
*/
