/**
 * @file   lpc2478_main.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 14:51:34 2011
 * 
 * @brief  
 * 
 * 
 */
#include "lpc2478_inc.h"

volatile uint8_t gl_pCH452_key = 0;
int main(){

    PLL_Init();
    Buzzer_Init();
    timer2_capinit();

    while(1){
    	Buzzer(BUZZER_ON);
    	Delay_ms(1);
    	Buzzer(BUZZER_OFF);
    	Delay_ms(1);
    }
    return 0;
}
