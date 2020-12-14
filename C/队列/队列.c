#include<stdlib.h>
#include<stdio.h>

#define FALSE 0
#define TRUE 1
typedef int BOOL;
typedef int ElemType;
//队列
typedef struct queue
{
    int front;
    int rear;
    int maxSize;
    ElemType* elemente;
}Queue;

//创建一个能容纳mSize个单元的空队列
void create(Queue* Q, int mSize)
{
    Q->maxSize = mSize;
    Q->elemente = (ElemType*)malloc(sizeof(ElemType) * mSize);
    Q->front = Q->rear = 0;
}

//销毁队列
void Destroy(Queue* Q)
{
    Q->maxSize = 0;
    free(Q->elemente);
    Q->front = Q->rear = -1;
}

//判断队列是否为空
BOOL IsEmpty(Queue* Q)
{
    return Q->front == Q->rear;
}

//判断队列是否已满
BOOL IsFull(Queue* Q)
{
    return (Q->rear + 1) % Q->maxSize == Q->front;
}

//获取队头元素，并通过x返回
BOOL Front(Queue* Q, ElemType* x)
{
    if (IsEmpty(Q))
        return FALSE;
    *x = Q->elemente[(Q->front + 1) % Q->maxSize];
    return TRUE;
}

//队尾插入元素
BOOL EnQueue(Queue* Q, ElemType x)
{
    if (IsFull(Q))
        return FALSE;
    Q->rear = (Q->rear + 1) % Q->maxSize;
    Q->elemente[Q->rear] = x;
    return TRUE;
}

//从队头删除元素
BOOL DeQueue(Queue* Q)
{
    if (IsEmpty(Q))
        return FALSE;
    Q->front = (Q->front + 1) % Q->maxSize;
    return TRUE;
}

//清空队列元素
void Clear(Queue* Q)
{
    Q->front = Q->rear = 0;
}
