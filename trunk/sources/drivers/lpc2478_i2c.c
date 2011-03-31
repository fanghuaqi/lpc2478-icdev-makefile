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
		/* set PIO2.14 and PIO2,15 to I2C1 SDA and SCL  function to 11 on both SDA and SCL.*/
		setregbits(PINSEL4,~(0xf<<28),(0xf<<28));
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
	setregbits(PINSEL1,~(3<<20),(0x0<<20));  	/*设置p0.26为gpio*/
	setregbits(FIO3DIR3,~(1<<2),(0x1<<2));  	/*设置地址脚为输出*/
	//setregbits(FIO3CLR3,0x00,(0x1<<2));			/*设置p0.26输出为低*/
	FIO3CLR3  = 0x04;
    /*--- Clear flags ---*/
	setreg(i2c_baseAddr + I2CONCLR_OFFSET,I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC);

    /*--- Reset registers ---*/
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
 * 
 * 
 * @param sla 
 * 
 * @return 
 */
uint8_t I2C_Master_ReadByte(uint8_t I2cChannel,  uint8_t SlaveAddr)
{
    uint8_t data;
    uint32_t i2c_baseAddr = 0;

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

    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x8)	    	/*起始字必须为0x8*/
    {
    	data = getreg(i2c_baseAddr + I2STAT_OFFSET);
    }
    setreg(i2c_baseAddr + I2DAT_OFFSET, SlaveAddr + I2C_READ);    				/*设置读取的从设备的地址*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_STAC|I2CONCLR_SIC);			/*清除SI,STR,启动串行传输*/
          
    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x40);				    	/*起始字必须为0x8*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI位，准备读取数据*/

    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x58);						/*接收数据，无ACK*/
    data = getreg(i2c_baseAddr + I2DAT_OFFSET) ;								/*读取数据*/

    setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位STO*/  /*注意：必须先发数据再清除SI等位*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC|I2CONCLR_AAC);
    while( getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );

    return data;
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
    uint16_t i = 0;
    uint32_t i2c_baseAddr = 0;

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
      
	while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x8);				    		/*起始字必须为0x8*/
	setreg(i2c_baseAddr + I2DAT_OFFSET, SlaveAddr + I2C_WRITE);    				/*设置读取的从设备的地址*/
	setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_STAC|I2CONCLR_SIC);			/*清除SI,STR,启动串行传输*/
     
	while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x18)
		{
		i = getreg(i2c_baseAddr + I2STAT_OFFSET);						/*等待SLA+W传输完毕*/
		}
    setreg(i2c_baseAddr + I2DAT_OFFSET, I2cData);    								/*设置读取的从设备的地址*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI标志*/
   
    while(getreg(i2c_baseAddr + I2STAT_OFFSET) != 0x28);						/*等待数据传输完毕*/
    setreg(i2c_baseAddr + I2CONSET_OFFSET, I2CONSET_STO);						/*发送停止位*/  /*注意：必须先发数据再清除SI等位*/
    setreg(i2c_baseAddr + I2CONCLR_OFFSET, I2CONCLR_SIC);						/*清除SI位*/

    //for(i = 0;i<8000;i++);
    while( getreg(i2c_baseAddr + I2CONSET_OFFSET) & I2CONSET_STO );				/*等待STO置零*/

    return ERCD_OK;
}
