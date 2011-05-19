/**
 * @file   lpc_i2c.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Fri Mar 25 11:33:43 2011
 *
 * @brief
 *
 *
 */
#ifndef TARGET_I2C_H
#define TARGET_I2C_H

#include "lpc2478_inc.h"

/*CH452 interrupt pin*/

/*channel definitions*/
#define	I2C_CHL0	0
#define I2C_CHL1 	1
#define I2C_CHL2 	2
/*channel clk definitions*/
#define	I2C0_CLK	4000
#define I2C1_CLK 	4000
#define I2C2_CLK 	4000
/*channel addr definitions*/
#define	I2C0_ADDR	0x60   							/*由于CH452的ADDR引脚被强制拉高，所以addr配置为60h*/
#define I2C1_ADDR 	0x31
#define I2C2_ADDR 	0x82
#define EEPROM_ADDR 0xA0
/* EEPROM W/R Operation  */
#define EEPROM_WRITE 0
#define EEPROM_READ  1
/* EEPROM High addr*/
#define EEPROM_P0    0x02
#define	EEPROM_CLK	 1000000
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
#define I2C_READ_OP			 1
#define I2C_WRITE_OP		 0
#define ACK_BIT              1
/*CH452 LED color definitions*/
#define LED_OFF              0
#define LED_RED              1
#define LED_GREEN            2
#define LED_YELLOW           3

#define BUFSIZE			0x20
#define MAX_TIMEOUT		50000

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

extern volatile uint8_t gl_CH452_key ;



void 		I2C_AddrBit_Init(void);
ERCD 	  	I2C_Init(uint8_t I2cChannel, uint16_t I2cMode, uint16_t I2cClk, uint8_t I2cAddress);
ERCD 		I2C_Master_ReadBuf(uint8_t i2cChannel, uint8_t slaveAddr, uint8_t *rec_buffer, uint16_t buffer_len);
ERCD 		I2C_Master_WriteBuf(uint8_t i2cChannel,  uint8_t slaveAddr, uint8_t *send_buffer, uint16_t buffer_len);
uint8_t 	I2C_Master_ReadByte(uint8_t i2cChannel, uint8_t slaveAddr);
ERCD 		I2C_Master_WriteByte(uint8_t i2cChannel,  uint8_t slaveAddr, uint8_t i2cData);

ERCD 		CH452_Init(void);
ERCD        CH452_LED_OPEN(uint16_t led_mask, uint8_t colorType);
ERCD        CH452_LED_OPEN_SEL(uint8_t led_num, uint8_t colorType);
ERCD 		CH452_KeyPress_Signal(void);
ERCD 		CH452_Set_SegValue(uint8_t *seg_value);
ERCD 		CH452_Get_SegValue(uint8_t *seg_value);

ERCD        EEPROM_Init(uint8_t i2c_channel,uint16_t clock);
uint8_t     EEPROM_ReadByte(uint8_t i2c_channel, uint32_t addr);
ERCD        EEPROM_WriteByte(uint8_t i2c_channel, uint32_t addr, uint8_t data);

#define	CH452_CLOSE_ALLLEDS()	I2C_Master_WriteByte(I2C_CHL0, I2C0_ADDR|(CH452_LEVEL>>7), 0)

#endif
