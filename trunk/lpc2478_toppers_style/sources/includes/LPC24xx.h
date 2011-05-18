/******************************************************************************
 *   LPC23xx.h:  Header file for NXP LPC23xx/24xx Family Microprocessors
 *   The header file is the super set of all hardware definition of the 
 *   peripherals for the LPC23xx/24xx family microprocessor.
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *   2007.05.17  ver 1.01    several corrections
 *   2007.09.05  ver 1.02    added VICVectPriorityx symbols
 *   2007.09.05  ver 1.03    FIO1PIN1 value corrected
 *   2010.12.28  ver 1.04    modified for TOPPERS Software
 *
******************************************************************************/

#ifndef __LPC24xx_H
#define __LPC24xx_H

/* Vectored Interrupt Controller (VIC) */
#define VIC_BASE_ADDR	0xFFFFF000
#define VICIRQStatus   (VIC_BASE_ADDR + 0x000)
#define VICFIQStatus   (VIC_BASE_ADDR + 0x004)
#define VICRawIntr     (VIC_BASE_ADDR + 0x008)
#define VICIntSelect   (VIC_BASE_ADDR + 0x00C)
#define VICIntEnable   (VIC_BASE_ADDR + 0x010)
#define VICIntEnClr    (VIC_BASE_ADDR + 0x014)
#define VICSoftInt     (VIC_BASE_ADDR + 0x018)
#define VICSoftIntClr   (VIC_BASE_ADDR + 0x01C)
#define VICProtection   (VIC_BASE_ADDR + 0x020)
#define VICSWPrioMask   (VIC_BASE_ADDR + 0x024)

#define VICVectAddr0   (VIC_BASE_ADDR + 0x100)
#define VICVectAddr1   (VIC_BASE_ADDR + 0x104)
#define VICVectAddr2   (VIC_BASE_ADDR + 0x108)
#define VICVectAddr3   (VIC_BASE_ADDR + 0x10C)
#define VICVectAddr4   (VIC_BASE_ADDR + 0x110)
#define VICVectAddr5   (VIC_BASE_ADDR + 0x114)
#define VICVectAddr6   (VIC_BASE_ADDR + 0x118)
#define VICVectAddr7   (VIC_BASE_ADDR + 0x11C)
#define VICVectAddr8   (VIC_BASE_ADDR + 0x120)
#define VICVectAddr9   (VIC_BASE_ADDR + 0x124)
#define VICVectAddr10   (VIC_BASE_ADDR + 0x128)
#define VICVectAddr11   (VIC_BASE_ADDR + 0x12C)
#define VICVectAddr12   (VIC_BASE_ADDR + 0x130)
#define VICVectAddr13   (VIC_BASE_ADDR + 0x134)
#define VICVectAddr14   (VIC_BASE_ADDR + 0x138)
#define VICVectAddr15   (VIC_BASE_ADDR + 0x13C)
#define VICVectAddr16   (VIC_BASE_ADDR + 0x140)
#define VICVectAddr17   (VIC_BASE_ADDR + 0x144)
#define VICVectAddr18   (VIC_BASE_ADDR + 0x148)
#define VICVectAddr19   (VIC_BASE_ADDR + 0x14C)
#define VICVectAddr20   (VIC_BASE_ADDR + 0x150)
#define VICVectAddr21   (VIC_BASE_ADDR + 0x154)
#define VICVectAddr22   (VIC_BASE_ADDR + 0x158)
#define VICVectAddr23   (VIC_BASE_ADDR + 0x15C)
#define VICVectAddr24   (VIC_BASE_ADDR + 0x160)
#define VICVectAddr25   (VIC_BASE_ADDR + 0x164)
#define VICVectAddr26   (VIC_BASE_ADDR + 0x168)
#define VICVectAddr27   (VIC_BASE_ADDR + 0x16C)
#define VICVectAddr28   (VIC_BASE_ADDR + 0x170)
#define VICVectAddr29   (VIC_BASE_ADDR + 0x174)
#define VICVectAddr30   (VIC_BASE_ADDR + 0x178)
#define VICVectAddr31   (VIC_BASE_ADDR + 0x17C)

/* The name convention below is from previous LPC2000 family MCUs, in LPC23xx/24xx,
these registers are known as "VICVectPriority(x)". */
#define VICVectCntl0   (VIC_BASE_ADDR + 0x200)
#define VICVectCntl1   (VIC_BASE_ADDR + 0x204)
#define VICVectCntl2   (VIC_BASE_ADDR + 0x208)
#define VICVectCntl3   (VIC_BASE_ADDR + 0x20C)
#define VICVectCntl4   (VIC_BASE_ADDR + 0x210)
#define VICVectCntl5   (VIC_BASE_ADDR + 0x214)
#define VICVectCntl6   (VIC_BASE_ADDR + 0x218)
#define VICVectCntl7   (VIC_BASE_ADDR + 0x21C)
#define VICVectCntl8   (VIC_BASE_ADDR + 0x220)
#define VICVectCntl9   (VIC_BASE_ADDR + 0x224)
#define VICVectCntl10   (VIC_BASE_ADDR + 0x228)
#define VICVectCntl11   (VIC_BASE_ADDR + 0x22C)
#define VICVectCntl12   (VIC_BASE_ADDR + 0x230)
#define VICVectCntl13   (VIC_BASE_ADDR + 0x234)
#define VICVectCntl14   (VIC_BASE_ADDR + 0x238)
#define VICVectCntl15   (VIC_BASE_ADDR + 0x23C)
#define VICVectCntl16   (VIC_BASE_ADDR + 0x240)
#define VICVectCntl17   (VIC_BASE_ADDR + 0x244)
#define VICVectCntl18   (VIC_BASE_ADDR + 0x248)
#define VICVectCntl19   (VIC_BASE_ADDR + 0x24C)
#define VICVectCntl20   (VIC_BASE_ADDR + 0x250)
#define VICVectCntl21   (VIC_BASE_ADDR + 0x254)
#define VICVectCntl22   (VIC_BASE_ADDR + 0x258)
#define VICVectCntl23   (VIC_BASE_ADDR + 0x25C)
#define VICVectCntl24   (VIC_BASE_ADDR + 0x260)
#define VICVectCntl25   (VIC_BASE_ADDR + 0x264)
#define VICVectCntl26   (VIC_BASE_ADDR + 0x268)
#define VICVectCntl27   (VIC_BASE_ADDR + 0x26C)
#define VICVectCntl28   (VIC_BASE_ADDR + 0x270)
#define VICVectCntl29   (VIC_BASE_ADDR + 0x274)
#define VICVectCntl30   (VIC_BASE_ADDR + 0x278)
#define VICVectCntl31   (VIC_BASE_ADDR + 0x27C)

/* LPC23xx/24xx VICVectPriority(x)". */
#define VICVectPriority0   (VIC_BASE_ADDR + 0x200)
#define VICVectPriority1   (VIC_BASE_ADDR + 0x204)
#define VICVectPriority2   (VIC_BASE_ADDR + 0x208)
#define VICVectPriority3   (VIC_BASE_ADDR + 0x20C)
#define VICVectPriority4   (VIC_BASE_ADDR + 0x210)
#define VICVectPriority5   (VIC_BASE_ADDR + 0x214)
#define VICVectPriority6   (VIC_BASE_ADDR + 0x218)
#define VICVectPriority7   (VIC_BASE_ADDR + 0x21C)
#define VICVectPriority8   (VIC_BASE_ADDR + 0x220)
#define VICVectPriority9   (VIC_BASE_ADDR + 0x224)
#define VICVectPriority10   (VIC_BASE_ADDR + 0x228)
#define VICVectPriority11   (VIC_BASE_ADDR + 0x22C)
#define VICVectPriority12   (VIC_BASE_ADDR + 0x230)
#define VICVectPriority13   (VIC_BASE_ADDR + 0x234)
#define VICVectPriority14   (VIC_BASE_ADDR + 0x238)
#define VICVectPriority15   (VIC_BASE_ADDR + 0x23C)
#define VICVectPriority16   (VIC_BASE_ADDR + 0x240)
#define VICVectPriority17   (VIC_BASE_ADDR + 0x244)
#define VICVectPriority18   (VIC_BASE_ADDR + 0x248)
#define VICVectPriority19   (VIC_BASE_ADDR + 0x24C)
#define VICVectPriority20   (VIC_BASE_ADDR + 0x250)
#define VICVectPriority21   (VIC_BASE_ADDR + 0x254)
#define VICVectPriority22   (VIC_BASE_ADDR + 0x258)
#define VICVectPriority23   (VIC_BASE_ADDR + 0x25C)
#define VICVectPriority24   (VIC_BASE_ADDR + 0x260)
#define VICVectPriority25   (VIC_BASE_ADDR + 0x264)
#define VICVectPriority26   (VIC_BASE_ADDR + 0x268)
#define VICVectPriority27   (VIC_BASE_ADDR + 0x26C)
#define VICVectPriority28   (VIC_BASE_ADDR + 0x270)
#define VICVectPriority29   (VIC_BASE_ADDR + 0x274)
#define VICVectPriority30   (VIC_BASE_ADDR + 0x278)
#define VICVectPriority31   (VIC_BASE_ADDR + 0x27C)

#define VICVectAddr    (VIC_BASE_ADDR + 0xF00)


/* Pin Connect Block */
#define PINSEL_BASE_ADDR	0xE002C000
#define PINSEL0        (PINSEL_BASE_ADDR + 0x00)
#define PINSEL1        (PINSEL_BASE_ADDR + 0x04)
#define PINSEL2        (PINSEL_BASE_ADDR + 0x08)
#define PINSEL3        (PINSEL_BASE_ADDR + 0x0C)
#define PINSEL4        (PINSEL_BASE_ADDR + 0x10)
#define PINSEL5        (PINSEL_BASE_ADDR + 0x14)
#define PINSEL6        (PINSEL_BASE_ADDR + 0x18)
#define PINSEL7        (PINSEL_BASE_ADDR + 0x1C)
#define PINSEL8        (PINSEL_BASE_ADDR + 0x20)
#define PINSEL9        (PINSEL_BASE_ADDR + 0x24)
#define PINSEL10       (PINSEL_BASE_ADDR + 0x28)
#define PINSEL11       (PINSEL_BASE_ADDR + 0x2c)

