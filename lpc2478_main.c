/**
 * @file   lpc2478_main.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 14:51:34 2011
 * 
 * @brief  
 * 
 * 
 */
#include "lpc2478_inc.h"

const uint8_t* Hello = "Hello World!\n";

void main(){

	int temp,i,j ;
    PLL_Init();
    UART_Init(115200);

    //FIO0MASK3 = 0x00;
    //setregbits(PINSEL0,~(3<<22),(0<<22));  	/*设置p0.11为gpio*/
    //setregbits(PINMODE0,~(3<<22),(0<<22));  	/*设置p0.11为下拉*/
    //setregbits(IODIR0,~(1<<25),(1<<25));  	/*设置地址脚为输出*/
    //setregbits(FIO0DIR1,~(1<<3),(1<<3));  	/*设置地址脚为输出*/
	//setregbits(FIO0CLR1,~(1<<3),(1<<3));			/*设置p0.11输出为低*/

    //IOCLR0 = (1l<< 25);
    //FIO0CLR3  = 0x02;
    //FIO3PIN0 = ((FIO3PIN0 & (~(1<<1))) |(0<<1));
    I2C_Init(I2C_CHL0,I2CMASTER,I2C0_CLK,I2C0_ADDR);
    I2C_Init(I2C_CHL1,I2CSLAVE,I2C1_CLK,I2C1_ADDR);


    I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|0x0e, 0x01); /*选择CH452的2线接口ACK。这个必须最先发出去*/
    I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|0x08, 0x03);/*打开键盘，显示驱动*/

    while(1){
    	UART_Printf("\nTest The CH452 Communicatation!\n");
    	Delay_ms(100);

    	i = (i>3)?0:i;
    	j = (j>255)?0:j;

    	temp = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|0x10|(i<<1)); /*读seg代码*/
    	UART_Printf("SEG：%d\n",temp);
    	Delay_ms(100);

    	I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|0x10|(i<<1), j); /*写LED*/

		temp = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|0x0); /*读芯片版本*/
		UART_Printf("CH452 Version：%d\n",temp);
		Delay_ms(100);

		temp = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|0xe); /*读按键代码*/
		UART_Printf("Key Pin：%d\n",temp);
		Delay_ms(100);

    	i++;
    	j++;
    }
    
}
