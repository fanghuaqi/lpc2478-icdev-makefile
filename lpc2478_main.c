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
    I2C_Init(I2C_CHL0,I2CMASTER,I2C0_CLK,I2C0_ADDR);
    //I2C_Init(I2C_CHL1,I2CSLAVE,I2C1_CLK,I2C1_ADDR);

    I2C_Master_WriteByte(I2C_CHL0, 0x60|0x0e, 0x01); /*选择CH452的2线接口ACK。这个必须最先发出去*/
    I2C_Master_WriteByte(I2C_CHL0, 0x60|0x08, 0x03);/*打开键盘，显示驱动*/
    temp = I2C_Master_ReadByte(I2C_CHL0, 0x60|0x0); /*读芯片版本*/
    UART_Printf("%d\n",temp);

    while(1){
    	i = (i>3)?0:i;
    	j = (j>255)?0:j;
    	UART_Printf(Hello);
    	Delay_ms(100);
    	I2C_Master_WriteByte(I2C_CHL0, 0x60|0x10|(i<<1), j);
    	i++;
    	j++;
    }
    
}
