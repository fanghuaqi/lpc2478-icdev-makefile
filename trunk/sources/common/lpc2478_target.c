/**
 * @file   target.c
 * @author fanghuaqi <578567190@qq.com>
 * @date   Sun Mar 27 14:59:21 2011
 * 
 * @brief  
 * 
 * 
 */

#define DEFAULT_ISTKSZ  40960 /* 40KB 堆栈(SVC模式下)  */

static unsigned int intstack[DEFAULT_ISTKSZ];		/* interrupt stack */

unsigned int * const p_intstack = &intstack[DEFAULT_ISTKSZ];
