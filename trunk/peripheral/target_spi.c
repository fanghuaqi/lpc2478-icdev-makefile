/*
 * =====================================================================================
 *
 *       Filename:  target_spi.c
 *
 *    Description:
 *
 *        Version:  0.1
 *        Created:  2011-5-7 19:58:25
 *
 *         Author:  Ren Wei , renweihust@gmail.com
 *        Company:  HUST-Renesas Lab
 *       Revision:
 * =====================================================================================
 *	@0.1 	Ren Wei	2011-5-7	create orignal file
 * =====================================================================================
 */

#include "LPC24xx.h"
#include "target_spi.h"
#include <sil.h>
#include <kernel.h>
#include "kernel_cfg.h"
#include "target_config.h"



/* Delay count after each write */
#define DELAY_COUNT		10

#define SPI0_INT_FLAG	0x01

/* SPI select pin */
#define SPI0_SEL		(1 << 16)		/* P0.16 is used as GPIO, CS signal to FPGA SPI0 */

#define ABRT		(1 << 3)		/* SPI0 interrupt status */
#define MODF		(1 << 4)
#define ROVR		(1 << 5)
#define WCOL		(1 << 6)
#define SPIF		(1 << 7)

/* SPI 0 PCR register */
#define SPI0_BE		0x04
#define SPI0_CPHA	0x08
#define SPI0_CPOL	0x10
#define SPI0_MSTR	0x20
#define SPI0_LSBF	0x40
#define SPI0_SPIE	0x80


#define SPI0_PCLK	72000000L


#define SPI0_XFER_DONE	0x1
#define SPI0_XFER_ERROR	0x2


#define SEL_SLAVE()	 	sil_wrw_mem((void *)IOCLR0, sil_rew_mem((void *)IOCLR0) | SPI0_SEL)
#define DIS_SEL_SLAVE() sil_wrw_mem((void *)IOSET0, sil_rew_mem((void *)IOSET0) | SPI0_SEL)

/* spi initialize block */
typedef struct spi_device_init_block {
	ID			spi_semid;			/* device semaphore */
	ID			xfer_flgid;			/* tansfer flag id */
} SPI_INIB;

/* spi control block */
typedef struct spi_ctrl_block {
	const SPI_INIB	*p_spi_inib;
	uint32_t	max_speed_hz;		/* max speed */
	uint32_t	mode;				/* spi mode */
	bool_t		openflag;			/* flag for open */
	bool_t		errorflag;			/* error flag */

	bool_t		rcv_ena;			/* rcv enable */
	uint_t		xfer_size;			/* tansfer size */

	const uint16_t 	*snd_buffer;		/* point to send buffer */
	uint16_t	*rcv_buffer;		/* point to receive buffer */
} SPI_CB;


static const SPI_INIB	spi_inib = {
	  	SPI0_SEM, SPI0_FLG,
};

static SPI_CB spi_cb;


#define SVC(exp, ercd_exp) \
				{ if ((exp) < 0) { ercd = (ercd_exp); goto error_exit; }}



static ER gen_ercd_sys(SPI_CB *p_spi_cb)
{
	p_spi_cb->errorflag = true;
	return(E_SYS);
}


static ER gen_ercd_wait(ER rercd, SPI_CB *p_spi_cb)
{
	switch (MERCD(rercd)) {
	case E_RLWAI:
	case E_DLT:
		return(rercd);
	default:
		p_spi_cb->errorflag = true;
		return(E_SYS);
	}
}


void lpc2478_spi_initialize(intptr_t exinf)
{
	spi_cb.p_spi_inib = &spi_inib;
	spi_cb.openflag = false;
}