#define PINMODE0        (PINSEL_BASE_ADDR + 0x40)
#define PINMODE1        (PINSEL_BASE_ADDR + 0x44)
#define PINMODE2        (PINSEL_BASE_ADDR + 0x48)
#define PINMODE3        (PINSEL_BASE_ADDR + 0x4C)
#define PINMODE4        (PINSEL_BASE_ADDR + 0x50)
#define PINMODE5        (PINSEL_BASE_ADDR + 0x54)
#define PINMODE6        (PINSEL_BASE_ADDR + 0x58)
#define PINMODE7        (PINSEL_BASE_ADDR + 0x5C)
#define PINMODE8        (PINSEL_BASE_ADDR + 0x60)
#define PINMODE9        (PINSEL_BASE_ADDR + 0x64)

/* General Purpose Input/Output (GPIO) */
#define GPIO_BASE_ADDR		0xE0028000
#define IOPIN0         (GPIO_BASE_ADDR + 0x00)
#define IOSET0         (GPIO_BASE_ADDR + 0x04)
#define IODIR0         (GPIO_BASE_ADDR + 0x08)
#define IOCLR0         (GPIO_BASE_ADDR + 0x0C)
#define IOPIN1         (GPIO_BASE_ADDR + 0x10)
#define IOSET1         (GPIO_BASE_ADDR + 0x14)
#define IODIR1         (GPIO_BASE_ADDR + 0x18)
#define IOCLR1         (GPIO_BASE_ADDR + 0x1C)

/* GPIO Interrupt Registers */
#define IO0_INT_EN_R    (GPIO_BASE_ADDR + 0x90) 
#define IO0_INT_EN_F    (GPIO_BASE_ADDR + 0x94)
#define IO0_INT_STAT_R   (GPIO_BASE_ADDR + 0x84)
#define IO0_INT_STAT_F   (GPIO_BASE_ADDR + 0x88)
#define IO0_INT_CLR     (GPIO_BASE_ADDR + 0x8C)

#define IO2_INT_EN_R    (GPIO_BASE_ADDR + 0xB0) 
#define IO2_INT_EN_F    (GPIO_BASE_ADDR + 0xB4)
#define IO2_INT_STAT_R   (GPIO_BASE_ADDR + 0xA4)
#define IO2_INT_STAT_F   (GPIO_BASE_ADDR + 0xA8)
#define IO2_INT_CLR     (GPIO_BASE_ADDR + 0xAC)

#define IO_INT_STAT     (GPIO_BASE_ADDR + 0x80)

#define PARTCFG_BASE_ADDR		0x3FFF8000
#define PARTCFG        (PARTCFG_BASE_ADDR + 0x00) 

/* Fast I/O setup */
#define FIO_BASE_ADDR		0x3FFFC000
#define FIO0DIR        (FIO_BASE_ADDR + 0x00) 
#define FIO0MASK       (FIO_BASE_ADDR + 0x10)
#define FIO0PIN        (FIO_BASE_ADDR + 0x14)
#define FIO0SET        (FIO_BASE_ADDR + 0x18)
#define FIO0CLR        (FIO_BASE_ADDR + 0x1C)

#define FIO1DIR        (FIO_BASE_ADDR + 0x20) 
#define FIO1MASK       (FIO_BASE_ADDR + 0x30)
#define FIO1PIN        (FIO_BASE_ADDR + 0x34)
#define FIO1SET        (FIO_BASE_ADDR + 0x38)
#define FIO1CLR        (FIO_BASE_ADDR + 0x3C)

#define FIO2DIR        (FIO_BASE_ADDR + 0x40) 
#define FIO2MASK       (FIO_BASE_ADDR + 0x50)
#define FIO2PIN        (FIO_BASE_ADDR + 0x54)
#define FIO2SET        (FIO_BASE_ADDR + 0x58)
#define FIO2CLR        (FIO_BASE_ADDR + 0x5C)

#define FIO3DIR        (FIO_BASE_ADDR + 0x60) 
#define FIO3MASK       (FIO_BASE_ADDR + 0x70)
#define FIO3PIN        (FIO_BASE_ADDR + 0x74)
#define FIO3SET        (FIO_BASE_ADDR + 0x78)
#define FIO3CLR        (FIO_BASE_ADDR + 0x7C)

#define FIO4DIR        (FIO_BASE_ADDR + 0x80) 
#define FIO4MASK       (FIO_BASE_ADDR + 0x90)
#define FIO4PIN        (FIO_BASE_ADDR + 0x94)
#define FIO4SET        (FIO_BASE_ADDR + 0x98)
#define FIO4CLR        (FIO_BASE_ADDR + 0x9C)

/* FIOs can be accessed through WORD, HALF-WORD or BYTE. */
#define FIO0DIR0       (FIO_BASE_ADDR + 0x00) 
#define FIO1DIR0       (FIO_BASE_ADDR + 0x20) 
#define FIO2DIR0       (FIO_BASE_ADDR + 0x40) 
#define FIO3DIR0       (FIO_BASE_ADDR + 0x60) 
#define FIO4DIR0       (FIO_BASE_ADDR + 0x80) 

#define FIO0DIR1       (FIO_BASE_ADDR + 0x01) 
#define FIO1DIR1       (FIO_BASE_ADDR + 0x21) 
#define FIO2DIR1       (FIO_BASE_ADDR + 0x41) 
#define FIO3DIR1       (FIO_BASE_ADDR + 0x61) 
#define FIO4DIR1       (FIO_BASE_ADDR + 0x81) 

#define FIO0DIR2       (FIO_BASE_ADDR + 0x02) 
#define FIO1DIR2       (FIO_BASE_ADDR + 0x22) 
#define FIO2DIR2       (FIO_BASE_ADDR + 0x42) 
#define FIO3DIR2       (FIO_BASE_ADDR + 0x62) 
#define FIO4DIR2       (FIO_BASE_ADDR + 0x82) 

#define FIO0DIR3       (FIO_BASE_ADDR + 0x03) 
#define FIO1DIR3       (FIO_BASE_ADDR + 0x23) 
#define FIO2DIR3       (FIO_BASE_ADDR + 0x43) 
#define FIO3DIR3       (FIO_BASE_ADDR + 0x63) 
#define FIO4DIR3       (FIO_BASE_ADDR + 0x83) 

#define FIO0DIRL       (FIO_BASE_ADDR + 0x00) 
#define FIO1DIRL       (FIO_BASE_ADDR + 0x20) 
#define FIO2DIRL       (FIO_BASE_ADDR + 0x40) 
#define FIO3DIRL       (FIO_BASE_ADDR + 0x60) 
#define FIO4DIRL       (FIO_BASE_ADDR + 0x80) 

#define FIO0DIRU       (FIO_BASE_ADDR + 0x02) 
#define FIO1DIRU       (FIO_BASE_ADDR + 0x22) 
#define FIO2DIRU       (FIO_BASE_ADDR + 0x42) 
#define FIO3DIRU       (FIO_BASE_ADDR + 0x62) 
#define FIO4DIRU       (FIO_BASE_ADDR + 0x82) 

#define FIO0MASK0      (FIO_BASE_ADDR + 0x10) 
#define FIO1MASK0      (FIO_BASE_ADDR + 0x30) 
#define FIO2MASK0      (FIO_BASE_ADDR + 0x50) 
#define FIO3MASK0      (FIO_BASE_ADDR + 0x70) 
#define FIO4MASK0      (FIO_BASE_ADDR + 0x90) 

#define FIO0MASK1      (FIO_BASE_ADDR + 0x11) 
#define FIO1MASK1      (FIO_BASE_ADDR + 0x21) 
#define FIO2MASK1      (FIO_BASE_ADDR + 0x51) 
#define FIO3MASK1      (FIO_BASE_ADDR + 0x71) 
#define FIO4MASK1      (FIO_BASE_ADDR + 0x91) 

#define FIO0MASK2      (FIO_BASE_ADDR + 0x12) 
#define FIO1MASK2      (FIO_BASE_ADDR + 0x32) 
#define FIO2MASK2      (FIO_BASE_ADDR + 0x52) 
#define FIO3MASK2      (FIO_BASE_ADDR + 0x72) 
#define FIO4MASK2      (FIO_BASE_ADDR + 0x92) 

#define FIO0MASK3      (FIO_BASE_ADDR + 0x13) 
#define FIO1MASK3      (FIO_BASE_ADDR + 0x33) 
#define FIO2MASK3      (FIO_BASE_ADDR + 0x53) 
#define FIO3MASK3      (FIO_BASE_ADDR + 0x73) 
#define FIO4MASK3      (FIO_BASE_ADDR + 0x93) 

#define FIO0MASKL      (FIO_BASE_ADDR + 0x10) 
#define FIO1MASKL      (FIO_BASE_ADDR + 0x30) 
#define FIO2MASKL      (FIO_BASE_ADDR + 0x50) 
#define FIO3MASKL      (FIO_BASE_ADDR + 0x70) 
#define FIO4MASKL      (FIO_BASE_ADDR + 0x90) 

#define FIO0MASKU      (FIO_BASE_ADDR + 0x12) 
#define FIO1MASKU      (FIO_BASE_ADDR + 0x32) 
#define FIO2MASKU      (FIO_BASE_ADDR + 0x52) 
#define FIO3MASKU      (FIO_BASE_ADDR + 0x72) 
#define FIO4MASKU      (FIO_BASE_ADDR + 0x92) 

#define FIO0PIN0       (FIO_BASE_ADDR + 0x14) 
#define FIO1PIN0       (FIO_BASE_ADDR + 0x34) 
#define FIO2PIN0       (FIO_BASE_ADDR + 0x54) 
#define FIO3PIN0       (FIO_BASE_ADDR + 0x74) 
#define FIO4PIN0       (FIO_BASE_ADDR + 0x94) 

#define FIO0PIN1       (FIO_BASE_ADDR + 0x15) 
#define FIO1PIN1       (FIO_BASE_ADDR + 0x35) 
#define FIO2PIN1       (FIO_BASE_ADDR + 0x55) 
#define FIO3PIN1       (FIO_BASE_ADDR + 0x75) 
#define FIO4PIN1       (FIO_BASE_ADDR + 0x95) 

#define FIO0PIN2       (FIO_BASE_ADDR + 0x16) 
#define FIO1PIN2       (FIO_BASE_ADDR + 0x36) 
#define FIO2PIN2       (FIO_BASE_ADDR + 0x56) 
#define FIO3PIN2       (FIO_BASE_ADDR + 0x76) 
#define FIO4PIN2       (FIO_BASE_ADDR + 0x96) 

