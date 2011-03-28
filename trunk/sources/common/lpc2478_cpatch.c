/**
 * @file   lpc2478_cpatch.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 19:41:25 2011
 * 
 * @brief  realize some lib functions
 * 
 * 
 */

#include "lpc2478_cpatch.h"

void *MemCpy(void *dest, const void *src, uint16_t count)
{
    int8_t *tmp = dest;
    const int8_t *s = src;

    while (count--)
        *tmp++ = *s++;
    return dest;
}
int16_t*  _sbrk(int16_t incr)
{
	extern int16_t _end; /* Defined by the linker */
	static int16_t *heap_end;
	int *prev_heap_end;
	if (heap_end == 0) {
	heap_end = &_end;
	}
	prev_heap_end = heap_end;
	/*if ((heap_end + incr) > (int *)(0xA2000000)) {
		return -1;
	}*/
	heap_end += incr;
	return (int16_t*) prev_heap_end;
	}



