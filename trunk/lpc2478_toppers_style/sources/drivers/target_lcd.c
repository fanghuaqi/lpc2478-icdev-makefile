/**
 * @file   lpc2478_lcd.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Apr 10 20:44:12 2011
 * 
 * @brief  lm6800 lcd driver for lpc2478
 * 
 * 
 */

#include "target_lcd.h"

uint16_t gl_curRow = 0;
uint16_t gl_curCol = 0;



void io_ctrl(uint8_t ioinf,uint8_t value)
{
	uint32_t controlreg = 0;
	uint32_t port,bit;
	port = (ioinf >> 5);
	bit = ioinf & 0x1F;
	if (port>4){
		port = 4;
	}
	controlreg = FIO0PIN+(port<<5) - ((!!value)<<2);

	sil_wrw_mem((void *)controlreg,sil_rew_mem((void *)controlreg) | (0x1<<bit) );
}
void io_init(uint8_t ioinf,uint8_t dir)
{
	uint32_t controlreg_sel = 0;
	uint32_t controlreg_dir = 0;
	uint32_t port,bit;

	port = (ioinf >> 5);
	bit = ioinf & 0x1F;

	dir = dir & 0x01;

	if (port>4){
		port = 4;
	}

	controlreg_sel = PINSEL_BASE_ADDR + (port<<3) + ((!!(bit>>4))<<2);
	controlreg_dir = FIO_BASE_ADDR  + (port<<5);

	if (bit > 15){
		sil_wrw_mem((void *)controlreg_sel,sil_rew_mem((void *)controlreg_sel) & (~(0x3<<(bit-15))) ); /*set as gpio*/
	}else{
		sil_wrw_mem((void *)controlreg_sel,sil_rew_mem((void *)controlreg_sel) & (~(0x3<<(bit))) ); /*set as gpio*/
	}

	sil_wrw_mem((void *)controlreg_dir,sil_rew_mem((void *)controlreg_dir) & (~(0x1<<bit)) ); /*direction as in or out*/
	sil_wrw_mem((void *)controlreg_dir,sil_rew_mem((void *)controlreg_dir) | (((uint32_t)dir)<<bit) );
}
uint8_t io_read(uint8_t ioinf)
{
	uint32_t controlreg_val = 0;
	uint32_t value;
	uint32_t port,bit;

	port = (ioinf >> 5);
	bit = ioinf & 0x1F;

	if (port>4){
		port = 4;
	}

	controlreg_val = FIO0PIN  + (port<<5);
	value = (sil_rew_mem((void *)controlreg_val)) & (1<<bit);

	return (uint8_t)value;
}

uint8_t lcd_in_data(void)
{
	uint8_t value = 0;

	/*io_init(LCD_DATA_P0,PIN_IN);
	io_init(LCD_DATA_P1,PIN_IN);
	io_init(LCD_DATA_P2,PIN_IN);
	io_init(LCD_DATA_P3,PIN_IN);
	io_init(LCD_DATA_P4,PIN_IN);
	io_init(LCD_DATA_P5,PIN_IN);
	io_init(LCD_DATA_P6,PIN_IN);
	io_init(LCD_DATA_P7,PIN_IN);

	value=io_read(LCD_DATA_P0);
	value|=((io_read(LCD_DATA_P1))<<1);
	value|=((io_read(LCD_DATA_P2))<<2);
	value|=((io_read(LCD_DATA_P3))<<3);
	value|=((io_read(LCD_DATA_P4))<<4);
	value|=((io_read(LCD_DATA_P5))<<5);
	value|=((io_read(LCD_DATA_P6))<<6);
	value|=((io_read(LCD_DATA_P7))<<7);*/
	sil_wrw_mem((void *)FIO3DIR,(sil_rew_mem((void *)FIO3DIR)) & (0xffffff00) );
	value = (sil_rew_mem((void *)FIO3PIN))&0xff;

	return value;
}
void lcd_out_data(uint8_t data)
{
	/*io_init(LCD_DATA_P0,PIN_OUT);
	io_init(LCD_DATA_P1,PIN_OUT);
	io_init(LCD_DATA_P2,PIN_OUT);
	io_init(LCD_DATA_P3,PIN_OUT);
	io_init(LCD_DATA_P4,PIN_OUT);
	io_init(LCD_DATA_P5,PIN_OUT);
	io_init(LCD_DATA_P6,PIN_OUT);
	io_init(LCD_DATA_P7,PIN_OUT);

	io_ctrl(LCD_DATA_P0,(data>>0)&0x1);
	io_ctrl(LCD_DATA_P1,(data>>1)&0x1);
	io_ctrl(LCD_DATA_P2,(data>>2)&0x1);
	io_ctrl(LCD_DATA_P3,(data>>3)&0x1);
	io_ctrl(LCD_DATA_P4,(data>>4)&0x1);
	io_ctrl(LCD_DATA_P5,(data>>5)&0x1);
	io_ctrl(LCD_DATA_P6,(data>>6)&0x1);
	io_ctrl(LCD_DATA_P7,(data>>7)&0x1);*/
	//sil_wrw_mem((void *)controlreg_dir,sil_rew_mem((void *)controlreg_dir) & (~(0x1<<bit)) ); /*direction as in or out*/
	sil_wrw_mem((void *)FIO3DIR,(sil_rew_mem((void *)FIO3DIR)) | (0xff) );
	sil_wrw_mem((void *)FIO3PIN,(sil_rew_mem((void *)FIO3PIN) & (0xffffff00)) | (data) );

}
/** 
 * 
 * 
 * 
 * @return 
 */