#define FIO0PIN3       (FIO_BASE_ADDR + 0x17) 
#define FIO1PIN3       (FIO_BASE_ADDR + 0x37) 
#define FIO2PIN3       (FIO_BASE_ADDR + 0x57) 
#define FIO3PIN3       (FIO_BASE_ADDR + 0x77) 
#define FIO4PIN3       (FIO_BASE_ADDR + 0x97) 

#define FIO0PINL       (FIO_BASE_ADDR + 0x14) 
#define FIO1PINL       (FIO_BASE_ADDR + 0x34) 
#define FIO2PINL       (FIO_BASE_ADDR + 0x54) 
#define FIO3PINL       (FIO_BASE_ADDR + 0x74) 
#define FIO4PINL       (FIO_BASE_ADDR + 0x94) 

#define FIO0PINU       (FIO_BASE_ADDR + 0x16) 
#define FIO1PINU       (FIO_BASE_ADDR + 0x36) 
#define FIO2PINU       (FIO_BASE_ADDR + 0x56) 
#define FIO3PINU       (FIO_BASE_ADDR + 0x76) 
#define FIO4PINU       (FIO_BASE_ADDR + 0x96) 

#define FIO0SET0       (FIO_BASE_ADDR + 0x18) 
#define FIO1SET0       (FIO_BASE_ADDR + 0x38) 
#define FIO2SET0       (FIO_BASE_ADDR + 0x58) 
#define FIO3SET0       (FIO_BASE_ADDR + 0x78) 
#define FIO4SET0       (FIO_BASE_ADDR + 0x98) 

#define FIO0SET1       (FIO_BASE_ADDR + 0x19) 
#define FIO1SET1       (FIO_BASE_ADDR + 0x29) 
#define FIO2SET1       (FIO_BASE_ADDR + 0x59) 
#define FIO3SET1       (FIO_BASE_ADDR + 0x79) 
#define FIO4SET1       (FIO_BASE_ADDR + 0x99) 

#define FIO0SET2       (FIO_BASE_ADDR + 0x1A) 
#define FIO1SET2       (FIO_BASE_ADDR + 0x3A) 
#define FIO2SET2       (FIO_BASE_ADDR + 0x5A) 
#define FIO3SET2       (FIO_BASE_ADDR + 0x7A) 
#define FIO4SET2       (FIO_BASE_ADDR + 0x9A) 

#define FIO0SET3       (FIO_BASE_ADDR + 0x1B) 
#define FIO1SET3       (FIO_BASE_ADDR + 0x3B) 
#define FIO2SET3       (FIO_BASE_ADDR + 0x5B) 
#define FIO3SET3       (FIO_BASE_ADDR + 0x7B) 
#define FIO4SET3       (FIO_BASE_ADDR + 0x9B) 

#define FIO0SETL       (FIO_BASE_ADDR + 0x18) 
#define FIO1SETL       (FIO_BASE_ADDR + 0x38) 
#define FIO2SETL       (FIO_BASE_ADDR + 0x58) 
#define FIO3SETL       (FIO_BASE_ADDR + 0x78) 
#define FIO4SETL       (FIO_BASE_ADDR + 0x98) 

#define FIO0SETU       (FIO_BASE_ADDR + 0x1A) 
#define FIO1SETU       (FIO_BASE_ADDR + 0x3A) 
#define FIO2SETU       (FIO_BASE_ADDR + 0x5A) 
#define FIO3SETU       (FIO_BASE_ADDR + 0x7A) 
#define FIO4SETU       (FIO_BASE_ADDR + 0x9A) 

#define FIO0CLR0       (FIO_BASE_ADDR + 0x1C) 
#define FIO1CLR0       (FIO_BASE_ADDR + 0x3C) 
#define FIO2CLR0       (FIO_BASE_ADDR + 0x5C) 
#define FIO3CLR0       (FIO_BASE_ADDR + 0x7C) 
#define FIO4CLR0       (FIO_BASE_ADDR + 0x9C) 

#define FIO0CLR1       (FIO_BASE_ADDR + 0x1D) 
#define FIO1CLR1       (FIO_BASE_ADDR + 0x2D) 
#define FIO2CLR1       (FIO_BASE_ADDR + 0x5D) 
#define FIO3CLR1       (FIO_BASE_ADDR + 0x7D) 
#define FIO4CLR1       (FIO_BASE_ADDR + 0x9D) 

#define FIO0CLR2       (FIO_BASE_ADDR + 0x1E) 
#define FIO1CLR2       (FIO_BASE_ADDR + 0x3E) 
#define FIO2CLR2       (FIO_BASE_ADDR + 0x5E) 
#define FIO3CLR2       (FIO_BASE_ADDR + 0x7E) 
#define FIO4CLR2       (FIO_BASE_ADDR + 0x9E) 

#define FIO0CLR3       (FIO_BASE_ADDR + 0x1F) 
#define FIO1CLR3       (FIO_BASE_ADDR + 0x3F) 
#define FIO2CLR3       (FIO_BASE_ADDR + 0x5F) 
#define FIO3CLR3       (FIO_BASE_ADDR + 0x7F) 
#define FIO4CLR3       (FIO_BASE_ADDR + 0x9F) 

#define FIO0CLRL       (FIO_BASE_ADDR + 0x1C) 
#define FIO1CLRL       (FIO_BASE_ADDR + 0x3C) 
#define FIO2CLRL       (FIO_BASE_ADDR + 0x5C) 
#define FIO3CLRL       (FIO_BASE_ADDR + 0x7C) 
#define FIO4CLRL       (FIO_BASE_ADDR + 0x9C) 

#define FIO0CLRU       (FIO_BASE_ADDR + 0x1E) 
#define FIO1CLRU       (FIO_BASE_ADDR + 0x3E) 
#define FIO2CLRU       (FIO_BASE_ADDR + 0x5E) 
#define FIO3CLRU       (FIO_BASE_ADDR + 0x7E) 
#define FIO4CLRU       (FIO_BASE_ADDR + 0x9E) 


/* System Control Block(SCB) modules include Memory Accelerator Module,
Phase Locked Loop, VPB divider, Power Control, External Interrupt, 
Reset, and Code Security/Debugging */
#define SCB_BASE_ADDR	0xE01FC000

/* Memory Accelerator Module (MAM) */
#define MAMCR          (SCB_BASE_ADDR + 0x000)
#define MAMTIM         (SCB_BASE_ADDR + 0x004)
#define MEMMAP         (SCB_BASE_ADDR + 0x040)

/* Phase Locked Loop (PLL) */
#define PLLCON         (SCB_BASE_ADDR + 0x080)
#define PLLCFG         (SCB_BASE_ADDR + 0x084)
#define PLLSTAT        (SCB_BASE_ADDR + 0x088)
#define PLLFEED        (SCB_BASE_ADDR + 0x08C)

/* Power Control */
#define PCON           (SCB_BASE_ADDR + 0x0C0)
#define PCONP          (SCB_BASE_ADDR + 0x0C4)

/* Clock Divider */
// #define APBDIV         (SCB_BASE_ADDR + 0x100)
#define CCLKCFG        (SCB_BASE_ADDR + 0x104)
#define USBCLKCFG      (SCB_BASE_ADDR + 0x108)
#define CLKSRCSEL      (SCB_BASE_ADDR + 0x10C)
#define PCLKSEL0       (SCB_BASE_ADDR + 0x1A8)
#define PCLKSEL1       (SCB_BASE_ADDR + 0x1AC)
	
/* External Interrupts */
#define EXTINT         (SCB_BASE_ADDR + 0x140)
#define INTWAKE        (SCB_BASE_ADDR + 0x144)
#define EXTMODE        (SCB_BASE_ADDR + 0x148)
#define EXTPOLAR       (SCB_BASE_ADDR + 0x14C)

/* Reset, reset source identification */
#define RSIR           (SCB_BASE_ADDR + 0x180)

/* RSID, code security protection */
#define CSPR           (SCB_BASE_ADDR + 0x184)

/* AHB configuration */
#define AHBCFG1        (SCB_BASE_ADDR + 0x188)
#define AHBCFG2        (SCB_BASE_ADDR + 0x18C)

/* System Controls and Status */
#define SCS            (SCB_BASE_ADDR + 0x1A0)	

/* MPMC(EMC) registers, note: all the external memory controller(EMC) registers 
are for LPC24xx only. */
#define STATIC_MEM0_BASE		0x80000000
#define STATIC_MEM1_BASE		0x81000000
#define STATIC_MEM2_BASE		0x82000000
#define STATIC_MEM3_BASE		0x83000000

#define DYNAMIC_MEM0_BASE		0xA0000000
#define DYNAMIC_MEM1_BASE		0xB0000000
#define DYNAMIC_MEM2_BASE		0xC0000000
#define DYNAMIC_MEM3_BASE		0xD0000000

/* External Memory Controller (EMC) */
#define EMC_BASE_ADDR		0xFFE08000
#define EMC_CTRL       (EMC_BASE_ADDR + 0x000)
#define EMC_STAT       (EMC_BASE_ADDR + 0x004)
#define EMC_CONFIG     (EMC_BASE_ADDR + 0x008)

/* Dynamic RAM access registers */
#define EMC_DYN_CTRL     (EMC_BASE_ADDR + 0x020)
#define EMC_DYN_RFSH     (EMC_BASE_ADDR + 0x024)
#define EMC_DYN_RD_CFG   (EMC_BASE_ADDR + 0x028)
#define EMC_DYN_RP       (EMC_BASE_ADDR + 0x030)
#define EMC_DYN_RAS      (EMC_BASE_ADDR + 0x034)
#define EMC_DYN_SREX     (EMC_BASE_ADDR + 0x038)
#define EMC_DYN_APR      (EMC_BASE_ADDR + 0x03C)
#define EMC_DYN_DAL      (EMC_BASE_ADDR + 0x040)
#define EMC_DYN_WR       (EMC_BASE_ADDR + 0x044)
#define EMC_DYN_RC       (EMC_BASE_ADDR + 0x048)
#define EMC_DYN_RFC      (EMC_BASE_ADDR + 0x04C)
#define EMC_DYN_XSR      (EMC_BASE_ADDR + 0x050)
#define EMC_DYN_RRD      (EMC_BASE_ADDR + 0x054)
#define EMC_DYN_MRD      (EMC_BASE_ADDR + 0x058)

