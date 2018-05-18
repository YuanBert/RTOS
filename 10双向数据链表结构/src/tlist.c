#include "tlib.h"

#define firstNode	headNode.nextNode
#define lastNode	headNode.preNode

//初始化节点
void tNodeInit(tNode * node)
{
	node->nextNode = node;
	node->preNode = node;
}

void tListInit(tList * list)
{
	list->firstNode = &(list->headNode);
    list->lastNode = &(list->headNode);
    list->nodeCount = 0;
}

uint32_t tListCount(tList * list)
{
    return list->nodeCount;
}

tNode * tListFirst(tList* list)
{
    tNode * node = (tNode*)0;
    if(0 != list->nodeCount)
    {
        node = list->firstNode;
    }
    return node;
}

tNode * tListLast(tList* list)
{
    tNode* node = (tNode*)0;
    if(0 != list->nodeCount)
    {
        node = list->lastNode;
    }
    return node;
}

tNode * tListPre(tList * list,tNode * node)
{
    if(node == node->preNode)
    {
        return (tNode*)0;
    }
    else
    {
        return node->preNode;
    }
}

tNode * tListNext(tList * list,tNode * node)
{
    if(node == node->nextNode)
    {
        return (tNode*)0;
    }
    else
    {
        return node->nextNode;
    }
}

void tListRemoveAll(tList * list)
{
    uint32_t count;
    tNode * nextNode;
    
    nextNode = list->firstNode;
    for(count = list->nodeCount; 0 != count; count--)
    {
        tNode* currentNode = nextNode;
        nextNode = nextNode->nextNode;
        
    }
}












