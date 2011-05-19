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

#include "target_timer.h"

void timer2_capinit(void)
{
	/*power on timer2*/
	sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP)|(1<<22));
	/*pclk of timer is cclk*/
	sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1)&(~(0x3<<12)));
	sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1)|(0x1<<12));
	/*p0.4 as cap2*/
	sil_wrw_mem((void *)PINSEL0,sil_rew_mem((void *)PINSEL0)|(0x3<<8));
	/*prescale counter is 0*/
	sil_wrw_mem((void *)T2PR,0x0);
	/*reset the interrupts*/
    sil_wrw_mem((void *)T2IR,0xff);
    /*disable and reset counter*/
    sil_wrw_mem((void *)T2TCR,0x02);
    /*timer mode,capture on rising edge CAP2.0 for TIMER2*/
    sil_wrw_mem((void *)T2CTCR,0x00);
    /*disable match control*/
    sil_wrw_mem((void *)T2MCR,0x00);
    /*capture rising and falling edge cr0 load TC and generate interrupt*/
    sil_wrw_mem((void *)T2CCR,0x05);
    /*start counter*/
    sil_wrw_mem((void *)T2TCR,0x01);
}
uint32_t read_timer2cap(void)
{
    return (sil_rew_mem((void *)T2CR0));
}