ER lpc2478_spi_opn_dev(uint32_t speed, uint32_t mode)
{
	SPI_CB	*p_spi_cb;
	ER	ercd;

	if (sns_dpn()) {
		return (E_CTX);
	}

	p_spi_cb = &spi_cb;

	if ((speed > SPI0_PCLK/8) || (SPI0_PCLK/2 % speed)) {
		return (E_PAR);
	}
	SVC(loc_cpu(), gen_ercd_sys(p_spi_cb));

	if (p_spi_cb->openflag) {
		ercd = E_OBJ;
	}
 	else {
		/* power the spi module */
		sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) |(1 << 8));
		/* set SPI PCLK */
		sil_wrw_mem((void *)PCLKSEL0, sil_rew_mem((void *)PCLKSEL0) & ~(3 << (PCLK_SPI*2)));
		sil_wrw_mem((void *)PCLKSEL0, sil_rew_mem((void *)PCLKSEL0) | (1 << (PCLK_SPI*2)));
		/* clear command register */
  		sil_wrw_mem((void *)S0SPCR, 0x00);
  		/* Port 0.15 SPI SCK, port0.16 uses GPIO SPI_SEL,
  		   port0.17 MISO, port0.18 MOSI */
  		sil_wrw_mem((void *)PINSEL0, sil_rew_mem((void *)PINSEL0) | 0xC0000000);
		sil_wrw_mem((void *)PINSEL1, sil_rew_mem((void *)PINSEL1) & ~0x00000003);
  		sil_wrw_mem((void *)PINSEL1, sil_rew_mem((void *)PINSEL1) | 0x0000003C);

		/* set SSEL= high */
  		sil_wrw_mem((void *)IODIR0, sil_rew_mem((void *)IODIR0) | SPI0_SEL);
  		sil_wrw_mem((void *)IOSET0, sil_rew_mem((void *)IOSET0) | SPI0_SEL);

		sil_wrw_mem((void *)S0SPCCR, SPI0_PCLK / speed);
		sil_wrw_mem((void *)S0SPCR, mode);

		p_spi_cb->openflag = true;
		p_spi_cb->mode = mode;
		p_spi_cb->max_speed_hz = speed;

		p_spi_cb->rcv_ena = false;
		p_spi_cb->xfer_size = 0;

		ercd = E_OK;
	}
	SVC(unl_cpu(), gen_ercd_sys(p_spi_cb));
error_exit:
	return (ercd);
}


ER lpc2478_spi_wri_dat(const uint16_t *buf, uint32_t len)
{
	ER ercd, rercd;
	SPI_CB	*p_spi_cb;
	uint_t 	wricnt = 0U;
	FLGPTN	result;


	if (len == 0 || buf == NULL) {
		ercd = E_PAR;
		return ercd;
	}

	if (sns_dpn()) {
		return (E_CTX);
	}

	p_spi_cb = &spi_cb;

	if (!(p_spi_cb->openflag)) {
		return (E_OBJ);
	}


	if (p_spi_cb->errorflag) {
		return (E_SYS);
	}

	SVC(rercd = wai_sem(p_spi_cb->p_spi_inib->spi_semid),
										gen_ercd_wait(rercd, p_spi_cb));

	SVC(loc_cpu(), gen_ercd_sys(p_spi_cb));

	SEL_SLAVE();
	/* enable SPI interrupts */
	sil_wrw_mem((void *)S0SPCR, sil_rew_mem((void *)S0SPCR) | SPI0_SPIE);
	sil_wrw_mem((void *)S0SPDR, *buf++);
	p_spi_cb->xfer_size = len ;
	p_spi_cb->snd_buffer = buf;

	SVC(unl_cpu(), gen_ercd_sys(p_spi_cb));

	SVC(rercd = wai_flg(p_spi_cb->p_spi_inib->xfer_flgid, SPI0_XFER_DONE | SPI0_XFER_ERROR, TWF_ORW, &result),
										gen_ercd_wait(rercd, p_spi_cb));
	DIS_SEL_SLAVE();
	if (result & SPI0_XFER_ERROR) {
		ercd = E_OBJ;
		wricnt = len - p_spi_cb->xfer_size;
	} else {
		ercd = E_OK;
		wricnt = len;
	}

	SVC(rercd = sig_sem(p_spi_cb->p_spi_inib->spi_semid),
										gen_ercd_wait(rercd, p_spi_cb));

  error_exit:
	return(wricnt > 0U ? (ER_UINT) wricnt : ercd);
}



