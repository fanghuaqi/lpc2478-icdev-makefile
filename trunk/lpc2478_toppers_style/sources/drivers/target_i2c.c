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
		setregbits(PINMODE1,~(0xf<<22),(0xa<<22));
		setregbits(PINSEL5,(~(0x3<<14)),0x0);
		setregbits(PINMODE5,(~(0x3<<14)),0x0);
		setregbits(FIO2DIR2,(~(0x1<<7))&0xff,(0x1<<7));  /*p2.0 output*/
		setregbits(FIO2SET2,(~(0x1<<7))&0xff,(0x1<<7));   /*p2.0 high*/
		break;

	case I2C_CHL1:
		i2c_baseAddr = I2C1_BASE_ADDR;
		setregbits(PCONP,MASK_ALL,1 << PCI2C1);
		setregbits(PCLKSEL1,~(3<<6),(I2C_CLK_DIV<<6));
		/* set PIO0.0 and PIO0.1 to I2C1 SDA and SCL  function to 11 on both SDA and SCL.*/
		setregbits(PINSEL0,~(0xf<<0),(0xf<<0));
		setregbits(PINMODE0,~(0xf<<0),(0xa<<0));
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
    setreg(i2c_baseAddr + I2DAT_OFFSET, SlaveAddr + I2C_READ_OP);    				/*设置读取的从设备的地址*/

    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_STAC|I2CONCLR_SIC);			/*清除SI,STR,启动串行传输*/
          
    //while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x48))
    while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x40))				    		/*起始字必须为0x8*/
    {
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
    }
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI位，准备读取数据*/

    //while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x50))
    while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x58))							/*接收数据，无ACK*/
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
	//setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);          	/*发送一个起始状态位STA*/
      
	while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x8) 				    		/*起始字必须为0x8*/
	{
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
	}
	setreg(i2c_baseAddr + I2DAT_OFFSET, SlaveAddr + I2C_WRITE_OP);    				/*设置读取的从设备的地址*/
	//setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_AA|I2CONSET_I2EN);       			    /*使能I2C作为主机*/
	setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC|I2CONCLR_STAC);			/*清除SI,STR,启动串行传输*/

