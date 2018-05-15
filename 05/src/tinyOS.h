#ifndef __tinyOS_H
#define __tinyOS_H

#include <stdint.h>

//Cortex-M ��ջ��Ԫ���ͣ���ջ��Ԫ�Ĵ�СΪ32λ
typedef uint32_t tTaskStack;

//����ṹ�������˰�һ�����������Ϣ
typedef struct _tTask{
	
	uint32_t * stack;
	
	//������ʱ������
	uint32_t delayTicks;
}tTask;

extern tTask *currentTask;
extern tTask *nextTask;

void  tTaskSwitch(void);
void  tTaskRunFirst(void);

#endif
