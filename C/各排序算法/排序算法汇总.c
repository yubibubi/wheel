#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define FALSE 0;
#define TRUE 1
#define ERROR 0
#define OK 1
#define Overflow 2//上溢
#define Underflow 3//下溢
#define NotPressent 4//元素不存在
#define Duplicate 5//有重复元素
#define MaxSize 100000


typedef int KeyType;
typedef int DataType;
typedef int ElemType;
typedef struct entry           //数据元素
{
	KeyType key;				//排序关键字，KeyType应该为可比较类型
	//DataType data;				//data包含数据元素中的其他数据项
}Entry;

typedef struct list {				//顺序表
	int n;				//待排序数据元素数量
	Entry D[MaxSize];		//静态数组存储数据元素
}List;


/*
void Init(List list)
{
	Entry e;
	int length;
	int i;
	printf("输入数组长度：");
	scanf_s("%d", &length);
	list.n = length;

	for (i = 0; i < length; i++)
	{
		int k, d;
		printf("请输入第%d个数据", i + 1);
		scanf_s("%d%d", &k, &d);
		list.D[i].key = k;
		list.D[i].data = d;
	}
	return;
}
*/

//简单选择排序
int FindMin(List list, int startIndex)//在startIndex至表位范围内找到最小关键字元素下标
{
	int i, minIndex = startIndex;
	for (i = startIndex + 1; i < list.n; i++)
	{
		if (list.D[i].key < list.D[minIndex].key)
			minIndex = i;
	}
	return minIndex;
}
void Swap(Entry* D, int i, int j)//交换顺序表中两个元素位置
{
	Entry temp;
	if (i == j)return;
	temp = *(D + i);
	*(D + i) = *(D + j);
	*(D + j) = temp;
}
void SelectSort(List* list)
{
	int minIndex, startIndex = 0;
	while (startIndex < list->n - 1)
	{
		minIndex = FindMin(*list, startIndex);
		Swap(list->D, startIndex, minIndex);
		startIndex++;
	}
}
//不稳定,时间的复杂度O(n^2),空间复杂度O(1)


//直接插入排序算法
void InsertSort(List* list)
{
	int i, j;//i为待插入元素下标
	Entry insertItem;//每一趟代插入
	for (i = 0; i < list->n; i++)
	{
		insertItem = list->D[i];//将第i个元素放入insertItem中，与前面有序数组比较
		for (j = i - 1; j >= 0; j--)
		{
			//不断将有序序列中元素向后移动，为待插入元素空出一个位置
			if (insertItem.key < list->D[j].key)
				list->D[j + 1] = list->D[j];
			else break;
		}
		list->D[j + 1] = insertItem;
	}
}
//稳定,时间复杂度O(n^2),空间复杂度O(1)


//冒泡排序算法：将最大（最小）元素沉底
typedef int BOOL;
void BubbleSort(List* list)
{
	int i, j;//i标识每趟排序范围最后一个元素下标，每趟排序元素下标范围是0~i
	for (i = list->n - 1; i > 0; i--)
	{
		BOOL isSwap = FALSE;//标记一趟排序中是否发生了元素交换
		for (j = 0; j < i; j++)
		{
			if (list->D[j].key > list->D[j + 1].key)
			{
				Swap(list->D, j, j + 1);
				isSwap = TRUE;
			}
		}
		if (!isSwap)break;
	}
}
//稳定,时间复杂度O(n^2),空间复杂度O(1)


//序列化分方法
int Partition(List* list, int low, int high)
{
	int i = low, j = high + 1;
	Entry pivot = list->D[low];//pivot是分割元素
	do {
		do i++; while (i <= high && list->D[i].key < pivot.key);//i前进
		do j--; while (list->D[j].key > pivot.key);//j前进
		if (i < j)Swap(list->D, i, j);
	} while (i < j);
	Swap(list->D, low, j);
	return j;//此时j成为分割元素下标
}
//快速排序算法
void QuickSort(List* list, int low, int high)//快速排序的递归函数
{
	int k;
	if (low < high)//当前排序序列至少包含2个元素
	{
		k = Partition(list, low, high);
		QuickSort(list, low, k - 1);
		QuickSort(list, k + 1, high);
	}
}
void mainQuickSort(List* list)//快速算法的主调用函数
{
	QuickSort(list, 0, list->n - 1);
}
//不稳定,时间复杂度最糟情况O(n^2),一般情况为O(ln(n));空间复杂度O(n)


