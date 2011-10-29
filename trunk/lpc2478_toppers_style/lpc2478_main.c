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

static void system_test1(void);

int main()
{
	uint8_t i = 0;
	volatile uint32_t start_dly_cnt = 0;
	volatile uint32_t cnt_to_delay[64] = {0};
	volatile uint32_t cnt_passed = 0;
    /*pll init*/
	PLL_Init();
    UART_Init(115200);
    timer2_capinit();

	//sil_wrw_mem((void *)SCS,0x3);/* EMC reset disable*/
	//while(sil_rew_mem((void *)EMC_STAT)&0x1);
	//sil_wrw_mem((void *)EMC_CTRL,0);/*disable EMC*/

//	sil_wrw_mem((void *)FIO3DIR,sil_rew_mem((void *)FIO3DIR) & (0xff00) );
//	sil_wrw_mem((void *)PINMODE6,0x0000ffff);
//	Delay_ms(1000);
//	sil_wrw_mem((void *)PINMODE6,0x00000000);

	LCD_IO_Init();

//    LCD_CHIP_SEL_0();
//    LCD_OUT_DATA(0x00);
//	LCD_RST_LOW();
//	LCD_RS_LOW();
//	LCD_R_W_LOW();
//	LCD_E_LOW();
    LCD_Init();


    //UART_Printf("Flush Screen Test Start\n");
    //timer2_delayms(3000);
    while(1)
    {
    	sil_wrw_mem((void *)T2TCR,0x02);
    	sil_wrw_mem((void *)T2TCR,0x01);
    	start_dly_cnt = sil_rew_mem((void *)T2TC);
    	LCD_ClrScreen(i);
    	cnt_passed = sil_rew_mem((void *)T2TC) - start_dly_cnt;
    	cnt_to_delay[i/4] += cnt_passed;
    	if ((!(i%4))&&(i!=0)){
    		cnt_to_delay[i/4-1] = cnt_to_delay[i/4-1] / 4;
    	}
    	if (i==255){
    		cnt_to_delay[i/4] = cnt_to_delay[i/4] / 4;
    	}

    	//UART_Printf("Use %d to FLush Screen Used:%ld\n",i,cnt_passed);
    	/*LCD_RST_LOW();
    	LCD_RS_HIGH();
    	LCD_R_W_LOW();
    	LCD_E_HIGH();
    	LCD_OUT_DATA(0x55);
    	//LCD_CHIP_SEL_2();
    	sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xfffff8ff)) | (5L<<8) );*/
    	i++;
    	timer2_delayms(1);
    }

    return 0;
}
static void system_test1(void)
{
//	RTCTime local_time, alarm_time, current_time;
//	uint16_t i = 0, j = 1;
//
//    /*pll init*/
//	PLL_Init();
//    //Buzzer_Init();
//    //UART_Init(115200);
//    RTC_Init();
//    //pwm_init(PWM_CHANNEL_1,1000);
//    timer2_capinit();
//    //EEPROM_Init(I2C_CHL1,EEPROM_CLK);
//    //CH452_Init(CH452_CLK);
//	local_time.RTC_Sec = 00;
//	local_time.RTC_Min = 33;
//	local_time.RTC_Hour = 11;
//	local_time.RTC_Mday = 25;
//	local_time.RTC_Wday = 3;
//	local_time.RTC_Yday = 145;		/* current date 05/10/2011 */
//	local_time.RTC_Mon = 5;
//	local_time.RTC_Year = 2011;
//	//RTC_SetTime( local_time );		/* Set local time */
//	alarm_time.RTC_Sec = 0;
//	alarm_time.RTC_Min = 34;
//	alarm_time.RTC_Hour = 11;
//	alarm_time.RTC_Mday = 25;
//	alarm_time.RTC_Wday = 3;
//	alarm_time.RTC_Yday = 145;		/* alarm date 05/10/2011 */
//	alarm_time.RTC_Mon = 5;
//	alarm_time.RTC_Year = 2011;
//	RTC_SetAlarm(alarm_time);
//	RTC_Start();
//    while(1){
//    	i = (i>15)?0:i;
//    	//CH452_LED_OPEN(1<<i,1);
//    	current_time = RTC_GetTime();
//    	UART_Printf("Time: %d-%d-%d\t%d:%d:%d\n",current_time.RTC_Year,current_time.RTC_Mon,current_time.RTC_Mday,current_time.RTC_Hour,current_time.RTC_Min,current_time.RTC_Sec);
////    	for (i=0x0;i<0x80;i++){
////    		EEPROM_WriteByte(I2C_CHL1,i,(uint8_t)(i*j));
////    	}
////    	current_time = RTC_GetTime();
////    	UART_Printf("Time: %d-%d-%d\t%d:%d:%d\n",current_time.RTC_Year,current_time.RTC_Mon,current_time.RTC_Mday,current_time.RTC_Hour,current_time.RTC_Min,current_time.RTC_Sec);
////    	for (i=0x0;i<0x80;i++){
////    		UART_Printf("%d:%d\n",i,EEPROM_ReadByte(I2C_CHL1,i));
////    		timer2_delayms(10);
////    	}
////    	current_time = RTC_GetTime();
////    	UART_Printf("Time: %d-%d-%d\t%d:%d:%d\n",current_time.RTC_Year,current_time.RTC_Mon,current_time.RTC_Mday,current_time.RTC_Hour,current_time.RTC_Min,current_time.RTC_Sec);
////    	j = (j>15)?0:j;
////    	j++;
//    	//pwm_setpwm1duty(PWM_PORT_2,20);
//    	//pwm_setpwm1duty(PWM_PORT_1,20);
////    	Buzzer(BUZZER_ON);
//    	//Delay_ms(2000);
////    	Buzzer(BUZZER_OFF);
////    	//timer2_delayms(1000);
////    	PRINT_Log("Hello World!\n");
//    }
}