ER lpc2478_spi_rea_dat(uint16_t *buf, uint32_t len)
{

	ER ercd, rercd;
	SPI_CB	*p_spi_cb;
	uint_t 	reacnt = 0U;
	FLGPTN	result;

	if (len == 0 || buf == NULL) {
		ercd = E_PAR;
		return ercd;
	}

	if (sns_dpn()) {
		return (E_CTX);
	}

	p_spi_cb = &spi_cb;

	if (!(p_spi_cb->openflag)) {
		return (E_OBJ);
	}

	if (p_spi_cb->errorflag) {
		return (E_SYS);
	}

	SVC(rercd = wai_sem(p_spi_cb->p_spi_inib->spi_semid),
										gen_ercd_wait(rercd, p_spi_cb));

	SVC(loc_cpu(), gen_ercd_sys(p_spi_cb));

	SEL_SLAVE();
	/* enable SPI interrupts */
	sil_wrw_mem((void *)S0SPCR, sil_rew_mem((void *)S0SPCR) | SPI0_SPIE);

	sil_wrw_mem((void *)S0SPDR, 0xFFFF);	/* write dummy data to start transfer */
	p_spi_cb->xfer_size = len;
	p_spi_cb->snd_buffer = buf;
	p_spi_cb->rcv_ena = true;

	SVC(unl_cpu(), gen_ercd_sys(p_spi_cb));

	SVC(rercd = wai_flg(p_spi_cb->p_spi_inib->xfer_flgid, SPI0_XFER_DONE | SPI0_XFER_ERROR, TWF_ORW, &result),
										gen_ercd_wait(rercd, p_spi_cb));
	DIS_SEL_SLAVE();
	if (result & SPI0_XFER_ERROR) {
		ercd = E_OBJ;
		reacnt = len - p_spi_cb->xfer_size;
	} else {
		ercd = E_OK;
		reacnt = len;
	}

	SVC(rercd = sig_sem(p_spi_cb->p_spi_inib->spi_semid),
										gen_ercd_wait(rercd, p_spi_cb));
  error_exit:
	return(reacnt > 0U ? (ER_UINT) reacnt : ercd);
}

ER lpc2478_spi_wri_then_rea(uint16_t tx_data, uint16_t *rx_data)
{
	if (!(p_spi_cb->openflag)) {
		return (E_OBJ);
	}


}


ER lpc2478_spi_cls_dev(void)
{
	SPI_CB *p_spi_cb;
	ER	ercd;
	bool_t eflag = false;
	if (sns_dpn()) {
		return (E_CTX);
	}

	p_spi_cb = &spi_cb;

	SVC(dis_dsp(), gen_ercd_sys(p_spi_cb));
	if (!(p_spi_cb->openflag)) {
		ercd = E_OBJ;
	}
	else {

		p_spi_cb->openflag = false;

		if (loc_cpu() < 0) {
			eflag = true;
		}

		sil_wrw_mem((void *)S0SPCCR, 0x0);
		sil_wrw_mem((void *)S0SPCR, 0x00);
		sil_wrw_mem((void *)PCONP, sil_rew_mem((void *)PCONP) & ~(1 << 8));
		DIS_SEL_SLAVE();
		dis_int(INTNO_SPI0);

		if (unl_cpu() < 0) {
			eflag = true;
		}

		if (ini_sem(p_spi_cb->p_spi_inib->spi_semid) < 0) {
			eflag = true;
		}

		if (ini_flg(p_spi_cb->p_spi_inib->xfer_flgid) <0 ) {
			eflag = true;
		}

		if (eflag) {
			ercd = gen_ercd_sys(p_spi_cb);
		} else {
			ercd = E_OK;
		}

	}
	SVC(ena_dsp(), gen_ercd_sys(p_spi_cb));

error_exit:
	return (ercd);
}

ER lpc2478_spi_ctl_dev(uint32_t ioctl, uint8_t *buf)
{
	ER	ercd;

	ercd = E_OK;
	return (ercd);
}

void lpc2478_spi_int_handler(void)
{
	uint32_t status;
	uint32_t dummy;
	FLGPTN	result = 0;

	/* clear interrupt */
	sil_wrw_mem((void *)S0SPINT, SPI0_INT_FLAG);

	status  = sil_rew_mem((void *)S0SPSR);

	if (status & SPIF) {

		if (spi_cb.rcv_ena) {
			*spi_cb.rcv_buffer++ = sil_rew_mem((void *)S0SPDR);
		} else {
			dummy = sil_rew_mem((void *)S0SPDR); /* flush Rx FIFO */
		}

		if (--spi_cb.xfer_size) {
			if (spi_cb.snd_buffer != NULL) {
				sil_wrw_mem((void *)S0SPDR, *spi_cb.snd_buffer++);
			} else {
				sil_wrw_mem((void *)S0SPDR, 0xFFFF); /* init new transfer */
			}
		} else {
			result = SPI0_XFER_DONE;	/* one transfer is finished */
			spi_cb.rcv_ena = false;
			spi_cb.snd_buffer = NULL;
			spi_cb.rcv_buffer = NULL;
			/* disable int */
			sil_wrw_mem((void *)S0SPCR, sil_rew_mem((void *)S0SPCR) & ~SPI0_SPIE);
		}
	} else {
		result = SPI0_XFER_ERROR;
		if (status & WCOL) { /* write collision */
			dummy = sil_rew_mem((void *)S0SPDR); /* flush Rx FIFO */
		}
	}
	i_unlock_cpu();
	iset_flg(spi_cb.p_spi_inib->xfer_flgid, result);
}