#define EMC_DYN_CFG0     (EMC_BASE_ADDR + 0x100)
#define EMC_DYN_RASCAS0   (EMC_BASE_ADDR + 0x104)
#define EMC_DYN_CFG1     (EMC_BASE_ADDR + 0x140)
#define EMC_DYN_RASCAS1   (EMC_BASE_ADDR + 0x144)
#define EMC_DYN_CFG2     (EMC_BASE_ADDR + 0x160)
#define EMC_DYN_RASCAS2   (EMC_BASE_ADDR + 0x164)
#define EMC_DYN_CFG3     (EMC_BASE_ADDR + 0x180)
#define EMC_DYN_RASCAS3   (EMC_BASE_ADDR + 0x184)

/* static RAM access registers */
#define EMC_STA_CFG0      (EMC_BASE_ADDR + 0x200)
#define EMC_STA_WAITWEN0   (EMC_BASE_ADDR + 0x204)
#define EMC_STA_WAITOEN0   (EMC_BASE_ADDR + 0x208)
#define EMC_STA_WAITRD0   (EMC_BASE_ADDR + 0x20C)
#define EMC_STA_WAITPAGE0 EMC_BASE_ADDR + 0x210
#define EMC_STA_WAITWR0   (EMC_BASE_ADDR + 0x214)
#define EMC_STA_WAITTURN0 EMC_BASE_ADDR + 0x218

#define EMC_STA_CFG1      (EMC_BASE_ADDR + 0x220)
#define EMC_STA_WAITWEN1   (EMC_BASE_ADDR + 0x224)
#define EMC_STA_WAITOEN1   (EMC_BASE_ADDR + 0x228)
#define EMC_STA_WAITRD1   (EMC_BASE_ADDR + 0x22C)
#define EMC_STA_WAITPAGE1 EMC_BASE_ADDR + 0x230
#define EMC_STA_WAITWR1   (EMC_BASE_ADDR + 0x234)
#define EMC_STA_WAITTURN1 EMC_BASE_ADDR + 0x238

#define EMC_STA_CFG2      (EMC_BASE_ADDR + 0x240)
#define EMC_STA_WAITWEN2   (EMC_BASE_ADDR + 0x244)
#define EMC_STA_WAITOEN2   (EMC_BASE_ADDR + 0x248)
#define EMC_STA_WAITRD2   (EMC_BASE_ADDR + 0x24C)
#define EMC_STA_WAITPAGE2 EMC_BASE_ADDR + 0x250
#define EMC_STA_WAITWR2   (EMC_BASE_ADDR + 0x254)
#define EMC_STA_WAITTURN2 EMC_BASE_ADDR + 0x258

#define EMC_STA_CFG3      (EMC_BASE_ADDR + 0x260)
#define EMC_STA_WAITWEN3   (EMC_BASE_ADDR + 0x264)
#define EMC_STA_WAITOEN3   (EMC_BASE_ADDR + 0x268)
#define EMC_STA_WAITRD3   (EMC_BASE_ADDR + 0x26C)
#define EMC_STA_WAITPAGE3  (EMC_BASE_ADDR + 0x270)
#define EMC_STA_WAITWR3   (EMC_BASE_ADDR + 0x274)
#define EMC_STA_WAITTURN3 (EMC_BASE_ADDR + 0x278)

#define EMC_STA_EXT_WAIT   (EMC_BASE_ADDR + 0x880)

	
/* Timer 0 */
#define TMR0_BASE_ADDR		0xE0004000
#define T0IR           (TMR0_BASE_ADDR + 0x00)
#define T0TCR          (TMR0_BASE_ADDR + 0x04)
#define T0TC           (TMR0_BASE_ADDR + 0x08)
#define T0PR           (TMR0_BASE_ADDR + 0x0C)
#define T0PC           (TMR0_BASE_ADDR + 0x10)
#define T0MCR          (TMR0_BASE_ADDR + 0x14)
#define T0MR0          (TMR0_BASE_ADDR + 0x18)
#define T0MR1          (TMR0_BASE_ADDR + 0x1C)
#define T0MR2          (TMR0_BASE_ADDR + 0x20)
#define T0MR3          (TMR0_BASE_ADDR + 0x24)
#define T0CCR          (TMR0_BASE_ADDR + 0x28)
#define T0CR0          (TMR0_BASE_ADDR + 0x2C)
#define T0CR1          (TMR0_BASE_ADDR + 0x30)
#define T0CR2          (TMR0_BASE_ADDR + 0x34)
#define T0CR3          (TMR0_BASE_ADDR + 0x38)
#define T0EMR          (TMR0_BASE_ADDR + 0x3C)
#define T0CTCR         (TMR0_BASE_ADDR + 0x70)

/* Timer 1 */
#define TMR1_BASE_ADDR		0xE0008000
#define T1IR           (TMR1_BASE_ADDR + 0x00)
#define T1TCR          (TMR1_BASE_ADDR + 0x04)
#define T1TC           (TMR1_BASE_ADDR + 0x08)
#define T1PR           (TMR1_BASE_ADDR + 0x0C)
#define T1PC           (TMR1_BASE_ADDR + 0x10)
#define T1MCR          (TMR1_BASE_ADDR + 0x14)
#define T1MR0          (TMR1_BASE_ADDR + 0x18)
#define T1MR1          (TMR1_BASE_ADDR + 0x1C)
#define T1MR2          (TMR1_BASE_ADDR + 0x20)
#define T1MR3          (TMR1_BASE_ADDR + 0x24)
#define T1CCR          (TMR1_BASE_ADDR + 0x28)
#define T1CR0          (TMR1_BASE_ADDR + 0x2C)
#define T1CR1          (TMR1_BASE_ADDR + 0x30)
#define T1CR2          (TMR1_BASE_ADDR + 0x34)
#define T1CR3          (TMR1_BASE_ADDR + 0x38)
#define T1EMR          (TMR1_BASE_ADDR + 0x3C)
#define T1CTCR         (TMR1_BASE_ADDR + 0x70)

/* Timer 2 */
#define TMR2_BASE_ADDR		0xE0070000
#define T2IR           (TMR2_BASE_ADDR + 0x00)
#define T2TCR          (TMR2_BASE_ADDR + 0x04)
#define T2TC           (TMR2_BASE_ADDR + 0x08)
#define T2PR           (TMR2_BASE_ADDR + 0x0C)
#define T2PC           (TMR2_BASE_ADDR + 0x10)
#define T2MCR          (TMR2_BASE_ADDR + 0x14)
#define T2MR0          (TMR2_BASE_ADDR + 0x18)
#define T2MR1          (TMR2_BASE_ADDR + 0x1C)
#define T2MR2          (TMR2_BASE_ADDR + 0x20)
#define T2MR3          (TMR2_BASE_ADDR + 0x24)
#define T2CCR          (TMR2_BASE_ADDR + 0x28)
#define T2CR0          (TMR2_BASE_ADDR + 0x2C)
#define T2CR1          (TMR2_BASE_ADDR + 0x30)
#define T2CR2          (TMR2_BASE_ADDR + 0x34)
#define T2CR3          (TMR2_BASE_ADDR + 0x38)
#define T2EMR          (TMR2_BASE_ADDR + 0x3C)
#define T2CTCR         (TMR2_BASE_ADDR + 0x70)

/* Timer 3 */
#define TMR3_BASE_ADDR		0xE0074000
#define T3IR           (TMR3_BASE_ADDR + 0x00)
#define T3TCR          (TMR3_BASE_ADDR + 0x04)
#define T3TC           (TMR3_BASE_ADDR + 0x08)
#define T3PR           (TMR3_BASE_ADDR + 0x0C)
#define T3PC           (TMR3_BASE_ADDR + 0x10)
#define T3MCR          (TMR3_BASE_ADDR + 0x14)
#define T3MR0          (TMR3_BASE_ADDR + 0x18)
#define T3MR1          (TMR3_BASE_ADDR + 0x1C)
#define T3MR2          (TMR3_BASE_ADDR + 0x20)
#define T3MR3          (TMR3_BASE_ADDR + 0x24)
#define T3CCR          (TMR3_BASE_ADDR + 0x28)
#define T3CR0          (TMR3_BASE_ADDR + 0x2C)
#define T3CR1          (TMR3_BASE_ADDR + 0x30)
#define T3CR2          (TMR3_BASE_ADDR + 0x34)
#define T3CR3          (TMR3_BASE_ADDR + 0x38)
#define T3EMR          (TMR3_BASE_ADDR + 0x3C)
#define T3CTCR         (TMR3_BASE_ADDR + 0x70)


/* Pulse Width Modulator (PWM) */
#define PWM0_BASE_ADDR		0xE0014000
#define PWM0IR          (PWM0_BASE_ADDR + 0x00)
#define PWM0TCR         (PWM0_BASE_ADDR + 0x04)
#define PWM0TC          (PWM0_BASE_ADDR + 0x08)
#define PWM0PR          (PWM0_BASE_ADDR + 0x0C)
#define PWM0PC          (PWM0_BASE_ADDR + 0x10)
#define PWM0MCR         (PWM0_BASE_ADDR + 0x14)
#define PWM0MR0         (PWM0_BASE_ADDR + 0x18)
#define PWM0MR1         (PWM0_BASE_ADDR + 0x1C)
#define PWM0MR2         (PWM0_BASE_ADDR + 0x20)
#define PWM0MR3         (PWM0_BASE_ADDR + 0x24)
#define PWM0CCR         (PWM0_BASE_ADDR + 0x28)
#define PWM0CR0         (PWM0_BASE_ADDR + 0x2C)
#define PWM0CR1         (PWM0_BASE_ADDR + 0x30)
#define PWM0CR2         (PWM0_BASE_ADDR + 0x34)
#define PWM0CR3         (PWM0_BASE_ADDR + 0x38)
#define PWM0EMR         (PWM0_BASE_ADDR + 0x3C)
#define PWM0MR4         (PWM0_BASE_ADDR + 0x40)
#define PWM0MR5         (PWM0_BASE_ADDR + 0x44)
#define PWM0MR6         (PWM0_BASE_ADDR + 0x48)
#define PWM0PCR         (PWM0_BASE_ADDR + 0x4C)
#define PWM0LER         (PWM0_BASE_ADDR + 0x50)
#define PWM0CTCR        (PWM0_BASE_ADDR + 0x70)

