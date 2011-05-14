/**
 * @file   lpc2478_cpu.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:23:05 2011
 *
 * @brief  common definition for lpc2478
 *
 *
 */

#ifndef  LPC2478_CPU_H
#define  LPC2478_CPU_H


#include  "lpc2478_inc.h"
/**
 * type definitions of lpc2478
 *
 */
typedef  unsigned long   uint32_t;
typedef  signed   long   int32_t;
typedef  unsigned int    uint16_t;
typedef  signed   int    int16_t;
typedef  unsigned char   uint8_t;
typedef  signed   char   int8_t;
typedef  unsigned char   ERCD;
#define Inline	static __inline__	/* インライン関数 */
#define  setreg(regaddr,value)  		 {(*(volatile unsigned long *)(regaddr)) = (value);}

#define  setregbits(reg,mask,value) 	 {(reg) = ((reg)&(mask))|(value);}
#define  testequal(regaddr,value) 	 	 ((*(volatile unsigned long *)(regaddr)) == (value))
#define  getreg(regaddr) 	 	 	     ((*(volatile unsigned long *)(regaddr)))
#define  setregbit(regaddr,mask,value)   {getreg(regaddr) = ((getreg(regaddr))&(mask))|(value);}
#define  MASK_ALL						 0xffffffff


Inline uint32_t
sil_rew_mem(void *mem)
{
	uint32_t	data;

	data = *((volatile uint32_t *) mem);
	return(data);
}

Inline void
sil_wrw_mem(void *mem, uint32_t data)
{
	*((volatile uint32_t *) mem) = data;
}
#endif
