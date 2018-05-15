#include "tinyOS.h"
#include "ARMCM3.h"

tTask *  currentTask;
tTask *  nextTask;
tTask *  idleTask;
tTask *  taskTable[2];

void tTaskSched()
{
	if(currentTask == idleTask)
	{
		if(0 == taskTable[0]->delayTicks)
		{
			nextTask = taskTable[0];
		}
		else if(0 == taskTable[1]->delayTicks)
		{
			nextTask = taskTable[1];
		}
		else
		{
			return;
		}
	}
	else
	{
		if(currentTask == taskTable[0])
		{
			if(0 == taskTable[1]->delayTicks)
			{
				nextTask = taskTable[1];
			}
			else if(0 != currentTask->delayTicks)
			{
				nextTask = idleTask;
			}
			else
			{
				return;
			}
		}
		else if(currentTask == taskTable[1])
		{
			if(0 == taskTable[0]->delayTicks)
			{
				nextTask = taskTable[0];
			}
			else if(0 != currentTask->delayTicks)
			{
				nextTask = idleTask;
			}
			else
			{
				return;
			}
		}
	}
	tTaskSwitch();
}
void tSetSysTickPeriod(uint32_t ms)
{
	//中断向量的配置
	NVIC_SetPriority(SysTick_IRQn,(1 << __NVIC_PRIO_BITS) - 1);
	
	//系统时钟的配置
	SysTick->LOAD = ms * SystemCoreClock / 1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk|
					SysTick_CTRL_TICKINT_Msk|
					SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler()
{
	int i;
	for(i = 0; i<2;i++)
	{
		if(taskTable[i]->delayTicks > 0)
		{
			taskTable[i]->delayTicks--;
		}
	}
	tTaskSched();
}
	
void taskDelay(int delay)
{
	currentTask->delayTicks = delay;
	tTaskSched();
}

void delay(int count)
{
	while(--count > 0);
}
	
tTask tTask1;
tTask tTask2;
tTask tTaskIdle;

tTaskStack task1Env[1024];
tTaskStack task2Env[1024];
tTaskStack idleTaskEnv[1024];


void tTaskInit(tTask* task,void (*entry)(void*),void *param,tTaskStack * stack)
{
	*(--stack) = (unsigned long)(1 << 24);
	*(--stack) = (unsigned long)entry;
	*(--stack) = (unsigned long)0x14;
	*(--stack) = (unsigned long)0x12;
	*(--stack) = (unsigned long)0x3;
	*(--stack) = (unsigned long)0x2;
	*(--stack) = (unsigned long)0x1;
	*(--stack) = (unsigned long)param;
	
	*(--stack) = (unsigned long)0x11;
	*(--stack) = (unsigned long)0x10;
	*(--stack) = (unsigned long)0x9;
	*(--stack) = (unsigned long)0x8;
	*(--stack) = (unsigned long)0x7;
	*(--stack) = (unsigned long)0x6;
	*(--stack) = (unsigned long)0x5;
	*(--stack) = (unsigned long)0x4;
	
	
	task->stack = stack;
	task->delayTicks = 0;
}



int task1flag;
void task1Entry(void *param)
{
	tSetSysTickPeriod(10);
	while(1)
	{
		task1flag = 1;
		taskDelay(1);
		task1flag = 0;
		taskDelay(1);
	}
}
int task2flag;
void task2Entry(void *param)
{
	while(1)
	{
		task2flag = 1;
		taskDelay(1);
		task2flag = 0;
		taskDelay(1);
	}
}

void idleTaskEntry(void *param)
{
	while(1)
	{
		//空闲任务
	}
}











int main()
{
	tTaskInit(&tTask1,task1Entry,(void *)0x11111111,&task1Env[1024]);
	tTaskInit(&tTask2,task2Entry,(void *)0x11111111,&task2Env[1024]);
	tTaskInit(&tTaskIdle,idleTaskEntry,(void *)0x11111111,&idleTaskEnv[1024]);

	taskTable[0] = &tTask1;
	taskTable[1] = &tTask2;
	idleTask = &tTaskIdle;
	
	nextTask = taskTable[0];
	
	tTaskRunFirst();
	
	return 0;
}
