#include<stdlib.h>
#include<stdio.h>


#define ERROR 0
#define OK 1
#define Overflow 2//上溢
#define Underflow 3//下溢
#define NotPressent 4//元素不存在
#define Duplicate 5//有重复元素

typedef int ElemType;
typedef struct eNode
{
    int adjVex;//与任意顶点u相邻接的顶点
    ElemType w;//边的权值
    struct eNode* nextArc;//指向下一个边结点
}ENode;
typedef struct lGraph
{
    int n;//图的当前顶点数
    int e;//图的当前边数
    ENode** a;//指向一维指针数组
}LGraph;



typedef int Status;
Status Init(LGraph* lg, int nSize)//邻接表初始化
{
    int i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));//动态生成长度为n的一维指针数组
    if (!lg->a)
        return ERROR;
    else
    {
        for (i = 0; i < lg; i++) lg->a[i] = NULL;
        return OK;
    }
}

void Destroy(LGraph *lg)//邻接表撤销
{
    int i;
    ENode* p, * q;
    for (i = 0; i < lg->n; i++)
    {
        p = lg->a[i];//指针p指向顶点i的单链表的第一个边结点
        q = p;
        while (p)//释放顶点i单链表中所有边结点
        {
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    free(lg->a);//释放一维指针数组a的存储空间
}

Status Exist(LGraph* lg, int u, int v)//边的搜索
{
    ENode* p;
    if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
        return ERROR;
    p = lg->a[u];//指针p指向顶点u的单链表的第一个边结点
    while (p && p->adjVex != v) p = p->nextArc;
    if (!p) return ERROR;//未找到此边，返回ERROR
    else return OK;//找到返回OK
}

Status Insert(LGraph* lg, int u, int v, ElemType w)//边的插入
{
    ENode* p;
    if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
        return ERROR;
    if (Exist(lg, u, v))
        return Duplicate;
    p = (ENode*)malloc(sizeof(ENode));
    p->adjVex = v;
    p->w = w;
    p->nextArc = lg->a[u];//将新的边结点插入单链表的最前面
    lg->a[u] = p;
    lg->e++;
    return OK;
}

Status Remove(LGraph* lg, int u, int v)
{
    ENode* p, * q;
    if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
        return ERROR;
    p = lg->a[u], q = NULL;
    while (p && p->nextArc != v)
    {
        p = q;
        p = p->nextArc;
    }
    if (!p)return NotPressent;//p为空，带删除边不存在
    if (q)q->nextArc = p->nextArc;//从单链表中删除此边
    else lg->a[u] = p->nextArc;
    free(p);
    lg->e--;
    return OK;
}