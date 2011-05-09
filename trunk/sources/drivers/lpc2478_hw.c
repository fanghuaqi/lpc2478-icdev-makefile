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
void Buzzer_Init(void)
{
	SCS |= 0x00000001;	/* set GPIOx to use Fast I/O */
	setregbits(PINSEL4,~(0x3<<0),(0x0<<0));   /*p2.0 as gpio*/
	setregbits(PINMODE4,~(0x3<<0),(0x3<<0));  /*p2.0 pull up*/
	setregbits(FIO2DIR0,~(0x1<<0),(0x1<<0));  /*p2.0 output*/
	PINSEL10 = 0x00;   //ETM interface is disabled. must set this
	//	setregbits(FIO2DIRL,~(0x1<<0),(0x1<<0));  /*p2.0 output*/
//	setregbits(FIO2DIR,~(0x1<<0),(0x1<<0));  /*p2.0 output*/
//	    setregbits(PINSEL7,~(0x30<<0),(0x0<<0));   /*p2.0 as gpio*/
//		setregbits(PINMODE7,~(0x30<<0),(0x0<<0));  /*p2.0 pull up*/
//		setregbits(FIO3DIR2,~(0x1<<2),(0x1<<2));  /*p2.0 output*/
		//setregbits(FIO2DIRL,~(0x1<<0),(0x1<<0));  /*p2.0 output*/
		//setregbits(FIO3DIR,~(0x1<<0),(0x1<<0));  /*p2.0 output*/
	//PINSEL4 = 0;
}
void PWM_Init()
{
	setregbits(PCONP,MASK_ALL,3 << 5);
	setregbits(PCLKSEL0,~(0x0f<<10),(0x05<<10));
	setregbits(PINSEL4,~(0x3<<0),(0x1<<0));
	setregbits(PINMODE4,~(0x3<<0),(0x0<<0));
}
void Buzzer(uint8_t buzzer)
{
	if (buzzer == 1){
//		setregbits(FIO2PIN0,~(0x1<<0),(0x1<<0));   /*p2.0 high*/
//		setregbits(FIO2PIN,~(0x1<<0),(0x1<<0));   /*p2.0 high*/
		setregbits(FIO2SET0,~(0x1<<0),(0x1<<0));   /*p2.0 high*/
//		setregbits(FIO2SET,~(0x1<<0),(0x1<<0));   /*p2.0 high*/
//		setregbits(FIO2PINL,~(0x1<<0),(0x1<<0));   /*p2.0 high*/
//		setregbits(FIO2PIN,~(0x1<<0),(0x1<<0));   /*p2.0 high*/
//			setregbits(FIO3SET2,~(0x1<<2),(0x1<<2));   /*p2.0 high*/
	}else {
//			setregbits(FIO3CLR2,~(0x1<<2),(0x1<<2));   /*p2.0 low*/
//		setregbits(FIO2PIN0,~(0x1<<0),(0x0<<0));   /*p2.0 low*/
//		setregbits(FIO2PIN,~(0x1<<0),(0x0<<0));   /*p2.0 low*/
		setregbits(FIO2CLR0,~(0x1<<0),(0x1<<0));   /*p2.0 low*/
//		setregbits(FIO2CLR,~(0x1<<0),(0x1<<0));   /*p2.0 low*/
//		setregbits(FIO2PINL,~(0x1<<0),(0x0<<0));   /*p2.0 low*/
//		setregbits(FIO2PIN,~(0x1<<0),(0x0<<0));   /*p2.0 low*/
	}


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
		for(j=0;j<33;j++)
		{
			for(k=0;k<ms;k++);
		}
	}
}

