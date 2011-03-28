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
#include "lpc2478_uart.h"

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
          
	#if UART_PORT == 1
		/* UART1 init */
		PCONP |= 0x00000010; 					  /* Power on UART1    */
		PCLKSEL0 &= 0xFFFFFCFF;                   /* Periphral clock init  */
		PCLKSEL0 |= 0x00000100;                   /* UART1 clk = CCLK*/
		PINSEL0 &= 0x3FFFFFFF;	                  /* P0.15 TXD1, P0.16 RXD1     */
		PINSEL0 |= 0x40000000;
		PINSEL1 &= 0xFFFFFFFC;
		PINSEL1 |= 0x00000001;
		PINMODE0 &= 0xFFFFFCFF;                    /*  UART receive pins should not have pull-down resistors enabled */
		PINMODE0 |= 0x00000000;
		PINMODE1 &= 0xFFFFFFFC;
		PINMODE1 |= 0x00000000;
		U1LCR    = 0x83;		                  /* 8 bits, no Parity, 1 Stop bit   DLAB =1       */
		Fdiv     = ( Fp_uartclk / 16 ) / baudrate ;	  /*baud rate                                                   */
		U1DLM    = (Fdiv >> 8) & 0xff;
		U1DLL    = Fdiv & 0xff;
		U1LCR    = 0x03;		                  /* DLAB = 0                                                   */
		U1FCR    = 0x07;		                  /* Enable and reset TX and RX FIFO  */
	#elif UART_PORT == 0
		/* UART1 init */
        PCONP |= 1<<3; 					  /* Power on UART0    */
        PCLKSEL0 &= 0xFFFFFF3F;                   /* Periphral clock init  */
        PCLKSEL0 |= 0x00000040;                   /* UART0 clk = CCLK*/
        PINSEL0 &= 0xFFFFFF0F;	                  /* P0.2 TXD0, P0.3 RXD0     */
        PINSEL0 |= 0x00000050;
        PINMODE0 &= 0xFFFFFF0F;                    /*  UART receive pins should not have pull-down resistors enabled */
        PINMODE0 |= 0x0000000;
        U0LCR    = 0x83;		                  /* 8 bits, no Parity, 1 Stop bit   DLAB =1       */
        Fdiv     = ( Fp_uartclk / 16 ) / baudrate ;	  /*baud rate                                                   */
        U0DLM    = (Fdiv >> 8) & 0xff;
        U0DLL    = Fdiv & 0xff;
    	U0LCR    = 0x03;		                  /* DLAB = 0                                                   */
        U0FCR    = 0x07;		                  /* Enable and reset TX and RX FIFO  */
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
		while (!(U1LSR & 0x20));  /* wait until U1THR is empty.*/
			U1THR  = ch;
	#elif UART_PORT == 0
		while (!(U0LSR & 0x20));  /* wait until U1THR is empty.*/
			U0THR  = ch;
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
    static uint8_t  buffer[40 + 1];
            va_list     vArgs;


    va_start(vArgs, format);
    vsprintf((int8_t *)buffer, (int8_t const *)format, vArgs);
    va_end(vArgs);
    UART_PrintStr((uint8_t*) buffer);
}
