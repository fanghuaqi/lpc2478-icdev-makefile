/**
 * @file   lpc_i2c.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Fri Mar 25 11:36:32 2011
 * 
 * @brief  
 * 
 * 
 */

#include  "target_i2c.h"

volatile uint8_t gl_CH452_key  = 0xff;

/*clear i2c status*/
#define I2C_CLEAR_STAT(i2c_baseAddr,I2C_STAT)     sil_wrw_mem((void *)((i2c_baseAddr) + I2CONCLR_OFFSET),(I2C_STAT))
/*send 1 byte i2c data*/
#define I2C_SEND(i2c_baseAddr,I2C_DAT)            sil_wrw_mem((void *)((i2c_baseAddr) + I2DAT_OFFSET),(I2C_DAT))
/*read 1 byte i2c data*/
#define I2C_READ(i2c_baseAddr)                    sil_rew_mem((void *)((i2c_baseAddr) + I2DAT_OFFSET))
/*i2c ack*/
#define I2C_ACK(i2c_baseAddr, status)             while(sil_rew_mem((void *)(i2c_baseAddr + I2STAT_OFFSET)) != (status))

/**
 *
 *
 * @param i2c_baseAddr
 *
 * @return
 */
Inline void I2C_START(uint32_t i2c_baseAddr)
{
	/*clear all the status*/
	I2C_CLEAR_STAT(i2c_baseAddr, (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC));
	/*enable i2c as master*/
	sil_wrw_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET), I2CONSET_I2EN);
	/*send a START condition*/
	sil_wrw_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET), I2CONSET_STA);
}

/**
 * I2C_STOP
 *
 * @param i2c_baseAddr
 *
 * @return
 */
Inline void I2C_STOP(uint32_t i2c_baseAddr)
{
	/*NOTICE: first data set with I2DAT then write I2CONSET next write I2CONCLR*/
	/*send a STOP condition and AA bit*/
	sil_wrw_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET), (I2CONSET_STO|I2CONSET_AA));
	/*clear SI flag*/
	I2C_CLEAR_STAT(i2c_baseAddr, (I2CONCLR_SIC|I2CONCLR_AAC));
	/*wait until the STO bit of I2CONSET clear*/
    while(sil_rew_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET)) & I2CONSET_STO);
}

void I2C_AddrBit_Init(void)
{
	/*P2.23 work as address bit select GPIO with pull-up resistor*/
	sil_wrw_mem((void *)PINSEL5,sil_rew_mem((void *)PINSEL5) & (~(0x3<<14)));
	sil_wrw_mem((void *)PINMODE5,sil_rew_mem((void *)PINMODE5) & (~(0x3<<14)));
	/*P2.23 set as output and set high output*/
	sil_wrw_mem((void *)FIO2DIR2,sil_rew_mem((void *)FIO2DIR2) | ((0x1<<7)&0xff));
	sil_wrw_mem((void *)FIO2SET2,sil_rew_mem((void *)FIO2SET2) | ((0x1<<7)&0xff));
}

/** 
 * I2C_BaseAddr_Calc
 * 
 * @param i2c_channel
 * 
 * @return 
 */
uint32_t I2C_BaseAddr_Calc(uint8_t i2cChannel)
{
    uint32_t i2c_baseAddr = 0;

	switch (i2cChannel){
		case I2C_CHL0:
			i2c_baseAddr = I2C0_BASE_ADDR;
			break;

		case I2C_CHL1:
			i2c_baseAddr = I2C1_BASE_ADDR;
			break;

		case I2C_CHL2:
			i2c_baseAddr = I2C2_BASE_ADDR;
			break;

		default:
			return ERCD_ARG_ERR;
			break;
	}
    return i2c_baseAddr;
}

