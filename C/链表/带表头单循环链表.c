#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct node
{
    ElemType element;
    struct node* link;
}Node;
typedef struct headerList//带表头单链表定义
{
    Node* head;
    int n;              //存储节点个数
}HeaderList;

#define ERROR 0;
#define OK 1;
#define Overflow 2;//上溢
#define Underflow 3;//下溢
#define NotPresent 4;//元素不存在
#define Duolicate 5;//有重复元素
typedef int Status;
Status Init(HeaderList* h)//初始化
{
    h->head = (Node*)malloc(sizeof(Node));
    if (!h->head)
        return ERROR;
    h->head->link = NULL;
    h->n = 0;
    return OK;
}
Status Insert(HeaderList* h, int i, ElemType x)//插入，i为位置，x为插入元素
{
    Node* p, * q;
    int j;
    p = h->head;
    if (i<-1 || i>h->n - 1)
        return ERROR;
    for (j = 0; j <= i; j++)
        p = p->link;
    q = (Node*)malloc(sizeof(Node));
    q->element = x;
    q->link = p->link;
    p->link = q;
    h->n++;
    return OK;
}
Status Delete(HeaderList* h, int i)//删除
{
    int j;
    Node* p, * q;
    if (!h->n)
        return ERROR;
    if (i<0 || i>h->n)
        return ERROR;
    q = h->head;
    for (j = 0; j < i; j++)
        q = q->link;
    p = q->link;
    q->link = p->link;
    free(p);
    h->n--;
    return OK;
}
Status Find(HeaderList* h, int i, ElemType* x)//返回元素在链表中的下标
{
    int j;
    Node* p;
    if (i<0 || i>h->n)
        return ERROR;
    p = h->head;
    for (j = 0; j <= i; j++)
        p = p->link;
    *x = p->element;
    return OK;
}
Status Output(HeaderList* h)//链表输出（有疑问）
{
    Node* p;
    if (!h->n)
        return ERROR;
    p = h->head;
    while (p->link)
    {
        p = p->link;
        printf("%d ", p->element);
    }
    return OK;
}
void Destroy(HeaderList* h)
{
    Node* p, * q;
    p = h->head;
    while (p->link)
    {
        q = p->link;
        free(p);
        p = q;
    }
}


Status Transform(HeaderList *h)
{
    Node *p,*q;
    int i=0;//有几个元素就是几个
    int j=0,k;
    ElemType m;

    p=h->head;
    if (!h->n)
        return ERROR;
    while(p->link)
    {
        i++;
        p=p->link;
    }

    k=i;
    p=h->head;
    for(j=0;j<i/2;j++)
    {
        p=p->link;
        m=p->element;
        q=h->head;
        for(k=0;k<i-j;k++)
            q=q->link;
        q->element=q->element+m;
        m=q->element-m;
        q->element=q->element-m;
        p->element=m;
    }
}



int main()
{
    int i;
    int x;
    HeaderList h;
    Init(&h);
    for (i = 0; i < 9; i++)
        Insert(&h, i - 1, i);
    printf("the headerlisr is:");
    Output(&h);
    Delete(&h, 0);
    printf("\nthe headerlisr is:");
    Output(&h);
    Find(&h, 0, &x);
    printf("\nthe value is:");
    printf("%d ", x);
    Destroy(&h);
}