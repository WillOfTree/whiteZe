#include "LIB80C52.h"


// 矩阵键盘相关方法
#if CTRL_MATRIXKEY
/**
 * @brief 获取矩阵键盘
 */
int MatrixKey(){
	return 0;
}
#endif


//定时器相关方法
#if CTRL_DELAY
/**
  * @brief  
  * @param  
  * @retval 
  */
void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}
#endif


#if CTRL_BUZZER
/**
 * @brief  蜂鸣器
 * @param  
 * @retval 
 **/
void BuzzerTime()
{
    BUZZER = !BUZZER;
}
/** 使用样例
for(i = 0; i<100; i++){
    BuzzerTime(); // 核心
    Delay(1);
}
*/
#endif


#if CTRL_DTUBE
/**
 * @brief  数码管显示
 * @param  
 * @retval 
 **/
void DigitalTube(unsigned int location, int n)
{

    /* 不明白这么定义，移动代码会出错
    而且在这个数组定义前不可使用if*/
    unsigned char NixieTable[] = {
        D_NUM00, D_NUM01, D_NUM02, D_NUM03, D_NUM04,
        D_NUM05, D_NUM06, D_NUM07, D_NUM08, D_NUM09,
        D_ERROR
    };
    
    // 3个位确定位置
    switch(location){
        case 0: 
            DTUBR_PIN0 = 0;
            DTUBR_PIN1 = 0;
            DTUBR_PIN2 = 0;
            break;
        case 1: 
            DTUBR_PIN0 = 1;
            DTUBR_PIN1 = 0;
            DTUBR_PIN2 = 0;
            break;
        case 2: 
            DTUBR_PIN0 = 0;
            DTUBR_PIN1 = 1;
            DTUBR_PIN2 = 0;
            break;
        case 3: 
            DTUBR_PIN0 = 1;
            DTUBR_PIN1 = 1;
            DTUBR_PIN2 = 0;
            break;
        case 4: 
            DTUBR_PIN0 = 0;
            DTUBR_PIN1 = 0;
            DTUBR_PIN2 = 1;
            break;
        case 5: 
            DTUBR_PIN0 = 1;
            DTUBR_PIN1 = 0;
            DTUBR_PIN2 = 1;
            break;
        case 6: 
            DTUBR_PIN0 = 0;
            DTUBR_PIN1 = 1;
            DTUBR_PIN2 = 1;
            break;
        case 7: 
            DTUBR_PIN0 = 1;
            DTUBR_PIN1 = 1;
            DTUBR_PIN2 = 1;
            break;
    }
    
    // 如果数
    DTUBR_PIN_NUM = NixieTable[n];
}
#endif