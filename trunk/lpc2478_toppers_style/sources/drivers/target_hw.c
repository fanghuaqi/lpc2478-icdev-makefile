/**
 * @file   lpc2478_hw.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:15:46 2011
 * 
 * @brief  lpc2478 hardware such as led ,buzzers
 * 
 * 
 */

#include  "target_hw.h"

void LED_Init(void)
{
	sil_wrw_mem((void *)SCS,sil_rew_mem((void *)SCS)|0x00000001);                /*set GPIOx to use Fast I/O */
	/* P3[20] - p3[27] =>LEDS as GPIOs*/
	sil_wrw_mem((void *)PINSEL7,sil_rew_mem((void *)PINSEL7)&0xff0000ff);

	/*select P320 - P327  pull_up*/
	sil_wrw_mem((void *)PINMODE7,sil_rew_mem((void *)PINSEL7)&0xff0000ff);

	/* P320-P327 as output */
	sil_wrw_mem((void *)FIO3DIR2,sil_rew_mem((void *)FIO3DIR2)|0x000000f0);
	sil_wrw_mem((void *)FIO3DIR3,sil_rew_mem((void *)FIO3DIR3)|0x0000000f);
}

void Buzzer_Init(void)
{
	sil_wrw_mem((void *)SCS,sil_rew_mem((void *)SCS)|0x00000001);                /*set GPIOx to use Fast I/O */
	sil_wrw_mem((void *)PINSEL10,0);                                             /*ETM interface is disabled. must set this*/

	sil_wrw_mem((void *)PINSEL4,sil_rew_mem((void *)PINSEL4) & (~(0x3<<2)) );    /*set GPIOx to use Fast I/O */
	sil_wrw_mem((void *)PINMODE4,sil_rew_mem((void *)PINMODE4) & (~(0x3<<2)) );  /*p2.0 pull up*/
	sil_wrw_mem((void *)FIO2DIR0,sil_rew_mem((void *)FIO2DIR0) | (0x1<<1) );     /*p2.0 output*/
}

void Buzzer(uint8_t buzzer)
{
	if (buzzer == BUZZER_ON){
		sil_wrw_mem((void *)FIO2SET0,sil_rew_mem((void *)FIO2SET0) | (0x1<<1) ); /*p2.0 high*/
	}else {
		sil_wrw_mem((void *)FIO2CLR0,sil_rew_mem((void *)FIO2CLR0) | (0x1<<1) ); /*p2.0 low*/
	}
}

void LED_Output(uint8_t ledvalue)
{
	sil_wrw_mem((void *)FIO3SET2,(0xf0 & (ledvalue<<4)));
	sil_wrw_mem((void *)FIO3SET3,(0x0f & (ledvalue>>4)));

	sil_wrw_mem((void *)FIO3CLR2,(0xf0 & ((~ledvalue)<<4)));
	sil_wrw_mem((void *)FIO3CLR3,(0x0f & ((~ledvalue)>>4)));
}

void Delay_ms(uint32_t ms)
{
	volatile uint32_t i,j,k;
	for(i=0;i<50;i++)
	{
		for(j=0;j<33;j++)
		{
			for(k=0;k<ms;k++);
		}
	}
}

void Delay_us(uint32_t us)
{
	volatile uint32_t i,k;
	for(i=0;i<1;i++)
	{
		for(k=0;k<us;k++);
	}
}
