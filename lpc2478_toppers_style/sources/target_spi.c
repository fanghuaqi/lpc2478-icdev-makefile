
/**
 * =====================================================================================
 * 
 * @Filename  :target_spi.c
 * @Version   : 0.1
 * @Author    :fanghuaqi <578567190@qq.com>
 * @Date      :Wed May  4 15:00:31 2011
 * 
 * @Brief     :
 * 
 * 
 * @Company   :HUST-Renesas Lab
 * @Revision  :
 * ======================================================================================
 * @0.1 Byfanghuaqi  Wed May  4 15:00:31 2011 Create orignal file
 * ======================================================================================
 */

#include "target_spi.h"

/** 
 * 
 * SPIInit Init the spi mode as master or slave
 * @param spi_mode 
 * 
 * @return error code of the initial of the spi mode 
 */
ERCD SPIInit(uint16_t spi_mode,uint32_t spi_clock)
{
    uint8_t spi_clock_count;
    
    /* Enable SPI*/
    sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) | (1<<8));
    /* SPI clock settings*/
    sil_wrw_mem((void *)PCLKSEL0, sil_rew_mem((void *)PCLKSEL0) & (~(0x03<<16)) | (SPI_CLK_DIV<<16));  /*SPI peripheral'clock is 1/2 clock*/
    spi_clock_count = (uint8_t)(SPI_PCLK/spi_clock);
    sil_wrw_mem((void *)S0SPCCR, spi_clock_count);
    /* Port 0.15 SPI SCK, port0.16 uses GPIO SPI_SEL, 
       port0.17 MISO, port0.18 MOSI*/
    sil_wrw_mem((void *)PINSEL0, (sil_rew_mem((void *)PINSEL0) & (~(0x03<<30))) | (0x03<<30));              /*P0.15 as sck*/
    sil_wrw_mem((void *)PINSEL1, (sil_rew_mem((void *)PINSEL0) & (~(0x3c<<0))) | (0x3c<<0));                /*P0.16=>GPIO,P0.17=>MISO,P0.18=>MOSI*/
    sil_wrw_mem((void *)IODIR0, sil_rew_mem((void *)IODIR0) | (1<<16));
}
