/*
 * =====================================================================================
 *
 *       Filename:  rtc.h
 *
 *    Description:  
 *
 *        Version:  0.1
 *        Created:  2011-2-16 10:59:46
 *
 *         Author:  Ren Wei , renweihust@gmail.com
 *        Company:  HUST-Renesas Lab
 *       Revision:  
 * =====================================================================================
 *	@0.1 	Ren Wei	2011-2-16	create orignal file
 * =====================================================================================
 */
#ifndef RTC_H
#define	RTC_H
#include <t_stddef.h>
#include <sil.h>

/* Counter Increment Interrupt Register */
#define IMSEC		0x00000001	/* Interrupt mask for Seconds */
#define IMMIN		0x00000002  /* Interrupt mask for Minutes */
#define IMHOUR		0x00000004  /* Interrupt mask for Hours */
#define IMDOM		0x00000008  /* Interrupt mask for Day of month */
#define IMDOW		0x00000010  /* Interrupt mask for Day of week */
#define IMDOY		0x00000020  /* Interrupt mask for Day of year */
#define IMMON		0x00000040  /* Interrupt mask for Month */
#define IMYEAR		0x00000080  /* Interrupt mask for Year */

#define AMRSEC		0x00000001  /* Alarm mask for Seconds */
#define AMRMIN		0x00000002  /* Alarm mask for Minutes */
#define AMRHOUR		0x00000004  /* Alarm mask for Hours */
#define AMRDOM		0x00000008  /* Alarm mask for Day of Month */
#define AMRDOW		0x00000010  /* Alarm mask for Day of Week */
#define AMRDOY		0x00000020  /* Alarm mask for Day of Year */
#define AMRMON		0x00000040  /* Alarm mask for Month */
#define AMRYEAR		0x00000080  /* Alarm mask for Year */


#define ILR_RTCCIF	0x01	/* Enable Counter Increment Interrupt */
#define ILR_RTCALF	0x02	/* Enable Alarm Interrupt */

#define CCR_CLKEN	0x01	/* enable RTC */
#define CCR_CTCRST	0x02	/* enable RST */
#define CCR_CLKSRC	0x10	/* use external XTAL */


#define INHNO_RTC     13      	/* int handler no */
#define INTNO_RTC     13      	/* intno */
#define INTPRI_RTC    -6     	/* RTC int priority */
#define INTATR_RTC    0U     	/* RTC interrupt attribute  */


Inline
void RTCReset(void)
{
	sil_wrw_mem((void *)RTC_CCR, sil_rew_mem((void *)RTC_CCR) | CCR_CTCRST);
}

Inline
void RTCStop(void)
{
	sil_wrw_mem((void *)RTC_CCR, sil_rew_mem((void *)RTC_CCR) & ~CCR_CLKEN);
}


typedef struct {
	uint16_t	year;	/* 1..4095 */
	uint8_t	month;	/* 1..12 */
	uint8_t	mday;	/* 1.. 31 */
	uint8_t	wday;	/* 1..7 */
	uint8_t	hour;	/* 0..23 */
	uint8_t	min;	/* 0..59 */
	uint8_t	sec;	/* 0..59 */
} RTC;

extern void RTCInitialize(intptr_t exinf);			/* Initialize RTC */
extern void RTCGetTime(RTC* rtc);			/* Get time */
extern void RTCSetTime(const RTC* rtc);		/* Set time */
extern void	RTCSetAlarm(const RTC* alarm);	/* set alarm */
extern void RTCSsetAlarmMask(const uint32_t mask);	/* set alarm mask */
extern void RTCIntHandler(void);			/* RTC interrupt handler */

#endif /* RTC_H */
