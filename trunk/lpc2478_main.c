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
volatile uint8_t gl_pCH452_key = 0;
void main(){

	uint8_t temp,col,row,pressed,i = 0;
	int8_t j = 0;
    PLL_Init();
    UART_Init(115200);
    I2C_Init(I2C_CHL0,I2CMASTER,I2C0_CLK,I2C0_ADDR); 			/*init the i2c0 as master*/
    CH452_Init();												/*init ch452 keyboard and led*/
    EINT0_Init(FALLING_EDGE,HIGHEST_PRIORITY);

    while(1){
    	temp = gl_CH452_key;									/*read the ch452 key */
    	if (temp & 0x80){   									/*the first time pressed?*/
    		pressed = 0;
    		col = 0;
    		row = 0;
    	}else{
    		pressed = !!(temp & (1<<6));
    		col = temp&0x07;
    		row = (temp >> 3)&0x07;
    	}
    	if (pressed){   										/*Key Pressed*/
			UART_Printf("\nR %d C %d P \n",(temp >> 3)&0x07,temp&0x07);
			Delay_ms(10);
			CH452_KeyPress_Signal();
			gl_CH452_key = gl_CH452_key & 0x3f;
    	}
    	i = (i>15)?0:i;
    	j = (j>-1)?15:j;
    	if (i == 15){
    		I2C_Master_WriteByte(I2C_CHL0, CH452_LEVEL_CMD, 0);
    	}
    	if (!(temp & 0x80)){  									/*key process*/
    		if (col == 3){
    			switch (row) {
					case 0:
						CH452_LED_OPEN(1<<i,1);
						break;
					case 1:
						CH452_LED_OPEN(1<<i,2);
					    break;
					case 2:
						CH452_LED_OPEN(1<<i,3);
						break;
					case 3:
						CH452_LED_OPEN_SEL((15-i),3);
						break;
					case 4:
						CH452_LED_OPEN_SEL((15-i),2);
						break;
    			}
    		}
    	}
    	Delay_ms(10);
    	i++;
    	j--;
    }
    
}