ERCD I2C_Init(uint8_t i2cChannel, uint16_t i2cMode, uint16_t i2cClk, uint8_t i2cAddress)
{
	uint32_t i2c_baseAddr = 0;
	uint16_t i2c_clk_temp = 0;


	switch (i2cChannel){
		case I2C_CHL0:
			i2c_baseAddr = I2C0_BASE_ADDR;
			/*power on iic*/
			sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP) | (1<<PCI2C0));
			/*i2c clock select*/
			sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0) & (~(3<<14)));
			sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0) | (I2C_CLK_DIV<<14));
			/* set PIO0.27 and PIO0.28 to I2C0 SDA and SCL
			 * function to 01 on both SDA and SCL.*/
			sil_wrw_mem((void *)PINSEL1,sil_rew_mem((void *)PINSEL1) & (~(0xf<<22)));
			sil_wrw_mem((void *)PINSEL1,sil_rew_mem((void *)PINSEL1) | (0x5<<22));
			/* neither pull-up nor pull-down*/
			sil_wrw_mem((void *)PINMODE1,sil_rew_mem((void *)PINMODE1) & (~(0xf<<22)));
			sil_wrw_mem((void *)PINMODE1,sil_rew_mem((void *)PINMODE1) | (0xa<<22));
			break;

		case I2C_CHL1:
			i2c_baseAddr = I2C1_BASE_ADDR;
			/*power on iic*/
			sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP) | (1<<PCI2C1));
			/*i2c clock select*/
			sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1) & (~(3<<6)));
			sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1) | (I2C_CLK_DIV<<6));
			/* set PIO0.0 and PIO0.1 to I2C1 SDA and SCL
			 * function to 11 on both SDA and SCL.*/
			sil_wrw_mem((void *)PINSEL0,sil_rew_mem((void *)PINSEL0) | (0xf<<0));
			/* neither pull-up nor pull-down*/
			sil_wrw_mem((void *)PINMODE0,sil_rew_mem((void *)PINMODE0) & (~(0xf<<0)));
			sil_wrw_mem((void *)PINMODE0,sil_rew_mem((void *)PINMODE0) | (0xa<<0));
			break;

		case I2C_CHL2:
			i2c_baseAddr = I2C2_BASE_ADDR;
			/*power on iic*/
			sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP) | (1<<PCI2C2));
			/*i2c clock select*/
			sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1) & (~(3<<20)));
			sil_wrw_mem((void *)PCLKSEL1,sil_rew_mem((void *)PCLKSEL1) | (I2C_CLK_DIV<<20));
			/* set PIO2.30 and PIO2.31 to I2C2 SDA and SCL
			 * function to 11 on both SDA and SCL.*/
			sil_wrw_mem((void *)PINSEL5,sil_rew_mem((void *)PINSEL5) | (0xf<<28));
			/* neither pull-up nor pull-down*/
			sil_wrw_mem((void *)PINMODE5,sil_rew_mem((void *)PINMODE5) & (~(0xf<<28)));
			sil_wrw_mem((void *)PINMODE5,sil_rew_mem((void *)PINMODE5) | (0xa<<28));
			break;

		default:
			return ERCD_ARG_ERR;
			break;
	}

    /*Clear flags*/
	sil_wrw_mem((void *)(i2c_baseAddr + I2CONCLR_OFFSET), (I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC) );

    /*clock registers set*/
	i2c_clk_temp = I2C_PCLK / i2cClk;
	sil_wrw_mem((void *)(i2c_baseAddr + I2SCLH_OFFSET), ((i2c_clk_temp+1)>>1));
	sil_wrw_mem((void *)(i2c_baseAddr + I2SCLL_OFFSET), ((i2c_clk_temp)>>1));

	/*Mode select: Master or Slave*/
    if (i2cMode == I2CSLAVE){/*Slave Mode*/
    	/*slave address set*/
    	sil_wrw_mem((void *)(i2c_baseAddr + I2ADR_OFFSET), i2cAddress);
    	/*I2C enable and  Assert Acknowledge */
    	sil_wrw_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET), (I2CONSET_I2EN|I2CONSET_AA));
    }else{/*Master Mode*/
    	/*I2C enable*/
    	sil_wrw_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET), I2CONSET_I2EN);
    }

    return ERCD_OK;
}