#define PWM1_BASE_ADDR		0xE0018000
#define PWM1IR          (PWM1_BASE_ADDR + 0x00)
#define PWM1TCR         (PWM1_BASE_ADDR + 0x04)
#define PWM1TC          (PWM1_BASE_ADDR + 0x08)
#define PWM1PR          (PWM1_BASE_ADDR + 0x0C)
#define PWM1PC          (PWM1_BASE_ADDR + 0x10)
#define PWM1MCR         (PWM1_BASE_ADDR + 0x14)
#define PWM1MR0         (PWM1_BASE_ADDR + 0x18)
#define PWM1MR1         (PWM1_BASE_ADDR + 0x1C)
#define PWM1MR2         (PWM1_BASE_ADDR + 0x20)
#define PWM1MR3         (PWM1_BASE_ADDR + 0x24)
#define PWM1CCR         (PWM1_BASE_ADDR + 0x28)
#define PWM1CR0         (PWM1_BASE_ADDR + 0x2C)
#define PWM1CR1         (PWM1_BASE_ADDR + 0x30)
#define PWM1CR2         (PWM1_BASE_ADDR + 0x34)
#define PWM1CR3         (PWM1_BASE_ADDR + 0x38)
#define PWM1EMR         (PWM1_BASE_ADDR + 0x3C)
#define PWM1MR4         (PWM1_BASE_ADDR + 0x40)
#define PWM1MR5         (PWM1_BASE_ADDR + 0x44)
#define PWM1MR6         (PWM1_BASE_ADDR + 0x48)
#define PWM1PCR         (PWM1_BASE_ADDR + 0x4C)
#define PWM1LER         (PWM1_BASE_ADDR + 0x50)
#define PWM1CTCR        (PWM1_BASE_ADDR + 0x70)



#define UxRBR          0x00
#define UxTHR          0x00
#define UxDLL          0x00
#define UxDLM          0x04
#define UxIER          0x04
#define UxIIR          0x08
#define UxFCR          0x08
#define UxLCR          0x0C
#define UxLSR          0x14
#define UxSCR          0x1C
#define UxACR          0x20
#define UxICR          0x24
#define UxFDR          0x28
#define UxTER          0x30

/* Universal Asynchronous Receiver Transmitter 0 (UART0) */
#define UART0_BASE_ADDR		0xE000C000
#define U0RBR          (UART0_BASE_ADDR + 0x00)
#define U0THR          (UART0_BASE_ADDR + 0x00)
#define U0DLL          (UART0_BASE_ADDR + 0x00)
#define U0DLM          (UART0_BASE_ADDR + 0x04)
#define U0IER          (UART0_BASE_ADDR + 0x04)
#define U0IIR          (UART0_BASE_ADDR + 0x08)
#define U0FCR          (UART0_BASE_ADDR + 0x08)
#define U0LCR          (UART0_BASE_ADDR + 0x0C)
#define U0LSR          (UART0_BASE_ADDR + 0x14)
#define U0SCR          (UART0_BASE_ADDR + 0x1C)
#define U0ACR          (UART0_BASE_ADDR + 0x20)
#define U0ICR          (UART0_BASE_ADDR + 0x24)
#define U0FDR          (UART0_BASE_ADDR + 0x28)
#define U0TER          (UART0_BASE_ADDR + 0x30)

/* Universal Asynchronous Receiver Transmitter 1 (UART1) */
#define UART1_BASE_ADDR		0xE0010000
#define U1RBR          (UART1_BASE_ADDR + 0x00)
#define U1THR          (UART1_BASE_ADDR + 0x00)
#define U1DLL          (UART1_BASE_ADDR + 0x00)
#define U1DLM          (UART1_BASE_ADDR + 0x04)
#define U1IER          (UART1_BASE_ADDR + 0x04)
#define U1IIR          (UART1_BASE_ADDR + 0x08)
#define U1FCR          (UART1_BASE_ADDR + 0x08)
#define U1LCR          (UART1_BASE_ADDR + 0x0C)
#define U1MCR          (UART1_BASE_ADDR + 0x10)
#define U1LSR          (UART1_BASE_ADDR + 0x14)
#define U1MSR          (UART1_BASE_ADDR + 0x18)
#define U1SCR          (UART1_BASE_ADDR + 0x1C)
#define U1ACR          (UART1_BASE_ADDR + 0x20)
#define U1FDR          (UART1_BASE_ADDR + 0x28)
#define U1TER          (UART1_BASE_ADDR + 0x30)

/* Universal Asynchronous Receiver Transmitter 2 (UART2) */
#define UART2_BASE_ADDR		0xE0078000
#define U2RBR          (UART2_BASE_ADDR + 0x00)
#define U2THR          (UART2_BASE_ADDR + 0x00)
#define U2DLL          (UART2_BASE_ADDR + 0x00)
#define U2DLM          (UART2_BASE_ADDR + 0x04)
#define U2IER          (UART2_BASE_ADDR + 0x04)
#define U2IIR          (UART2_BASE_ADDR + 0x08)
#define U2FCR          (UART2_BASE_ADDR + 0x08)
#define U2LCR          (UART2_BASE_ADDR + 0x0C)
#define U2LSR          (UART2_BASE_ADDR + 0x14)
#define U2SCR          (UART2_BASE_ADDR + 0x1C)
#define U2ACR          (UART2_BASE_ADDR + 0x20)
#define U2ICR          (UART2_BASE_ADDR + 0x24)
#define U2FDR          (UART2_BASE_ADDR + 0x28)
#define U2TER          (UART2_BASE_ADDR + 0x30)

/* Universal Asynchronous Receiver Transmitter 3 (UART3) */
#define UART3_BASE_ADDR		0xE007C000
#define U3RBR          (UART3_BASE_ADDR + 0x00)
#define U3THR          (UART3_BASE_ADDR + 0x00)
#define U3DLL          (UART3_BASE_ADDR + 0x00)
#define U3DLM          (UART3_BASE_ADDR + 0x04)
#define U3IER          (UART3_BASE_ADDR + 0x04)
#define U3IIR          (UART3_BASE_ADDR + 0x08)
#define U3FCR          (UART3_BASE_ADDR + 0x08)
#define U3LCR          (UART3_BASE_ADDR + 0x0C)
#define U3LSR          (UART3_BASE_ADDR + 0x14)
#define U3SCR          (UART3_BASE_ADDR + 0x1C)
#define U3ACR          (UART3_BASE_ADDR + 0x20)
#define U3ICR          (UART3_BASE_ADDR + 0x24)
#define U3FDR          (UART3_BASE_ADDR + 0x28)
#define U3TER          (UART3_BASE_ADDR + 0x30)

/* I2C Interface 0 */
#define I2C0_BASE_ADDR		0xE001C000
#define I20CONSET      (I2C0_BASE_ADDR + 0x00)
#define I20STAT        (I2C0_BASE_ADDR + 0x04)
#define I20DAT         (I2C0_BASE_ADDR + 0x08)
#define I20ADR         (I2C0_BASE_ADDR + 0x0C)
#define I20SCLH        (I2C0_BASE_ADDR + 0x10)
#define I20SCLL        (I2C0_BASE_ADDR + 0x14)
#define I20CONCLR      (I2C0_BASE_ADDR + 0x18)

/* I2C Interface 1 */
#define I2C1_BASE_ADDR		0xE005C000
#define I21CONSET      (I2C1_BASE_ADDR + 0x00)
#define I21STAT        (I2C1_BASE_ADDR + 0x04)
#define I21DAT         (I2C1_BASE_ADDR + 0x08)
#define I21ADR         (I2C1_BASE_ADDR + 0x0C)
#define I21SCLH        (I2C1_BASE_ADDR + 0x10)
#define I21SCLL        (I2C1_BASE_ADDR + 0x14)
#define I21CONCLR      (I2C1_BASE_ADDR + 0x18)

/* I2C Interface 2 */
#define I2C2_BASE_ADDR		0xE0080000
#define I22CONSET      (I2C2_BASE_ADDR + 0x00)
#define I22STAT        (I2C2_BASE_ADDR + 0x04)
#define I22DAT         (I2C2_BASE_ADDR + 0x08)
#define I22ADR         (I2C2_BASE_ADDR + 0x0C)
#define I22SCLH        (I2C2_BASE_ADDR + 0x10)
#define I22SCLL        (I2C2_BASE_ADDR + 0x14)
#define I22CONCLR      (I2C2_BASE_ADDR + 0x18)

/* SPI0 (Serial Peripheral Interface 0) */
#define SPI0_BASE_ADDR		0xE0020000
#define S0SPCR         (SPI0_BASE_ADDR + 0x00)
#define S0SPSR         (SPI0_BASE_ADDR + 0x04)
#define S0SPDR         (SPI0_BASE_ADDR + 0x08)
#define S0SPCCR        (SPI0_BASE_ADDR + 0x0C)
#define S0SPINT        (SPI0_BASE_ADDR + 0x1C)

/* SSP0 Controller */
#define SSP0_BASE_ADDR		0xE0068000
#define SSP0CR0        (SSP0_BASE_ADDR + 0x00)
#define SSP0CR1        (SSP0_BASE_ADDR + 0x04)
#define SSP0DR         (SSP0_BASE_ADDR + 0x08)
#define SSP0SR         (SSP0_BASE_ADDR + 0x0C)
#define SSP0CPSR       (SSP0_BASE_ADDR + 0x10)
#define SSP0IMSC       (SSP0_BASE_ADDR + 0x14)
#define SSP0RIS        (SSP0_BASE_ADDR + 0x18)
#define SSP0MIS        (SSP0_BASE_ADDR + 0x1C)
#define SSP0ICR        (SSP0_BASE_ADDR + 0x20)
#define SSP0DMACR      (SSP0_BASE_ADDR + 0x24)

/* SSP1 Controller */
#define SSP1_BASE_ADDR		0xE0030000
#define SSP1CR0        (SSP1_BASE_ADDR + 0x00)
#define SSP1CR1        (SSP1_BASE_ADDR + 0x04)
#define SSP1DR         (SSP1_BASE_ADDR + 0x08)
#define SSP1SR         (SSP1_BASE_ADDR + 0x0C)
#define SSP1CPSR       (SSP1_BASE_ADDR + 0x10)
#define SSP1IMSC       (SSP1_BASE_ADDR + 0x14)
#define SSP1RIS        (SSP1_BASE_ADDR + 0x18)
#define SSP1MIS        (SSP1_BASE_ADDR + 0x1C)
#define SSP1ICR        (SSP1_BASE_ADDR + 0x20)
#define SSP1DMACR      (SSP1_BASE_ADDR + 0x24)


