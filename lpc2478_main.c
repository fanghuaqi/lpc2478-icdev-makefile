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

    PLL_Init();
    UART_Init(115200);
    I2C_Init(I2C_CHL0,I2CMASTER,I2C0_CLK,I2C0_ADDR);


    while(1){
    	PRINT_Log(Hello);
    	Delay_ms(100);
    	I2C_ReadByte(WCH452_ADDR);
    }
    
}
