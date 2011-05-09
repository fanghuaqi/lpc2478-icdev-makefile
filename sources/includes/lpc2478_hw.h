/**
 * @file   lpc2478_hw.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:34:55 2011
 *
 * @brief  lpc2478 hareware
 *
 *
 */

#ifndef LPC2478_HW_H_
#define LPC2478_HW_H_

#include  "lpc2478_inc.h"

void LED_Init(void);
void LED_Output(uint8_t ledvalue);
void Buzzer_Init(void);
void Buzzer(uint8_t buzzer);
void Delay_ms(uint32_t ms);
#endif
