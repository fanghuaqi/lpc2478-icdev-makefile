/**
 * =====================================================================================
 * 
 * @Filename  :lpc2478_rtc.c
 * @Version   : 0.1
 * @Author    :fanghuaqi <578567190@qq.com>
 * @Date      :Tue May 10 11:05:48 2011
 * 
 * @Brief     :the rtc test project
 * 
 * 
 * @Company   :HUST-Renesas Lab
 * @Revision  :
 * ======================================================================================
 * @0.1 Byfanghuaqi  Tue May 10 11:05:48 2011 Create orignal file
 * ======================================================================================
 */

#include "lpc2478_rtc.h"

ERCD RTC_Init(void)
{
    setregbits(PCONP,MASK_ALL,1 << 9);  /* power on  the rtc*/
    setregbits(RTC_AMR,MASK_ALL,0);  /*compare all the value when alarm*/
    setregbits(RTC_CIIR,MASK_ALL,0);  /*no interrupt*/
    setregbits(RTC_CISS,MASK_ALL,0);  /*no subsecond*/
    setregbits(RTC_CCR,MASK_ALL,0x10);  /*clock source select as RTC*/
    setregbits(PCONP,MASK_ALL,0 << 9);  /* use battery to power the rtc*/
    return ERCD_OK;
}
ERCD RTC_Start(void)
{
    setregbits(RTC_CCR,(~(1<<0)),(1<<0));/*enable rtc clock*/
    setregbits(RTC_ILR,(~(0x7<<0)),(0<<0));/*do noting*/
    return ERCD_OK;
}
ERCD RTC_Stop(void)
{
     setregbits(RTC_CCR,(~(1<<0)),(0<<0));/*disable rtc clock*/
     return ERCD_OK;
}

ERCD RTC_SetTime(RTCTime Time)
{
	setregbits(RTC_CCR,(~(1<<1)),(1<<0));/*ctc reset*/
	RTC_SEC = Time.RTC_Sec;
    RTC_MIN = Time.RTC_Min;
    RTC_HOUR = Time.RTC_Hour;
    RTC_DOM = Time.RTC_Mday;
    RTC_DOW = Time.RTC_Wday;
    RTC_DOY = Time.RTC_Yday;
    RTC_MONTH = Time.RTC_Mon;
    RTC_YEAR = Time.RTC_Year;
    setregbits(RTC_CCR,(~(1<<1)),(0<<0));/*ctc reset*/
    return ERCD_OK;
}

ERCD RTC_SetAlarm(RTCTime Alarm)
{
    RTC_ALSEC = Alarm.RTC_Sec;
    RTC_ALMIN = Alarm.RTC_Min;
    RTC_ALHOUR = Alarm.RTC_Hour;
    RTC_ALDOM = Alarm.RTC_Mday;
    RTC_ALDOW = Alarm.RTC_Wday;
    RTC_ALDOY = Alarm.RTC_Yday;
    RTC_ALMON = Alarm.RTC_Mon;
    RTC_ALYEAR = Alarm.RTC_Year; 
    return ERCD_OK;
}

RTCTime RTC_GetTime( void ) 
{
    RTCTime LocalTime;
    
    LocalTime.RTC_Sec = RTC_SEC;
    LocalTime.RTC_Min = RTC_MIN;
    LocalTime.RTC_Hour = RTC_HOUR;
    LocalTime.RTC_Mday = RTC_DOM;
    LocalTime.RTC_Wday = RTC_DOW;
    LocalTime.RTC_Yday = RTC_DOY;
    LocalTime.RTC_Mon = RTC_MONTH;
    LocalTime.RTC_Year = RTC_YEAR;
    return (LocalTime);    
}

