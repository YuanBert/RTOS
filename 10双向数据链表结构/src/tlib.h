#ifndef __TLIB_H
#define __TLIB_H

#include <stdint.h>

//位图数据结构
typedef struct 
{
	uint32_t bitmap;
}tBitmap;

//定义节点数据结构
typedef struct _tNode
{
	struct _tNode * preNode;
	struct _tNode * nextNode;
}tNode;

//定义链表数据结构
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