ERCD I2C_Master_ReadBuf(uint8_t i2cChannel, uint8_t slaveAddr, uint8_t *rec_buffer, uint16_t buffer_len)
{
    uint32_t i2c_baseAddr = 0;
    uint16_t rec_cnt = 0;

    i2c_baseAddr = I2C_BaseAddr_Calc(i2cChannel);
    /*Transmit a START condition*/
    I2C_START(i2c_baseAddr);
    I2C_ACK(i2c_baseAddr, 0x8);
    /*Transmit SLA+R :slave address + Read Operation Bit*/
    I2C_SEND(i2c_baseAddr,(slaveAddr + I2C_READ_OP));
    I2C_CLEAR_STAT(i2c_baseAddr, (I2CONCLR_STAC|I2CONCLR_SIC)); /*clear SI and STR bit*/
    I2C_ACK(i2c_baseAddr, 0x40);
    /*prepare to read data from i2c bus*/
    I2C_CLEAR_STAT(i2c_baseAddr, I2CONCLR_SIC);    /*clear SI bit to prepare to receive data*/
    if (buffer_len != 0){
		while (rec_cnt < (buffer_len-1)){
			I2C_ACK(i2c_baseAddr, 0x50);/*wait data to be received with ACK*/
			rec_buffer[rec_cnt] = I2C_READ(i2c_baseAddr); /*read data*/
			sil_wrw_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET), I2CONSET_AA);
			I2C_CLEAR_STAT(i2c_baseAddr, I2CONCLR_SIC); /*clear SI flag*/
			rec_cnt ++;
		}
		//I2C_CLEAR_STAT(i2c_baseAddr, (I2CONCLR_STAC|I2CONCLR_SIC)); /*clear AA bit and SI flag*/
		I2C_ACK(i2c_baseAddr, 0x58);/*wait data to be received with NO ACK*/
		rec_buffer[rec_cnt] = I2C_READ(i2c_baseAddr); /*read data*/
    }
    /*Transmit STOP and AA bits*/
    I2C_STOP(i2c_baseAddr);

    return ERCD_OK;
}

/** 
 * 
 * 
 * @param sla 
 * @param data 
 * 
 * @return 
 */
ERCD I2C_Master_WriteBuf(uint8_t i2cChannel,  uint8_t slaveAddr, uint8_t *send_buffer, uint16_t buffer_len)
{
    uint32_t i2c_baseAddr = 0;
    uint16_t send_cnt = 0;

    i2c_baseAddr = I2C_BaseAddr_Calc(i2cChannel);
    /*Transmit a START condition*/
    I2C_START(i2c_baseAddr);
    I2C_ACK(i2c_baseAddr, 0x8);
    /*Transmit SLA+W :slave address + Write Operation Bit*/
    I2C_SEND(i2c_baseAddr,(slaveAddr + I2C_WRITE_OP));
    I2C_CLEAR_STAT(i2c_baseAddr, (I2CONCLR_STAC|I2CONCLR_SIC)); /*clear SI and STR bit*/
    I2C_ACK(i2c_baseAddr, 0x18);
    if (buffer_len != 0){
		while (send_cnt < buffer_len){
			I2C_SEND(i2c_baseAddr, send_buffer[send_cnt]); /*write data*/
			sil_wrw_mem((void *)(i2c_baseAddr + I2CONSET_OFFSET), I2CONSET_AA);
			I2C_CLEAR_STAT(i2c_baseAddr, I2CONCLR_SIC); /*clear SI flag*/
			send_cnt ++;
			I2C_ACK(i2c_baseAddr, 0x28);
		}
    }
    /*Transmit STOP and AA bits*/
    I2C_STOP(i2c_baseAddr);

    return ERCD_OK;
}

uint8_t I2C_Master_ReadByte(uint8_t i2cChannel, uint8_t slaveAddr)
{
	uint8_t i2c_dat = 0;
	I2C_Master_ReadBuf(i2cChannel,slaveAddr,&i2c_dat,1);
	return i2c_dat;
}
ERCD I2C_Master_WriteByte(uint8_t i2cChannel,  uint8_t slaveAddr, uint8_t i2cData)
{
	return I2C_Master_WriteBuf(i2cChannel,slaveAddr,&i2cData,1);
}


