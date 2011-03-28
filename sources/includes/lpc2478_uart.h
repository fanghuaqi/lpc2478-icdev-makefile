/**
 * @file   lpc2478_uart.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:37:57 2011
 *
 * @brief  lpc2478 uart
 *
 *
 */


#ifndef LPC2478_UART_H
#define LPC2478_UART_H



#include <stdarg.h>
#include <stdio.h>
#include "lpc2478_inc.h"


#define Fp_uartclk_div 1
#define Fp_uartclk	(Fcclk / Fp_uartclk_div)
#define UART_PORT 0


void  UART_Init  (uint32_t baudrate);
void  UART_PrintChar (uint8_t ch);
void  UART_PrintStr (uint8_t *str);
void  UART_Printf(uint8_t  *format, ...);

#define  PRINT_ENABLE         1

#if PRINT_ENABLE
#define  PRINT_Log(...)       UART_Printf(__VA_ARGS__)
#define  PRINT_Err(rc)        UART_Printf("ERROR: In %s at Line %u - rc = %d\n", __FUNCTION__, __LINE__, rc)

#else
#define  PRINT_Log(...)       do {} while(0)
#define  PRINT_Err(rc)        do {} while(0)

#endif

#endif
