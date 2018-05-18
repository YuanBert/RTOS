#ifndef __tinyOS_H
#define __tinyOS_H

#include <stdint.h>
#include "tlib.h"
#include "tConfig.h"




#define NULL  ((void *)0)
//Cortex-M ��ջ��Ԫ���ͣ���ջ��Ԫ�Ĵ�СΪ32λ
typedef uint32_t tTaskStack;

//����ṹ�������˰�һ�����������Ϣ
typedef struct _tTask{
	
	uint32_t * stack;
	
	//������ʱ������
	uint32_t delayTicks;
	
	//�����������ȼ�
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