ERCD CH452_Init(uint16_t i2cClk)
{
	I2C_AddrBit_Init();
	I2C_Init(CH452_CHL,I2CMASTER,i2cClk,CH452_ADDR);
	I2C_Master_WriteByte(CH452_CHL,CH452_ACK_CMD, CH452_ACK_DATA); 				/*选择CH452的2线接口ACK。这个必须最先发出去*/
    I2C_Master_WriteByte(CH452_CHL,CH452_SYSON2_CMD, CH452_SYSON2_DATA);		/*打开键盘，显示驱动*/
    I2C_Master_WriteByte(CH452_CHL,CH452_NO_BCD_CMD, 0x40); 					/*设置非BCD译码,扫描极限为4,显示驱动占空比为100%*/
    I2C_Master_WriteByte(CH452_CHL,CH452_TWINKLE_CMD, 0x00); 					/*设置不闪烁*/
    I2C_Master_WriteByte(CH452_CHL,CH452_LEVEL_CMD,CH452_LEVEL_DATA|0x09);
    CH452_LED_OPEN_SEL(3,1);
    CH452_LED_OPEN(0x7fff,LED_YELLOW);													/*关闭所有CH452上的LED*/
    return ERCD_OK;
}
/** 
 * 
 * 
 * @param led_mask 
 * @param colorType LED_OFF LED_RED 
 * 
 * @return 
 */
ERCD  CH452_LED_OPEN(uint16_t led_mask, uint8_t colorType)
{
    uint8_t seg_value[4];
    uint8_t led_maskH, led_maskL;

    if ((led_mask & 0x8000) || (colorType > LED_YELLOW)){
        return ERCD_ARG_ERR;
    }

    led_maskL = (uint8_t)led_mask;
    led_maskH = (uint8_t)(led_mask>>8) & 0x7f;

    /*Read the seg value of every DIG 0 - 3*/
    seg_value[0] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG0_CMD) & (~led_maskL);
    seg_value[1] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG1_CMD) & (~led_maskL);
    seg_value[2] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG2_CMD) & (~led_maskH) & 0xef;
    seg_value[3] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG3_CMD) & (~led_maskH) & 0xef;
                                       
    switch (colorType){
        case LED_OFF:
            break;
        case LED_RED:
            seg_value[0] |= led_maskL;
            seg_value[2] |= led_maskH;
            break;
        case LED_GREEN:
        	seg_value[1] |= led_maskL;
        	seg_value[3] |= led_maskH;
            break;
        case LED_YELLOW:
        	seg_value[0] |= led_maskL;
        	seg_value[1] |= led_maskL;
        	seg_value[2] |= led_maskH;
        	seg_value[3] |= led_maskH;
            break;
        default:
            return ERCD_ARG_ERR;
            break;
    }
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG0_CMD, seg_value[0]|CH452_DIG0_DATA);
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG1_CMD, seg_value[1]|CH452_DIG1_DATA);
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG2_CMD, seg_value[2]|CH452_DIG2_DATA);
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG3_CMD, seg_value[3]|CH452_DIG3_DATA);

    return ERCD_OK;
}

ERCD  CH452_LED_OPEN_SEL(uint8_t led_num, uint8_t colorType)
{
	if ((led_num & 0x10) || (colorType > LED_YELLOW)){
        return ERCD_ARG_ERR;
    }

    if (led_num > 7){
    	led_num = 15 -led_num + 0x10;    /*指定LED的编号大于8，说明灯处于第二排，此时灯的编码需要加上0x10*/
    }
    else{
    	led_num = 7 - led_num;
    }

    if (colorType == LED_OFF){
    	I2C_Master_WriteByte(CH452_CHL, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA));
    	I2C_Master_WriteByte(CH452_CHL, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA|0x08));
    }else if (colorType == LED_RED){
    	I2C_Master_WriteByte(CH452_CHL, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA));
		I2C_Master_WriteByte(CH452_CHL, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA|0x08));
    }else if (colorType == LED_GREEN){
    	I2C_Master_WriteByte(CH452_CHL, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA));
		I2C_Master_WriteByte(CH452_CHL, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA|0x08));
    }else if (colorType == LED_YELLOW){
    	I2C_Master_WriteByte(CH452_CHL, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA));
		I2C_Master_WriteByte(CH452_CHL, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA|0x08));
    }

    return ERCD_OK;
}


