#ifndef __tinyOS_H
#define __tinyOS_H

#include <stdint.h>

//Cortex-M 的栈单元类型：堆栈单元的大小为32位
typedef uint32_t tTaskStack;

//任务结构：包含了把一任务的所有信息
typedef struct _tTask{
	
	uint32_t * stack;
}tTask;

#endif
