/*
 * =====================================================================================
 *
 *       Filename:  target_i2c.c
 *
 *    Description:  i2c driver
 *
 *        Version:  0.1
 *        Created:  2011-5-23 16:46:08
 *
 *         Author:  Ren Wei , renweihust@gmail.com
 *        Company:  HUST-Renesas Lab
 *       Revision:  
 * =====================================================================================
 *	@0.1 	Ren Wei	2011-5-23	create orignal file
 * =====================================================================================
 */
#include "target_i2c.h"
#include "kernel_cfg.h"



/*clear i2c status*/
#define I2C_CLEAR_STAT(i2c_base_addr,I2C_STAT)     sil_wrw_mem((void *)((i2c_base_addr) + I2CONCLR_OFFSET),(I2C_STAT))
/*send 1 byte i2c data*/
#define I2C_SEND(i2c_base_addr,I2C_DAT)            sil_wrw_mem((void *)((i2c_base_addr) + I2DAT_OFFSET),(I2C_DAT))
/*read 1 byte i2c data*/
#define I2C_READ(i2c_base_addr)                    sil_rew_mem((void *)((i2c_base_addr) + I2DAT_OFFSET))
/*i2c ack*/
#define I2C_ACK(i2c_base_addr, status)             while(sil_rew_mem((void *)(i2c_base_addr + I2STAT_OFFSET)) != (status))


#define I2C_MASTER_START 		0x08	/* start condition */
#define I2C_MASTER_RS			0x10	/* repeat condition */
#define I2C_MASTER_W_ACK		0x18	/* SLA+W has been transmitted and ACK received */
#define I2C_MASTER_W_NACK		0x20	/* SLA+W has been transmitted and NOT ACK received */
#define I2C_MASTER_TX_ACK		0x28	/* one byte has been transmitted and ACK received */
#define I2C_MASTER_TX_NACK		0x30	/* one byte has been transmitted and NOT ACK received */
#define I2C_MASTER_LOST			0x38	/* Arbitration lost in SLA+R/W or data bytes */
#define I2C_MASTER_R_ACK		0x40	/* SLA+R has been transmitted and ACK received */
#define I2C_MASTER_R_NACK		0x48	/* SLA+R has been transmitted and NOT ACK received */
#define I2C_MASTER_RX_ACK		0x50	/* one byte has been received and ACK received */
#define I2C_MASTER_RX_NACK		0x58	/* one byte has been received and NOT ACK received */


#define I2C_SLAVE_W_ACK			0x60	/* SLA+w has been received. ACK returned */
#define I2C_SLAVE_LOST_W		0x68	/* Aribitration lost and  SLA+W has been received. ACK returned */
#define I2C_SLAVE_CALL			0x70	/* General call address has been received. ACK returned */
#define I2C_SLAVE_LOST_CALL		0x78    /* LOST+CALL */
#define I2C_SLAVE_RX_ACK		0x80	/* one byte has been received and ACK returned */
#define I2C_SLAVE_RX_NACK		0x88	/* one byte has been received and NOT ACK returned */
#define I2C_SLAVE_CALL_RX_ACK	0x90
#define I2C_SLAVE_CALL_RX_NACK	0x98
#define I2C_SLAVE_STOP_RS		0xA0	/* STOP or RS has been received */
#define I2C_SLAVE_R_ACK			0xA8
#define I2C_SLAVE_LOST_R		0xB0	/* Aribitration lost and  SLA+R has been received. ACK returned */
#define I2C_SLAVE_TX_ACK		0x80	/* one byte has been transmitted and ACK returned */
#define I2C_SLAVE_TX_NACK		0x88	/* one byte has been transmitted and NOT ACK returned */

typedef struct i2c_initialization_block
{
	uint32_t base_addr;	/* base reg address */
	unsigned int intno; /* int no */
	ID	i2c_flgid;				
	ID	i2c_semid;		/* semphore for device */	
} I2C_INIB;

typedef struct i2c_control_block {
	const I2C_INIB *p_i2c_inib;

	bool_t openflag;
	bool_t errorflag;
	uint8_t mode;
	uint8_t slave_address;
	uint8_t *data_buffer;
	unsigned int xfer_size;
	unsigned int xfer_count;

} I2C_CB;


