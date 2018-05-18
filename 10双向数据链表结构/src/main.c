#include "tinyOS.h"
#include "ARMCM3.h"

tTask *  currentTask;
tTask *  nextTask;
tTask *  idleTask;
tTask *  taskTable[TINGOS_PRO_COUNT] = {NULL};

tBitmap taskPrioBitmap;

uint8_t schedLockCounter;

void tTaskSchedInit(void)
{
	schedLockCounter = 0;
	tBitmapInit(&taskPrioBitmap);
}

void tTaskSchedDissable(void)
{
	uint32_t status = tTaskEnterCritical();
	
	if(schedLockCounter < 255)
	{
		schedLockCounter++;
	}
	tTaskExitCritical(status);
}

void tTaskSchedEnable(void)
{
	uint32_t status = tTaskEnterCritical();
	
	if(schedLockCounter > 0)
	{
		if(--schedLockCounter == 0)
		{
			tTaskSched();
		}
	}
	tTaskExitCritical(status);
}


tTask * tTaskHighestReady(void)
{
	uint32_t highestPrio = tBitmapGetFirstSet(&taskPrioBitmap);
	return taskTable[highestPrio];
}


int  shareCount;
uint32_t  tickCount;



void tTaskSched()
{
	uint32_t primask;
	tTask * tempTask;
	primask = tTaskEnterCritical();
	if(schedLockCounter > 0)
	{
		tTaskExitCritical(primask);
		return ;
	}
	
	tempTask = tTaskHighestReady();
	if(tempTask!= currentTask)
	{
		nextTask = tempTask;
		tTaskSwitch();
	}
	tTaskExitCritical(primask);
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
	uint32_t primask;
	primask = tTaskEnterCritical();
	int i;
	for(i = 0; i< TINGOS_PRO_COUNT;i++)
	{
		/*此处可以添加对任务表的检测*/
		if(NULL == taskTable[i])
		{
			continue;
		}
		if(taskTable[i]->delayTicks > 0)
		{
			taskTable[i]->delayTicks--;
		}
		else
		{
			tBitmapSet(&taskPrioBitmap,i);
		}
	}
	tickCount++;
	tTaskSched();
	tTaskExitCritical(primask);
}
	
void taskDelay(int delay)
{
	uint32_t primask;
	primask = tTaskEnterCritical();
	currentTask->delayTicks = delay;
	tBitmapClear(&taskPrioBitmap,currentTask->prio);
	tTaskExitCritical(primask);
	
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


void tTaskInit(tTask* task,void (*entry)(void*),void *param, uint32_t prio,tTaskStack * stack)
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
	task->prio = prio;
	
	taskTable[prio] =  task;
	tBitmapSet(&taskPrioBitmap,prio);
}

int task1flag;
int firstSet;
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
	
	tTaskSchedInit();
	tTaskInit(&tTask1,task1Entry,(void *)0x11111111,0,&task1Env[1024]);
	tTaskInit(&tTask2,task2Entry,(void *)0x11111111,1,&task2Env[1024]);
	tTaskInit(&tTaskIdle,idleTaskEntry,(void *)0x11111111,TINGOS_PRO_COUNT-1,&idleTaskEnv[1024]);
	idleTask = &tTaskIdle;
	
	nextTask = tTaskHighestReady();
	
	tTaskRunFirst();
	
	return 0;
}
