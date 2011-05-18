/**
 * =====================================================================================
 * 
 * @Filename  :lpc2478_timer.c
 * @Version   : 0.1
 * @Author    :fanghuaqi <578567190@qq.com>
 * @Date      :Sat May 14 20:41:47 2011
 * 
 * @Brief     :timer init as capture or output 
 * 
 * 
 * @Company   :HUST-Renesas Lab
 * @Revision  :
 * ======================================================================================
 * @0.1 Byfanghuaqi  Sat May 14 20:41:47 2011 Create orignal file
 * ======================================================================================
 */

#include "lpc2478_timer.h"

void timer2_capinit(void)
{
	sil_wrw_mem(PCONP,sil_rew_mem(PCONP)|(1<<22));/*power on timer2*/
	sil_wrw_mem(PCLKSEL1,(PCLKSEL1&(~(0x3<<12)))|(0x1<<12));/*pclk of timer is cclk*/
	sil_wrw_mem(PINSEL0,sil_rew_mem(PINSEL0)|(0x3<<8)); /*p0.4 as cap2*/
	sil_wrw_mem(T2PR,0);                      /*prescale counter is 0*/
    sil_wrw_mem(T2IR,0xff);                   /*reset the interrupts*/
    sil_wrw_mem(T2TCR,0x02);                   /*disable and reset counter*/
    sil_wrw_mem(T2CTCR,0x00);                 /*timer mode,capture on rising edge CAP2.0 for TIMER2*/
    sil_wrw_mem(T2MCR,0x00);                  /*disable match control*/
    sil_wrw_mem(T2CCR,0x05);                  /*capture rising and falling edge cr0 load TC and generate interrupt*/
    sil_wrw_mem(T2TCR,0x01);                   /*start counter*/
}
uint32_t read_timer2cap(void)
{
    return (T2CR0);
}
