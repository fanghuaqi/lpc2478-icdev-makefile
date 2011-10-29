/**
 * @file   lpc2478_lcd.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Apr 10 20:42:56 2011
 *
 * @brief  the lm6800 lcd driver
 *
 *
 */

#ifndef  TARGET_LCD_H
#define  TARGET_LCD_H

#include  "lpc2478_inc.h"


extern void io_ctrl(uint8_t ioinf,uint8_t value);
extern void io_init(uint8_t ioinf,uint8_t dir);
extern uint8_t io_read(uint8_t ioinf);
extern uint8_t lcd_in_data(void);
extern void lcd_out_data(uint8_t data);

#define PIN_HIGH  1
#define PIN_LOW   0
#define PIN_OUT  1
#define PIN_IN   0

#define PORT_OFFSET 5
#define PORT(num) ((num)<<PORT_OFFSET)

#define RST_PIN		((PORT(3)) | (11))
#define CSA_PIN		((PORT(3)) | (8))
#define CSB_PIN		((PORT(3)) | (9))
#define CSC_PIN		((PORT(3)) | (10))
#define RS_PIN		((PORT(3)) | (13))
#define RW_PIN		((PORT(3)) | (15))
#define E_PIN		((PORT(3)) | (14))

#define LCD_DATA_P0  ((PORT(3)) | (0))
#define LCD_DATA_P1  ((PORT(3)) | (1))
#define LCD_DATA_P2  ((PORT(3)) | (2))
#define LCD_DATA_P3  ((PORT(3)) | (3))
#define LCD_DATA_P4  ((PORT(3)) | (4))
#define LCD_DATA_P5  ((PORT(3)) | (5))
#define LCD_DATA_P6  ((PORT(3)) | (6))
#define LCD_DATA_P7  ((PORT(3)) | (7))

/*pin assignment*/
#define LCD_RST RST_PIN
#define LCD_RS RS_PIN
#define LCD_R_W RW_PIN
#define LCD_E E_PIN
#define LCD_CSA CSA_PIN
#define LCD_CSB CSB_PIN
#define LCD_CSC CSC_PIN

#define LCD_DATA_BUS 3

#define LCD_DISPLAY_ON  0x3f
#define LCD_DISPLAY_OFF  0x3E
#define LCD_DISPLAY_START_ADDR 0xc0
#define LCD_SET_X_ADDRESS 0xb8
#define LCD_SET_Y_ADDRESS 0x40
#define LCD_CHIP_WIDTH 64
#define LCD_ROWS 64
#define LCD_COLS 256
/*marco operation instruction*/
//#define LCD_RST_HIGH()    io_ctrl(LCD_RST,PIN_HIGH) /*RST:Reset signal high*/
//#define LCD_RST_LOW()     io_ctrl(LCD_RST,PIN_LOW) /*reset signal low*/
//#define LCD_RS_HIGH()     io_ctrl(LCD_RS,PIN_HIGH)  /*RS:data or instruction select signal high*/
//#define LCD_RS_LOW()      io_ctrl(LCD_RS,PIN_LOW)  /*RS:data or instruction select signal low*/
//#define LCD_R_W_HIGH()    io_ctrl(LCD_R_W,PIN_HIGH) /*read or write signal high*/
//#define LCD_R_W_LOW()     io_ctrl(LCD_R_W,PIN_LOW) /*read or write signal low*/
//#define LCD_E_HIGH()      io_ctrl(LCD_E,PIN_HIGH)    /*Enable signal high*/
//#define LCD_E_LOW()       io_ctrl(LCD_E,PIN_LOW)  /*Enable signal low*/
//#define LCD_E_HIGH_LOW()  {LCD_E_HIGH();_nop_();LCD_E_LOW();} /*E falling edge*/
//#define LCD_IN_DATA()     lcd_in_data() /*the lcd data bus*/
//#define LCD_OUT_DATA(c)   lcd_out_data(c) /*output data on the data bus*/
//
//
//#define LCD_CHIP_SEL_0()   {io_ctrl(LCD_CSA,PIN_LOW);io_ctrl(LCD_CSB,PIN_LOW);io_ctrl(LCD_CSC,PIN_LOW);} /*select the left-most section*/
//#define LCD_CHIP_SEL_1()   {io_ctrl(LCD_CSA,PIN_HIGH);io_ctrl(LCD_CSB,PIN_LOW);io_ctrl(LCD_CSC,PIN_LOW);} /*select the left-most section*/
//#define LCD_CHIP_SEL_2()   {io_ctrl(LCD_CSA,PIN_LOW);io_ctrl(LCD_CSB,PIN_HIGH);io_ctrl(LCD_CSC,PIN_LOW);} /*select the left-most section*/
//#define LCD_CHIP_SEL_3()   {io_ctrl(LCD_CSA,PIN_HIGH);io_ctrl(LCD_CSB,PIN_HIGH);io_ctrl(LCD_CSC,PIN_LOW);} /*select the left-most section*/
//
//#define LCD_CHIP_SEL_OUTPUT()   {io_ctrl(LCD_CSA,PIN_HIGH);io_ctrl(LCD_CSB,PIN_HIGH);io_ctrl(LCD_CSC,PIN_HIGH);}  /*select the left-most section*/
//#define LCD_CHIP_DISABLE_ALL()  io_ctrl(LCD_CSC,PIN_HIGH);           /*Disable all the access to the LCD module*/

