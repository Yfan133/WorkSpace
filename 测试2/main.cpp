#include<iostream>
#include<assert.h>
using namespace std;
#pragma warning (disable:4996)
//为什么这里要传二级指针，而队列传的一级指针
typedef struct StackNode
{
    int data;
    struct StackNode* next;
}StackNode, * Stack;
void StackInit(Stack* st)
{
    assert(st != NULL);
    *st = NULL;
}
void StackPush(Stack* st, int data)
{
    assert(st != NULL);
    StackNode* s = (StackNode*)malloc(sizeof(StackNode));
    s->data = data;
    s->next = *st;
    *st = s;
}
int StackTop(Stack* st)
{
    assert(st != NULL);
    return (*st)->data;
}
void StackPop(Stack* st)
{
    assert(st != NULL);
    StackNode* s = *st;
    (*st) = (*st)->next;
    free(s);
    s = NULL;
}
bool IsEmpty(Stack* st)
{
    assert(st != NULL);
    return (*st) == NULL;
}
typedef struct SQNode
{
    StackNode* s1;
    StackNode* s2;
}SQNode;
void SQInit(SQNode* pq)
{
    assert(pq != NULL);
    StackInit(&(pq->s1));
    StackInit(&(pq->s2));
}
void SQPush(SQNode* pq,int val)
{
    assert(pq != NULL);
    StackPush(&(pq->s1), val);
}
int SQPop(SQNode* pq)
{
    assert(pq != NULL);
    int val = -1;
    if (pq->s2 != NULL) {
        val = StackTop(&(pq->s2));
        StackPop(&(pq->s2));
        return val;
    }
    while (pq->s1 != NULL) {
        val = StackTop(&(pq->s1));
        StackPop(&(pq->s1));
        StackPush(&(pq->s2), val);
    }
    if (pq->s2 != NULL) 
        StackPop(&(pq->s2));
    return val;
}
SQNode* SQcreat()
{
    SQNode* p = (SQNode*)malloc(sizeof(SQNode));
    SQInit(p);
    return p;
}
int main()
{
    SQNode* p = SQcreat();
    SQPush(p, 1);
    SQPush(p, 2);
    SQPop(p);
    SQPop(p);
    SQPop(p);
    return 0;
}

//#define CapacityInit 2
//typedef struct Stack
//{
//    int* base;
//    int capacity;
//    int top;
//}StackNode;
//void StackInit(StackNode* pst)
//{
//    assert(pst != NULL);
//    pst->capacity = CapacityInit;
//    pst->base = (int*)malloc(sizeof(int) * pst->capacity);
//    pst->top = 0;
//}
//void StackExpand(StackNode* pst)
//{
//    assert(pst != NULL);
//    pst->capacity *= 2;
//    pst->base = (int*)realloc(pst->base, sizeof(int) * pst->capacity);
//    if(pst->base==NULL)
//        return;
//}
//bool IsFull(StackNode* pst)
//{
//    assert(pst != NULL);
//    return pst->capacity == pst->top;
//}
//void StackPush(StackNode* pst,int data)
//{
//    assert(pst != NULL);
//    if (IsFull(pst))
//        StackExpand(pst);
//    pst->base[pst->top++] = data;
//
//}
//int StackTop(StackNode* pst)
//{
//    assert(pst != NULL);
//    return pst->base[pst->top - 1];
//}
//void StackShow(StackNode* pst)
//{
//    assert(pst != NULL);
//    int i = pst->top-1;
//    while (i >= 0)
//    {
//        printf("%d->", pst->base[i--]);
//    }
//    printf("OVER!\n");
//}
//int main()
//{
//    StackNode st;
//    StackInit(&st);
//    StackPush(&st, 1);
//    StackPush(&st, 2);
//    StackPush(&st, 3);
//    StackPush(&st, 4);
//    StackPush(&st, 4);
//    StackShow(&st);
//    printf("%d", StackTop(&st));
//    return 0;
//}
