/**
 * @file   lpc2478_lcd.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Apr 10 20:42:56 2011
 *
 * @brief  the lm6800 lcd driver
 *
 *
 */

#ifndef  LPC2478_LCD_H
#define  LPC2478_LCD_H



#include  "lpc2478_inc.h"

/*pin assignment*/
#define LCD_RST PINSEL4
#define LCD_RS PINSEL4
#define LCD_R_W PINSEL4
#define LCD_E PINSEL4
#define LCD_CSA PINSEL4
#define LCD_CSB PINSEL4
#define LCD_CSC PINSEL4
#define LCD_DATA_BUS PINSEL4

#define LCD_DISPLAY_ON  0x3f
#define LCD_DISPLAY_START_ADDR 0xc0
#define LCD_SET_X_ADDRESS 0xb8
#define LCD_SET_Y_ADDRESS 0x40
#define LCD_CHIP_WIDTH 64
#define LCD_ROWS 64
#define LCD_COLS 256
/*marco operation instruction*/
#define LCD_RST_LOW()     LCD_RST = 0 /*RST:Reset signal high*/
#define LCD_RST_HIGH()    LCD_RST = 1 /*reset signal low*/
#define LCD_RS_HIGH()     LCD_RS = 1  /*RS:data or instruction select signal high*/
#define LCD_RS_LOW()      LCD_RS = 0  /*RS:data or instruction select signal low*/
#define LCD_R_W_HIGH()    LCD_R_W = 1 /*read or write signal high*/
#define LCD_R_W_LOW()     LCD_R_W = 0 /*read or write signal low*/
#define LCD_E_HIGH()      LCD_E = 1   /*Enable signal high*/
#define LCD_E_LOW()       LCD_E = 0   /*Enable signal low*/
#define LCD_E_HIGH_LOW()  {LCD_E_HIGH();LCD_E_LOW();} /*E falling edge*/
#define LCD_IN_DATA()     LCD_DATA_BUS /*the lcd data bus*/
#define LCD_OUT_DATA(c)   LCD_DATA_BUS = (c) /*output data on the data bus*/
#define DELAY_US()    {}                   /*delay 1 us*/
#define LCD_CHIP_SEL_0()   {LCD_CSA = 0;LCD_CSB = 0;LCD_CSC=0;} /*select the left-most section*/
#define LCD_CHIP_SEL_1()   {LCD_CSA = 1;LCD_CSB = 0;LCD_CSC=0;} /*select the left-most section*/
#define LCD_CHIP_SEL_2()   {LCD_CSA = 0;LCD_CSB = 1;LCD_CSC=0;} /*select the left-most section*/
#define LCD_CHIP_SEL_3()   {LCD_CSA = 1;LCD_CSB = 1;LCD_CSC=0;} /*select the left-most section*/
#define LCD_CHIP_DISABLE_ALL() {LCD_CSC = 0}           /*Disable all the access to the LCD module*/

/*function declaration*/
ERCD LCD_Init(void);
ERCD LCD_Write_CMD(uint8_t cmdcode);
ERCD LCD_Write_Char(uint8_t char_data);
uint8_t LCD_Read_Char(void);
uint8_t LCD_Read_Status(void);
ERCD LCD_Chip_Select(uint8_t chipsel);
ERCD LCD_Locate(uint16_t row, uint16_t col);

#endif