ERCD LCD_Init(void)
{
    uint8_t i ;
    LCD_RST_LOW();                  /*RST must keep low at least 1us then go high*/
    Delay_ms(100);
    LCD_RST_HIGH();
    Delay_ms(10);
    for (i = 0; i < 4; i++){
        LCD_Chip_Select(i);
        LCD_Write_CMD(LCD_DISPLAY_ON);/*Display on*/
        LCD_Write_CMD(LCD_DISPLAY_START_ADDR|0x0);/*display startline register 0*/
    }
    return ERCD_OK;
}

/**
 *
 *
 *
 * @return
 */
ERCD LCD_IO_Init(void)
{
	/*io_init(LCD_DATA_P0,PIN_OUT);
	io_init(LCD_DATA_P1,PIN_OUT);
	io_init(LCD_DATA_P2,PIN_OUT);
	io_init(LCD_DATA_P3,PIN_OUT);
	io_init(LCD_DATA_P4,PIN_OUT);
	io_init(LCD_DATA_P5,PIN_OUT);
	io_init(LCD_DATA_P6,PIN_OUT);
	io_init(LCD_DATA_P7,PIN_OUT);*/
	sil_wrw_mem((void *)PINSEL6,sil_rew_mem((void *)PINSEL6) & (0x3L<<12) );
	sil_wrw_mem((void *)PINMODE6,0x0000ffff);
	sil_wrw_mem((void *)FIO3DIR,sil_rew_mem((void *)FIO3DIR) | (0xffff) );

	/*io_init(LCD_RST,PIN_OUT);
	io_init(LCD_RS,PIN_OUT);
	io_init(LCD_R_W,PIN_OUT);
	io_init(LCD_E,PIN_OUT);
	io_init(LCD_CSA,PIN_OUT);
	io_init(LCD_CSB,PIN_OUT);
	io_init(LCD_CSC,PIN_OUT);*/

    return ERCD_OK;
}
/** 
 * 
 * 
 * @param cmdcode 
 * 
 * @return 
 */
ERCD LCD_Write_CMD(uint8_t cmdcode)
{
    //while(LCD_Read_Status() & 0x90);

	LCD_RS_LOW();                   /*when RS=0 R/W=0,cmd write the data bus*/
	//LCD_E_LOW();
	LCD_R_W_LOW();
	Delay_us(10);

	LCD_E_HIGH();
    LCD_OUT_DATA(cmdcode);          /*output cmd  on the bus*/
    Delay_us(5);

    LCD_E_LOW();//LCD_E_HIGH_LOW();               /*when E high->low data appear on the bus*/
    //Delay_us(1);
	_nop_();
	_nop_();
	_nop_();
    return ERCD_OK;
}
/** 
 * 
 * 
 * @param char_data 
 * 
 * @return 
 */
ERCD LCD_Write_Char(uint8_t char_data)
{
    //while(LCD_Read_Status() & 0x90);
	//LCD_E_LOW();
	LCD_RS_HIGH();                  /*when RS=1 R/W=0,cmd write the data bus*/
	//LCD_E_LOW();
	LCD_R_W_LOW();
	Delay_us(10);

	LCD_E_HIGH();
    LCD_OUT_DATA(char_data);        /*output data on the bus*/
    Delay_us(5);

    LCD_E_LOW();//LCD_E_HIGH_LOW();               /*when E high->low(falling edge) data appear on the bus*/
    //Delay_us(1);
	_nop_();
	_nop_();
	_nop_();
    return ERCD_OK;
}
/** 
 * 
 * 
 * 
 * @return 
 */
