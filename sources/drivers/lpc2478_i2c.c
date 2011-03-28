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
		//PCONP |= (1 << PCI2C0);
		setregbits(PCONP,1 << PCI2C0,(0xf<<28));
		setregbits(PCLKSEL0,~(3<<14),(I2C_CLK_DIV<<14));
		/* set PIO0.27 and PIO0.28 to I2C0 SDA and SCK  function to 01 on both SDA and SCK.*/
		setregbits(PINSEL1,~(0xf<<22),(0x5<<22));
//		PCLKSEL0 |= ~(3<<14);
//		PCLKSEL0 &= (I2C_CLK_DIV<<14);
//		PINSEL1 |= ~(0xf<<22);/* set PIO0.27 and PIO0.28 to I2C0 SDA and SCK */
//		PINSEL1 &= (0x5<<22);/* function to 01 on both SDA and SCK. */
		break;
	case I2C_CHL1:
		i2c_baseAddr = I2C1_BASE_ADDR;
		//PCONP |= (1 << PCI2C1);
		setregbits(PCONP,1 << PCI2C1,(0xf<<28));
		setregbits(PCLKSEL1,~(3<<6),(I2C_CLK_DIV<<6));
		/* set PIO2.24 and PIO2,25 to I2C1 SDA and SCK  function to 11 on both SDA and SCK.*/
		setregbits(PINSEL4,~(0xf<<28),(0xf<<28));
//		PCLKSEL1 |= ~(3<<6);
//		PCLKSEL1 &= (I2C_CLK_DIV<<6);
//		PINSEL4 |= ~(0xf<<28);/* set PIO2.24 and PIO2,25 to I2C1 SDA and SCK */
//		PINSEL4 &= (0xf<<28);/* function to 11 on both SDA and SCK. */
		break;
	case I2C_CHL2:
		i2c_baseAddr = I2C2_BASE_ADDR;
		//PCONP |= (1 << PCI2C2);
		setregbits(PCONP,1 << PCI2C2,(0xf<<28));
		setregbits(PCLKSEL1,~(3<<20),(I2C_CLK_DIV<<20));
		/* set PIO2.30 and PIO2.30 to I2C2 SDA and SCK  function to 11 on both SDA and SCK.*/
		setregbits(PINSEL5,~(0xf<<28),(0xf<<28));
//		PCLKSEL1 |= ~(3<<20);
//		PCLKSEL1 &= (I2C_CLK_DIV<<20);
//		PINSEL5 &= ~(0xf<<28);/* set PIO2.30 and PIO2.30 to I2C2 SDA and SCK */
//		PINSEL5 |= (0xf<<28);/* function to 11 on both SDA and SCK. */
		break;
	default:
		return ERCD_ARG_ERR;
		break;
	}
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
uint8_t I2C_Master_ReadByte(uint8_t I2cChannel,  uint8_t sla)
{
    uint8_t data;

    I20CONCLR = (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC);
    I20CONSET = I2CONSET_I2EN;//使能I2C作为主机

    I20CONSET = I2CONSET_STA;//发送一个起始状态位
    I20CONSET = I2CONSET_STA;//test restart!!

    while(I20STAT != 0x8)//起始字必须为0x8
    	{
    	data = I20STAT;

    	}
    I20DAT = sla+1;//设置 SLA+R
    I20CONCLR = 0x8|0x20;//清零SI位，以传输SLA+R
          
    while(I20STAT != 0x40);//起始字0x40
    I20CONCLR = I2CONCLR_SIC;//清零SI位，以读取EEPROM
    while(I20STAT != 0x58);//接受数据，无ACK
    data = I20DAT;//读数据
          
   
    I20CONCLR = (I2CONCLR_SIC|I2CONCLR_AAC);        
    I20CONSET = I2CONSET_STO;//设置ST0位为1，以停止传输
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
uint8_t I2C_WriteByte(uint8_t sla, uint8_t data)
{
    uint16_t i = 0;
    
    I20CONCLR = (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC);
    I20CONSET = I2CONSET_I2EN;		//使能I2C主机模式e
    I20CONSET = I2CONSET_STA;		//发送起始状态
      
    while(I20STAT != 0x8);
    I20DAT = sla;			//设置 SLA+W:1010000+0
    I20CONCLR = (I2CONCLR_SIC|I2CONCLR_STAC);//对SI清零以发送SLA+W
     
    while(I20STAT != 0x18);
    I20DAT = data;//写入数据
    I20CONCLR = I2CONCLR_SIC;//清零SI位，发送地址值
   
    while(I20STAT != 0x28);//起始值必为0x28
    I20CONCLR = I2CONCLR_SIC;   
    I20CONSET = I2CONSET_STO;//置ST0位为1，以停止传输   

    for(i = 0;i<8000;i++);
    
    return 1;
}
