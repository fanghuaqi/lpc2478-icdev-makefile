/*
 * @file   lpc2478_i2c_cmd.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sat Apr  2 10:48:16 2011
 *
 * @brief
 *
 *
 */

#ifndef _LPC2478_I2C_CMD_H
#define _LPC2478_I2C_CMD_H

#include "lpc2478_inc.h"

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
#define CH452_NOP_CMD		(CH452_ADDR|((CH452_NOP_CMD&0x0f00)>>7))					// 空操作
#define CH452_RESET_CMD    	(CH452_ADDR|((CH452_RESET&0x0f00)>>7))					// 复位
#define CH452_LEVEL_CMD		(CH452_ADDR|((CH452_LEVEL&0x0f00)>>7))					// 加载光柱值,需另加7位数据
#define CH452_CLR_BIT_CMD	(CH452_ADDR|((CH452_CLR_BIT&0x0f00)>>7))					// 段位清0,需另加6位数据
#define CH452_SET_BIT_CMD	(CH452_ADDR|((CH452_SET_BIT&0x0f00)>>7))					// 段位置1,需另加6位数据
#define CH452_SLEEP_CMD		(CH452_ADDR|((CH452_SLEEP&0x0f00)>>7))						// 进入睡眠状态
#define CH452_LEFTMOV_CMD   (CH452_ADDR|((CH452_RIGHTCYC&0x0f00)>>7))			            // 设置移动方式-左移
#define CH452_LEFTCYC_CMD   (CH452_ADDR|((CH452_LEFTCYC&0x0f00)>>7))			            // 设置移动方式-左循环
#define CH452_RIGHTMOV_CMD  (CH452_ADDR|((CH452_RIGHTMOV&0x0f00)>>7))			            // 设置移动方式-右移
#define CH452_RIGHTCYC_CMD  (CH452_ADDR|((CH452_RIGHTCYC&0x0f00)>>7))			            // 设置移动方式-右循环
#define CH452_SELF_BCD_CMD	(CH452_ADDR|((CH452_SELF_BCD&0x0f00)>>7))						// 自定义BCD码,需另加7位数据
#define CH452_SYSOFF_CMD    (CH452_ADDR|((CH452_SYSOFF&0x0f00)>>7))						// 关闭显示、关闭键盘
#define CH452_SYSON1_CMD    (CH452_ADDR|((CH452_SYSON1&0x0f00)>>7))						// 开启显示
#define CH452_SYSON2_CMD    (CH452_ADDR|((CH452_SYSON1&0x0f00)>>7))						// 开启显示、键盘
#define CH452_SYSON2W_CMD   (CH452_ADDR|((CH452_SYSON2W&0x0f00)>>7))						// 开启显示、键盘, 真正2线接口
#define CH452_NO_BCD_CMD    (CH452_ADDR|((CH452_NO_BCD&0x0f00)>>7))						// 设置默认显示方式,可另加3位扫描极限
#define CH452_BCD_CMD       (CH452_ADDR|((CH452_BCD&0x0f00)>>7))						// 设置BCD译码方式,可另加3位扫描极限
#define CH452_TWINKLE_CMD   (CH452_ADDR|((CH452_TWINKLE&0x0f00)>>7))			            // 设置闪烁控制,需另加8位数据
#define CH452_GET_KEY_CMD	(CH452_ADDR|((CH452_GET_KEY&0x0f00)>>7))						// 获取按键,返回按键代码
#define CH452_DIG0_CMD      (CH452_ADDR|((CH452_DIG0&0x0f00)>>7))						// 数码管位0显示,需另加8位数据
#define CH452_DIG1_CMD      (CH452_ADDR|((CH452_DIG1&0x0f00)>>7))			            // 数码管位1显示,需另加8位数据
#define CH452_DIG2_CMD      (CH452_ADDR|((CH452_DIG2&0x0f00)>>7))			            // 数码管位2显示,需另加8位数据
#define CH452_DIG3_CMD      (I2C0_ADDR|((CH452_DIG3&0x0f00)>>7))			            // 数码管位3显示,需另加8位数据
#define CH452_DIG4_CMD      (CH452_ADDR|((CH452_DIG4&0x0f00)>>7))			            // 数码管位4显示,需另加8位数据
#define CH452_DIG5_CMD      (CH452_ADDR|((CH452_DIG5&0x0f00)>>7))						// 数码管位5显示,需另加8位数据
#define CH452_DIG6_CMD      (CH452_ADDR|((CH452_DIG6&0x0f00)>>7))						// 数码管位6显示,需另加8位数据
#define CH452_DIG7_CMD      (CH452_ADDR|((CH452_DIG7&0x0f00)>>7))			            // 数码管位7显示,需另加8位数据
#define CH452_ACK_CMD       (CH452_ADDR|((CH452_ACK&0x0f00)>>7))			            // 2线接口ACK

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

#endif
