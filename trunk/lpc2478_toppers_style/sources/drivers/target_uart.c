/**
 * @file   lpc2478_uart.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:05:54 2011
 * 
 * @brief  lpc2478 uart module
 * 
 * 
 */

/**
 * file includes
 */
#include "target_uart.h"

/*
**************************************************************************************************************
*                                         INITIALIZE UART
*
* Description: This function initializes UART port, setup pin select, clock, parity, stopbits, FIFO etc
*
* Arguments  : baud_rate    UART baud rate (115200)
*
* Returns    : None
*
**************************************************************************************************************
*/

void  UART_Init(uint32_t baudrate)
{
    uint32_t  Fdiv;
          
	#if UART_PORT == 1  /* UART1 init */
		/* Power on UART1    */
		sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) | 0x00000010);
		/* Periphral clock init
		 * UART1 clk = CCLK */
		sil_wrw_mem((void *)PCLKSEL0, sil_rew_mem((void *)PCLKSEL0) & 0xFFFFFCFF);
		sil_wrw_mem((void *)PCLKSEL0, sil_rew_mem((void *)PCLKSEL0) | 0x00000100);
		/* P0.15 TXD1, P0.16 RXD1     */
		sil_wrw_mem((void *)PINSEL0, sil_rew_mem((void *)PINSEL0) & 0x3FFFFFFF);
		sil_wrw_mem((void *)PINSEL0, sil_rew_mem((void *)PINSEL0) | 0x40000000);
		sil_wrw_mem((void *)PINSEL1, sil_rew_mem((void *)PINSEL1) & 0xFFFFFFFC);
		sil_wrw_mem((void *)PINSEL1, sil_rew_mem((void *)PINSEL1) | 0x00000001);
		/*  UART receive pins should not have pull-down resistors enabled */
		sil_wrw_mem((void *)PINMODE0, sil_rew_mem((void *)PINMODE0) & 0xFFFFFCFF);
		sil_wrw_mem((void *)PINMODE1, sil_rew_mem((void *)PINMODE1) & 0xFFFFFFFC);
		/* 8 bits, no Parity, 1 Stop bit   DLAB =1 */
		sil_wrw_mem((void *)U1LCR, 0x83);
		/*baud rate set*/
		Fdiv = (Fp_uartclk / 16) / baudrate ;
		sil_wrw_mem((void *)U1DLM, (Fdiv >> 8) & 0xff);
		sil_wrw_mem((void *)U1DLL, Fdiv & 0xff);
		/* DLAB = 0*/
		sil_wrw_mem((void *)U1LCR, 0x03);
		/* Enable and reset TX and RX FIFO*/
		sil_wrw_mem((void *)U1FCR, 0x07);
	#elif UART_PORT == 0   /* UART2 init */
		/* Power on UART0    */
		sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP)|(1<<3));
		/* Periphral clock init
		 * UART0 clk = CCLK*/
		sil_wrw_mem((void *)PCLKSEL0, sil_rew_mem((void *)PCLKSEL0)&(0xFFFFFF3F));
		sil_wrw_mem((void *)PCLKSEL0, sil_rew_mem((void *)PCLKSEL0)|(0x00000040));
		/* P0.2 TXD0, P0.3 RXD0*/
		sil_wrw_mem((void *)PINSEL0, sil_rew_mem((void *)PINSEL0)&(0xFFFFFF0F));
		sil_wrw_mem((void *)PINSEL0, sil_rew_mem((void *)PINSEL0)|(0x00000050));
		/*  UART receive pins should not have pull-down resistors enabled */
		sil_wrw_mem((void *)PINMODE0, sil_rew_mem((void *)PINMODE0)&(0xFFFFFF0F));
		/* 8 bits, no Parity, 1 Stop bit   DLAB =1 */
		sil_wrw_mem((void *)U0LCR,0x83);
		/* baud rate  set*/
        Fdiv  = ( Fp_uartclk / 16 ) / baudrate ;
        sil_wrw_mem((void *)U0DLM, (Fdiv >> 8) & 0xff);
        sil_wrw_mem((void *)U0DLL, Fdiv & 0xff);
		/* DLAB = 0  */
        sil_wrw_mem((void *)U0LCR, 0x03);
        /* Enable and reset TX and RX FIFO  */
        sil_wrw_mem((void *)U0FCR, 0x07);
	#endif
}

/*
**************************************************************************************************************
*                                         PRINT CHARECTER
*
* Description: This function is used to print a single charecter through UART1.
*
* Arguments  : ch    charecter to be printed
*
* Returns    : None
*
**************************************************************************************************************
*/

void  UART_PrintChar (uint8_t ch)
{
	#if  UART_PORT == 1
		while (!(sil_rew_mem((void *)U1LSR) & 0x20));  /* wait until U1THR is empty.*/
		sil_wrw_mem((void *)U1THR, ch);
	#elif UART_PORT == 0
		while (!(sil_rew_mem((void *)U0LSR) & 0x20));  /* wait until U1THR is empty.*/
		sil_wrw_mem((void *)U0THR, ch);
	#endif

}

/*
**************************************************************************************************************
*                                         PRINT STRING
*
* Description: This function is used to print a string
*
* Arguments  : str    Pointer to the string
*
* Returns    : None
*
**************************************************************************************************************
*/

void  UART_PrintStr (uint8_t *str)
{

   while ((*str) != 0) {
      if (*str == '\n') {
         UART_PrintChar(*str++);
         UART_PrintChar('\r');
      } else {
         UART_PrintChar(*str++);
      }    
   }
}

/*
**************************************************************************************************************
*                                        PRINT FORMATTED STRING
*
* Description: This function is used to print formatted string. This function takes variable length arguments
*
* Arguments  : variable length arguments
*
* Returns    : None
*
**************************************************************************************************************
*/

void  UART_Printf (uint8_t *format, ...)
{
    static char  buffer[40 + 1];
    va_list     vArgs;


    va_start(vArgs, format);
    vsprintf((char *)buffer, (const char *)format, vArgs);
    va_end(vArgs);
    UART_PrintStr((uint8_t*) buffer);
}
