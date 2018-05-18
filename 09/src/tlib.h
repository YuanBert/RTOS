#ifndef __TLIB_H
#define __TLIB_H

#include <stdint.h>

#define tNodeParent(node, parent,name)  (parent*((uint32_t)node - (uint32_t)&((parent*)0)->name))

typedef struct 
{
	uint32_t bitmap;
}tBitmap;

typedef struct _tNode
{
    struct _tNode * preNode;
    struct _tNode * nextNode;
}tNode;

typedef struct _tList
{
    tNode       headNode;
    uint32_t    nodeCount;
}tList;

void tBitmapInit(tBitmap* bitmap);
uint32_t tBitmapPosCount(void);
void tBitmapSet(tBitmap* bitmap,uint32_t pos);
void tBitmapClear(tBitmap* bitmap, uint32_t pos);
uint32_t tBitmapGetFirstSet(tBitmap* bitmap);

void tNodeInit(tNode * node);
void tListInit(tList * list);
uint32_t tListCount(tList * list);
tNode * tListFirst(tList * list);
tNode * tListLast(tList * list);
void tListRemoveAll(tList * list);
void tListAddFirst(tList * list,tNode * node);
void tListAddLast(tList * list, tNode * node);
void tListRemoveFirst(tList * list);
void tListInsterAfter(tList * list,tNode * nodeAfter,tNode * nodeToInster);
void tListRemove(tList * list, tNode * node);
#endif
