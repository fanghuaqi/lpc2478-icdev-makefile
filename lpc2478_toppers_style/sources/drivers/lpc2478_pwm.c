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

#include "lpc2478_pwm.h"

ERCD pwm_init(uint8_t channel,uint32_t pwm_period)
{
    uint32_t pwm_mr0;
    if ((channel > 1)){
        return ERCD_ARG_ERR;
    }
    if (channel == 0){
        setregbits(PCONP,(~(1<<5)),(1<<5));                    /*power on pwm0*/
        setregbits(PCLKSEL0,(~(3<<10)),(1<<10));               /*select pwmclk as pclk*/
        setregbits(PINSEL2,MASK_ALL,0);                        /*no change for pwm channel 0*/
        setregbits(PWM0PCR,(~(0x3f<<9)),(0<<9));               /*disable pwm0 output*/
    }else{
        setregbits(PCONP,(~(1<<6)),(1<<6));                    /*power on pwm1*/
        setregbits(PCLKSEL0,(~(3<<12)),(1<<12));               /*select pwmclk as pclk*/
        setregbits(PINSEL4,(~(0xf<<0)),(0x5<<0));              /*pwm1.1&1.2 select*/
        PINSEL10 = 0x00;   //ETM interface is disabled. must set this
        setregbits(PWM1TCR,MASK_ALL,0x02);                     /*pwm timer counter reset*/
        setregbits(PWM1MCR,MASK_ALL,0x02);                     /*pwmtc reset 0 when it match pwmmr0*/
        setregbits(PWM1PR,MASK_ALL,0);                         /*tc increase every PR+1 cycles of PCLK*/
        pwm_mr0 = Fcclk / pwm_period;
        setregbits(PWM1MR0,MASK_ALL,pwm_mr0);                  /*pwm1 period set*/
        setregbits(PWM1MR1,MASK_ALL,0);                        /*pwm1.1 initial output 0*/
        setregbits(PWM1MR2,MASK_ALL,0);                        /*pwm1.2 initial output 0*/
        setregbits(PWM1PCR,(~(0x3f<<9)),(3<<9));               /*enable pwm1.1 & 1.2 output,pwm1.1 pwm1.2 single edge select*/
    }
    return ERCD_OK;
}
ERCD pwm_setpwm1duty(uint8_t port, uint32_t pwm_duty)
{
    uint32_t pwmdutyreg = 0;
    uint32_t pwmperreg = 0;
    
    
    pwmperreg = PWM1MR0;
    if (pwmperreg > 10000){ /*less data loss*/
        pwmdutyreg = (pwmperreg / 100) * pwm_duty;
    }else{
        pwmdutyreg = (pwmperreg * pwm_duty)/ 100;
    }
    switch(port){
         case 1:
             PWM1MR1 = pwmdutyreg;

             break;
         case 2:
             PWM1MR2 = pwmdutyreg;
             break;
         default:
             return ERCD_ARG_ERR;
             break;
    }
    PWM1LER = 0x07;    /*pwm1.1-1.3 latch enable*/
    PWM1TCR = 0x09;   /*enable pwm counter and enable pwm mode*/
    return ERCD_OK;
}
