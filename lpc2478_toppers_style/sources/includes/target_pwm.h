/**
 * @Title: lpc2478_pwm.h
 * @Package lpc2478-icdev
 * @Description: TODO(用一句话描述该文件做什么)
 * @author fanghuaqi
 * @date 2011-5-13 上午09:49:12
 * @version V1.0
 */

#ifndef TARGET_PWM_H_
#define TARGET_PWM_H_

#include "lpc2478_inc.h"

#define  PWM_CHANNEL_0         0
#define  PWM_CHANNEL_1         1
#define  PWM_PORT_1            1
#define  PWM_PORT_2            2

ERCD pwm_init(uint8_t channel,uint32_t pwm_freq);
ERCD pwm_setpwm1duty(uint8_t port, uint32_t pwm_duty);

#endif /* LPC2478_PWM_H_ */