uint8_t LCD_Read_Char(void)
{
    uint8_t data_read;
    while(LCD_Read_Status() & 0x90);
    /*when read data ,a dummy read is needed*/
    LCD_RS_HIGH();                   /*when RS=1 R/W=1,read data from the displayram*/
    LCD_E_LOW();
    LCD_R_W_HIGH();
    Delay_us(1);

	LCD_E_HIGH();                    /*when E=1 and device is selected data appear*/
    data_read = LCD_IN_DATA();       /*in data on the bus*/
    Delay_us(1);
    LCD_E_LOW();
    Delay_us(1);
	_nop_();
	_nop_();
	_nop_();
    return data_read;				 /*must pull low here*/
}
/**
 * 
 * 
 * 
 * @return
 */
uint8_t LCD_Read_Status(void)
{
    uint8_t status;
    /*when read status ,a dummy read is not needed*/
//	LCD_OUT_DATA(0x00);
//	_nop_();
//	_nop_();

    LCD_RS_LOW();                  /*when RS=0 R/W=1,read status ofthe l*/
    LCD_E_LOW();
    LCD_R_W_HIGH();
    Delay_us(1);

	LCD_E_HIGH();                   /*when E=1 and device is selecte dat ppear*/
    status= LCD_IN_DATA();         /*n data on the bus*/
    Delay_us(1);
	LCD_E_LOW();    			/*must pull low here*/
	Delay_us(1);

	return 0;
}
/** 
  
  * 
  * param cipsel 
  * 
  * @return 
  */
ERCD LCD_Chip_Select(uint8_t chipsel)
{
    if (chipsel > 3){
        return ERCD_ARG_ERR;
    }
	//LCD_CHIP_SEL_OUTPUT();
	//Delay(1);
    switch (chipsel){
        case 0:
            LCD_CHIP_SEL_0();
            break;
        case 1:
            LCD_CHIP_SEL_1();
            break;
        case 2:
            LCD_CHIP_SEL_2();
            break;
        case 3:
            LCD_CHIP_SEL_3();
            break;
        default:
            break;
    }
    //LCD_CHIP_SEL(chipsel);

	//Delay(1);
	_nop_();
	_nop_();
	_nop_();
    return ERCD_OK;
}
/* 
* 
* 
* @ara row 
 * @param col 
 * 
 * @return 
 */
ERCD LCD_Locate(uint16_t row, uint16_t col)
{
    uint8_t chipsel = 0;
	gl_curRow = row;
	gl_curCol = col;
    if ( (col < LCD_COLS) && (row < LCD_ROWS) ){ /*check if the row and col is over range */
        chipsel = col / LCD_CHIP_WIDTH;
        LCD_Chip_Select(chipsel);
    } else {
        return ERCD_ARG_ERR;
    }
    LCD_Write_CMD(LCD_SET_X_ADDRESS|(row>>3)); /*Page address*/
    LCD_Write_CMD(LCD_SET_Y_ADDRESS|(col%LCD_CHIP_WIDTH));
    return ERCD_OK;
}



ERCD LCD_PutDot(uint16_t row, uint16_t col, uint8_t dot_state)
{

	uint8_t ram;
	LCD_Write_CMD(LCD_DISPLAY_ON);
	LCD_Locate(row,col);
	ram = LCD_Read_Char();
	ram = LCD_Read_Char();
	ram = (ram & (~(1<<(row%8))) & 0xff) | (dot_state<<(row%8));
	LCD_Locate(row,col);
    LCD_Write_Char(ram);
    return ERCD_OK;
}

