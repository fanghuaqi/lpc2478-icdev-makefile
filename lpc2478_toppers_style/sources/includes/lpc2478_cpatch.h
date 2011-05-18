/**
 * @file   lpc2478_cpatch.h
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:30:38 2011
 *
 * @brief  realize some functions that used by this program
 *
 *
 */

#ifndef LPC2478_CPATCH_H_
#define LPC2478_CPATCH_H_

#include  "lpc2478_inc.h"

extern void *MemCpy(void *dest, const void *src, uint16_t count);
extern int16_t*  _sbrk(int16_t incr);
#endif
