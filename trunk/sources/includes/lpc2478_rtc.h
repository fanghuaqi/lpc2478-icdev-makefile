/**
 * =====================================================================================
 *
 * @Filename  :lpc2478_rtc.h
 * @Version   : 0.1
 * @Author    :fanghuaqi <578567190@qq.com>
 * @Date      :Tue May 10 14:23:33 2011
 *
 * @Brief     :
 *
 *
 * @Company   :HUST-Renesas Lab
 * @Revision  :
 * ======================================================================================
 * @0.1 Byfanghuaqi  Tue May 10 14:23:34 2011 Create orignal file
 * ======================================================================================
 */
#ifndef _LPC2478_RTC_H
#define _LPC2478_RTC_H

#include "lpc2478_inc.h"

typedef struct {
    uint16_t RTC_Sec;     /* Second value - [0,59] */
    uint16_t RTC_Min;     /* Minute value - [0,59] */
    uint16_t RTC_Hour;    /* Hour value - [0,23] */
    uint16_t RTC_Mday;    /* Day of the month value - [1,31] */
    uint16_t RTC_Mon;     /* Month value - [1,12] */
    uint16_t RTC_Year;    /* Year value - [0,4095] */
    uint16_t RTC_Wday;    /* Day of week value - [0,6] */
    uint16_t RTC_Yday;    /* Day of year value - [1,365] */
} RTCTime;

/* rtc function marco */
#define RTC_SET_ALARM_MASK(AlarmMask)           RTC_AMR = (AlarmMask)
#define RTC_CTCRST()                            setregbits(RTC_CCR,(~(1<<1)),(1<<1))

#define IMSEC		0x00000001
#define IMMIN		0x00000002
#define IMHOUR		0x00000004
#define IMDOM		0x00000008
#define IMDOW		0x00000010
#define IMDOY		0x00000020
#define IMMON		0x00000040
#define IMYEAR		0x00000080

#define AMRSEC		0x00000001  /* Alarm mask for Seconds */
#define AMRMIN		0x00000002  /* Alarm mask for Minutes */
#define AMRHOUR		0x00000004  /* Alarm mask for Hours */
#define AMRDOM		0x00000008  /* Alarm mask for Day of Month */
#define AMRDOW		0x00000010  /* Alarm mask for Day of Week */
#define AMRDOY		0x00000020  /* Alarm mask for Day of Year */
#define AMRMON		0x00000040  /* Alarm mask for Month */
#define AMRYEAR		0x00000080  /* Alarm mask for Year */

#define PREINT_RTC	0x000001C8  /* Prescaler value, integer portion,
				    PCLK = 15Mhz */
#define PREFRAC_RTC	0x000061C0  /* Prescaler value, fraction portion,
				    PCLK = 15Mhz */
#define ILR_RTCCIF	0x01
#define ILR_RTCALF	0x02

#define CCR_CLKEN	0x01
#define CCR_CTCRST	0x02
#define CCR_CLKSRC	0x10

ERCD RTC_Init(void);
ERCD RTC_Start(void);
ERCD RTC_Stop(void);
ERCD RTC_SetTime(RTCTime Time);
ERCD RTC_SetAlarm(RTCTime Alarm);
RTCTime RTC_GetTime(void);

#endif
