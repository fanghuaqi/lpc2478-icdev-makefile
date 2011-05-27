/*
 * =====================================================================================
 *
 *       Filename:  target_i2c.h
 *
 *    Description:  
 *
 *        Version:  0.1
 *        Created:  2011-5-27 18:38:35
 *
 *         Author:  Ren Wei , renweihust@gmail.com
 *        Company:  HUST-Renesas Lab
 *       Revision:  
 * =====================================================================================
 *	@0.1 	Ren Wei	2011-5-27	create orignal file
 * =====================================================================================
 */
#ifdef TARGET_I2C_H
#include "LPC24xx.h"
#include <t_stddef.h>
#include <sil.h>


#define TNUM_I2C 	1


#define INTNO_I2C0	9		/* int no */
#define INHNO_I2C0	9		/* int handler no */
#define INTPRI_I2C0 -4		/* int priority */
#define INTATR_I2C0	0		/* int attribute */

#define INTNO_I2C1	19		/* int no */
#define INHNO_I2C1	19      /* int handler no */
#define INTPRI_I2C1 -4      /* int priority */
#define INTATR_I2C1	0       /* int attribute */

#define INTNO_I2C2	30		/* int no */
#define INHNO_I2C2	30      /* int handler no */
#define INTPRI_I2C2 -4      /* int priority */
#define INTATR_I2C2	0       /* int attribute */

/*channel definitions*/
#define	I2C_CHL0	0
#define I2C_CHL1 	1
#define I2C_CHL2 	2

/* operation mode */
#define I2CMASTER		0x01
#define I2CSLAVE		0x02

/*channel clk definitions*/
#define	I2C0_CLK	4000
#define I2C1_CLK 	4000
#define I2C2_CLK 	4000
/*channel addr definitions*/
#define	I2C0_ADDR	0x60   							/*由于CH452的ADDR引脚被强制拉高，所以addr配置为60h*/
#define I2C1_ADDR 	0x31
#define I2C2_ADDR 	0x82
#define EEPROM_ADDR 0xA0

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

/* EEPROM W/R Operation  */
#define EEPROM_WRITE 0
#define EEPROM_READ  1
/* EEPROM High addr*/
#define EEPROM_P0    0x02
#define	EEPROM_CLK	 1000000

/*CH452 LED color definitions*/
#define LED_OFF              0
#define LED_RED              1
#define LED_GREEN            2
#define LED_YELLOW           3
#define WCH452_ADDR     0x60

#define RD_BIT			0x01



/* 常量定义 */

/* CH451和CH452的常用命令码 */
#define CH452_NOP		0x0000					// 空操作
#define CH452_RESET     0x0201					// 复位
#define CH452_LEVEL		0x0100					// 加载光柱值,需另加7位数据
#define CH452_CLR_BIT	0x0180					// 段位清0,需另加6位数据
#define CH452_SET_BIT	0x01C0					// 段位置1,需另加6位数据
#define CH452_SLEEP		0x0202					// 进入睡眠状态
#define CH452_LEFTMOV   0x0300		            // 设置移动方式-左移
#define CH452_LEFTCYC   0x0301		            // 设置移动方式-左循环
#define CH452_RIGHTMOV  0x0302		            // 设置移动方式-右移
#define CH452_RIGHTCYC  0x0303		            // 设置移动方式-右循环
#define CH452_SELF_BCD	0x0380					// 自定义BCD码,需另加7位数据
#define CH452_SYSOFF    0x0400					// 关闭显示、关闭键盘
#define CH452_SYSON1    0x0401					// 开启显示
#define CH452_SYSON2    0x0403					// 开启显示、键盘
#define CH452_SYSON2W   0x0423					// 开启显示、键盘, 真正2线接口
#define CH452_NO_BCD    0x0500					// 设置默认显示方式,可另加3位扫描极限
#define CH452_BCD       0x0580					// 设置BCD译码方式,可另加3位扫描极限
#define CH452_TWINKLE   0x0600		            // 设置闪烁控制,需另加8位数据
#define CH452_GET_KEY	0x0700					// 获取按键,返回按键代码
#define CH452_DIG0      0x0800					// 数码管位0显示,需另加8位数据
#define CH452_DIG1      0x0900		            // 数码管位1显示,需另加8位数据
#define CH452_DIG2      0x0a00		            // 数码管位2显示,需另加8位数据
#define CH452_DIG3      0x0b00		            // 数码管位3显示,需另加8位数据
#define CH452_DIG4      0x0c00		            // 数码管位4显示,需另加8位数据
#define CH452_DIG5      0x0d00					// 数码管位5显示,需另加8位数据
#define CH452_DIG6      0x0e00					// 数码管位6显示,需另加8位数据
#define CH452_DIG7      0x0f00		            // 数码管位7显示,需另加8位数据
#define CH452_ACK       0x0700		            // 2线接口ACK