const I2C_INIB i2c_inib_table[TNUM_I2C] = {
	{ I2C0_BASE_ADDR, INTNO_I2C0,
	  I2C_FLG0, I2C_SEM0 },
#if TNUM_I2C >= 2
	{ I2C1_BASE_ADDR, INTNO_I2C1,
	  I2C_FLG1, I2C_SEM1 },
#endif 
#if TNUM_I2C >= 3
	{ I2C2_BASE_ADDR, INTNO_I2C2,
	  I2C_FLG2, I2C_SEM2 },
#endif
};

static I2C_CB i2c_cb_table[TNUM_I2C];

#define SVC(exp, ercd_exp) \
				{ if ((exp) < 0) { ercd = (ercd_exp); goto error_exit; }}


static ER
gen_ercd_sys(I2C_CB *p_i2c_cb)
{
	p_i2c_cb->errorflag = true;
	return(E_SYS);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_hardware_init
 *  Description:  init the hardware of i2c 
 *	Parameters:
 *			channel, the i2c channel to be initialized
 *			mode,	 SLAVE or MASTER
 *			clk,	 i2c clk
 *			address, address for SLAVE
 * 	return value:
 * 			error code
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
static ER i2c_hardware_init(ID channel, uint32_t mode, uint32_t clk, uint8_t address)
{
	uint32_t i2c_base_addr = 0;
	uint32_t i2c_clk_temp = 0;

	switch (channel) {
		case I2C_CHL0:
			i2c_base_addr = I2C0_BASE_ADDR;
			/*power on iic*/
			sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP) | (1<<PCI2C0));
			/*i2c clock select*/
			sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0) & (~(3<<14)));
			sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0) | (I2C_CLK_DIV<<14));
			/* set PIO0.27 and PIO0.28 to I2C0 SDA and SCL */
			sil_wrw_mem((void *)PINSEL1,sil_rew_mem((void *)PINSEL1) & (~(0xf<<22)));
			sil_wrw_mem((void *)PINSEL1,sil_rew_mem((void *)PINSEL1) | (0x5<<22));
			/* neither pull-up nor pull-down*/
			sil_wrw_mem((void *)PINMODE1,sil_rew_mem((void *)PINMODE1) & (~(0xf<<22)));
			sil_wrw_mem((void *)PINMODE1,sil_rew_mem((void *)PINMODE1) | (0xa<<22));
			break;
		case I2C_CHL1:
			i2c_base_addr = I2C1_BASE_ADDR;
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
			i2c_base_addr = I2C2_BASE_ADDR;
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
			return E_OBJ;
			break;	
	}

	 /*Clear flags*/
	sil_wrw_mem((void *)(i2c_base_addr + I2CONCLR_OFFSET), (I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC) );

    /*clock registers set*/
	i2c_clk_temp = I2C_PCLK / clk;
	
	sil_wrw_mem((void *)(i2c_base_addr + I2SCLH_OFFSET), ((i2c_clk_temp+1)>>1));
	sil_wrw_mem((void *)(i2c_base_addr + I2SCLL_OFFSET), ((i2c_clk_temp)>>1));

	/*Mode select: Master or Slave*/
    if (mode == I2CSLAVE) {/*Slave Mode*/
    	/*slave address set*/
    	sil_wrw_mem((void *)(i2c_base_addr + I2ADR_OFFSET), address);
    }

	return E_OK;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_start
 *  Description:  send start condition
 *	Parameters:
 *			i2c_base_addr, base
 * 	return value:
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
Inline void i2c_start(uint32_t i2c_base_addr)
{
	/*clear all the status*/
	I2C_CLEAR_STAT(i2c_base_addr, (I2CONCLR_STAC|I2CONCLR_SIC|I2CONCLR_AAC));
	/*enable i2c */
	sil_wrw_mem((void *)(i2c_base_addr + I2CONSET_OFFSET), I2CONSET_I2EN);
	/*send a START condition*/
	sil_wrw_mem((void *)(i2c_base_addr + I2CONSET_OFFSET), I2CONSET_STA);
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_initialize
 *  Description:  i2c initialization
 *	Parameters:
 * 	return value:
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
void i2c_initialize(intptr_t exinf)
{
	uint_t i;
	I2C_CB *p_i2c_cb;

	for (p_i2c_cb = i2c_cb_table, i = 0; i < TNUM_I2C; p_i2c_cb++, i++) {
		p_i2c_cb->p_i2c_inib = &(i2c_inib_table[i]);
		p_i2c_cb->openflag = false;
		p_i2c_cb->errorflag = false;
	}
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_open
 *  Description:  open an i2c channel
 *	Parameters:
 *			channel, i2c channel to be initialized
 *			mode,	SLAVE or MASTER
 *			clk,	i2c clk
 *			address, SLAVE address
 * 	return value:
 * 		error code
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
ER i2c_open(ID channel, uint32_t mode, uint32_t clk, uint8_t address)
{
	I2C_CB *p_i2c_cb;
	ER ercd;

	if (sns_dpn()) {
		return (E_CTX);
	}

	/* parameters check */
	if (!(0 <= channel && channel < TNUM_I2C)) {
		return (E_ID);				/* check channel no */
	}

	if (clk > (I2C_PCLK/2)) {
		return (E_PAR);
	}
	
	p_i2c_cb = &(i2c_cb_table[channel]);

	/* disable dispatch */
	SVC(dis_dsp(), gen_ercd_sys(p_i2c_cb));

	if (p_i2c_cb->openflag) {
		ercd = E_OBJ;  /* already open? */
	}
	else {

		p_i2c_cb->mode = mode;
		p_i2c_cb->xfer_size = 0;
		p_i2c_cb->xfer_count = 0;
		p_i2c_cb->data_buffer = NULL;

		if (loc_cpu() < 0) {
			ercd = E_SYS;
			goto error_exit_enadsp;
		}

		if (i2c_hardware_init(channel, mode, clk, address) == E_OK) {
			p_i2c_cb->openflag = true;
			p_i2c_cb->errorflag = false;
			ercd = E_OK;
			ena_int(p_i2c_cb->p_i2c_inib->intno);
		} else {
			ercd = E_OBJ;
		}

		if (unl_cpu() < 0) {
			p_i2c_cb->errorflag = true;
			ercd = E_SYS;
			goto error_exit_enadsp;
		}
	}

error_exit_enadsp:
	SVC(ena_dsp(), gen_ercd_sys(p_i2c_cb));
error_exit:
	return(ercd);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_master_read
 *  Description:  read as I2C master
 *	Parameters:
 *			channel, i2c channel to read
 *			slave_address, the slave device's address
 *			buf,	buffer to store read data
 *			len, 	length
 *			mode,  polling or WAIT?
 * 	return value:
 * 		errorcode or already number of already read data
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
ER i2c_master_read(ID channel, uint8_t slave_address, uint8_t *buf, uint32_t len, uint8_t mode)
{
	I2C_CB *p_i2c_cb;
	ER ercd;
	uint32_t i2c_base_addr = 0;
	uint16_t rea_cnt = 0;

	if (sns_dpn()) {
		return (E_CTX);
	}
		/* parameters check */
	if (!(0 <= channel && channel < TNUM_I2C)) {
		return (E_ID);				/* check channel no */
	}

	if (len == 0 || buf == NULL) {
		return (E_PAR);
	}

	
	p_i2c_cb = &(i2c_cb_table[channel]);

	if (!(p_i2c_cb->openflag)) {
		return (E_OBJ);
	}

	if (p_i2c_cb->errorflag) {
		return (E_SYS);
	}
	
	/* get the device semaphore */
	SVC(wai_sem(p_i2c_cb->p_i2c_inib->i2c_semid), gen_ercd_sys(p_i2c_cb));

	i2c_base_addr = p_i2c_cb->p_i2c_inib->base_addr;

	if (mode == I2C_WAIT) {
			
		p_i2c_cb->data_buffer = buf;
		p_i2c_cb->xfer_size = len;
		p_i2c_cb->xfer_count = 0;
		p_i2c_cb->slave_address = (slave_address + I2C_WRITE_OP);
		
		/* enbable i2c communication and enable int */	
		i2c_start(i2c_base_addr);
		
		if (wai_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_XFER_DONE | I2C_XFER_ERR, TWF_ORW, &stat) < 0) {
			ercd = E_SYS;
			goto error_release;
		}

		if (stat & I2C_XFER_ERR) {
			DBG("tansfer error");
			if (p_i2c_cb->xfer_count > 0) {
				ercd = p_i2c_cb->xfer_count;
			} else {
				ercd = E_OBJ;
			}
		} else {
			ercd = len;
		}
	} else { /* polling mode */
		i2c_start(i2c_base_addr);
    	I2C_ACK(i2c_base_addr, I2C_MASTER_START);
    	/*Transmit SLA+R :slave address + Read Operation Bit*/
    	I2C_SEND(i2c_base_addr,(slave_address + I2C_READ_OP));
    	I2C_CLEAR_STAT(i2c_base_addr, (I2CONCLR_STAC | I2CONCLR_SIC)); /*clear SI and STR bit*/
    	I2C_ACK(i2c_baseAddr, I2C_MASTER_R_ACK);
		sil_wrw_mem((void *)(i2c_base_addr + I2CONSET_OFFSET), I2CONSET_AA);
    	/*prepare to read data from i2c bus*/
    	I2C_CLEAR_STAT(i2c_base_addr, I2CONCLR_SIC);    /*clear SI bit to prepare to receive data*/
		while (rea_cnt < (len-1)) {
			I2C_ACK(i2c_base_addr, I2C_MASTER_RX_ACK);  /* wait data to be received with ACK */
			buf[rea_cnt] = I2C_READ(i2c_base_addr); /*read data*/
			I2C_CLEAR_STAT(i2c_base_addr, I2CONCLR_SIC); /*clear SI flag*/
			rea_cnt++;
		}
		I2C_CLEAR_STAT(i2c_base_addr, I2CONCLR_AAC); /* not ack at last data */
		I2C_ACK(i2c_base_addr, I2C_MASTER_RX_NACK);/*wait data to be received with NO ACK*/
		buf[rec_cnt] = I2C_READ(i2c_base_addr); /*read data*/
    	/*Transmit STOP and AA bits*/
    	I2C_STOP(i2c_base_addr);
		ercd = len;	
	}

error_release:
	SVC(sig_sem(p_i2c_cb->p_i2c_inib->i2c_semid), gen_ercd_sys(p_i2c_cb));
error_exit:
	return ercd;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_master_write
 *  Description:  write data as master
 *	Parameters:
 *			channel, i2c channel to write data
 *			slave_address, slave device's address
 *			buf, 	data to write
 *			len,	length
 *			mode, 	polling or wait
 * 	return value:
 * 		errorcode or number of already written data
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
ER i2c_master_write(ID channel, uint8_t slave_address, uint8_t *buf, uint32_t len, uint8_t mode)
{
	I2C_CB *p_i2c_cb;
	ER ercd;
	uint32_t i2c_base_addr = 0;
	uint16_t wri_cnt = 0;
	FLGPTN	stat;

	if (sns_dpn()) {
		return (E_CTX);
	}
	
	/* parameters check */
	if (!(0 <= channel && channel < TNUM_I2C)) {
		return (E_ID);				/* check channel no */
	}

	if (len == 0 || buf == NULL) {
		return (E_PAR);
	}

	
	p_i2c_cb = &(i2c_cb_table[channel]);

	if (!(p_i2c_cb->openflag)) {
		return (E_OBJ);
	}

	if (p_i2c_cb->errorflag) {
		return (E_SYS);
	}

	/* get the device semaphore */
	SVC(wai_sem(p_i2c_cb->p_i2c_inib->i2c_semid), gen_ercd_sys(p_i2c_cb));
	
	i2c_base_addr = p_i2c_cb->p_i2c_inib->base_addr;


	if (mode == I2C_WAIT) {
		p_i2c_cb->data_buffer = buf;
		p_i2c_cb->xfer_size = len;
		p_i2c_cb->xfer_count = 0;
		p_i2c_cb->slave_address = (slave_address + I2C_WRITE_OP);
		// enbable i2c communication and enable int
		i2c_start(i2c_base_addr);

		if (wai_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_XFER_DONE | I2C_XFER_ERR, TWF_ORW, &stat) < 0) {
			ercd = E_SYS;
			goto error_release;
		}

		if (stat & I2C_XFER_ERR) {
			DBG("tansfer error");
			if (p_i2c_cb->xfer_count > 0) {
				ercd = p_i2c_cb->xfer_count;
			} else {
				ercd = E_OBJ;
			}

		} else {
			ercd = len;
		}
		
	} else { /* polling mode */
		i2c_start(i2c_base_addr);
    	I2C_ACK(i2c_base_addr, I2C_MASTER_START);
    	/*Transmit SLA+W :slave address + Write Operation Bit*/
    	I2C_SEND(i2c_base_addr,(slave_address + I2C_WRITE_OP));
    	I2C_CLEAR_STAT(i2c_base_addr, (I2CONCLR_STAC | I2CONCLR_SIC)); /*clear SI and STR bit*/
    	I2C_ACK(i2c_base_addr, I2C_MASTER_W_ACK);
		while (wri_cnt < len) {
			I2C_SEND(i2c_base_addr, buf[wri_cnt]); /*write data*/
			I2C_CLEAR_STAT(i2c_base_addr, I2CONCLR_SIC); /*clear SI flag*/
			wri_cnt++;
			I2C_ACK(i2c_base_addr, I2C_MASTER_TX_ACK);
    	}
    	/*Transmit STOP and AA bits*/
    	I2C_STOP(i2c_base_addr);   
		ercd = len;	
	}

error_release:
	SVC(sig_sem(p_i2c_cb->p_i2c_inib->i2c_semid), gen_ercd_sys(p_i2c_cb));
error_exit:
	return ercd;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_close
 *  Description:  close i2c channel
 *	Parameters:
 *			channel, i2c channel to close
 * 	return value:
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
ER i2c_close(ID channel)
{
	I2C_CB *p_i2c_cb;
	ER ercd;
	uint32_t i2c_base_addr = 0;

	if (sns_dpn()) {
		return (E_CTX);
	}
		/* parameters check */
	if (!(0 <= channel && channel < TNUM_I2C)) {
		return (E_ID);				/* check channel no */
	}

	p_i2c_cb = &(i2c_cb_table[channel]);

	if (!(p_i2c_cb->openflag)) {
		return (E_OBJ);
	}

		/* get the device semaphore */
	SVC(wai_sem(p_i2c_cb->p_i2c_inib->i2c_semid), gen_ercd_sys(p_i2c_cb));	
	
	i2c_base_addr = p_i2c_cb->p_i2c_inib->base_addr;
	
	p_i2c_cb->xfer_size = 0;
	p_i2c_cb->xfer_count = 0;
	p_i2c_cb->data_buffer = NULL;
	p_i2c_cb->slave_address = 0;
	p_i2c_cb->openflag = false;
	p_i2c_cb->errorflag = false;

	I2C_CLEAR_STAT(i2c_base_addr,  I2CONCLR_I2ENC); /*disable i2c channel*/

	ercd = E_OK;
/* power off channel to save power */
	switch (channel) {
		case I2C_CHL0:
			sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP) & ~(1<<PCI2C0));
			break;
		case I2C_CHL1:
			sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP) & ~(1<<PCI2C1));
			break;
		case I2C_CHL2:
			sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP) & ~(1<<PCI2C2));
			break;
		default:
			ercd = E_OBJ;
			break;
	}
	dis_int(p_i2c_cb->p_i2c_inib->intno);
	SVC(sig_sem(p_i2c_cb->p_i2c_inib->i2c_semid), gen_ercd_sys(p_i2c_cb));
