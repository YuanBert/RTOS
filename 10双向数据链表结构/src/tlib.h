#ifndef __TLIB_H
#define __TLIB_H

#include <stdint.h>

//λͼ���ݽṹ
typedef struct 
{
	uint32_t bitmap;
}tBitmap;

//����ڵ����ݽṹ
typedef struct _tNode
{
	struct _tNode * preNode;
	struct _tNode * nextNode;
}tNode;

//�����������ݽṹ
typedef struct _tList
{
	tNode headNode;
	uint32_t nodeCount;
}tList;

void tBitmapInit(tBitmap* bitmap);
uint32_t tBitmapPosCount(void);
void tBitmapSet(tBitmap* bitmap,uint32_t pos);
void tBitmapClear(tBitmap* bitmap, uint32_t pos);
uint32_t tBitmapGetFirstSet(tBitmap* bitmap);

#endif