ERCD LCD_PutAsc(uint8_t asc_type,uint8_t asc_code)
{

	uint8_t i;
	uint16_t asc_codeTemp,row,col;

	asc_codeTemp = asc_code;
	LCD_Write_CMD(LCD_DISPLAY_ON);
	if (asc_type > ASC_16X16){
		return ERCD_ARG_ERR;
	}

	switch (asc_code){ /*deal with the special code*/
		case '\n': /*put tthe cursor to the next row*/
			if (asc_type == ASC_8X8){
				LCD_Locate((gl_curRow+8)&(LCD_ROWS-1),0); /*8X8 row gap is 8*/
			}else if ((asc_type == ASC_8X16) || (asc_type == ASC_16X16)){
				LCD_Locate((gl_curRow+16)&(LCD_ROWS-1),0);/*8X16 16X16 row gap is 16*/
			}
			return ERCD_OK;
		case '\r': /*put the cursor to head of current row*/
			LCD_Locate(gl_curRow,0);
			return ERCD_OK;
		case '\b':/*put the cursor backspace a character but don't delete the character before it*/
			if (asc_type == ASC_8X8){
				if ((gl_curCol-8) > (LCD_COLS -1)){
					gl_curRow = (gl_curRow - 8)&(LCD_ROWS-1);
					gl_curCol = (gl_curCol-8)&(LCD_COLS-1);
				}
				else
				{
					gl_curRow = (gl_curRow)&(LCD_ROWS-1);
					gl_curCol = (gl_curCol-8)&(LCD_COLS-1);
				}
			}else if (asc_type == ASC_8X16){
				if ((gl_curCol-8) > (LCD_COLS -1)){
					gl_curRow = (gl_curRow - 16)&(LCD_ROWS-1);
					gl_curCol = (gl_curCol-8)&(LCD_COLS-1);
				}
				else{
					gl_curRow = (gl_curRow)&(LCD_ROWS-1);
					gl_curCol = (gl_curCol-8)&(LCD_COLS-1);
				}
			}else if (asc_type == ASC_16X16){
				if ((gl_curCol-16) > (LCD_COLS -1)){
					gl_curRow = (gl_curRow - 16)&(LCD_ROWS-1);
					gl_curCol = (gl_curCol-16)&(LCD_COLS-1);
				}
				else{
					gl_curRow = (gl_curRow)&(LCD_ROWS-1);
					gl_curCol = (gl_curCol-16)&(LCD_COLS-1);
				}
			}
			LCD_Locate(gl_curRow,gl_curCol);
			return ERCD_OK;
		default:
			row = gl_curRow;
			col = gl_curCol;
			if ( (asc_type == ASC_8X8) ){ /*adjust the output row and column in order to avoid output a ascii word errorly*/
				col = (col >> 3) << 3;
				row = (row >> 3) << 3;
			}else if((asc_type == ASC_8X16)){
				col = (col >> 3) << 3;
				row = (row >> 4) << 4; /*adjust the row */
			}else if (asc_type == ASC_16X16){
				col = (col >> 4) << 4;
				row = (row >> 4) << 4;
			}
			break;
	}

	switch (asc_type){ /*adjust to the different character type*/
		case ASC_16X16:
			LCD_Locate(row,col);
			for (i = 0;i < 16; i++){
				LCD_Write_Char(gl_asckey16X16[i+((asc_codeTemp-ASC_CODE_START)<<5)]); /*notice the priority*/
			}
			LCD_Locate((row+8)&(LCD_ROWS-1),col);
			for (i = 16;i < 32; i++){
				LCD_Write_Char(gl_asckey16X16[i+((asc_codeTemp-ASC_CODE_START)<<5)]); /*notice the priority*/
			}
			if ((col+16) > (LCD_COLS-1)){
				row = (row + 16)&(LCD_ROWS-1);
			}
			LCD_Locate(row, (col+16)&(LCD_COLS-1));
			break;
		case ASC_8X16:
			LCD_Locate(row,col);
			for (i = 0;i < 8; i++){
				LCD_Write_Char(gl_asckey8X16[i+((asc_codeTemp-ASC_CODE_START)<<4)]); /*notice the priority*/
			}
			LCD_Locate((row+8)&(LCD_ROWS-1),col);
			for (i = 8;i < 16; i++){
				LCD_Write_Char(gl_asckey8X16[i+((asc_codeTemp-ASC_CODE_START)<<4)]); /*notice the priority*/
			}
			if ((col+8) > (LCD_COLS-1)){
				row = (row + 16)&(LCD_ROWS-1);
			}
			LCD_Locate(row, (col+8)&(LCD_COLS-1));
			break;
		case ASC_8X8:
			LCD_Locate(row,col);
			for (i = 0;i < 8; i++){
				LCD_Write_Char(gl_asckey8X8[i+((asc_codeTemp-ASC_CODE_START)<<3)]); /*notice the priority*/
			}
			if ((col+8) > (LCD_COLS-1)){
				row = (row + 8)&(LCD_ROWS-1);
			}
			LCD_Locate(row,(col+8)&(LCD_COLS-1));
			break;
		default:
			break;
	}
    return ERCD_OK;
}
ERCD LCD_PutAscStr(uint8_t asc_type,uint8_t *asc_str)
{
	while((*asc_str) != 0){
		LCD_PutAsc(asc_type,*asc_str++);
	}
	return ERCD_OK;
}
void LCD_PutCode(uint8_t asc_code)
{
//#if _LCM_PUT_8X8
	LCD_PutAsc(ASC_16X16,asc_code);
//#else
//	LCD_PutAsc(ASC_8X16,asc_code);
//#endif
}

ERCD LCD_ClrScreen(uint8_t char_code)
{
	uint16_t i ,j, k;
	for(k=0;k<4;k++)
	{
		LCD_Chip_Select(k);
		for(j=0;j<8;j++)
		{
			LCD_Write_CMD(LCD_SET_X_ADDRESS|j);
			LCD_Write_CMD(LCD_SET_Y_ADDRESS);
			for(i=0;i<64;i++)
				LCD_Write_Char(char_code);
		}
	}
	//LCD_Locate(0,0);
	return ERCD_OK;
}
