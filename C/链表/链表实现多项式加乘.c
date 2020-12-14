#include<stdio.h>
#include<stdlib.h>
typedef struct pNode
{
    int coef;//系数
    int exp;//指数
    struct pNode* link;
}PNode;
typedef struct polynominal
{
    PNode* head;
}Polynominal;

void Create(Polynominal* p)//创建多项式（带表头的单循环链）
{
    PNode* pn, * pre, * q;
    p->head = (PNode*)malloc(sizeof(PNode));
    p->head->exp = -1;
    p->head->link = p->head;
    for (;;)
    {
        pn = (PNode*)malloc(sizeof(PNode));
        printf("coef:\n");
        scanf_s("%d", &pn->coef);
        if (pn->coef == 0)break;
        printf("exp:\n");
        scanf_s("%d", &pn->exp);
        if (pn->exp < 0) break;//指数小于0，退出

        pre = p->head;//保存刚好大于传入指数的节点
        q = p->head->link;//用于传递查询指数

        while (q && q->exp > pn->exp)
        {
            pre = q;
            q = q->link;
        }

        pn->link = q;//完成新节点的插入
        pre->link = pn;
    }
}

void Show(Polynominal* pn)
{
    PNode* p;
    p = pn->head;
    while (p->link->exp >= 0)
    {
        p = p->link;
        printf("%dx^%d", p->coef, p->exp);
        if (p->link->exp >= 0)
            printf("+");
    }
}

void Add(Polynominal* px, Polynominal* qx)
{
    PNode* q, * q1 = qx->head, * p, * p1, * temp;
    p = px->head->link;//p指向多项式px的第一个节点
    q = q1->link;//q1是q的前驱

    while (p->exp >= 0)
    {
        while (p->exp < q->exp)
        {
            q1 = q;
            q = q->link;
        }
        if (p->exp == q->exp)
        {
            q->coef = q->coef + p->coef;
            if (q->coef == 0)
            {
                q1->link = q->link;//执行删除操作
                free(q);
                q = q1->link;
                p = p->link;
            }
            else
            {
                q1 = q;
                q = q->link;
                p = p->link;
            }
        }
        else//p->exp>q->exp的情况
        {
            temp = (PNode*)malloc(sizeof(PNode));
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            q1 = q1->link; p = p->link;
        }
    }

}

void Muli(Polynominal* px, Polynominal* qx,Polynominal *m)
{
    PNode* p, * q, * temp, * m1, * m2;
    p = px->head;
    q = qx->head;

    m->head = (PNode*)malloc(sizeof(PNode));
    m->head->exp = -1;
    m->head->link = m->head;
    
    while (p->link->exp >= 0)
    {
        p = p->link;
        q = qx->head;
        while (q->link->exp >= 0)
        {
            q = q->link;
            temp = (PNode*)malloc(sizeof(PNode));
            temp->coef = p->coef * q->coef;
            temp->exp = p->exp + q->exp;

            m1 = m->head->link;
            m2 = m->head;

            while (m1 && m1->exp >= temp->exp)
            {
                m2 = m1;
                m1 = m1->link;
            }

            if (m2->exp == temp->exp)
            {
                m2->coef = m2->coef + temp->coef;
            }
            else
            {
                temp->link = m1;//完成新节点的插入
                m2->link = temp;;
            }

        }
    }
}

int main()
{
    Polynominal p,q,m;
    printf("第一个多项式：");
    Create(&p);
    printf("第二个多项式：");
    Create(&q);
    Muli(&p, &q, &m);
    Show(&m);
    return 0;
}