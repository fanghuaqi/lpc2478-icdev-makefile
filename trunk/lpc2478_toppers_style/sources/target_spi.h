
/**
 * =====================================================================================
 *
 * @Filename  :target_spi.h
 * @Version   : 0.1
 * @Author    :fanghuaqi <578567190@qq.com>
 * @Date      :Wed May  4 15:10:49 2011
 *
 * @Brief     :some marco of the spi registers bit definition
 *
 *
 * @Company   :HUST-Renesas Lab
 * @Revision  :
 * ======================================================================================
 * @0.1 Byfanghuaqi  Wed May  4 15:10:49 2011 Create orignal file
 * ======================================================================================
 */
#ifndef _TARGET_SPI_H_
#define _TARGET_SPI_H_

#include "lpc2478_inc.h"


/*
 * spi control register bit marco
 * Offset start at 0
 */
#define  SPI_BE            0x00000004                    /*control the bits that spi sends per transfer is 8 or more*/
#define  SPI_BE_OFFSET     2                             /*the offset of BE bit at SPI control regsiter*/
#define  SPI_CPHA          0x00000008                    /*spi clock phase control bit*/
#define  SPI_CPHA_OFFSET   3                             /*the offset of CPHA bit at SPI control regsiter*/
#define  SPI_CPOL          0x00000010                    /*clock polarity control*/
#define  SPI_CPOL_OFFSET   4                             /*the offset of CPOL bit at SPI control regsiter*/
#define  SPI_MSTR          0x00000020                    /*Master mode select bit*/
#define  SPI_MSTR_OFFSET   5                             /*the offset of MSTR bit at SPI control regsiter*/
#define  SPI_LSBF          0x00000040                    /*LSB or MSB control bit*/
#define  SPI_LSBF_OFFSET   6                             /*the offset of LSBF bit at SPI control regsiter*/
#define  SPI_SPIE          0x00000080                    /*serial peripherial interrupt enable bit*/
#define  SPI_SPIE_OFFSET   7                             /*the offset of SPIE bit at SPI control regsiter*/
#define  SPI_BITS          0x00000f00                    /*this filed control the number of bits per transfer*/
#define  SPI_BITS_OFFSET   8                             /*the offset of BITS bit at SPI control regsiter*/


/*
 * some important bit marco of spi control
 */
#define  SPI_BE_8Bits      0x00000000                    /*8bit per spi transfer*/
#define  SPI_BE_8BitsMore  0x00000004                    /*not less than 8bits per spi transfer*/
#define  SPI_CPHA_SF       0x00000000                    /*data Sampled on the First clock edge of SCK*/
#define  SPI_CPHA_SS       0x00000008                    /*data Sampled on the Second clock edge of SCK*/
#define  SPI_CPOL_SCKH     0x00000000                    /*SCK is active High*/
#define  SPI_CPOL_SCKL     0x00000010                    /*SCK is active Low*/
#define  SPI_MSTR_SLAVE    0x00000000                    /*spi operates in slave mode*/
#define  SPI_MSTR_MASTER   0x00000020                    /*spi operates in master mode*/
#define  SPI_LSBF_MSB      0x00000000                    /*spi data transfer MSB(bit 7) first*/
#define  SPI_LSBF_LSB      0x00000040                    /*spi data transfer LSB(bit 0) first*/
#define  SPI_SPIE_DE       0x00000000                    /*spi interrupt is inhibited(disabled)*/
#define  SPI_SPIE_EN       0x00000080                    /*spi interrupt is enabled each time SPIF or MODF bits activate*/
#define  SPI_BITS_8        0x00000800                    /*8 bits per transfer*/
#define  SPI_BITS_9        0x00000900                    /*9 bits per transfer*/
#define  SPI_BITS_10       0x00000A00                    /*10 bits per transfer*/
#define  SPI_BITS_11       0x00000B00                    /*11 bits per transfer*/
#define  SPI_BITS_12       0x00000C00                    /*12 bits per transfer*/
#define  SPI_BITS_13       0x00000D00                    /*13 bits per transfer*/
#define  SPI_BITS_14       0x00000E00                    /*14 bits per transfer*/
#define  SPI_BITS_15       0x00000F00                    /*15 bits per transfer*/
#define  SPI_BITS_16       0x00000000                    /*16 bits per transfer*/

/*
 * the usual used spi control register macros
 */
#define  SPI_MODE_MASTER   SPI_MSTR_MASTER|SPI_SPIE_DE|SPI_BE_8BitsMore          /*master,no interrupt,>=8bits,reset as default*/
#define  SPI_MODE_SLAVE    SPI_MSTR_SLAVE|SPI_SPIE_DE|SPI_BE_8BitsMore           /*slave,no interrupt,>=8bits,reset as default*/
#define  SPI_PCLK_DIV      2
#define  SPI_PCLK          36000000L
/*
 * spi status bits macro and its offset
 * offset start at 0
 */
#define  SPI_ABRT          0x00000008                    /*slave abort bit,read spi status reg clear it*/
#define  SPI_ABRT_OFFSET   3                             /*the offset of ABRT in spi status register*/
#define  SPI_MODF          0x00000010                    /*mode fault bit,read spi status reg and write spi control reg clear it */
#define  SPI_MODF_OFFSET   4                             /*the offset of MODF in spi status register*/
#define  SPI_ROVR          0x00000020                    /*read overrun bit,read spi status register clear it*/
#define  SPI_ROVR_OFFSET   5                             /*the offset of ROVR in spi status register*/
#define  SPI_WCOL          0x00000040                    /*write collision bit,read spi status reg and access spi data reg clear it*/
#define  SPI_WCOL_OFFSET   6                             /*the offset of WCOL in spi status register*/
#define  SPI_SPIF          0x00000080                    /*spi transfer complete flag ,clear as the WCOL bit*/


/*
 * SPI interrupt flag bit macro and its offset
 */
#define  SPI_INTF          0x00000000                    /*spi interrupt flag,clear by write 1 to this bit*/
#define  SPI_INTF_OFFSET   0                             /*the offset of spi interrupt flag in spi interrupt register*/

#endif
