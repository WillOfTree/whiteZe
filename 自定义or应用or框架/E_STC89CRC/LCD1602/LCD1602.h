#ifndef __LCD1602_H__
#define __LCD1602_H__

#define CTRL_CHAR 0
#define CTRL_STRING 0
#define CTRL_NUM 0
#define CTRL_SNUM 0
#define CTRL_HNUM 0
#define CTRL_BNUM 0

//用户调用函数：
void LCD_Init();
#if CTRL_CHAR
// 在第一行第一列显示字符‘A’：LCD_ShowChar(1, 1, 'A')
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
#endif
#if CTRL_STRING
// 在其实位置（Line行，column列）显示字符串:LCD_ShowChar(1, 1, 'ABC')
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
#endif
#if CTRL_NUM
// 指定位置开始显示所给数字
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
#endif
#if CTRL_SNUM
// 有符号十进制显示所给数字
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
#endif
#if CTRL_HNUM
// 十六进制显示所给数字
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
#endif
#if CTRL_BNUM
// 二进制显示所给数字
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
#endif

#endif