/* CH451和CH452的常用命令码+地址*/
#define CH452_NOP_CMD		(I2C0_ADDR|((CH452_NOP_CMD&0x0f00)>>7))					// 空操作
#define CH452_RESET_CMD    	(I2C0_ADDR|((CH452_RESET&0x0f00)>>7))					// 复位
#define CH452_LEVEL_CMD		(I2C0_ADDR|((CH452_LEVEL&0x0f00)>>7))					// 加载光柱值,需另加7位数据
#define CH452_CLR_BIT_CMD	(I2C0_ADDR|((CH452_CLR_BIT&0x0f00)>>7))					// 段位清0,需另加6位数据
#define CH452_SET_BIT_CMD	(I2C0_ADDR|((CH452_SET_BIT&0x0f00)>>7))					// 段位置1,需另加6位数据
#define CH452_SLEEP_CMD		(I2C0_ADDR|((CH452_SLEEP&0x0f00)>>7))						// 进入睡眠状态
#define CH452_LEFTMOV_CMD   (I2C0_ADDR|((CH452_RIGHTCYC&0x0f00)>>7))			            // 设置移动方式-左移
#define CH452_LEFTCYC_CMD   (I2C0_ADDR|((CH452_LEFTCYC&0x0f00)>>7))			            // 设置移动方式-左循环
#define CH452_RIGHTMOV_CMD  (I2C0_ADDR|((CH452_RIGHTMOV&0x0f00)>>7))			            // 设置移动方式-右移
#define CH452_RIGHTCYC_CMD  (I2C0_ADDR|((CH452_RIGHTCYC&0x0f00)>>7))			            // 设置移动方式-右循环
#define CH452_SELF_BCD_CMD	(I2C0_ADDR|((CH452_SELF_BCD&0x0f00)>>7))						// 自定义BCD码,需另加7位数据
#define CH452_SYSOFF_CMD    (I2C0_ADDR|((CH452_SYSOFF&0x0f00)>>7))						// 关闭显示、关闭键盘
#define CH452_SYSON1_CMD    (I2C0_ADDR|((CH452_SYSON1&0x0f00)>>7))						// 开启显示
#define CH452_SYSON2_CMD    (I2C0_ADDR|((CH452_SYSON1&0x0f00)>>7))						// 开启显示、键盘
#define CH452_SYSON2W_CMD   (I2C0_ADDR|((CH452_SYSON2W&0x0f00)>>7))						// 开启显示、键盘, 真正2线接口
#define CH452_NO_BCD_CMD    (I2C0_ADDR|((CH452_NO_BCD&0x0f00)>>7))						// 设置默认显示方式,可另加3位扫描极限
#define CH452_BCD_CMD       (I2C0_ADDR|((CH452_BCD&0x0f00)>>7))						// 设置BCD译码方式,可另加3位扫描极限
#define CH452_TWINKLE_CMD   (I2C0_ADDR|((CH452_TWINKLE&0x0f00)>>7))			            // 设置闪烁控制,需另加8位数据
#define CH452_GET_KEY_CMD	(I2C0_ADDR|((CH452_GET_KEY&0x0f00)>>7))						// 获取按键,返回按键代码
#define CH452_DIG0_CMD      (I2C0_ADDR|((CH452_DIG0&0x0f00)>>7))						// 数码管位0显示,需另加8位数据
#define CH452_DIG1_CMD      (I2C0_ADDR|((CH452_DIG1&0x0f00)>>7))			            // 数码管位1显示,需另加8位数据
#define CH452_DIG2_CMD      (I2C0_ADDR|((CH452_DIG2&0x0f00)>>7))			            // 数码管位2显示,需另加8位数据
#define CH452_DIG3_CMD      (I2C0_ADDR|((CH452_DIG3&0x0f00)>>7))			            // 数码管位3显示,需另加8位数据
#define CH452_DIG4_CMD      (I2C0_ADDR|((CH452_DIG4&0x0f00)>>7))			            // 数码管位4显示,需另加8位数据
#define CH452_DIG5_CMD      (I2C0_ADDR|((CH452_DIG5&0x0f00)>>7))						// 数码管位5显示,需另加8位数据
#define CH452_DIG6_CMD      (I2C0_ADDR|((CH452_DIG6&0x0f00)>>7))						// 数码管位6显示,需另加8位数据
#define CH452_DIG7_CMD      (I2C0_ADDR|((CH452_DIG7&0x0f00)>>7))			            // 数码管位7显示,需另加8位数据
#define CH452_ACK_CMD       (I2C0_ADDR|((CH452_ACK&0x0f00)>>7))			            // 2线接口ACK

