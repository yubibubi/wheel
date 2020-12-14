#include<stdlib.h>
#include<stdio.h>
typedef int ElemType;
typedef struct seqList 
{
	int n;
	int maxLength;
	ElemType* element;
}SeqList;



//顺序表初始化
#define ERROR 0;
#define OK 1;
#define Overflow 2;//上溢
#define Underflow 3;//下溢
#define NotPresent 4;//元素不存在
#define Duolicate 5;//有重复元素
typedef int Status;
Status Init(SeqList *L,int mSize)
{
	L->maxLength = mSize;
	L->n = 0;
	L->element = (ElemType*)malloc(sizeof(ElemType) * mSize);//动态生成一维数组空间
	if (!L->element)
		return ERROR;
	return OK;
}

//顺序表查找
Status Find(SeqList L, int i, ElemType* x)
{
	if (i<0 || i>L.n - 1)
		return ERROR;//判断元素下表i是否越界
	*x = L.element[i];//取出element[i]的值通过参数x返回
	return OK;
}

//顺序表元素插入
Status Insert(SeqList* L, int i, ElemType x)
{
	int j;
	if (i<-1 || i>L->n - 1)//判断是否越界
		return ERROR;
	if (L->n == L->maxLength)//判断顺序表存储空间是都已满
		return ERROR;
	for (j = L->n - 1; j > i; j--)
		L->element[j + 1] = L->element[j];//从后往前逐个后移元素
	L->element[i + 1] = x;//将新元素放入下标为i+1的位置
	L->n = L->n + 1;
	return OK;
}

//顺序表元素删除
Status Delete(SeqList* L, int i)
{
	int j;
	if (i<0 || i>L->n - 1)
		return ERROR;
	if (!L->n)
		return ERROR;
	for (j = i + 1; j < L->n; j++)
		L->element[j - 1] = L->element[j];
	L->n--;
	return OK;
}

//顺序表输出
Status Output(SeqList* L)
{
	int i;
	if (L->n == 0)//判断顺序表是否为空
		return ERROR;
	for (i = 0; i <= L->n - 1; i++)
		printf("%d ", L->element[i]);
	printf("\n");
	return OK;
}

//顺序表撤销
void Destroy(SeqList* L) 
{
	L->n = 0;
	L->maxLength = 0;
	free(L->element);
}


//主函数测试顺序表
void main()
{
	int i;
	SeqList list;
	Init(&list, 10);
	for (i = 0; i < 10; i++)
		Insert(&list, i - 1, i);
	Output(&list);
	Delete(&list, 0);
	Output(&list);
	Destroy(&list);
}