error_exit:
	return ercd;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  i2c_int_isr
 *  Description:  i2c interrupt service routine
 *	Parameters:	
 *		channel, i2c channel
 * 	return value:
 * 		none
 *  Created:  2011-5-27 by Ren Wei
 * =====================================================================================
 */
static void i2c_int_isr(ID channel)
{
	uint8_t stat;
	I2C_CB *p_i2c_cb;
	uint32_t i2c_base_addr;

	p_i2c_cb = &(i2c_cb_table[channel]);

	i2c_base_addr = p_i2c_cb->p_i2c_inib->base_addr;
	
	stat = sil_rew_mem((void *)(i2c_base_addr + I2STAT_OFFSET)) & 0xFF;
	i_unlock_cpu();

	if (p_i2c_cb->mode != I2CSLAVE) {
		switch (stat) {
			case I2C_MASTER_START:	/* start condition */
				/*Clear flags*/
				I2C_SEND(i2c_base_addr, p_i2c_cb->slave_address);
				break;
			case I2C_MASTER_RS:		/* repeated start */	
				I2C_SEND(i2c_base_addr, p_i2c_cb->slave_address);
				p_i2c_cb->stat = stat;
				break;
			case I2C_MASTER_W_ACK:	/* SLA+W ack */
				I2C_SEND(i2c_base_addr, p_i2c_cb->data_buffer[p_i2c_cb->xfer_count]);
				p_i2c_cb->stat = stat;
				p_i2c_cb->retry = 0;
				break;
			case I2C_MASTER_W_NACK: /* SLA+W not ack, resend SLA+W */
				p_i2c_cb->retry++;
				if (p_i2c_cb->retry > I2C_RETRY_ADDR) {
					p_i2c_cb->retry = 0;		/* device not responde to SLA+W */
					I2C_STOP(i2c_base_addr);	/* stop transfer */
				 	iset_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_ERROR_ADDR);	
				} else {
					I2C_SEND(i2c_base_addr, p_i2c_cb->slave_address); /* resend SLA+W */
				}
				break;
			case I2C_MASTER_TX_ACK: /* data ack */
				p_i2c_cb->retry = 0;
				if (p_i2c_cb->xfer_count < p_i2c_cb->xfer_size) {
					p_i2c_cb->xfer_count++;
					I2C_SEND(i2c_base_addr, p_i2c_cb->data_buffer[p_i2c_cb->xfer_count]);
				} else { /* xfer finished */
					p_i2c_cb->xfer_count = 0;
					p_i2c_cb->xfer_size = 0;
					I2C_STOP(i2c_base_addr);
					iset_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_XFER_DONE);	
				}
				break;
			case I2C_MASTER_TX_NACK: /* data not ack */
				p_i2c_cb->retry++;
				if (p_i2c_cb->retry > I2C_RETRY_DAT) {
					p_i2c_cb->retry = 0;
					iset_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_ERROR_DAT);
					I2C_STOP(i2c_base_addr);	/* stop transfer */   
				} else {
					I2C_SEND(i2c_base_addr, p_i2c_cb->data_buffer[p_i2c_cb->xfer_count]); /* whether need to resend data ?*/
				}
				break;
			case I2C_MASTER_R_ACK:
				p_i2c_cb->retry = 0;
				sil_wrw_mem((void *)(i2c_base_addr + I2CONSET_OFFSET), I2CONSET_AA); /* ack after data received */
				break;
			case I2C_MASTER_R_NACK:
				p_i2c_cb->retry++;
				if (p_i2c_cb->retry > I2C_RETRY_ADDR) {
					p_i2c_cb->retry = 0;
					I2C_STOP(i2c_base_addr);	/* stop transfer */
				 	iset_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_ERROR_ADDR);	
				} else {
					I2C_SEND(i2c_base_addr, p_i2c_cb->slave_address); /* resend address+op code */
				}
			case I2C_MASTER_RX_ACK:
				p_i2c_cb->data_buffer[p_i2c_cb->xfer_count] = I2C_READ(i2c_base_addr);
				p_i2c_cb->xfer_count++;
				if (p_i2c_cb->xfer_count >= (p_i2c_cb->xfer_size -1)) {
					I2C_CLEAR_STAT(i2c_base_addr, I2CONCLR_AAC);
				} 
				break;
			case I2C_MASTER_RX_NACK:
				p_i2c_cb->xfer_count = 0;
				p_i2c_cb->xfer_size = 0;
				p_i2c_cb->data_buffer[p_i2c_cb->xfer_count] = I2C_READ(i2c_base_addr);
				iset_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_XFER_DONE);	
				I2C_STOP(i2c_base_addr);
				break;
			case I2C_MASTER_LOST:
				iset_flg(p_i2c_cb->p_i2c_inib->i2c_flgid, I2C_XFER_LOST);
				break;
			default:
				break;
		}
		I2C_CLEAR_STAT(i2c_base_addr, I2CONCLR_SIC); /*clear SI flag*/
	} else { /* slave mode */
			/* to do */
	}
}


void i2c0_int_handler(void)
{
	i2c_int_isr(I2C_CHL0);
}

#if TNUM_I2C >= 2
void i2c1_int_handler(void)
{
	i2c_int_isr(I2C_CHL1);
}
#endif

#if TNUM_I2C >= 3
void i2c2_int_handler(void)
{
	i2c_int_isr(I2C_CHL2);
}
#endif