/* Real Time Clock */
#define RTC_BASE_ADDR		0xE0024000
#define RTC_ILR         (RTC_BASE_ADDR + 0x00)
#define RTC_CTC         (RTC_BASE_ADDR + 0x04)
#define RTC_CCR         (RTC_BASE_ADDR + 0x08)
#define RTC_CIIR        (RTC_BASE_ADDR + 0x0C)
#define RTC_AMR         (RTC_BASE_ADDR + 0x10)
#define RTC_CTIME0      (RTC_BASE_ADDR + 0x14)
#define RTC_CTIME1      (RTC_BASE_ADDR + 0x18)
#define RTC_CTIME2      (RTC_BASE_ADDR + 0x1C)
#define RTC_SEC         (RTC_BASE_ADDR + 0x20)
#define RTC_MIN         (RTC_BASE_ADDR + 0x24)
#define RTC_HOUR        (RTC_BASE_ADDR + 0x28)
#define RTC_DOM         (RTC_BASE_ADDR + 0x2C)
#define RTC_DOW         (RTC_BASE_ADDR + 0x30)
#define RTC_DOY         (RTC_BASE_ADDR + 0x34)
#define RTC_MONTH       (RTC_BASE_ADDR + 0x38)
#define RTC_YEAR        (RTC_BASE_ADDR + 0x3C)
#define RTC_CISS        (RTC_BASE_ADDR + 0x40)
#define RTC_ALSEC       (RTC_BASE_ADDR + 0x60)
#define RTC_ALMIN       (RTC_BASE_ADDR + 0x64)
#define RTC_ALHOUR      (RTC_BASE_ADDR + 0x68)
#define RTC_ALDOM       (RTC_BASE_ADDR + 0x6C)
#define RTC_ALDOW       (RTC_BASE_ADDR + 0x70)
#define RTC_ALDOY       (RTC_BASE_ADDR + 0x74)
#define RTC_ALMON       (RTC_BASE_ADDR + 0x78)
#define RTC_ALYEAR      (RTC_BASE_ADDR + 0x7C)
#define RTC_PREINT      (RTC_BASE_ADDR + 0x80)
#define RTC_PREFRAC     (RTC_BASE_ADDR + 0x84)


/* A/D Converter 0 (AD0) */
#define AD0_BASE_ADDR		0xE0034000
#define AD0CR          (AD0_BASE_ADDR + 0x00)
#define AD0GDR         (AD0_BASE_ADDR + 0x04)
#define AD0INTEN       (AD0_BASE_ADDR + 0x0C)
#define AD0DR0         (AD0_BASE_ADDR + 0x10)
#define AD0DR1         (AD0_BASE_ADDR + 0x14)
#define AD0DR2         (AD0_BASE_ADDR + 0x18)
#define AD0DR3         (AD0_BASE_ADDR + 0x1C)
#define AD0DR4         (AD0_BASE_ADDR + 0x20)
#define AD0DR5         (AD0_BASE_ADDR + 0x24)
#define AD0DR6         (AD0_BASE_ADDR + 0x28)
#define AD0DR7         (AD0_BASE_ADDR + 0x2C)
#define AD0STAT        (AD0_BASE_ADDR + 0x30)


/* D/A Converter */
#define DAC_BASE_ADDR		0xE006C000
#define DACR           (DAC_BASE_ADDR + 0x00)


/* Watchdog */
#define WDG_BASE_ADDR		0xE0000000
#define WDMOD          (WDG_BASE_ADDR + 0x00)
#define WDTC           (WDG_BASE_ADDR + 0x04)
#define WDFEED         (WDG_BASE_ADDR + 0x08)
#define WDTV           (WDG_BASE_ADDR + 0x0C)
#define WDCLKSEL       (WDG_BASE_ADDR + 0x10)

/* CAN CONTROLLERS AND ACCEPTANCE FILTER */
#define CAN_ACCEPT_BASE_ADDR		0xE003C000
#define CAN_AFMR	   (CAN_ACCEPT_BASE_ADDR + 0x00)  	
#define CAN_SFF_SA 	   (CAN_ACCEPT_BASE_ADDR + 0x04)  	
#define CAN_SFF_GRP_SA    (CAN_ACCEPT_BASE_ADDR + 0x08)
#define CAN_EFF_SA 	   (CAN_ACCEPT_BASE_ADDR + 0x0C)
#define CAN_EFF_GRP_SA    (CAN_ACCEPT_BASE_ADDR + 0x10)  	
#define CAN_EOT 	   (CAN_ACCEPT_BASE_ADDR + 0x14)
#define CAN_LUT_ERR_ADR CAN_ACCEPT_BASE_ADDR + 0x18  	
#define CAN_LUT_ERR    (CAN_ACCEPT_BASE_ADDR + 0x1C)

#define CAN_CENTRAL_BASE_ADDR		0xE0040000  	
#define CAN_TX_SR    (CAN_CENTRAL_BASE_ADDR + 0x00)  	
#define CAN_RX_SR    (CAN_CENTRAL_BASE_ADDR + 0x04)  	
#define CAN_MSR    (CAN_CENTRAL_BASE_ADDR + 0x08)

#define CAN1_BASE_ADDR		0xE0044000
#define CAN1MOD    (CAN1_BASE_ADDR + 0x00)  	
#define CAN1CMR    (CAN1_BASE_ADDR + 0x04)  	
#define CAN1GSR    (CAN1_BASE_ADDR + 0x08)  	
#define CAN1ICR    (CAN1_BASE_ADDR + 0x0C)  	
#define CAN1IER    (CAN1_BASE_ADDR + 0x10)
#define CAN1BTR    (CAN1_BASE_ADDR + 0x14)  	
#define CAN1EWL    (CAN1_BASE_ADDR + 0x18)  	
#define CAN1SR 	   (CAN1_BASE_ADDR + 0x1C)  	
#define CAN1RFS    (CAN1_BASE_ADDR + 0x20)  	
#define CAN1RID    (CAN1_BASE_ADDR + 0x24)
#define CAN1RDA    (CAN1_BASE_ADDR + 0x28)  	
#define CAN1RDB    (CAN1_BASE_ADDR + 0x2C)
  	
#define CAN1TFI1    (CAN1_BASE_ADDR + 0x30)  	
#define CAN1TID1    (CAN1_BASE_ADDR + 0x34)  	
#define CAN1TDA1    (CAN1_BASE_ADDR + 0x38)
#define CAN1TDB1    (CAN1_BASE_ADDR + 0x3C)  	
#define CAN1TFI2    (CAN1_BASE_ADDR + 0x40)  	
#define CAN1TID2    (CAN1_BASE_ADDR + 0x44)  	
#define CAN1TDA2    (CAN1_BASE_ADDR + 0x48)  	
#define CAN1TDB2    (CAN1_BASE_ADDR + 0x4C)
#define CAN1TFI3    (CAN1_BASE_ADDR + 0x50)  	
#define CAN1TID3    (CAN1_BASE_ADDR + 0x54)  	
#define CAN1TDA3    (CAN1_BASE_ADDR + 0x58)  	
#define CAN1TDB3    (CAN1_BASE_ADDR + 0x5C)

#define CAN2_BASE_ADDR		0xE0048000
#define CAN2MOD    (CAN2_BASE_ADDR + 0x00)  	
#define CAN2CMR    (CAN2_BASE_ADDR + 0x04)  	
#define CAN2GSR    (CAN2_BASE_ADDR + 0x08)  	
#define CAN2ICR    (CAN2_BASE_ADDR + 0x0C)  	
#define CAN2IER    (CAN2_BASE_ADDR + 0x10)
#define CAN2BTR    (CAN2_BASE_ADDR + 0x14)  	
#define CAN2EWL    (CAN2_BASE_ADDR + 0x18)  	
#define CAN2SR 	   (CAN2_BASE_ADDR + 0x1C)  	
#define CAN2RFS    (CAN2_BASE_ADDR + 0x20)  	
#define CAN2RID    (CAN2_BASE_ADDR + 0x24)
#define CAN2RDA    (CAN2_BASE_ADDR + 0x28)  	
#define CAN2RDB    (CAN2_BASE_ADDR + 0x2C)
  	
#define CAN2TFI1    (CAN2_BASE_ADDR + 0x30)  	
#define CAN2TID1    (CAN2_BASE_ADDR + 0x34)  	
#define CAN2TDA1    (CAN2_BASE_ADDR + 0x38)
#define CAN2TDB1    (CAN2_BASE_ADDR + 0x3C)  	
#define CAN2TFI2    (CAN2_BASE_ADDR + 0x40)  	
#define CAN2TID2    (CAN2_BASE_ADDR + 0x44)  	
#define CAN2TDA2    (CAN2_BASE_ADDR + 0x48)  	
#define CAN2TDB2    (CAN2_BASE_ADDR + 0x4C)
#define CAN2TFI3    (CAN2_BASE_ADDR + 0x50)  	
#define CAN2TID3    (CAN2_BASE_ADDR + 0x54)  	
#define CAN2TDA3    (CAN2_BASE_ADDR + 0x58)  	
#define CAN2TDB3    (CAN2_BASE_ADDR + 0x5C)


/* MultiMedia Card Interface(MCI) Controller */
#define MCI_BASE_ADDR		0xE008C000
#define MCI_POWER      (MCI_BASE_ADDR + 0x00)
#define MCI_CLOCK      (MCI_BASE_ADDR + 0x04)
#define MCI_ARGUMENT   (MCI_BASE_ADDR + 0x08)
#define MCI_COMMAND    (MCI_BASE_ADDR + 0x0C)
#define MCI_RESP_CMD   (MCI_BASE_ADDR + 0x10)
#define MCI_RESP0      (MCI_BASE_ADDR + 0x14)
#define MCI_RESP1      (MCI_BASE_ADDR + 0x18)
#define MCI_RESP2      (MCI_BASE_ADDR + 0x1C)
#define MCI_RESP3      (MCI_BASE_ADDR + 0x20)
#define MCI_DATA_TMR   (MCI_BASE_ADDR + 0x24)
#define MCI_DATA_LEN   (MCI_BASE_ADDR + 0x28)
#define MCI_DATA_CTRL   (MCI_BASE_ADDR + 0x2C)
#define MCI_DATA_CNT   (MCI_BASE_ADDR + 0x30)
#define MCI_STATUS     (MCI_BASE_ADDR + 0x34)
#define MCI_CLEAR      (MCI_BASE_ADDR + 0x38)
#define MCI_MASK0      (MCI_BASE_ADDR + 0x3C)
#define MCI_MASK1      (MCI_BASE_ADDR + 0x40)
#define MCI_FIFO_CNT   (MCI_BASE_ADDR + 0x48)
#define MCI_FIFO       (MCI_BASE_ADDR + 0x80)


