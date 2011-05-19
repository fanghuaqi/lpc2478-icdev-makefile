/**
 * =====================================================================================
 *
 * @Filename  :lpc2478_timer.h
 * @Version   : 0.1
 * @Author    :fanghuaqi <578567190@qq.com>
 * @Date      :Sat May 14 21:06:39 2011
 *
 * @Brief     :
 *
 *
 * @Company   :HUST-Renesas Lab
 * @Revision  :
 * ======================================================================================
 * @0.1 Byfanghuaqi  Sat May 14 21:06:40 2011 Create orignal file
 * ======================================================================================
 */
#ifndef  TARGET_TIMER_H
#define  TARGET_TIMER_H


#include  "lpc2478_inc.h"

void timer2_capinit(void);
uint32_t read_timer2cap(void);
#endif
