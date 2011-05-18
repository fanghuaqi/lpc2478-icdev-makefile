/**
 * @file   lpc2478_clk.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:02:55 2011
 * 
 * @brief  lpc2478 clock module initialize
 * 
 * 
 */



/**
 * File include
 */
#include  "target_clk.h"


/** 
 * PLL_Feed
 * 
 */
Inline void PLL_Feed(void)
{
	/* A correct feed sequence must be written to the PLLFEED register
	 * in order for changes to the PLLCON and PLLCFG registers to take effect */
	sil_wrw_mem((void *)PLLFEED,0xAA);
	sil_wrw_mem((void *)PLLFEED,0x55);
}
/** 
 * USBClk_Init
 * 
 */
Inline void USBClk_Init(void)
{
	/*When the PLL is running, the output must be divided
	 * in order to bring the USB clock frequency to 48 MHz with a 50% duty cycle.*/
	sil_wrw_mem((void *)USBCLKCFG,0x05);                 /*PLLClk/6=48Mhz*/
}
/** 
 * PLL_Init
 * 
 */
void PLL_Init(void)
{
	/* Disconnect the PLL with one feed sequence if PLL is already connected.*/
	sil_wrw_mem((void *)PLLCON,0x00);
	/* Disable the PLL with one feed sequence. */
	PLL_Feed();
	/* Change the CPU Clock Divider setting to speed up operation without the PLL */
	sil_wrw_mem((void *)CCLKCFG,0x00);

	/* Setting Multiplier and Divider values*/
	/*Target clock set at max 72MHz refer to cpu feather */
	/*IRC Internal RC oscillator*/
	/* Selects the main oscillator as the PLL clock source.
	 * The precision of the IRC does not allow for use of the USB interface, */
	sil_wrw_mem((void *)CLKSRCSEL,0x01);
	/* Write to the PLLCFG and make it effective with one feed sequence */
	/* M=12 N=1 PLLCLK=288MHz*/
	sil_wrw_mem((void *)PLLCFG,0x0B);
  	PLL_Feed();

  	sil_wrw_mem((void *)PLLCON,0x1);/* Enable the PLL with one feed sequence. */
	PLL_Feed();

	/*here better delay >=500us to wait the PLOCK stable*/
	/*Change the CPU Clock Divider setting for the operation with the PLL.
	 * It's critical to do this before connecting the PLL. */
	sil_wrw_mem((void *)CCLKCFG,0x03);
	USBClk_Init(); /*set the usb clk to 48Mhz*/

	/* Wait for the PLL to lock to set frequency*/
	/* Wait for the PLL to achieve lock by monitoring the PLOCK bit in the PLLSTAT register */
	while(!(sil_rew_mem((void *)PLLSTAT) & 0x04000000)) ;

	sil_wrw_mem((void *)PLLCON,0x03);/*Connect the PLL with one feed sequence.*/
	PLL_Feed();
	while(!(sil_rew_mem((void *)PLLSTAT) & 0x02000000)) ;/*wait until the pll is connected*/

	/*Setting  System Clock block PCLK_SYSCON =0x01 so sclk=cclk*/
	sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1)&0xcfffffff);
	sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1)|0x10000000);
}