/* CH451和CH452的常用命令码 数据段*/
#define CH452_NOP_DATA			0x00					// 空操作
#define CH452_RESET_DATA     	0x01					// 复位
#define CH452_LEVEL_DATA		0x00					// 加载光柱值,需另加7位数据
#define CH452_CLR_BIT_DATA		0x80					// 段位清0,需另加6位数据
#define CH452_SET_BIT_DATA		0xC0					// 段位置1,需另加6位数据
#define CH452_SLEEP_DATA		0x02					// 进入睡眠状态
#define CH452_LEFTMOV_DATA	    0x00		            // 设置移动方式-左移
#define CH452_LEFTCYC_DATA	    0x01		            // 设置移动方式-左循环
#define CH452_RIGHTMOV_DATA	    0x02		            // 设置移动方式-右移
#define CH452_RIGHTCYC_DATA  	0x03		            // 设置移动方式-右循环
#define CH452_SELF_BCD_DATA		0x80					// 自定义BCD码,需另加7位数据
#define CH452_SYSOFF_DATA    	0x00					// 关闭显示、关闭键盘
#define CH452_SYSON1_DATA    	0x01					// 开启显示
#define CH452_SYSON2_DATA    	0x03					// 开启显示、键盘
#define CH452_SYSON2W_DATA  	0x23					// 开启显示、键盘, 真正2线接口
#define CH452_NO_BCD_DATA	    0x00					// 设置默认显示方式,可另加3位扫描极限
#define CH452_BCD_DATA	        0x80					// 设置BCD译码方式,可另加3位扫描极限
#define CH452_TWINKLE_DATA		0x00		            // 设置闪烁控制,需另加8位数据
#define CH452_GET_KEY_DATA 		0x00					// 获取按键,返回按键代码
#define CH452_DIG0_DATA	        0x00					// 数码管位0显示,需另加8位数据
#define CH452_DIG1_DATA         0x00		            // 数码管位1显示,需另加8位数据
#define CH452_DIG2_DATA         0x00		            // 数码管位2显示,需另加8位数据
#define CH452_DIG3_DATA         0x00		            // 数码管位3显示,需另加8位数据
#define CH452_DIG4_DATA         0x00		            // 数码管位4显示,需另加8位数据
#define CH452_DIG5_DATA         0x00					// 数码管位5显示,需另加8位数据
#define CH452_DIG6_DATA         0x00					// 数码管位6显示,需另加8位数据
#define CH452_DIG7_DATA         0x00		            // 数码管位7显示,需另加8位数据
#define CH452_ACK_DATA          0x00		            // 2线接口ACK
// BCD译码方式下的特殊字符
#define		CH452_BCD_SPACE		0x10
#define		CH452_BCD_PLUS		0x11
#define		CH452_BCD_MINUS		0x12
#define		CH452_BCD_EQU		0x13
#define		CH452_BCD_LEFT		0x14
#define		CH452_BCD_RIGHT		0x15
#define		CH452_BCD_UNDER		0x16
#define		CH452_BCD_CH_H		0x17
#define		CH452_BCD_CH_L		0x18
#define		CH452_BCD_CH_P		0x19
#define		CH452_BCD_DOT		0x1A
#define		CH452_BCD_SELF		0x1E
#define		CH452_BCD_TEST		0x88
#define		CH452_BCD_DOT_X		0x80
//CH452 LED encode
#define		CH452_LED0			0x0080
#define		CH452_LED1			0x0040
#define		CH452_LED2			0x0020
#define		CH452_LED3			0x0010
#define		CH452_LED4			0x0008
#define		CH452_LED5			0x0004
#define		CH452_LED6			0x0002
#define		CH452_LED7			0x0001
#define		CH452_LED8			0x4000
#define		CH452_LED9			0x2000
#define		CH452_LED10			0x1000
#define		CH452_LED11			0x0800
#define		CH452_LED12			0x0400
#define		CH452_LED13			0x0200
#define		CH452_LED14			0x0100

// 有效按键代码
#define		CH452_KEY_MIN		0x40
#define		CH452_KEY_MAX		0x7F

extern void i2c_initialize(intptr_t exinf);
extern ER 	i2c_open(ID channel, uint32_t mode, uint32_t clk, uint8_t address);
extern ER i2c_master_read(ID channel, uint8_t slave_address, uint8_t *buf, uint32_t len, uint8_t mode);
extern ER i2c_master_write(ID channel, uint8_t slave_address, uint8_t *buf, uint32_t len, uint8_t mode);

extern void i2c0_int_handler(void);


#if TNUM_I2C >= 2
extern void i2c1_int_handler(void);
#endif

#if TNUM_I2C >= 3
extern void i2c2_int_handler(void);
#endif

#endif
