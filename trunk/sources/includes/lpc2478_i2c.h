/**
 * @file   lpc_i2c.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Fri Mar 25 11:33:43 2011
 *
 * @brief
 *
 *
 */
#ifndef __LPC2478_I2C_H
#define __LPC2478_I2C_H

#include "lpc2478_inc.h"


/*channel definitions*/
#define	I2C_CHL0	0
#define I2C_CHL1 	1
#define I2C_CHL2 	2
/*channel clk definitions*/
#define	I2C0_CLK	400000
#define I2C1_CLK 	4000
#define I2C2_CLK 	4000
/*channel addr definitions*/
#define	I2C0_ADDR	0x40   							/*由于CH452的ADDR引脚被强制拉低，所以addr配置为40h*/
#define I2C1_ADDR 	0x31
#define I2C2_ADDR 	0x82
/*i2c PCONP bit location*/
#define PCI2C0		7
#define PCI2C1		19
#define PCI2C2		26
/*i2c  register offset*/
#define I2CONSET_OFFSET      0x00
#define I2STAT_OFFSET        0x04
#define I2DAT_OFFSET         0x08
#define I2ADR_OFFSET         0x0C
#define I2SCLH_OFFSET        0x10
#define I2SCLL_OFFSET        0x14
#define I2CONCLR_OFFSET      0x18
/*clock devision*/
#define CLK_DIV_4			 0
#define CLK_DIV_1			 1
#define CLK_DIV_2			 2
#define CLK_DIV_8			 3
#define I2C_CLK_DIV	         CLK_DIV_1
#define I2C_PCLK			 (Fcclk/I2C_CLK_DIV)
/*I2C Read Or Write Define*/
#define I2C_READ			 1
#define I2C_WRITE			 0


#define BUFSIZE			0x20
#define MAX_TIMEOUT		0x00FFFFFF

#define WCH452_ADDR     0x60

#define I2CMASTER		0x01
#define I2CSLAVE		0x02

#define RD_BIT			0x01

#define I2C_IDLE			0
#define I2C_STARTED			1
#define I2C_RESTARTED		2
#define I2C_REPEATED_START	3
#define DATA_ACK			4
#define DATA_NACK			5

#define I2CONSET_I2EN		0x00000040  /* I2C Control Set Register */
#define I2CONSET_AA			0x00000004
#define I2CONSET_SI			0x00000008
#define I2CONSET_STO		0x00000010
#define I2CONSET_STA		0x00000020

#define I2CONCLR_AAC		0x00000004  /* I2C Control clear Register */
#define I2CONCLR_SIC		0x00000008
#define I2CONCLR_STAC		0x00000020
#define I2CONCLR_I2ENC		0x00000040

#define I2DAT_I2C			0x00000000  /* I2C Data Reg */
#define I2ADR_I2C			0x00000000  /* I2C Slave Address Reg */
#define I2SCLH_SCLH			0x00000080  /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL			0x00000080  /* I2C SCL Duty Cycle Low Reg */

ERCD 	  	I2C_Init(uint8_t I2cChannel, uint16_t I2cMode, uint16_t I2cClk, uint8_t I2cAddress);
uint8_t 	I2C_Master_ReadByte(uint8_t I2cChannel,  uint8_t SlaveAddr);
ERCD 		I2C_Master_WriteByte(uint8_t I2cChannel,  uint8_t SlaveAddr, uint8_t I2cData);


#endif
