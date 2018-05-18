#ifndef __tinyOS_H
#define __tinyOS_H

#include <stdint.h>
#include "tlib.h"
#include "tConfig.h"




#define NULL  ((void *)0)
//Cortex-M 的栈单元类型：堆栈单元的大小为32位
typedef uint32_t tTaskStack;

//任务结构：包含了把一任务的所有信息
typedef struct _tTask{
	
	uint32_t * stack;
	
	//任务延时计数器
	uint32_t delayTicks;
	
	//添加任务的优先级
	uint32_t prio;
}tTask;

extern tTask *currentTask;
extern tTask *nextTask;

void  tTaskSwitch(void);
void  tTaskRunFirst(void);

uint32_t tTaskEnterCritical(void);
void tTaskExitCritical(uint32_t status);
void tTaskSchedInit(void);
void tTaskSchedDissable(void);
void tTaskSchedEnable(void);
void tTaskSched(void);
#endif