//	while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x20))
	while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x18))//;							/*等待SLA+W传输完毕*/
	{
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
	}
	//Delay_ms(1);
    setreg(i2c_baseAddr + I2DAT_OFFSET, I2cData);    								/*设置读取的从设备的地址*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI标志*/
   
    //while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x30))
    while((getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x28))//;						/*等待数据传输完毕*/
    {
//    	timeout ++;
//		if (timeout > MAX_TIMEOUT){
//			//return ERCD_I2C_BUS_ERR;
//			goto TIMEOUT_ROUTINE;
//		}
    }
    //Delay_ms(1);
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
    I2C_Master_WriteByte(I2C_CHL0,CH452_LEVEL_CMD,CH452_LEVEL_DATA|0x09);
    CH452_LED_OPEN_SEL(3,1);
    CH452_LED_OPEN(0x7fff,LED_YELLOW);													/*关闭所有CH452上的LED*/
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
	uint32_t i2c_baseAddr = 0;

	I2C_Init(i2c_channel,I2CMASTER,clock,EEPROM_ADDR|EEPROM_WRITE);

	i2c_baseAddr=I2C_BASE_SEL(i2c_channel);
	I2C_START(i2c_baseAddr);
	I2C_ACK(i2c_baseAddr,0x08);
	I2C_SEND(i2c_baseAddr,EEPROM_ADDR|EEPROM_WRITE);
	I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_STAC|I2CONCLR_SIC);
	I2C_ACK(i2c_baseAddr,0x18);
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);
	setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_STAC|I2CONCLR_SIC);
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);          	/*发送一个起始状态位STA*/
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
    //uint8_t eeprom_data_addr[2];
    uint8_t eeprom_addr;
    uint8_t eeprom_data;
    uint32_t i2c_baseAddr = 0;
    
    if (addr & 0xfffe0000){
        return ERCD_ARG_ERR;
    }
    if (addr & 0x00010000){
        eeprom_addr = EEPROM_ADDR|EEPROM_P0;
    }else{
        eeprom_addr = EEPROM_ADDR;
    }
    
    i2c_baseAddr=I2C_BASE_SEL(i2c_channel);
    I2C_START(i2c_baseAddr);
    I2C_ACK(i2c_baseAddr,0x08);
    I2C_SEND(i2c_baseAddr,eeprom_addr|EEPROM_WRITE);
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_STAC|I2CONCLR_SIC);
    I2C_ACK(i2c_baseAddr,0x18);
    I2C_SEND(i2c_baseAddr,(uint8_t)(addr>>8));
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);
    I2C_ACK(i2c_baseAddr,0x28);
    I2C_SEND(i2c_baseAddr,(uint8_t)(addr));
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);
    I2C_ACK(i2c_baseAddr,0x28);
    I2C_STOP(i2c_baseAddr);
    I2C_START(i2c_baseAddr);
    I2C_ACK(i2c_baseAddr,0x08);
    I2C_SEND(i2c_baseAddr,eeprom_addr|EEPROM_READ);
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_STAC|I2CONCLR_SIC);
    I2C_ACK(i2c_baseAddr,0x40);
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);
    I2C_ACK(i2c_baseAddr,0x58);
    eeprom_data=I2C_READ(i2c_baseAddr);
    I2C_STOP(i2c_baseAddr);
    //I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)(addr>>8)); /*High addr Half first*/
    //I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)addr); /*low addr Half follow*/
    //eeprom_data = I2C_Master_ReadByte(i2c_channel, eeprom_addr);/*read data*/
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
    uint32_t i2c_baseAddr = 0;
//    uint8_t eeprom_data;
    if (addr & 0xfffe0000){
        return ERCD_ARG_ERR;
    }
    if (addr & 0x00010000){
        eeprom_addr = EEPROM_ADDR|EEPROM_P0;
    }else{
        eeprom_addr = EEPROM_ADDR;
    }
    i2c_baseAddr=I2C_BASE_SEL(i2c_channel);
    I2C_START(i2c_baseAddr);
    I2C_ACK(i2c_baseAddr,0x08);
    I2C_SEND(i2c_baseAddr,eeprom_addr|EEPROM_WRITE);
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_STAC|I2CONCLR_SIC);
    I2C_ACK(i2c_baseAddr,0x18);
    I2C_SEND(i2c_baseAddr,(uint8_t)(addr>>8));
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);
    I2C_ACK(i2c_baseAddr,0x28);
    I2C_SEND(i2c_baseAddr,(uint8_t)(addr));
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);
    I2C_ACK(i2c_baseAddr,0x28);
    I2C_SEND(i2c_baseAddr,data);
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);//must add this to make sure the data clock is right and enough
    I2C_ACK(i2c_baseAddr,0x28);//

    I2C_STOP(i2c_baseAddr);
	Delay_ms(4);//delay to make sure the data has write to the eeprom
    return ERCD_OK;
    //I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)(addr>>8)); /*High addr Half first*/
    //I2C_Master_WriteByte(i2c_channel, eeprom_addr,(uint8_t)addr); /*low addr Half follow*/
    //return I2C_Master_WriteByte(i2c_channel, eeprom_addr,data);
}

/** 
 * I2C_BASE_SEL
 * 
 * @param i2c_channel 
 * 
 * @return 
 */
