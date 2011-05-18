/*
 * lpc2478_irq.h
 *
 *  Created on: 2011-4-5
 *      Author: fanghuaqi
 */

#ifndef TARGET_IRQ_H_
#define TARGET_IRQ_H_

#include	"lpc2478_inc.h"

#define VECT_ADDR_INDEX	0x100
#define VECT_PRIO_INDEX 0x200

#define	WDT_INT			0
#define SWI_INT			1
#define ARM_CORE0_INT	2
#define	ARM_CORE1_INT	3
#define	TIMER0_INT		4
#define TIMER1_INT		5
#define UART0_INT		6
#define	UART1_INT		7
#define	PWM0_1_INT		8
#define I2C0_INT		9
#define SPI0_INT		10			/* SPI and SSP0 share VIC slot */
#define SSP0_INT		10
#define	SSP1_INT		11
#define	PLL_INT			12
#define RTC_INT			13
#define EINT0_INT		14
#define EINT1_INT		15
#define EINT2_INT		16
#define EINT3_INT		17
#define	ADC0_INT		18
#define I2C1_INT		19
#define BOD_INT			20
#define EMAC_INT		21
#define USB_INT			22
#define CAN_INT			23
#define MCI_INT			24
#define GPDMA_INT		25
#define TIMER2_INT		26
#define TIMER3_INT		27
#define UART2_INT		28
#define UART3_INT		29
#define I2C2_INT		30
#define I2S_INT			31

#define VIC_SIZE		32

#define FALLING_EDGE 	0
#define RISING_EDGE		1

#define PORT_0			0
#define PORT_2 			2

#define IO_INT_STAT_R_OFFSET  0
#define IO_INT_STAT_F_OFFSET  4
#define IO_INT_CLR_OFFSET     8
#define IO_INT_EN_R_OFFSET    12
#define IO_INT_EN_F_OFFSET    16

#define HIGHEST_PRIORITY	0x01
#define LOWEST_PRIORITY		0x0F


ERCD install_irq( uint16_t IntNumber, void *HandlerAddr, uint16_t Priority );
ERCD EINT3_Init(uint8_t port, uint8_t port_no, uint8_t int_edge);
ERCD EINT0_Init(uint8_t int_edge, uint8_t int_prio);
extern void  EINT0_ISR (void) __attribute__ ((interrupt("IRQ")));

#endif /* LPC2478_IRQ_H_ */
