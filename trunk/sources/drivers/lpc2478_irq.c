/*
 * lpc2478_irq.c
 *
 *  Created on: 2011-4-5
 *      Author: fanghuaqi
 */
#include "lpc2478_irq.h"

void  EINT0_ISR (void) __attribute__ ((interrupt("IRQ")));
/******************************************************************************
** Function name:		install_irq
**
** Descriptions:		Install interrupt handler
** parameters:			Interrupt number, interrupt handler address,
**						interrupt priority
** Returned value:		true or false, return false if IntNum is out of range
**
******************************************************************************/
ERCD install_irq( uint16_t IntNumber, void *HandlerAddr, uint16_t Priority )
{
	uint32_t *vect_addr;
	uint32_t *vect_prio;

    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    if ( IntNumber >= VIC_SIZE )
    {
		return ( ERCD_ARG_ERR );
    }
    else
    {
		/* find first un-assigned VIC address for the handler */
		vect_addr = (uint32_t *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + IntNumber*4);
		vect_prio = (uint32_t *)(VIC_BASE_ADDR + VECT_PRIO_INDEX + IntNumber*4);
		*vect_addr = (uint32_t)HandlerAddr;	/* set interrupt vector */
		*vect_prio = Priority;
		VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
		return ERCD_OK;
    }
}


ERCD EINT3_Init(uint8_t port, uint8_t port_no, uint8_t int_edge)
{
	uint32_t vect_addr_base = 0;

	if ((port != PORT_0) || (port != PORT_2)){
		return ERCD_ARG_ERR;
	}else if (port_no > 31){
		return ERCD_ARG_ERR;
	}else if (int_edge > 1){
		return ERCD_ARG_ERR;
	}

	if (port == PORT_0){
		vect_addr_base = GPIO_BASE_ADDR + 0x84;
	}else{
		vect_addr_base = GPIO_BASE_ADDR + 0xA4;
	}

	setregbit(vect_addr_base+IO_INT_CLR_OFFSET,~(1<<port_no),(1<<port_no));
	if (int_edge == FALLING_EDGE){
		setregbit(vect_addr_base+IO_INT_EN_F_OFFSET,~(1<<port_no),(1<<port_no));
	}else{
		setregbit(vect_addr_base+IO_INT_EN_F_OFFSET,~(1<<port_no),(1<<port_no));
	}
	IO0_INT_EN_R = (1<<port_no);
	return ERCD_OK;
}

ERCD EINT0_Init(uint8_t int_edge, uint8_t int_prio)
{
	if (int_edge > 1){
		return ERCD_ARG_ERR;
	}
	setregbits(PINSEL4,~(3<<20),(1<<20)) 				/* set P2.10 as EINT0*/
	setregbits(IO2_INT_EN_R,~(1<<10),(int_edge<<10));				/*Port2.10 is falling edge*/
	setregbits(EXTMODE,~(1<<0),1<<0);					/*EINT0 is edge sensitive.*/
	setregbits(EXTPOLAR,~(1<<0),int_edge<<0);					/*falling edge sensitive.*/
	install_irq(EINT0_INT,(void *)EINT0_ISR,int_prio);	/*install eint0 interrupt as the highest priority*/
	return ERCD_OK;
}

void EINT0_ISR()
{
	uint32_t ext3_int_status = 0;

	EXTINT =1;
	gl_CH452_key = I2C_Master_ReadByte(I2C_CHL0, I2C0_ADDR|(CH452_GET_KEY>>7)); /*读按键代码*/

	if (IO_INT_STAT & 0x01){ /*PORT 0 interrupt flag clear*/
		ext3_int_status = IO0_INT_STAT_R|IO0_INT_STAT_F;
		IO0_INT_CLR = ext3_int_status;
	}
	if (IO_INT_STAT & 0x04){/*PORT 2 interrupt flag clear*/
		ext3_int_status = IO2_INT_STAT_R|IO2_INT_STAT_F;
		IO2_INT_CLR = ext3_int_status;
	}
	/*Acknowledge Interrupt*/
	sil_wrw_mem((void *)VICVectAddr, 0);
}
