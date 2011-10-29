/**
 * @file   lpc2478_hw.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:34:55 2011
 *
 * @brief  lpc2478 hareware
 *
 *
 */

#ifndef TARGET_HW_H_
#define TARGET_HW_H_

#include  "lpc2478_inc.h"

#define BUZZER_ON 1
#define BUZZER_OFF 0

extern void LED_Init(void);
extern void LED_Output(uint8_t ledvalue);
extern void Buzzer_Init(void);
extern void Buzzer(uint8_t buzzer);
extern void Delay_ms(uint32_t ms);
extern void Delay_us(uint32_t us);
#endif
