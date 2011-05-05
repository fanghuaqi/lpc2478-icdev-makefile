/**
 * @file   lpc_i2c.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Fri Mar 25 11:36:32 2011
 * 
 * @brief  
 * 
 * 
 */

#include  "lpc2478_i2c.h"

volatile uint8_t gl_CH452_key  = 0xff;

/** 
 * 
 * I2C_Init
 * @param I2cMode 
 * 
 * @return 
 */
ERCD I2C_Init(uint8_t I2cChannel, uint16_t I2cMode, uint16_t I2cClk, uint8_t I2cAddress)
{
	uint32_t i2c_baseAddr = 0;
	uint16_t i2c_clk_temp = 0;


	switch (I2cChannel){
	case I2C_CHL0:
		i2c_baseAddr = I2C0_BASE_ADDR;
		setregbits(PCONP,MASK_ALL,1 << PCI2C0);
		setregbits(PCLKSEL0,~(3<<14),(I2C_CLK_DIV<<14));
		/* set PIO0.27 and PIO0.28 to I2C0 SDA and SCL  function to 01 on both SDA and SCL.*/
		setregbits(PINSEL1,~(0xf<<22),(0x5<<22));
		break;

	case I2C_CHL1:
		i2c_baseAddr = I2C1_BASE_ADDR;
		setregbits(PCONP,MASK_ALL,1 << PCI2C1);
		setregbits(PCLKSEL1,~(3<<6),(I2C_CLK_DIV<<6));
		/* set PIO0.0 and PIO0.1 to I2C1 SDA and SCL  function to 11 on both SDA and SCL.*/
		setregbits(PINSEL0,~(0xf<<0),(0xf<<0));
		break;

	case I2C_CHL2:
		i2c_baseAddr = I2C2_BASE_ADDR;
		setregbits(PCONP,MASK_ALL,1 << PCI2C2);
		setregbits(PCLKSEL1,~(3<<20),(I2C_CLK_DIV<<20));
		/* set PIO2.30 and PIO2.31 to I2C2 SDA and SCL  function to 11 on both SDA and SCL.*/
		setregbits(PINSEL5,~(0xf<<28),(0xf<<28));
		break;

	default:
		return ERCD_ARG_ERR;
		break;
	}

    /*--- Clear flags ---*/
	setreg(i2c_baseAddr + I2CONCLR_OFFSET,I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC);

    /*--- clock registers ---*/
	i2c_clk_temp = I2C_PCLK / I2cClk;
	setreg(i2c_baseAddr + I2SCLH_OFFSET, (i2c_clk_temp + 1)>>1);
	setreg(i2c_baseAddr + I2SCLL_OFFSET, (i2c_clk_temp)>>1);

    if ( I2cMode == I2CSLAVE )
    {
    	setreg(i2c_baseAddr + I2ADR_OFFSET, I2cAddress);
    	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_I2EN|I2CONSET_AA);
    }
    else
    {
    	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_I2EN);
    }

    return ERCD_OK;
}

/** 
 * I2C_Master_ReadByte
 * 
 * @param I2cChannel 
 * @param SlaveAddr 
 * 
 * @return 
 */
uint8_t I2C_Master_ReadByte(uint8_t I2cChannel,  uint8_t SlaveAddr)
{
    uint16_t timeout = 0;
    uint32_t i2c_baseAddr = 0;
    uint8_t i2c_data;

	switch (I2cChannel){
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
	setreg(i2c_baseAddr + I2CONCLR_OFFSET, (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC));
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_I2EN);       			    /*使能I2C作为主机*/
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);        			  	/*发送一个起始状态位STA*/

    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x8)	    					/*起始字必须为0x8*/
    {
//    	timeout ++;
//    	if (timeout > MAX_TIMEOUT){
//    		//return ERCD_I2C_BUS_ERR;
//    		goto TIMEOUT_ROUTINE;
//    	}
    }
    setreg(i2c_baseAddr + I2DAT_OFFSET, SlaveAddr + I2C_READ);    				/*设置读取的从设备的地址*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_STAC|I2CONCLR_SIC);			/*清除SI,STR,启动串行传输*/
          
    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x40)				    		/*起始字必须为0x8*/
    {
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
    }
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI位，准备读取数据*/

    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x58)							/*接收数据，无ACK*/
    {
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
    }
    i2c_data = getreg(i2c_baseAddr + I2DAT_OFFSET) ;

    setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位STO*/  /*注意：必须先发数据再清除SI等位*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC|I2CONCLR_AAC);
    while( getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );

    return i2c_data;

TIMEOUT_ROUTINE:
//	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位STO*/  /*注意：必须先发数据再清除SI等位*/
//    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC|I2CONCLR_AAC);
//    while( getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );
    return ERCD_I2C_BUS_ERR;
}

/** 
 * 
 * 
 * @param sla 
 * @param data 
 * 
 * @return 
 */
ERCD I2C_Master_WriteByte(uint8_t I2cChannel,  uint8_t SlaveAddr, uint8_t I2cData)
{
    uint32_t i2c_baseAddr = 0;
    uint16_t timeout = 0;

	switch (I2cChannel){
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
    
	setreg(i2c_baseAddr + I2CONCLR_OFFSET, (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC));
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_I2EN);          /*使能I2C作为主机*/
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);          	/*发送一个起始状态位STA*/
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);          	/*发送一个起始状态位STA*/
      
	while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x8) 				    		/*起始字必须为0x8*/
	{
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
	}
	setreg(i2c_baseAddr + I2DAT_OFFSET, SlaveAddr + I2C_WRITE);    				/*设置读取的从设备的地址*/
	setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_STAC|I2CONCLR_SIC);			/*清除SI,STR,启动串行传输*/
     
	while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x18)//;							/*等待SLA+W传输完毕*/
	{
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
	}
    setreg(i2c_baseAddr + I2DAT_OFFSET, I2cData);    								/*设置读取的从设备的地址*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI标志*/
   
    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x28)//;						/*等待数据传输完毕*/
    {
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
    }
    setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位*/  /*注意：必须先发数据再清除SI等位*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI位*/

    while( getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );				/*等待STO置零*/

    return ERCD_OK;

