#include<stdlib.h>
#include<stdio.h>


#define ERROR 0
#define OK 1
#define Overflow 2//上溢
#define Underflow 3//下溢
#define NotPressent 4//元素不存在
#define Duplicate 5//有重复元素

typedef int ElemType;
typedef struct mGraph
{
    ElemType **a;//邻接矩阵
    int n;//图的当前顶点数
    int e;//图的当前边数
    ElemType noEdge;//两顶点间无边时的值
}MGraph;



typedef int Status;
Status Init(MGraph *mg,int nSize,ElemType noEdgeValue)//初始化
{
    int i,j;
    mg->n=nSize;
    mg->e=0;
    mg->noEdge=noEdgeValue;
    mg->a=(ElemType**)malloc(nSize*sizeof(ElemType*));
    if(!mg->a)
        return ERROR;
    for(i=0;i<mg->n;i++)//动态生成二维数组
    {
        mg->a[i]=(ElemType*)malloc(nSize*sizeof(ElemType));
        for(j=0;j<mg->n;j++)mg->a[i][j]=mg->noEdge;
        mg->a[i][i]=0;
    }
    return OK;
}

void Destroy(MGraph *mg)
{
    int i;
    for(i=0;i<mg->n;i++)
        free(mg->a[i]);
    free(mg->a);
}

Status Insert(MGraph *mg,int u,int v,ElemType w)//边的插入
{
    if(u<0||v<0||u>mg->n-1||v>mg->n-1||u==v)
        return ERROR;
    if(mg->a[u][v]!=mg->noEdge)
        return Duplicate;//若待插入边已存在，则返回Duplicate
    mg->a[u][v]=w;//插入新边
    mg->e++;
    return OK;
}

Status Remove(MGraph *mg,int u,int v)
{
    if(u<0||v<0||u>mg->n-1||v>mg->n-1||u==v)
        return ERROR;
    if(mg->a[u][v]==mg->noEdge)
        return NotPressent;
    mg->a[u][v]=mg->noEdge;//删除边
    mg->e--;
    return OK;
}