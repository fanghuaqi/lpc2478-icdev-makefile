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

//const uint8_t* Hello = "Hello World!\n";
volatile uint8_t gl_pCH452_key = 0;
void main(){

	//uint8_t temp,col,row,pressed,i = 0;
	//int8_t j = 0;
	volatile uint32_t i = 0;
	RTCTime local_time, alarm_time, current_time;
    PLL_Init();

    UART_Init(115200);
    //I2C_Init(I2C_CHL0,I2CMASTER,I2C0_CLK,I2C0_ADDR); 			/*init the i2c0 as master*/
    //CH452_Init();												/*init ch452 keyboard and led*/
    //EINT0_Init(FALLING_EDGE,HIGHEST_PRIORITY);
    UART_Printf("Hello World!\n");
    //EEPROM_Init(I2C_CHL1,EEPROM_CLK);
    Buzzer_Init();
    RTC_Init();
    //I2CInit(40000);
   // Delay_ms(10);
	local_time.RTC_Sec = 59;
	local_time.RTC_Min = 19;
	local_time.RTC_Hour = 11;
	local_time.RTC_Mday = 11;
	local_time.RTC_Wday = 3;
	local_time.RTC_Yday = 131;		/* current date 05/10/2011 */
	local_time.RTC_Mon = 5;
	local_time.RTC_Year = 2011;
	//RTC_SetTime( local_time );		/* Set local time */
	alarm_time.RTC_Sec = 0;
	alarm_time.RTC_Min = 11;
	alarm_time.RTC_Hour = 15;
	alarm_time.RTC_Mday = 10;
	alarm_time.RTC_Wday = 1;
	alarm_time.RTC_Yday = 180;		/* alarm date 05/10/2011 */
	alarm_time.RTC_Mon = 5;
	alarm_time.RTC_Year = 2011;
	//RTC_SetAlarm(alarm_time);
	RTC_Start();
    while(1){
    	current_time = RTC_GetTime();
    	UART_Printf("Time: %d-%d-%d\t%d:%d:%d\n",current_time.RTC_Year,current_time.RTC_Mon,current_time.RTC_Mday,current_time.RTC_Hour,current_time.RTC_Min,current_time.RTC_Sec);
    	Delay_ms(1000);
    	//for (i=0x0;i<0x40;i++){
//    	    	//
//    		//I2CWriteByte(0xa0, i, 3);
//    		//EEPROM_WriteByte(I2C_CHL1,i,i);
//    	    //Delay_ms(40);
//    	    	//EEPROM_ReadByte(I2C_CHL1,i);
//    	}
//    	//Delay_ms(1);
//    	for (i=0x0;i<0x40;i++){
//    		UART_Printf("%d:%d\n",i,EEPROM_ReadByte(I2C_CHL1,i));//I2CReadByte(0xa0, i));
//    		//EEPROM_ReadByte(I2C_CHL1,i);
//    		//Delay_ms(50);
//    	}
    	//Buzzer(1);
    	//for (i=0x0;i<0x400;i++);
    	//Delay_ms(1);
    	//Buzzer(0);
    	//for (i=0x0;i<0x400;i++);
    	//Delay_ms(1);
    	//Delay_ms(1000);
    	//UART_Printf("Hello World!\n");
//    	temp = gl_CH452_key;									/*read the ch452 key */
//    	if (temp & 0x80){   									/*the first time pressed?*/
//    		pressed = 0;
//    		col = 0;
//    		row = 0;
//    	}else{
//    		pressed = !!(temp & (1<<6));
//    		col = temp&0x07;
//    		row = (temp >> 3)&0x07;
//    	}
//    	if (pressed){   										/*Key Pressed*/
//			UART_Printf("\nR %d C %d P \n",(temp >> 3)&0x07,temp&0x07);
//			Delay_ms(10);
//			CH452_KeyPress_Signal();
//			gl_CH452_key = gl_CH452_key & 0x3f;
//    	}
//    	i = (i>15)?0:i;
//    	j = (j>-1)?15:j;
//    	if (i == 15){
//    		I2C_Master_WriteByte(I2C_CHL0, CH452_LEVEL_CMD, 0);
//    	}
//    	if (!(temp & 0x80)){  									/*key process*/
//    		if (col == 3){
//    			switch (row) {
//					case 0:
//						CH452_LED_OPEN(1<<i,1);
//						break;
//					case 1:
//						CH452_LED_OPEN(1<<i,2);
//					    break;
//					case 2:
//						CH452_LED_OPEN(1<<i,3);
//						break;
//					case 3:
//						CH452_LED_OPEN_SEL((15-i),3);
//						break;
//					case 4:
//						CH452_LED_OPEN_SEL((15-i),2);
//						break;
//    			}
//    		}
//    	}
//    	Delay_ms(10);
//    	i++;
//    	j--;
    }
    
}