#define LCD_RST_HIGH()    sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) | (1L<<11) ); /*RST:Reset signal high*/
#define LCD_RST_LOW()     sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) & (~(1L<<11)) ); /*reset signal low*/
#define LCD_RS_HIGH()     sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) | (1L<<13) );  /*RS:data or instruction select signal high*/
#define LCD_RS_LOW()      sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) & (~(1L<<13)) );  /*RS:data or instruction select signal low*/
#define LCD_R_W_HIGH()    sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) | (1L<<15) ); /*read or write signal high*/
#define LCD_R_W_LOW()     sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) & (~(1L<<15)) );  /*read or write signal low*/
#define LCD_E_HIGH()      sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) | (1L<<14) );    /*Enable signal high*/
#define LCD_E_LOW()       sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN)) & (~(1L<<14)) );   /*Enable signal low*/
#define LCD_E_HIGH_LOW()  {LCD_E_HIGH();LCD_E_LOW();} /*E falling edge*/
#define LCD_IN_DATA()     lcd_in_data() /*the lcd data bus*/
#define LCD_OUT_DATA(c)   lcd_out_data(c) /*output data on the data bus*/


#define LCD_CHIP_SEL_0()   {sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xfffff8ff)) | (0L<<8) );} /*select the left-most section*/
#define LCD_CHIP_SEL_1()   {sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xfffff8ff)) | (1L<<8) );} /*select the left-most section*/
#define LCD_CHIP_SEL_2()   {sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xfffff8ff)) | (2L<<8) );} /*select the left-most section*/
#define LCD_CHIP_SEL_3()   {sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xfffff8ff)) | (3L<<8) );} /*select the left-most section*/

#define LCD_CHIP_SEL_OUTPUT()   {sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xfffff8ff)) | (7L<<8) );}  /*select the left-most section*/
#define LCD_CHIP_DISABLE_ALL()  sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xfffffBff)) | (1L<<10) );           /*Disable all the access to the LCD module*/


#define ASC_CODE_START 0
#define ASC_16X16 	2
#define ASC_8X16	1
#define ASC_8X8 	0
#define _LCM_PUT_8X8 1

extern uint16_t gl_curRow;
extern uint16_t gl_curCol ;

#define _nop_() //Delay_us(1);

/*function declaration*/
ERCD LCD_Init(void);
ERCD LCD_IO_Init(void);
ERCD LCD_Write_CMD(uint8_t cmdcode);
ERCD LCD_Write_Char(uint8_t char_data);
uint8_t LCD_Read_Char(void);
uint8_t LCD_Read_Status(void);
ERCD LCD_Chip_Select(uint8_t chipsel);
ERCD LCD_Locate(uint16_t row, uint16_t col);
ERCD LCD_ClrScreen(uint8_t char_code);
ERCD LCD_PutDot(uint16_t row, uint16_t col, uint8_t dot_state);
ERCD LCD_PutAsc(uint8_t asc_type,uint8_t asc_code);
ERCD LCD_PutAscStr(uint8_t asc_type,uint8_t *asc_str);
void LCD_PutCode(uint8_t asc_code);

#endif
