#include "tlib.h"


#define firstNode   headNode.nextNode
#define lastNode    headNode.preNode

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

tNode * tListFirst(tList * list)
{
    tNode * node = (tNode*)0;
    if(0 != list->nodeCount)
    {
        node = list->firstNode;
    }
    return node;
}

tNode * tListLast(tList * list)
{
    tNode * node = (tNode*)0;
    if(0 != list->nodeCount)
    {
        node = list->lastNode;
    }
    return node;
}

void tListRemoveAll(tList * list)
{
    uint32_t count;
    tNode * nextNode;
    
    nextNode = list->firstNode;
    for(count = list->nodeCount; count != 0; count--)
    {
        tNode * currentNode = nextNode;
        nextNode = nextNode->nextNode;
        
        currentNode->nextNode = currentNode;
        currentNode->preNode = currentNode;
    }
    list->headNode.nextNode = &(list->headNode);
    list->headNode.preNode = &(list->headNode);
}


void tListAddFirst(tList * list,tNode * node)
{
    node->preNode = list->firstNode->preNode;
    node->nextNode = list->firstNode;
    list->firstNode = node;
    list->firstNode->preNode = node;
//    tNode * nextNode;
//    nextNode = list->firstNode;
//    list->firstNode = node;
//    node->nextNode = nextNode;
//    nextNode->preNode = node;
//    node->preNode = &(list->headNode);
    list->nodeCount++;
}

void tListAddLast(tList * list, tNode * node)
{
    node->preNode = list->lastNode->preNode;
    node->nextNode = list->lastNode->nextNode;
    
    list->lastNode = node;
    list->lastNode->nextNode = node;
    list->nodeCount++;
}


void tListRemoveFirst(tList * list)
{
    tNode * node= (tNode*)0;
    if(0 != list->nodeCount)
    {
        node = list->firstNode;
        
        list->firstNode = node->nextNode;
        node->nextNode->preNode = &(list->headNode);
        
        node->preNode = node;
        node->nextNode = node;
        list->nodeCount--;
    }
}

void tListInsterAfter(tList * list,tNode * nodeAfter,tNode * nodeToInster)
{
    nodeToInster->preNode = nodeAfter;
    nodeToInster->nextNode = nodeAfter->nextNode;
    
    nodeAfter->nextNode->preNode = nodeToInster;
    nodeAfter->nextNode = nodeToInster;
    list->nodeCount++;
     
}

void tListRemove(tList * list, tNode * node)
{
    if(0 == list->nodeCount)
    {
        return ;
    }
    
    node->preNode->nextNode = node->nextNode;
    node->nextNode->preNode = node->preNode;
    node->preNode = node;
    node->nextNode = node;
    
    list->nodeCount--;
}