//序列两路合并方法
//n1和n2是两个子序列长度，low是第一个子序列的第一个元素的下标
void Merge(List* list, Entry* temp, int low, int n1, int n2)
{
	int i = low, j = low + n1;//i,j初始时分别指向两个序列的第一个元素
	while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1)
	{
		if (list->D[i].key <= list->D[j].key)
			*temp++ = list->D[i++];
		else *temp++ = list->D[j++];
	}
	while (i <= low + n1 - 1)
		*temp++ = list->D[i++];//剩余元素直接复制到temp
	while (j <= low + n1 + n2 - 1)
		*temp++ = list->D[j++];//剩余元素直接复制到temp
}
//两路合并排序算法
void MergeSort(List* list)
{
	Entry temp[MaxSize];
	int low, n1, n2, i, size = 1;
	while (size < list->n)
	{
		low = 0;//low是第一个子序列的第一个元素的下标
		while (low + size < list->n)//low+list<list->n说明至少存在两个子序列需要合并
		{
			n1 = size;
			if (low + size * 2 < list->n)
				n2 = size;//计算第二个序列长度
			else
				n2 = list->n - low - size;
			Merge(list, temp + low, low, n1, n2);
			low += n1 + n2;//确定下一对代合并序列中第一个序列的第一个元素下标
		}
		for (i = 0; i < low; i++)
			list->D[i] = temp[i];//复制一趟合并排序结果
		size *= 2;//子序列长度翻倍
	}
}
//稳定,时间复杂度O(n*ln n),空间复杂度O(n)





void AdjustDown(Entry heap[], int current, int border)
{
	int p = current;
	int minChild;
	Entry temp;
	while (2 * p + 1 <= border)
	{
		if ((2 * p + 2 <= border) && heap[2 * p + 1].key > heap[2 * p + 2].key)
			minChild = 2 * p + 2;
		else
			minChild = 2 * p + 1;
		if (heap[p].key <= heap[minChild].key)
			break;
		else
		{
			temp.key = heap[p].key;
			heap[p].key = heap[minChild].key;
			heap[minChild].key = temp.key;
			p = minChild;
		}
	}
}

//堆排序算法
#define maxSize 1005
typedef struct maxheap//定义最大堆结构体
{
	int n;
	Entry D[maxSize];
}MaxHeap;
void HeapSort(List* hp)
{
	int i; Entry temp;
	for (i = (hp->n - 2) / 2; i >= 0; i--)
		AdjustDown(hp->D, i, hp->n - 1);
	for (i = hp->n - 1; i > 0; i--)
	{
		Swap(hp->D, 0, i);
		AdjustDown(hp->D, 0, i - 1);
	}
}
//不稳定,时间复杂度O(n*ln n),空间复杂度O(1)


void getRand(List *list,int n)
{
	int i = n;
	int a;
	list->n = MaxSize;
	for (i = 0; i < MaxSize; i++)
	{
		a = rand();
		list->D[i].key = a;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	List list;
	int i;
	int n;
	int a;
	double t1, t2;
	/*
	printf("请输入随机数个数：");
	scanf_s("%d", &n);
	*/

	
	getRand(&list, MaxSize);

	t1 = GetTickCount64();
	HeapSort(&list);
	t2 = GetTickCount64();

	printf("堆排序程序执行时间(%d)：%fms", MaxSize, t2 - t1);







	FILE* fp = NULL;
	errno_t err;
	if ((err = fopen_s(&fp, "D:\\test.txt", "w")) != 0)
		printf("The file was not opened\n");

	for (i = 0; i < MaxSize; i++)
	{
		fprintf(fp, "%d\n", list.D[i].key);
	}
	fclose(fp);
	printf("\nIt's OK!");

	return 0;
}