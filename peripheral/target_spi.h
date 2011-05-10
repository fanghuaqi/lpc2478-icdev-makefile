/*
 * =====================================================================================
 *
 *       Filename:  target_spi.h
 *
 *    Description:  spi module head file
 *
 *        Version:  0.1
 *        Created:  2011-5-7 14:15:45
 *
 *         Author:  Ren Wei , renweihust@gmail.com
 *        Company:  HUST-Renesas Lab
 *       Revision:  
 * =====================================================================================
 *	@0.1 	Ren Wei	2011-5-7	create orignal file
 * =====================================================================================
 */

#ifndef TARGET_SPI_H
#define TARGET_SPI_H

#include <t_stddef.h>



#define INHNO_SPI0        10  	/* handler no*/
#define INTNO_SPI0        10    	/* intno */
#define INTPRI_SPI0       -3     /* interrupt priority */
#define INTATR_SPI0       0U     /* interrupt attribute */



#define SPI_CPHA_H     	0x08               		/* clock phase */
#define SPI_CPHA_L		0x00
#define SPI_CPOL_H      0x10               		/* clock polarity */
#define SPI_CPOL_L		0x00
#define SPI_MODE_0      (SPI_CPOL_L | SPI_CPHA_L) /* (original MicroWire) */
#define SPI_MODE_1      (SPI_CPOL_L | SPI_CPHA_H)
#define SPI_MODE_2      (SPI_CPOL_H | SPI_CPHA_L)
#define SPI_MODE_3      (SPI_CPOL_H | SPI_CPHA_H)
#define SPI_LSB_FIRST   0x40                    /* per-word bits-on-wire */
#define SPI_MSB_FIRST	0x00
#define SPI_MASTER		0x20
#define SPI_SLAVE		0x00
#define SPI_BITS(x)		((x << 8) | 0x01)


extern void lpc2478_spi_initialize(intptr_t exinf);
extern ER lpc2478_spi_opn_dev(uint32_t speed, uint32_t mode);
extern ER lpc2478_spi_rea_dat(uint16_t *buf, uint32_t len);
extern ER lpc2478_spi_wri_dat(const uint16_t *buf, uint32_t len);
extern ER lpc2478_spi_wri_then_rea(uint16_t tx_data, uint16_t *rx_data);
extern ER lpc2478_spi_cls_dev(void);
extern ER lpc2478_spi_ctl_dev(uint32_t ioctl, uint8_t *buf);

extern void lpc2478_spi_int_handler(void);

#endif	/* end of TARGET_SPI_H */ 
