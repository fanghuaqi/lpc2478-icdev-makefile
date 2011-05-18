/**
 * =====================================================================================
 * 
 * @Filename  :lpc2478_pwm.c
 * @Version   : 0.1
 * @Author    :fanghuaqi <578567190@qq.com>
 * @Date      :Thu May 12 20:37:40 2011
 * 
 * @Brief     :
 * 
 * 
 * @Company   :HUST-Renesas Lab
 * @Revision  :
 * ======================================================================================
 * @0.1 Byfanghuaqi  Thu May 12 20:37:40 2011 Create orignal file
 * ======================================================================================
 */

#include "target_pwm.h"

ERCD pwm_init(uint8_t channel,uint32_t pwm_freq)
{
    uint32_t pwm_mr0;
    if ((channel > 1)){
        return ERCD_ARG_ERR;
    }
    if (channel == 0){
    	/*power on pwm0*/
    	sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP)|(1<<5));
    	/*select pwmclk = pclk*/
    	sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0)&(~(3<<10)));
    	sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0)|(1<<10));
    	/*no change for pwm channel 0 because pwm0 on the board can't be used*/
    	sil_wrw_mem((void *)PINSEL2,sil_rew_mem((void *)PINSEL2)|(0));
    	/*disable pwm0 output*/
    	sil_wrw_mem((void *)PWM0PCR,sil_rew_mem((void *)PWM0PCR)&(~(0x3f<<9)));
    }else{
    	/*ETM interface is disabled. must set this when use PINSEL4*/
    	sil_wrw_mem((void *)PINSEL10, 0x00);
    	/*power on pwm1*/
    	sil_wrw_mem((void *)PCONP,sil_rew_mem((void *)PCONP)|(1<<6));
    	/*select pwmclk = pclk*/
    	sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0)&(~(3<<12)));
		sil_wrw_mem((void *)PCLKSEL0,sil_rew_mem((void *)PCLKSEL0)|(1<<12));
		/*pwm1.1&1.2 select*/
		sil_wrw_mem((void *)PINSEL4,sil_rew_mem((void *)PINSEL4)&(~(0xf<<0)));
		sil_wrw_mem((void *)PINSEL4,sil_rew_mem((void *)PINSEL4)|(0x5<<0));
		/*pwm timer counter reset*/
		sil_wrw_mem((void *)PWM1TCR,sil_rew_mem((void *)PWM1TCR)|0x02);
		/*pwmtc reset 0 when it match pwmmr0*/
		sil_wrw_mem((void *)PWM1MCR,sil_rew_mem((void *)PWM1MCR)|0x02);
		/*tc increase every PR+1 cycles of PCLK set PR=0*/
		sil_wrw_mem((void *)PWM1PR,0);
	    /*pwm1 period set*/
        pwm_mr0 = Fcclk / pwm_freq;
        sil_wrw_mem((void *)PWM1MR0,pwm_mr0);
        /*pwm1.1 & 1.2 initial output 0*/
        sil_wrw_mem((void *)PWM1MR1,0);
        sil_wrw_mem((void *)PWM1MR2,0);
        /*enable pwm1.1 & 1.2 output,pwm1.1 pwm1.2 single edge select*/
        sil_wrw_mem((void *)PWM1PCR,sil_rew_mem((void *)PWM1PCR)&(~(0x3f<<9)));
        sil_wrw_mem((void *)PWM1PCR,sil_rew_mem((void *)PWM1PCR)|(3<<9));
    }
    return ERCD_OK;
}
ERCD pwm_setpwm1duty(uint8_t port, uint32_t pwm_duty)
{
    uint32_t pwmdutyreg = 0;
    uint32_t pwmperreg = 0;
    
    
    pwmperreg = sil_rew_mem((void *)PWM1MR0);
    if (pwmperreg > 10000){ /*less data loss*/
        pwmdutyreg = (pwmperreg / 100) * pwm_duty;
    }else{
        pwmdutyreg = (pwmperreg * pwm_duty)/ 100;
    }
    switch(port){
         case 1:
        	 sil_wrw_mem((void *)PWM1MR1, pwmdutyreg);
             break;
         case 2:
        	 sil_wrw_mem((void *)PWM1MR2, pwmdutyreg);
             break;
         default:
             return ERCD_ARG_ERR;
             break;
    }
    /*pwm1.1-1.3 latch enable*/
    sil_wrw_mem((void *)PWM1LER, 0x07);
    /*enable pwm counter and enable pwm mode*/
    sil_wrw_mem((void *)PWM1TCR, 0x09);

    return ERCD_OK;
}
