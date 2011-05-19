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

int main()
{
	RTCTime local_time, alarm_time, current_time;
	uint16_t i = 0, j = 0;

    /*pll init*/
	PLL_Init();
    Buzzer_Init();
    UART_Init(115200);
    RTC_Init();
    pwm_init(PWM_CHANNEL_1,1000);
    timer2_capinit();
    EEPROM_Init(I2C_CHL1,EEPROM_CLK);
	local_time.RTC_Sec = 00;
	local_time.RTC_Min = 51;
	local_time.RTC_Hour = 19;
	local_time.RTC_Mday = 19;
	local_time.RTC_Wday = 4;
	local_time.RTC_Yday = 139;		/* current date 05/10/2011 */
	local_time.RTC_Mon = 5;
	local_time.RTC_Year = 2011;
	//RTC_SetTime( local_time );		/* Set local time */
	alarm_time.RTC_Sec = 0;
	alarm_time.RTC_Min = 52;
	alarm_time.RTC_Hour = 19;
	alarm_time.RTC_Mday = 19;
	alarm_time.RTC_Wday = 4;
	alarm_time.RTC_Yday = 139;		/* alarm date 05/10/2011 */
	alarm_time.RTC_Mon = 5;
	alarm_time.RTC_Year = 2011;
	RTC_SetAlarm(alarm_time);
	RTC_Start();
    while(1){
    	current_time = RTC_GetTime();
    	UART_Printf("Time: %d-%d-%d\t%d:%d:%d\n",current_time.RTC_Year,current_time.RTC_Mon,current_time.RTC_Mday,current_time.RTC_Hour,current_time.RTC_Min,current_time.RTC_Sec);
    	for (i=0x0;i<0x800;i++){
    		EEPROM_WriteByte(I2C_CHL1,i,(uint8_t)(i*j));
    	}
    	current_time = RTC_GetTime();
    	UART_Printf("Time: %d-%d-%d\t%d:%d:%d\n",current_time.RTC_Year,current_time.RTC_Mon,current_time.RTC_Mday,current_time.RTC_Hour,current_time.RTC_Min,current_time.RTC_Sec);
    	for (i=0x0;i<0x800;i++){
    		UART_Printf("%d:%d\n",i,EEPROM_ReadByte(I2C_CHL1,i));
    		timer2_delayms(50);
    	}
    	j = (j>15)?0:j;
    	j++;
    	//pwm_setpwm1duty(PWM_PORT_2,20);
    	//pwm_setpwm1duty(PWM_PORT_1,20);
    	//Buzzer(BUZZER_ON);
    	timer2_delayms(2000);
    	//Buzzer(BUZZER_OFF);
    	//timer2_delayms(1000);
    	PRINT_Log("Hello World!\n");
    }
    return 0;
}