/* I2S Interface Controller (I2S) */
#define I2S_BASE_ADDR		0xE0088000
#define I2S_DAO        (I2S_BASE_ADDR + 0x00)
#define I2S_DAI        (I2S_BASE_ADDR + 0x04)
#define I2S_TX_FIFO    (I2S_BASE_ADDR + 0x08)
#define I2S_RX_FIFO    (I2S_BASE_ADDR + 0x0C)
#define I2S_STATE      (I2S_BASE_ADDR + 0x10)
#define I2S_DMA1       (I2S_BASE_ADDR + 0x14)
#define I2S_DMA2       (I2S_BASE_ADDR + 0x18)
#define I2S_IRQ        (I2S_BASE_ADDR + 0x1C)
#define I2S_TXRATE     (I2S_BASE_ADDR + 0x20)
#define I2S_RXRATE     (I2S_BASE_ADDR + 0x24)


/* General-purpose DMA Controller */
#define DMA_BASE_ADDR		0xFFE04000
#define GPDMA_INT_STAT         (DMA_BASE_ADDR + 0x000)
#define GPDMA_INT_TCSTAT       (DMA_BASE_ADDR + 0x004)
#define GPDMA_INT_TCCLR        (DMA_BASE_ADDR + 0x008)
#define GPDMA_INT_ERR_STAT     (DMA_BASE_ADDR + 0x00C)
#define GPDMA_INT_ERR_CLR      (DMA_BASE_ADDR + 0x010)
#define GPDMA_RAW_INT_TCSTAT   (DMA_BASE_ADDR + 0x014)
#define GPDMA_RAW_INT_ERR_STAT DMA_BASE_ADDR + 0x018
#define GPDMA_ENABLED_CHNS     (DMA_BASE_ADDR + 0x01C)
#define GPDMA_SOFT_BREQ        (DMA_BASE_ADDR + 0x020)
#define GPDMA_SOFT_SREQ        (DMA_BASE_ADDR + 0x024)
#define GPDMA_SOFT_LBREQ       (DMA_BASE_ADDR + 0x028)
#define GPDMA_SOFT_LSREQ       (DMA_BASE_ADDR + 0x02C)
#define GPDMA_CONFIG           (DMA_BASE_ADDR + 0x030)
#define GPDMA_SYNC             (DMA_BASE_ADDR + 0x034)

/* DMA channel 0 registers */
#define GPDMA_CH0_SRC      (DMA_BASE_ADDR + 0x100)
#define GPDMA_CH0_DEST     (DMA_BASE_ADDR + 0x104)
#define GPDMA_CH0_LLI      (DMA_BASE_ADDR + 0x108)
#define GPDMA_CH0_CTRL     (DMA_BASE_ADDR + 0x10C)
#define GPDMA_CH0_CFG      (DMA_BASE_ADDR + 0x110)

/* DMA channel 1 registers */
#define GPDMA_CH1_SRC      (DMA_BASE_ADDR + 0x120)
#define GPDMA_CH1_DEST     (DMA_BASE_ADDR + 0x124)
#define GPDMA_CH1_LLI      (DMA_BASE_ADDR + 0x128)
#define GPDMA_CH1_CTRL     (DMA_BASE_ADDR + 0x12C)
#define GPDMA_CH1_CFG      (DMA_BASE_ADDR + 0x130)


/* USB Controller */
#define USB_INT_BASE_ADDR	0xE01FC1C0
#define USB_BASE_ADDR		0xFFE0C200		/* USB Base Address */

#define USB_INT_STAT    (USB_INT_BASE_ADDR + 0x00)

/* USB Device Interrupt Registers */
#define DEV_INT_STAT    (USB_BASE_ADDR + 0x00)
#define DEV_INT_EN      (USB_BASE_ADDR + 0x04)
#define DEV_INT_CLR     (USB_BASE_ADDR + 0x08)
#define DEV_INT_SET     (USB_BASE_ADDR + 0x0C)
#define DEV_INT_PRIO    (USB_BASE_ADDR + 0x2C)

/* USB Device Endpoint Interrupt Registers */
#define EP_INT_STAT     (USB_BASE_ADDR + 0x30)
#define EP_INT_EN       (USB_BASE_ADDR + 0x34)
#define EP_INT_CLR      (USB_BASE_ADDR + 0x38)
#define EP_INT_SET      (USB_BASE_ADDR + 0x3C)
#define EP_INT_PRIO     (USB_BASE_ADDR + 0x40)

/* USB Device Endpoint Realization Registers */
#define REALIZE_EP      (USB_BASE_ADDR + 0x44)
#define EP_INDEX        (USB_BASE_ADDR + 0x48)
#define MAXPACKET_SIZE   (USB_BASE_ADDR + 0x4C)

/* USB Device Command Reagisters */
#define CMD_CODE        (USB_BASE_ADDR + 0x10)
#define CMD_DATA        (USB_BASE_ADDR + 0x14)

/* USB Device Data Transfer Registers */
#define RX_DATA         (USB_BASE_ADDR + 0x18)
#define TX_DATA         (USB_BASE_ADDR + 0x1C)
#define RX_PLENGTH      (USB_BASE_ADDR + 0x20)
#define TX_PLENGTH      (USB_BASE_ADDR + 0x24)
#define USB_CTRL        (USB_BASE_ADDR + 0x28)

/* USB Device DMA Registers */
#define DMA_REQ_STAT        (USB_BASE_ADDR + 0x50)
#define DMA_REQ_CLR         (USB_BASE_ADDR + 0x54)
#define DMA_REQ_SET         (USB_BASE_ADDR + 0x58)
#define UDCA_HEAD           (USB_BASE_ADDR + 0x80)
#define EP_DMA_STAT         (USB_BASE_ADDR + 0x84)
#define EP_DMA_EN           (USB_BASE_ADDR + 0x88)
#define EP_DMA_DIS          (USB_BASE_ADDR + 0x8C)
#define DMA_INT_STAT        (USB_BASE_ADDR + 0x90)
#define DMA_INT_EN          (USB_BASE_ADDR + 0x94)
#define EOT_INT_STAT        (USB_BASE_ADDR + 0xA0)
#define EOT_INT_CLR         (USB_BASE_ADDR + 0xA4)
#define EOT_INT_SET         (USB_BASE_ADDR + 0xA8)
#define NDD_REQ_INT_STAT    (USB_BASE_ADDR + 0xAC)
#define NDD_REQ_INT_CLR     (USB_BASE_ADDR + 0xB0)
#define NDD_REQ_INT_SET     (USB_BASE_ADDR + 0xB4)
#define SYS_ERR_INT_STAT    (USB_BASE_ADDR + 0xB8)
#define SYS_ERR_INT_CLR     (USB_BASE_ADDR + 0xBC)
#define SYS_ERR_INT_SET     (USB_BASE_ADDR + 0xC0)

/* USB Host and OTG registers are for LPC24xx only */
/* USB Host Controller */
#define USBHC_BASE_ADDR		0xFFE0C000
#define HC_REVISION         (USBHC_BASE_ADDR + 0x00)
#define HC_CONTROL          (USBHC_BASE_ADDR + 0x04)
#define HC_CMD_STAT         (USBHC_BASE_ADDR + 0x08)
#define HC_INT_STAT         (USBHC_BASE_ADDR + 0x0C)
#define HC_INT_EN           (USBHC_BASE_ADDR + 0x10)
#define HC_INT_DIS          (USBHC_BASE_ADDR + 0x14)
#define HC_HCCA             (USBHC_BASE_ADDR + 0x18)
#define HC_PERIOD_CUR_ED    (USBHC_BASE_ADDR + 0x1C)
#define HC_CTRL_HEAD_ED     (USBHC_BASE_ADDR + 0x20)
#define HC_CTRL_CUR_ED      (USBHC_BASE_ADDR + 0x24)
#define HC_BULK_HEAD_ED     (USBHC_BASE_ADDR + 0x28)
#define HC_BULK_CUR_ED      (USBHC_BASE_ADDR + 0x2C)
#define HC_DONE_HEAD        (USBHC_BASE_ADDR + 0x30)
#define HC_FM_INTERVAL      (USBHC_BASE_ADDR + 0x34)
#define HC_FM_REMAINING     (USBHC_BASE_ADDR + 0x38)
#define HC_FM_NUMBER        (USBHC_BASE_ADDR + 0x3C)
#define HC_PERIOD_START     (USBHC_BASE_ADDR + 0x40)
#define HC_LS_THRHLD        (USBHC_BASE_ADDR + 0x44)
#define HC_RH_DESCA         (USBHC_BASE_ADDR + 0x48)
#define HC_RH_DESCB         (USBHC_BASE_ADDR + 0x4C)
#define HC_RH_STAT          (USBHC_BASE_ADDR + 0x50)
#define HC_RH_PORT_STAT1    (USBHC_BASE_ADDR + 0x54)
#define HC_RH_PORT_STAT2    (USBHC_BASE_ADDR + 0x58)

/* USB OTG Controller */
#define USBOTG_BASE_ADDR	0xFFE0C100
#define OTG_INT_STAT        (USBOTG_BASE_ADDR + 0x00)
#define OTG_INT_EN          (USBOTG_BASE_ADDR + 0x04)
#define OTG_INT_SET         (USBOTG_BASE_ADDR + 0x08)
#define OTG_INT_CLR         (USBOTG_BASE_ADDR + 0x0C)
/* On LPC23xx, the name is USBPortSel, on LPC24xx, the name is OTG_STAT_CTRL */ 
#define OTG_STAT_CTRL       (USBOTG_BASE_ADDR + 0x10)
#define OTG_TIMER           (USBOTG_BASE_ADDR + 0x14)

#define USBOTG_I2C_BASE_ADDR	0xFFE0C300
#define OTG_I2C_RX          (USBOTG_I2C_BASE_ADDR + 0x00)
#define OTG_I2C_TX          (USBOTG_I2C_BASE_ADDR + 0x00)
#define OTG_I2C_STS         (USBOTG_I2C_BASE_ADDR + 0x04)
#define OTG_I2C_CTL         (USBOTG_I2C_BASE_ADDR + 0x08)
#define OTG_I2C_CLKHI       (USBOTG_I2C_BASE_ADDR + 0x0C)
#define OTG_I2C_CLKLO       (USBOTG_I2C_BASE_ADDR + 0x10)

/* On LPC23xx, the names are USBClkCtrl and USBClkSt; on LPC24xx, the names are 
OTG_CLK_CTRL and OTG_CLK_STAT respectively. */
#define USBOTG_CLK_BASE_ADDR	0xFFE0CFF0
#define OTG_CLK_CTRL        (USBOTG_CLK_BASE_ADDR + 0x04)
#define OTG_CLK_STAT        (USBOTG_CLK_BASE_ADDR + 0x08)

