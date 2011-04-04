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

	int8_t temp,i,j,k ;
    PLL_Init();
    UART_Init(115200);

    //FIO0MASK3 = 0x00;
    setregbits(PINSEL0,~(3<<22),(0<<22));  	/*设置p0.11为gpio*/
    setregbits(PINMODE0,~(3<<22),(0<<22));  	/*设置p0.11为下拉*/
    //setregbits(IODIR0,~(1<<25),(1<<25));  	/*设置地址脚为输出*/
    setregbits(FIO0DIR1,~(1<<3),(0<<3));  	/*设置地址脚为输入*/
	//setregbits(FIO0CLR1,~(1<<3),(1<<3));			/*设置p0.11输出为低*/

    //IOCLR0 = (1l<< 25);
    //FIO0CLR3  = 0x02;
    //FIO3PIN0 = ((FIO3PIN0 & (~(1<<1))) |(0<<1));
    I2C_Init(I2C_CHL0,I2CMASTER,I2C0_CLK,I2C0_ADDR);
    I2C_Init(I2C_CHL1,I2CSLAVE,I2C1_CLK,I2C1_ADDR);

    
    I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|(CH452_ACK>>7), (uint8_t)(CH452_ACK)); /*选择CH452的2线接口ACK。这个必须最先发出去*/
    I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|(CH452_SYSON2>>7), (uint8_t)(CH452_SYSON2));/*打开键盘，显示驱动*/
    I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|(CH452_NO_BCD>>7), 0x00); /*设置非BCD译码,扫描极限为4,显示驱动占空比为100%*/
    I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|(CH452_TWINKLE>>7), 0x00); /*设置不闪烁*/
    CH452_LED_OPEN(0x7fff,0);
    while(1){
        if ((IOPIN0 & (1<<11)) == 0x00){
            //UART_Printf("\nKey Pressed!\n");
            temp = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|(CH452_GET_KEY>>7)); /*读按键代码*/
            if (temp & (1<<6)){   /*Key Pressed*/
                UART_Printf("\nR %d C %d P \n",(temp >> 3)&0x07,temp&0x07);
                //Delay_ms(200);
            }
            else{    /*No Key Pressed*/
            	UART_Printf("\nR %d C %d R \n",(temp >> 3)&0x07,temp&0x07);
                //Delay_ms(200);
            }
        }
    	//UART_Printf("\nTest The CH452 Communicatation!\n");
    	//Delay_ms(100);

    	i = (i>3)?0:i;
    	j = (j>255)?0:j;
    	Delay_ms(100);
    	temp = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|0x10|(i<<1)); /*读seg代码*/
    	//UART_Printf("\nSEG：%d\n",temp);
    	//Delay_ms(100);

    	//I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|0x10|(i<<1), j); /*写LED*/
    	//I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|(CH452_LEVEL>>7), 32);
        //CH452_LED_OPEN(0xff,3);
    	//I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|((CH452_SET_BIT&0x0f00)>>7),CH452_SET_BIT&0xff);
    	k = (k>15)?0:k;
    	CH452_LED_OPEN_SEL(k,0);
    	Delay_ms(500);
    	CH452_LED_OPEN_SEL(k,1);
		Delay_ms(500);
		CH452_LED_OPEN_SEL(k,2);
		Delay_ms(500);
		CH452_LED_OPEN_SEL(k,3);
		Delay_ms(500);
        //CH452_LED_OPEN(0x0555,2);
		temp = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|0x0); /*读芯片版本*/
		///UART_Printf("\nCH452 Version：%d\n",temp);
		//Delay_ms(100);

		//temp = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|0xe); /*读按键代码*/
		//UART_Printf("Key Pin：%d\n",temp);
		//Delay_ms(100);

    	i++;
    	j++;
    	k++;
    }
    
}