TIMEOUT_ROUTINE:
//	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位STO*/  /*注意：必须先发数据再清除SI等位*/
//	setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC|I2CONCLR_AAC);
//	while( getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );
	return ERCD_I2C_BUS_ERR;
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
    seg_value[0] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG0_CMD) & (~led_maskL);
    seg_value[1] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG1_CMD) & (~led_maskL);
    seg_value[2] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG2_CMD) & (~led_maskH) & 0xef;
    seg_value[3] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG3_CMD) & (~led_maskH) & 0xef;
                                       
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
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG0_CMD, seg_value[0]|CH452_DIG0_DATA);
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG1_CMD, seg_value[1]|CH452_DIG1_DATA);
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG2_CMD, seg_value[2]|CH452_DIG2_DATA);
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG3_CMD, seg_value[3]|CH452_DIG3_DATA);

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
    	I2C_Master_WriteByte(I2C_CHL0, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA));
    	I2C_Master_WriteByte(I2C_CHL0, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA|0x08));
    }else if (colorType == LED_RED){
    	I2C_Master_WriteByte(I2C_CHL0, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA));
		I2C_Master_WriteByte(I2C_CHL0, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA|0x08));
    }else if (colorType == LED_GREEN){
    	I2C_Master_WriteByte(I2C_CHL0, CH452_CLR_BIT_CMD,(led_num|CH452_CLR_BIT_DATA));
		I2C_Master_WriteByte(I2C_CHL0, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA|0x08));
    }else if (colorType == LED_YELLOW){
    	I2C_Master_WriteByte(I2C_CHL0, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA));
		I2C_Master_WriteByte(I2C_CHL0, CH452_SET_BIT_CMD,(led_num|CH452_SET_BIT_DATA|0x08));
    }

    return ERCD_OK;
}

ERCD CH452_Init(void)
{
    I2C_Master_WriteByte(I2C_CHL0, CH452_ACK_CMD, CH452_ACK_DATA); 				/*选择CH452的2线接口ACK。这个必须最先发出去*/
    I2C_Master_WriteByte(I2C_CHL0, CH452_SYSON2_CMD, CH452_SYSON2_DATA);		/*打开键盘，显示驱动*/
    I2C_Master_WriteByte(I2C_CHL0, CH452_NO_BCD_CMD, 0x40); 					/*设置非BCD译码,扫描极限为4,显示驱动占空比为100%*/
    I2C_Master_WriteByte(I2C_CHL0, CH452_TWINKLE_CMD, 0x00); 					/*设置不闪烁*/
    CH452_LED_OPEN(0x7fff,0);													/*关闭所有CH452上的LED*/
    return ERCD_OK;
}

ERCD CH452_Get_SegValue(uint8_t *seg_value)
{
	seg_value[0] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG0_CMD);
	seg_value[1] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG1_CMD);
	seg_value[2] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG2_CMD);
	seg_value[3] = I2C_Master_ReadByte(I2C_CHL0, CH452_DIG3_CMD);
	return ERCD_OK;
}
ERCD CH452_Set_SegValue(uint8_t *seg_value)
{
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG0_CMD, seg_value[0]|CH452_DIG0_DATA);
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG1_CMD, seg_value[1]|CH452_DIG1_DATA);
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG2_CMD, seg_value[2]|CH452_DIG2_DATA);
    I2C_Master_WriteByte(I2C_CHL0, CH452_DIG3_CMD, seg_value[3]|CH452_DIG3_DATA);
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
		I2C_Master_WriteByte(I2C_CHL0, CH452_LEVEL_CMD, cnt|CH452_LEVEL_DATA);
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
    return I2C_Init(i2c_channel,I2CMASTER,clock,EEPROM_ADDR|EEPROM_WRITE);

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
    //uint8_t eeprom_data_addr[2];
    uint8_t eeprom_addr;
    uint8_t eeprom_data;
    if (addr & 0xfffe0000){
        return ERCD_ARG_ERR;
    }
    if (addr & 0x00010000){
        eeprom_addr = EEPROM_ADDR|EEPROM_P0;
    }else{
        eeprom_addr = EEPROM_ADDR;
    }
    
    I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)(addr>>8)); /*High addr Half first*/
    I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)addr); /*low addr Half follow*/
    eeprom_data = I2C_Master_ReadByte(i2c_channel, eeprom_addr);/*read data*/
    return eeprom_data;
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
    uint8_t eeprom_addr;
//    uint8_t eeprom_data;
    if (addr & 0xfffe0000){
        return ERCD_ARG_ERR;
    }
    if (addr & 0x00010000){
        eeprom_addr = EEPROM_ADDR|EEPROM_P0;
    }else{
        eeprom_addr = EEPROM_ADDR;
    }
    I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)(addr>>8)); /*High addr Half first*/
    I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)addr); /*low addr Half follow*/
    return I2C_Master_WriteByte(i2c_channel, eeprom_addr,data);
}









