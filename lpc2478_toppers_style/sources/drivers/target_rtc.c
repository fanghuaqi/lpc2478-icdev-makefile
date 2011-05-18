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

#include "target_rtc.h"

ERCD RTC_Init(void)
{
	/*power on  the rtc*/
	sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP)|(1<<9));
	/*don't compare seconds*/
	sil_wrw_mem((void *)RTC_AMR, 0x01);
	sil_wrw_mem((void *)RTC_CIIR, 0x0);
	sil_wrw_mem((void *)RTC_CISS, 0x0);
	/*RTC clock source select as RTC*/
	sil_wrw_mem((void *)RTC_CCR, 0x10);

    return ERCD_OK;
}
ERCD RTC_Start(void)
{
	/*clear the interrupt bits must do this to let the alarm pin to be low*/
	sil_wrw_mem((void *)RTC_ILR, 0x7);
	/*enable rtc clock*/
	sil_wrw_mem((void *)RTC_CCR, 0x11);

    return ERCD_OK;
}
ERCD RTC_Stop(void)
{
	/*disable rtc clock*/
	sil_wrw_mem((void *)RTC_CCR,sil_rew_mem((void *)PCONP)&(~(1<<0)));

	return ERCD_OK;
}

ERCD RTC_SetTime(RTCTime Time)
{
	/*ctc reset*/
	sil_wrw_mem((void *)RTC_CCR,sil_rew_mem((void *)RTC_CCR)|(1<<1));
	/*RTC current time set*/
	sil_wrw_mem((void *)RTC_SEC, Time.RTC_Sec);
	sil_wrw_mem((void *)RTC_MIN, Time.RTC_Min);
	sil_wrw_mem((void *)RTC_HOUR, Time.RTC_Hour);
	sil_wrw_mem((void *)RTC_DOM, Time.RTC_Mday);
	sil_wrw_mem((void *)RTC_DOW, Time.RTC_Wday);
	sil_wrw_mem((void *)RTC_DOY, Time.RTC_Yday);
	sil_wrw_mem((void *)RTC_MONTH, Time.RTC_Mon);
	sil_wrw_mem((void *)RTC_YEAR, Time.RTC_Year);
    /*ctc start*/
    sil_wrw_mem((void *)RTC_CCR,sil_rew_mem((void *)RTC_CCR)&(~(1<<1)));

    return ERCD_OK;
}

ERCD RTC_SetAlarm(RTCTime Alarm)
{
	/*RTC alarm time set*/
	sil_wrw_mem((void *)RTC_ALSEC, Alarm.RTC_Sec);
	sil_wrw_mem((void *)RTC_ALMIN, Alarm.RTC_Min);
	sil_wrw_mem((void *)RTC_ALHOUR, Alarm.RTC_Hour);
	sil_wrw_mem((void *)RTC_ALDOM, Alarm.RTC_Mday);
	sil_wrw_mem((void *)RTC_ALDOW, Alarm.RTC_Wday);
	sil_wrw_mem((void *)RTC_ALDOY, Alarm.RTC_Yday);
	sil_wrw_mem((void *)RTC_ALMON, Alarm.RTC_Mon);
	sil_wrw_mem((void *)RTC_ALYEAR, Alarm.RTC_Year);

    return ERCD_OK;
}

RTCTime RTC_GetTime(void)
{
    RTCTime LocalTime;
    uint32_t ctime0,ctime1,ctime2;

    ctime0 = sil_rew_mem((void *)RTC_CTIME0);
    ctime1 = sil_rew_mem((void *)RTC_CTIME1);
    ctime2 = sil_rew_mem((void *)RTC_CTIME2);
//    LocalTime.RTC_Sec = ctime0&63;
//    LocalTime.RTC_Min = (ctime0>>8)&63;
//    LocalTime.RTC_Hour = (ctime0>>16)&23;
//    LocalTime.RTC_Mday = (ctime1>>0)&31;
//    LocalTime.RTC_Wday = (ctime0>>24)&6;
//    LocalTime.RTC_Yday = (ctime2>>0)&366;
//    LocalTime.RTC_Mon = (ctime1>>8)&12;
//    LocalTime.RTC_Year = (ctime1>>16)&4095;
    LocalTime.RTC_Sec = sil_rew_mem((void *)RTC_SEC);
    LocalTime.RTC_Min = sil_rew_mem((void *)RTC_MIN);
    LocalTime.RTC_Hour = sil_rew_mem((void *)RTC_HOUR);
    LocalTime.RTC_Mday = sil_rew_mem((void *)RTC_DOM);
    LocalTime.RTC_Wday = sil_rew_mem((void *)RTC_DOW);
    LocalTime.RTC_Yday = sil_rew_mem((void *)RTC_DOY);
    LocalTime.RTC_Mon = sil_rew_mem((void *)RTC_MONTH);
    LocalTime.RTC_Year = sil_rew_mem((void *)RTC_YEAR);

    return (LocalTime);    
}