/* Note: below three register name convention is for LPC23xx USB device only, match
with the spec. update in USB Device Section. */ 
#define USBPortSel          (USBOTG_BASE_ADDR + 0x10)
#define USBClkCtrl          (USBOTG_CLK_BASE_ADDR + 0x04)
#define USBClkSt            (USBOTG_CLK_BASE_ADDR + 0x08)

/* Ethernet MAC (32 bit data bus) -- all registers are RW unless indicated in parentheses */
#define MAC_BASE_ADDR		0xFFE00000 /* AHB Peripheral # 0 */
#define MAC_MAC1            (MAC_BASE_ADDR + 0x000) /* MAC config reg 1 */
#define MAC_MAC2            (MAC_BASE_ADDR + 0x004) /* MAC config reg 2 */
#define MAC_IPGT            (MAC_BASE_ADDR + 0x008) /* b2b InterPacketGap reg */
#define MAC_IPGR            (MAC_BASE_ADDR + 0x00C) /* non b2b InterPacketGap reg */
#define MAC_CLRT            (MAC_BASE_ADDR + 0x010) /* CoLlision window/ReTry reg */
#define MAC_MAXF            (MAC_BASE_ADDR + 0x014) /* MAXimum Frame reg */
#define MAC_SUPP            (MAC_BASE_ADDR + 0x018) /* PHY SUPPort reg */
#define MAC_TEST            (MAC_BASE_ADDR + 0x01C) /* TEST reg */
#define MAC_MCFG            (MAC_BASE_ADDR + 0x020) /* MII Mgmt ConFiG reg */
#define MAC_MCMD            (MAC_BASE_ADDR + 0x024) /* MII Mgmt CoMmanD reg */
#define MAC_MADR            (MAC_BASE_ADDR + 0x028) /* MII Mgmt ADdRess reg */
#define MAC_MWTD            (MAC_BASE_ADDR + 0x02C) /* MII Mgmt WriTe Data reg (WO) */
#define MAC_MRDD            (MAC_BASE_ADDR + 0x030) /* MII Mgmt ReaD Data reg (RO) */
#define MAC_MIND            (MAC_BASE_ADDR + 0x034) /* MII Mgmt INDicators reg (RO) */

#define MAC_SA0             (MAC_BASE_ADDR + 0x040) /* Station Address 0 reg */
#define MAC_SA1             (MAC_BASE_ADDR + 0x044) /* Station Address 1 reg */
#define MAC_SA2             (MAC_BASE_ADDR + 0x048) /* Station Address 2 reg */

#define MAC_COMMAND         (MAC_BASE_ADDR + 0x100) /* Command reg */
#define MAC_STATUS          (MAC_BASE_ADDR + 0x104) /* Status reg (RO) */
#define MAC_RXDESCRIPTOR    (MAC_BASE_ADDR + 0x108) /* Rx descriptor base address reg */
#define MAC_RXSTATUS        (MAC_BASE_ADDR + 0x10C) /* Rx status base address reg */
#define MAC_RXDESCRIPTORNUM MAC_BASE_ADDR + 0x110 /* Rx number of descriptors reg */
#define MAC_RXPRODUCEINDEX   (MAC_BASE_ADDR + 0x114) /* Rx produce index reg (RO) */
#define MAC_RXCONSUMEINDEX   (MAC_BASE_ADDR + 0x118) /* Rx consume index reg */
#define MAC_TXDESCRIPTOR    (MAC_BASE_ADDR + 0x11C) /* Tx descriptor base address reg */
#define MAC_TXSTATUS        (MAC_BASE_ADDR + 0x120) /* Tx status base address reg */
#define MAC_TXDESCRIPTORNUM  (MAC_BASE_ADDR + 0x124) /* Tx number of descriptors reg */
#define MAC_TXPRODUCEINDEX   (MAC_BASE_ADDR + 0x128) /* Tx produce index reg */
#define MAC_TXCONSUMEINDEX   (MAC_BASE_ADDR + 0x12C) /* Tx consume index reg (RO) */

#define MAC_TSV0            (MAC_BASE_ADDR + 0x158) /* Tx status vector 0 reg (RO) */
#define MAC_TSV1            (MAC_BASE_ADDR + 0x15C) /* Tx status vector 1 reg (RO) */
#define MAC_RSV             (MAC_BASE_ADDR + 0x160) /* Rx status vector reg (RO) */

#define MAC_FLOWCONTROLCNT   (MAC_BASE_ADDR + 0x170) /* Flow control counter reg */
#define MAC_FLOWCONTROLSTS   (MAC_BASE_ADDR + 0x174) /* Flow control status reg */

#define MAC_RXFILTERCTRL    (MAC_BASE_ADDR + 0x200) /* Rx filter ctrl reg */
#define MAC_RXFILTERWOLSTS   (MAC_BASE_ADDR + 0x204) /* Rx filter WoL status reg (RO) */
#define MAC_RXFILTERWOLCLR   (MAC_BASE_ADDR + 0x208) /* Rx filter WoL clear reg (WO) */

#define MAC_HASHFILTERL     (MAC_BASE_ADDR + 0x210) /* Hash filter LSBs reg */
#define MAC_HASHFILTERH     (MAC_BASE_ADDR + 0x214) /* Hash filter MSBs reg */

#define MAC_INTSTATUS       (MAC_BASE_ADDR + 0xFE0) /* Interrupt status reg (RO) */
#define MAC_INTENABLE       (MAC_BASE_ADDR + 0xFE4) /* Interrupt enable reg  */
#define MAC_INTCLEAR        (MAC_BASE_ADDR + 0xFE8) /* Interrupt clear reg (WO) */
#define MAC_INTSET          (MAC_BASE_ADDR + 0xFEC) /* Interrupt set reg (WO) */

#define MAC_POWERDOWN       (MAC_BASE_ADDR + 0xFF4) /* Power-down reg */
#define MAC_MODULEID        (MAC_BASE_ADDR + 0xFFC) /* Module ID reg (RO) */

/* PLL Setting Table Matrix */
/* 	
	Main Osc.	CCLKCFG		Fcco		Fcclk 		M 	N
	12Mhz		29		300Mhz		10Mhz			24	1
	12Mhz		35		360Mhz		10Mhz			14	0					
	12Mhz		27		336Mhz		12Mhz			13	0		
	12Mhz		17		360Mhz		20Mhz			14	0
	12Mhz		13		336Mhz		24Mhz			13	0
	12Mhz		11		300Mhz		25Mhz			24	1   
	12Mhz		9		300Mhz		30Mhz			24	1
	12Mhz		11		360Mhz		30Mhz			14	0
	12Mhz		9		320Mhz		32Mhz			39	2
	12Mhz		9		350Mhz		35Mhz			174	11
	12Mhz		7		312Mhz		39Mhz			12	0 
	12Mhz		7		360Mhz		45Mhz			14	0  
	12Mhz		5		300Mhz		50Mhz			24	1
	12Mhz		5		312Mhz		52Mhz			12	0
	12Mhz		5		336Mhz		56Mhz			13	0				
	12Mhz		3		300Mhz		75Mhz			24	1
	12Mhz		3		312Mhz		78Mhz			12	0  
	12Mhz		3		320Mhz		80Mhz			39	2
	12Mhz		3		336Mhz		84Mhz			13	0 
*/

/* These are limited number of Fcco configuration for
USB communication as the CPU clock and USB clock shares
the same PLL. The USB clock needs to be multiple of
48Mhz. */
/* Fcclk = 72Mhz, Fcco = 288Mhz, and USB 48Mhz */
#define PLL_MValue			11
#define PLL_NValue			0
#define CCLKDivValue		3
#define USBCLKDivValue		5



/* System configuration: Fosc, Fcclk, Fcco, Fpclk must be defined */
/* PLL input Crystal frequence range 4KHz~20MHz. */
#define MAIN_OSC_FRQ	12000000L
#define IRC_OSC_FRQ		4000000L
#define RTC_OSC_FRQ		32768L 

#define Fcclk (2*MAIN_OSC_FRQ*(PLL_MValue+1)/(PLL_NValue+1)/(CCLKDivValue+1))

#if   Fcclk == 72000000
#define EMC_PERIOD          13.8  // 72MHz 13.8 ns
#elif  Fcclk == 57000000
#define EMC_PERIOD          17.4  // 57.6MHz 17.4ns
#elif Fcclk == 48000000
#define EMC_PERIOD          20.8  // 48MHz  20.8 ns
#elif Fcclk == 36000000
#define EMC_PERIOD          27.8  // 36MHz  27.8 ns
#elif Fcclk == 24000000
#define EMC_PERIOD          41.7  // 24MHz  41.7ns
#else
#error Frequency not defined
#endif

#define P2C(Period)           (((Period<EMC_PERIOD)?0:(unsigned int)((float)Period/EMC_PERIOD))+1)


/* APB clock frequence , must be 1/2/4 multiples of ( Fcclk/4 ). */
/* If USB is enabled, the minimum APB must be greater than 16Mhz */ 

#define	UART_BAUD			115200		/* default baudrate */

#define	INTNO_BITPAT(intno) (1 << intno)

/*
*********************************************************************************************************
*                                           PCLK PERIPHERAL IDS
*********************************************************************************************************
*/

#define  PCLK_WDT                                      0
#define  PCLK_TIMER0                                   1
#define  PCLK_TIMER1                                   2
#define  PCLK_UART0                                    3
#define  PCLK_UART1                                    4
#define  PCLK_PWM0                                     5
#define  PCLK_PWM1                                     6
#define  PCLK_I2C0                                     7
#define  PCLK_SPI                                      8
#define  PCLK_RTC                                      9
#define  PCLK_SSP1                                    10
#define  PCLK_DAC                                     11
#define  PCLK_ADC                                     12
#define  PCLK_CAN1                                    13
#define  PCLK_CAN2                                    14
#define  PCLK_ACF                                     15
#define  PCLK_BAT_RAM                                 16
#define  PCLK_GPIO                                    17
#define  PCLK_PCB                                     18
#define  PCLK_I2C1                                    19
#define  PCLK_SSP0                                    21
#define  PCLK_TIMER2                                  22
#define  PCLK_TIMER3                                  23
#define  PCLK_UART2                                   24
#define  PCLK_UART3                                   25
#define  PCLK_I2C2                                    26
#define  PCLK_I2S									  27
#define  PCLK_MCI                                     28
#define  PCLK_SYSCON                                  30

#endif  // __LPC24xx_H

