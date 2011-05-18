/*
 * =====================================================================================
 *
 *       Filename:  rtc.c
 *
 *    Description:  rtc driver
 *
 *        Version:  0.1
 *        Created:  2011-2-16 10:50:09
 *
 *         Author:  Ren Wei , renweihust@gmail.com
 *        Company:  HUST-Renesas Lab
 *       Revision:  
 * =====================================================================================
 *	@0.1 	Ren Wei	2011-2-16	create orignal file
 * =====================================================================================
 */

#include <LPC24xx.h>
#include "rtc.h"



/*-----------------------------------------------------------------------------
 *		RTC functions  
 *-----------------------------------------------------------------------------*/

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  RTCInitialize
 *  Description:  initialize the rtc. RTC is powered by battery and
 *  			drived by external XTAL(32.768Khz)
 *	Parameters:
 * 	return value:
 *  Created:  2011-2-16 by Ren Wei
 * =====================================================================================
 */
void RTCInitialize(intptr_t exinf)
{
	/* supply PCLK to rtc  */
	sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) | 0x00000200);
	
	/* start RTC with external XTAL */
	sil_wrw_mem((void *)RTC_CCR, 0x11);
	sil_wrw_mem((void *)RTC_AMR, 0);
	sil_wrw_mem((void *)RTC_CISS, 0);
	sil_wrw_mem((void *)RTC_CIIR, 0);

	/* use battery to power the RTC */
	sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) & 0xFFFFFDFF);

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  RTCGetTime
 *  Description:  read RTC values, get current date & time
 *	Parameters:
 *		rtc		buffer to store read data
 * 	return value:
 *  Created:  2011-2-16 by Ren Wei
 * =====================================================================================
 */
void RTCGetTime(RTC *rtc)
{
	uint32_t d, t;

	t = sil_rew_mem((void *)RTC_CTIME0);
	d = sil_rew_mem((void *)RTC_CTIME1);

	rtc->sec = t & 63;
	rtc->min = (t >> 8) & 63;
	rtc->hour = (t >> 16) & 31;
	rtc->wday = (t >> 24) & 7;
	rtc->mday = d & 31;
	rtc->month = (d >> 8) & 15;
	rtc->year = (d >> 16) & 4095;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  RTCSetTime
 *  Description:  set date & time to rtc
 *	Parameters: rtc
 *			rtc	 the value to be set
 * 	return value:
 *  Created:  2011-2-16 by Ren Wei
 * =====================================================================================
 */
void RTCSetTime(const RTC *rtc)
{

	/* supply PCLK to rtc  */
	sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) | 0x00000200);
	
	/* stop rtc */
	sil_wrw_mem((void *)RTC_CCR, CCR_CLKEN | CCR_CTCRST);

	/* Update RTC registers */
	sil_wrw_mem((void *)RTC_SEC, rtc->sec);
	sil_wrw_mem((void *)RTC_MIN, rtc->min);
	sil_wrw_mem((void *)RTC_HOUR, rtc->hour);
	sil_wrw_mem((void *)RTC_DOW, rtc->wday);
	sil_wrw_mem((void *)RTC_DOM, rtc->mday);
	sil_wrw_mem((void *)RTC_MONTH, rtc->month);
	sil_wrw_mem((void *)RTC_YEAR, rtc->year);

	/* Restart RTC with external XTAL */
	sil_wrw_mem((void *)RTC_CCR, CCR_CLKEN | CCR_CLKSRC);

	/* use battery to power the RTC */
	sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) & 0xFFFFFDFF);

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  RTCSetAlarm
 *  Description:  set alarm to RTC. RTC will compare the current value
 *  			with alarm value. When two values match, the alarm out &
 *  			interrupt will be triggered
 *	Parameters:
 *		alarm	the value to be sed
 * 	return value:
 *  Created:  2011-2-16 by Ren Wei
 * =====================================================================================
 */
void RTCSetAlarm(const RTC *alarm)
{ 
	sil_wrw_mem((void *)RTC_ALSEC, alarm->sec);
	sil_wrw_mem((void *)RTC_ALMIN, alarm->min);
	sil_wrw_mem((void *)RTC_ALHOUR, alarm->hour);
	sil_wrw_mem((void *)RTC_ALDOM, alarm->wday);
	sil_wrw_mem((void *)RTC_ALDOW, alarm->mday);
	sil_wrw_mem((void *)RTC_ALMON, alarm->month);
	sil_wrw_mem((void *)RTC_ALYEAR, alarm->year);
	//sil_wrw_mem((void *)RTC_ILR, sil_rew_mem((void *)RTC_ILR) | ILR_RTCALF);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  RTCSetAlarmMask
 *  Description:  set the mask of alarm
 *	Parameters:
 *			mask 	mask value
 * 	return value:
 *  Created:  2011-2-16 by Ren Wei
 * =====================================================================================
 */
void RTCSetAlarmMask(const uint32_t mask)
{
	sil_wrw_mem((void *)RTC_AMR, mask);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  RTCIntHandler
 *  Description:  
 *	Parameters:
 * 	return value:
 *  Created:  2011-2-16 by Ren Wei
 * =====================================================================================
 */
void RTCIntHandler(void)
{
	/* clear interrupt */
	sil_wrw_mem((void *)RTC_ILR, sil_rew_mem((void *)RTC_ILR));	
}