ERCD CH452_Get_SegValue(uint8_t *seg_value)
{
	seg_value[0] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG0_CMD);
	seg_value[1] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG1_CMD);
	seg_value[2] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG2_CMD);
	seg_value[3] = I2C_Master_ReadByte(CH452_CHL, CH452_DIG3_CMD);
	return ERCD_OK;
}
ERCD CH452_Set_SegValue(uint8_t *seg_value)
{
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG0_CMD, seg_value[0]|CH452_DIG0_DATA);
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG1_CMD, seg_value[1]|CH452_DIG1_DATA);
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG2_CMD, seg_value[2]|CH452_DIG2_DATA);
    I2C_Master_WriteByte(CH452_CHL, CH452_DIG3_CMD, seg_value[3]|CH452_DIG3_DATA);
	return ERCD_OK;
}
/** 
 * 
 * 
 * 
 * @return 
 */
ERCD CH452_KeyPress_Signal(void)
{
	uint8_t seg_value[4];
	uint8_t cnt = 0;

	CH452_Get_SegValue(&seg_value[0]);
	for (cnt = 0; cnt < 32; cnt ++){
		I2C_Master_WriteByte(CH452_CHL, CH452_LEVEL_CMD, cnt|CH452_LEVEL_DATA);
		Delay_ms(25);
	}
	CH452_Set_SegValue(&seg_value[0]);
	return ERCD_OK;
}
/** 
 * EEPROM_Init
 * 
 * @param i2c_channel 
 * @param clock
 * @return 
 */
ERCD EEPROM_Init(uint8_t i2c_channel,uint16_t clock)
{
	I2C_Init(i2c_channel,I2CMASTER,clock,EEPROM_ADDR|EEPROM_WRITE);
	return ERCD_OK;
}
/** 
 * EEPROM_READ_BYTE
 * 
 * @param i2c_channel 
 * @param addr 
 * 
 * @return 
 */
uint8_t EEPROM_ReadByte(uint8_t i2c_channel, uint32_t addr)
{
    uint8_t eeprom_data_write[2];
    uint8_t eeprom_addr;
    uint8_t eeprom_data_read;
    
    if (addr & 0xfffe0000){
        return ERCD_ARG_ERR;
    }
    if (addr & 0x00010000){
        eeprom_addr = EEPROM_ADDR|EEPROM_P0;
    }else{
        eeprom_addr = EEPROM_ADDR;
    }
    
    eeprom_data_write[0] = (uint8_t)(addr>>8);
    eeprom_data_write[1] = (uint8_t)(addr);
    I2C_Master_WriteBuf(i2c_channel,eeprom_addr,&eeprom_data_write[0],2);
    eeprom_data_read = I2C_Master_ReadByte(i2c_channel,eeprom_addr);

    return eeprom_data_read;
}
/** 
 * EEPROM_WRITE_BYTE
 * 
 * @param i2c_channel 
 * @param addr 
 * 
 * @return 
 */
ERCD EEPROM_WriteByte(uint8_t i2c_channel, uint32_t addr, uint8_t data)
{
	uint8_t eeprom_data_write[2];
	uint8_t eeprom_addr;

    if (addr & 0xfffe0000){
        return ERCD_ARG_ERR;
    }
    if (addr & 0x00010000){
        eeprom_addr = EEPROM_ADDR|EEPROM_P0;
    }else{
        eeprom_addr = EEPROM_ADDR;
    }
    eeprom_data_write[0] = (uint8_t)(addr>>8);
	eeprom_data_write[1] = (uint8_t)(addr);
	eeprom_data_write[2] = (uint8_t)(data);
	I2C_Master_WriteBuf(i2c_channel,eeprom_addr,&eeprom_data_write[0],3);
	timer2_delayms(3);//delay to make sure the data has write to the eeprom
	return ERCD_OK;
}
