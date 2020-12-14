#include<stdlib.h>
#include<stdio.h>

#define FALSE 0;
#define TRUE 1
#define ERROR 0
#define OK 1
#define Overflow 2//上溢
#define Underflow 3//下溢
#define NotPressent 4//元素不存在
#define Duplicate 5//有重复元素

typedef int BOOL;
typedef int ElemType;
typedef struct mGraph
{
    ElemType** a;//邻接矩阵
    int n;//图的当前顶点数
    int e;//图的当前边数
    ElemType noEdge;//两顶点间无边时的值
}MGraph;



typedef int Status;
Status Init(MGraph* mg, int nSize, ElemType noEdgeValue)//初始化
{
    int i, j;
    mg->n = nSize;
    mg->e = 0;
    mg->noEdge = noEdgeValue;
    mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));
    if (!mg->a)
        return ERROR;
    for (i = 0; i < mg->n; i++)//动态生成二维数组
    {
        mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));
        for (j = 0; j < mg->n; j++)mg->a[i][j] = mg->noEdge;
        mg->a[i][i] = 0;
    }
    return OK;
}

void Destroy(MGraph* mg)
{
    int i;
    for (i = 0; i < mg->n; i++)
        free(mg->a[i]);
    free(mg->a);
}

Status Insert(MGraph* mg, int u, int v, ElemType w)//边的插入
{
    if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v)
        return ERROR;
    if (mg->a[u][v] != mg->noEdge)
        return Duplicate;//若待插入边已存在，则返回Duplicate
    mg->a[u][v] = w;//插入新边
    mg->e++;
    return OK;
}

Status Remove(MGraph* mg, int u, int v)
{
    if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v)
        return ERROR;
    if (mg->a[u][v] == mg->noEdge)
        return NotPressent;
    mg->a[u][v] = mg->noEdge;//删除边
    mg->e--;
    return OK;
}



//深度优先遍历
//邻接矩阵的单一顶点DFS
void DFS(int v, int visited[], MGraph g) {
    int j;
    printf("%d ", v);              //访问顶点v
    visited[v] = 1;               //为顶点v打上访问标记       
    for (j = 0; j < g.n; j++) {      //遍历v的邻接点
        if (!visited[j] && g.a[v][j] > 0) {  //当未被访问且有权值
            DFS(j, visited, g);
        }
    }
}


//邻接矩阵的全图DFS
void DFSGraph(MGraph g) {
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int)); //动态生成标记数组visted
    for (i = 0; i < g.n; i++) {
        visited[i] = 0;          //visted数组初始化
    }//visted数组初始化
    for (i = 0; i < g.n; i++) {//逐一检查每个顶点,若未被访问,则调用DFS
        if (!visited[i]) {//当未被访问且有权值
            DFS(i, visited, g);
        }
    }
    free(visited);//释放visted数组
}
//O(n^2)







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




//邻接矩阵的单一顶点BFS
void BFS(int v, int visited[], MGraph g) {
    Queue q;
    create(&q, g.n);//初始化队列
    visited[v] = 1;//为顶点v打上访问标记
    printf("%d ", v);//访问顶点v
    EnQueue(&q, v);//将顶点v放入队列
    while (!IsEmpty(&q)) {
        Front(&q, &v);
        DeQueue(&q);//队首顶点出队列
        for (int i = 0; i < g.n; i++) {//遍历v的每一项
            if (!visited[i] && g.a[v][i] > 0) {//若未被访问且有权值,则将其访问并放入队列,注意这里判断的是g.a[v][i]二维数组
                visited[i] = 1;
                printf("%d ", i);
                EnQueue(&q, i);
            }
        }
    }
}


//邻接矩阵的全图BFS
void BFSGraph(MGraph g) {
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int));//动态生成visited数组
    for (i = 0; i < g.n; i++) {//初始化visited数组
        visited[i] = 0;
    }
    for (i = 0; i < g.n; i++) {//逐一检查每个顶点,若未被访问,则调用BFS
        if (!visited[i]) {
            BFS(i, visited, g);
        }
    }
    free(visited);
}



int main() {
    MGraph g;
    int nSize, edge, u, v, i;
    ElemType w;
    printf("Please enter the size of the mgraph:");
    scanf_s("%d", &nSize);
    Init(&g, nSize, -1);
    printf("Please enter the number of the edges:");
    scanf_s("%d", &edge);
    printf("Now init the graph.\n");
    
    for (i = 0; i < edge; i++) {
        printf("Please enter the edge:");
        scanf_s("%d%d%d", &u, &v, &w);
        Insert(&g, u, v, w);
    }
    printf("DFS:\n");
    DFSGraph(g);
    printf("\nBFS:\n");
    BFSGraph(g);
    return 0;
}