uint32_t I2C_BASE_SEL(uint8_t i2c_channel)
{
    uint32_t i2c_baseAddr = 0;

	switch (i2c_channel){
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

/** 
 * 
 * 
 * @param i2c_baseAddr 
 * 
 * @return 
 */
ERCD I2C_START(uint32_t i2c_baseAddr)
{
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC));/*clear status*/
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_I2EN);          /*使能I2C作为主机*/
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);          	/*发送一个起始状态位STA*/
	//setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);          	/*发送一个起始状态位STA*/
	return ERCD_OK;
}
/** 
 * 
 * I2C_ACK
 * @param i2c_baseAddr 
 * @param status 
 * 
 * @return 
 */
/*ERCD I2C_ACK(uint32_t i2c_baseAddr,uint8_t status)
{
    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != status);
    return ERCD_OK;
}*/
/** 
 * I2C_STOP
 * 
 * @param i2c_baseAddr 
 * 
 * @return 
 */
ERCD I2C_STOP(uint32_t i2c_baseAddr)
{
    setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位STO*/  /*注意：必须先发数据再清除SI等位*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC|I2CONCLR_AAC);         
    while(getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );
    return ERCD_OK;
}



/*
I2C总线测试EEPROM器件函数:I2CInit,I2CWriteByte,I2CReadByte

*/
/*****************************************************************************
** Function name:		I2CInit
**
** Descriptions:		初始化I2C接口
**
** parameters:
**
** Returned value:		无
**
*****************************************************************************/
void I2CInit(unsigned int fi2c)
{
  PINSEL1 |= 0x1400000;			//选择SDA0,SCL0管脚功能
  I20SCLH = (57600000/fi2c + 1) / 2;	//设置时钟频率
  I20SCLL = (57600000/fi2c) / 2;
  I20CONCLR = (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC);
  I20CONSET = I2CONSET_I2EN;		//使能I2C主机模式
  //setup interrupt...
}
/*****************************************************************************
** Function name:		I2CWriteByte
**
** Descriptions:		向I2C总线写1个字节到AT24C02
**
** parameters:			data:数据
** 				address:写入地址
** Returned value:		无
**
*****************************************************************************/
unsigned char I2CWriteByte(unsigned char sla, unsigned char data,unsigned char address)
{
   int i;
   I20CONCLR = (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC);
   I20CONSET = I2CONSET_I2EN;		//使能I2C主机模式e
   I20CONSET = I2CONSET_STA;		//发送起始状态

   while(I20STAT != 0x8);
   I20DAT = sla;			//设置 SLA+W:1010000+0
   I20CONCLR = (I2CONCLR_SIC|I2CONCLR_STAC);//对SI清零以发送SLA+W

   while(I20STAT != 0x18);
   I20DAT = address;//对EEPROM写入地址
   I20CONCLR = I2CONCLR_SIC;//清零SI位，发送地址值

   while(I20STAT != 0x28);//起始值必为0x28
   I20DAT = data;//写数据到EEPROM
   I20CONCLR = I2CONCLR_SIC;//清零SI位，发送数据
   for(i = 0;i<4000;i++);//等待将数据发送给EEPROM
   Delay_ms(10);
   I20CONCLR = I2CONCLR_SIC;
   I20CONSET = I2CONSET_STO;//置ST0位为1，以停止传输

   for(i = 0;i<8000;i++);

   return 1;
}
/*****************************************************************************
** Function name:		I2CReadByte
**
** Descriptions:		从AT24C02中读取一个字节数据
**
** parameters:			address:读取地址
**
** Returned value:		无
**
*****************************************************************************/
unsigned char I2CReadByte(unsigned char sla, unsigned char address)
{
  char data;

  I20CONCLR = (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC);
  I20CONSET = I2CONSET_I2EN;//使能I2C作为主机

  I20CONSET = I2CONSET_STA;//发送一个起始状态位
  I20CONSET = I2CONSET_STA;//test restart!!

  while(I20STAT != 0x8);//起始字必须为0x8
  I20DAT = sla;//设置 SLA+W
  I20CONCLR = 0x8|0x20;//清零SI位，以传输SLA+W

  while(I20STAT != 0x18);//起始字必须为0x18
  I20DAT = address;//EEPROM将要读取的地址
  I20CONCLR = I2CONCLR_SIC;//清零SI位，以传输地址

  while(I20STAT != 0x28);//起始字必须为0x28
  I20CONSET = I2CONSET_STO;//停止测试写操作
  I20CONCLR = I2CONCLR_SIC;//清零SI位
  I20CONSET = I2CONSET_STA;//发送另一个起始状态

  while(I20STAT != 0x8);
  I20DAT = sla+1;//发送读命令:1010000+1
  I20CONCLR = (I2CONCLR_SIC|I2CONCLR_STAC);//清零SI位，以传输EPROM读命令

  while(I20STAT != 0x40);//起始字0x40
  I20CONCLR = I2CONCLR_SIC;//清零SI位，以读取EEPROM
  while(I20STAT != 0x58);//接受数据，无ACK
  data = I20DAT;//读数据


  I20CONCLR = (I2CONCLR_SIC|I2CONCLR_AAC);
  I20CONSET = I2CONSET_STO;//设置ST0位为1，以停止传输
  return data;
}
/*********************************************************************************
**                            End Of File
*********************************************************************************/
/** 
 * 
 * 
 * @param i2c_baseAddr 
 * 
 * @return 
 */
ERCD I2C_StartTransmission(uint32_t i2c_baseAddr)
{
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC));/*clear status*/
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_I2EN);          /*使能I2C作为主机*/
	setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STA);          	/*发送一个起始状态位STA*/
    I2C_ACK(i2c_baseAddr,0x08);
    return ERCD_OK;
}
/** 
 * 
 * 
 * @param i2c_baseAddr 
 * @param slaveAddr 
 * @param operation 
 * 
 * @return 
 */
