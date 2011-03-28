/**
 * @file   lpc2478_hw.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:15:46 2011
 * 
 * @brief  lpc2478 hardware such as led ,buzzers
 * 
 * 
 */

#include  "lpc2478_hw.h"

void LED_Init(void)
{
	/* P3[20] - p3[27] =>LEDS*/
	PINSEL7 &= 0xff0000ff; /*select P320-P327 as GPIOs*/
	PINSEL7 |= 0x00000000;

	PINMODE7 &= 0xff0000ff;/*select P320 - P327  pull_up*/
	PINMODE7 |= 0x00000000;

	FIO3DIR2 |= 0xf0; /* P320-P327 as output */
	FIO3DIR3 |= 0x0f;
}
void LED_Output(uint8_t ledvalue)
{
	FIO3SET2 = (0xf0 & (ledvalue<<4));
	FIO3SET3 = (0x0f & (ledvalue>>4));

	FIO3CLR2 = (0xf0 & ((~ledvalue)<<4));
	FIO3CLR3 = (0x0f & ((~ledvalue)>>4));
}
void Delay_ms(uint32_t ms)
{
	volatile uint32_t i,j,k;
	for(i=0;i<50;i++)
	{
		for(j=0;j<100;j++)
		{
			for(k=0;k<ms;k++);
		}
	}
}

