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
    setregbits(PCONP,(~(1 << 9)),1 << 9);  /* power on  the rtc*/
//    setregbits(RTC_AMR,MASK_ALL,0);  /*compare all the value when alarm*/
//    setregbits(RTC_CIIR,MASK_ALL,0);  /*no interrupt*/
//    setregbits(RTC_CISS,MASK_ALL,0);  /*no subsecond*/
    RTC_AMR = 0x01;
    RTC_CIIR = 0;
    RTC_CISS = 0;
    RTC_CCR = 0x10;
//    setregbits(RTC_CCR,MASK_ALL,0x10);  /*clock source select as RTC*/
    //RTC_PREINT = PREINT_RTC;
    //RTC_PREFRAC = PREFRAC_RTC;
    setregbits(PCONP,(~(1 << 9)),1 << 9);  /* use battery to power the rtc*/
    return ERCD_OK;
}
ERCD RTC_Start(void)
{
	RTC_ILR = 0x7; //clear the interrupt bits must do this to let the alarm pin to be low
	RTC_CCR = 0x11;
	//setregbits(RTC_CCR,(~(0x11<<0)),(0x11<<0));/*enable rtc clock*/
    //setregbits(RTC_ILR,(~(0x7<<0)),(0<<0));/*do noting*/
    return ERCD_OK;
}
ERCD RTC_Stop(void)
{
     setregbits(RTC_CCR,(~(1<<0)),(0<<0));/*disable rtc clock*/
     return ERCD_OK;
}

ERCD RTC_SetTime(RTCTime Time)
{
	//setregbits(PCONP,(~(1 << 9)),1 << 9);  /* power on  the rtc*/
	setregbits(RTC_CCR,(~(1<<1)),(1<<1));/*ctc reset*/
	RTC_SEC = Time.RTC_Sec;
    RTC_MIN = Time.RTC_Min;
    RTC_HOUR = Time.RTC_Hour;
    RTC_DOM = Time.RTC_Mday;
    RTC_DOW = Time.RTC_Wday;
    RTC_DOY = Time.RTC_Yday;
    RTC_MONTH = Time.RTC_Mon;
    RTC_YEAR = Time.RTC_Year;
    setregbits(RTC_CCR,(~(1<<1)),(0<<0));/*ctc reset*/
    //setregbits(PCONP,(~(1 << 9)),0 << 9);  /* use battery to power the rtc*/
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
    uint32_t ctime0,ctime1,ctime2;
    ctime0 = RTC_CTIME0;
    ctime1 = RTC_CTIME1;
    ctime2 = RTC_CTIME2;
//    LocalTime.RTC_Sec = ctime0&63;
//    LocalTime.RTC_Min = (ctime0>>8)&63;
//    LocalTime.RTC_Hour = (ctime0>>16)&23;
//    LocalTime.RTC_Mday = (ctime1>>0)&31;
//    LocalTime.RTC_Wday = (ctime0>>24)&6;
//    LocalTime.RTC_Yday = (ctime2>>0)&366;
//    LocalTime.RTC_Mon = (ctime1>>8)&12;
//    LocalTime.RTC_Year = (ctime1>>16)&4095;
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