ERCD I2C_SendAddr(uint32_t i2c_baseAddr,uint8_t slaveAddr,uint8_t operation)
{
    if (operation == I2C_WRITE_OP){
        I2C_SEND(i2c_baseAddr,slaveAddr|EEPROM_WRITE);
        I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_STAC|I2CONCLR_SIC);
        I2C_ACK(i2c_baseAddr,0x18);
    }else if (operation == I2C_READ_OP){
        I2C_SEND(i2c_baseAddr,slaveAddr|EEPROM_READ);
        I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_STAC|I2CONCLR_SIC);
        I2C_ACK(i2c_baseAddr,0x40);
    }else{
        return ERCD_ARG_ERR;
    }
}
/** 
 * 
 * 
 * @param i2c_baseAddr 
 * @param i2c_data 
 * 
 * @return 
 */
ERCD I2C_SendByte(uint32_t i2c_baseAddr, uint8_t i2c_data)
{
    I2C_SEND(i2c_baseAddr,(uint8_t)(i2c_data));
    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);
    I2C_ACK(i2c_baseAddr,0x28);
}
/** 
 * 
 * 
 * @param i2c_baseAddr 
 * @param ack_bit 
 * 
 * @return 
 */
uint8_t I2C_ReceiveByte(uint32_t i2c_baseAddr, uint8_t ack_bit)
{
    uint8_t eeprom_data;

    I2C_CLEAR_STAT(i2c_baseAddr,I2CONCLR_SIC|I2CONCLR_AAC);
    if (ack_bit & ACK_BIT){
        I2C_ACK(i2c_baseAddr,0x50);
    }else {
        I2C_ACK(i2c_baseAddr,0x58);
    }
    eeprom_data=I2C_READ(i2c_baseAddr);
}
/** 
 * 
 * 
 * @param i2c_baseAddr 
 * 
 * @return 
 */
ERCD I2C_StopTransmission(uint32_t i2c_baseAddr)
{
    setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位STO*/  /*注意：必须先发数据再清除SI等位*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC|I2CONCLR_AAC);         
    while(getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );
    return ERCD_OK;
}
