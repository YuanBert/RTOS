#ifndef __tinyOS_H
#define __tinyOS_H

#include <stdint.h>

//Cortex-M ��ջ��Ԫ���ͣ���ջ��Ԫ�Ĵ�СΪ32λ
typedef uint32_t tTaskStack;

//����ṹ�������˰�һ�����������Ϣ
typedef struct _tTask{
	
	uint32_t * stack;
}tTask;

#endif
