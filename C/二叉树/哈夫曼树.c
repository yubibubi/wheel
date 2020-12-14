#include <stdlib.h>
#include <stdio.h>
typedef struct BTNode{
	int  element;//节点数值
	struct BTNode * lchild;//左子节点
	struct BTNode * rchild;//右子节点
}BTNode;

typedef struct binarytree
{
	BTNode *root;
}BinaryTree;
void Create(BinaryTree *bt)
{
	bt->root=NULL;
}
BTNode* NewNode(int x,BTNode *ln,BTNode *rn)
{
	BTNode *p=(BTNode *)malloc(sizeof(BTNode));
	p->element=x;
	p->lchild=ln;
	p->rchild=rn;
	return p;
}

void MakeTree(BinaryTree*bt,int e,BinaryTree *left,BinaryTree *right)
{
	if(bt->root||left==right)
		return;
	bt->root=NewNode(e,left->root,right->root);
	left->root=right->root=NULL;
}

typedef struct hfmtNode{
	BinaryTree element;
	int w;
	struct hfmtNode *lChild;
	struct hfmtNode *rChild;
}HFMTNode;


typedef int BOOL;
typedef BTNode ElemType;
typedef struct priorityQueue
{
	BTNode *elements;
	int n;
	int maxsize;
}PriorityQueue;

void CreatePQ(PriorityQueue *PQ,int mSize)
{
	PQ->maxsize=mSize;
	PQ->n=0;
	PQ->elements=(BTNode *)malloc(mSize*sizeof(BTNode));
}

BOOL IsFULL(PriorityQueue *PQ)
{
	if(PQ->n==PQ->maxsize)
		return 1;
	else
		return 0;
}

BOOL IsEmpty(PriorityQueue *PQ)
{
	if(PQ->n==0)
		return 1;
	else
		return 0;
}


void AdjustUp(BTNode heap[],int current)
{
	int p=current;
	BTNode temp;
	while(p>0)
	{
		if(heap[p].element<heap[(p-1)/2].element)
		{
			temp.element=heap[p].element;
			heap[p].element=heap[(p-1)/2].element;
			heap[(p-1)/2].element=temp.element;
			p=(p-1)/2;
		}
		else
			break;
	}
}

void AdjustDown(BTNode heap[],int current,int border)
{
	int p=current;
	int minChild;
	BTNode temp;
	while(2*p+1<=border)
	{
		if((2*p+2<=border)&&heap[2*p+1].element>heap[2*p+2].element)
			minChild=2*p+2;
		else
			minChild=2*p+1;
		if(heap[p].element<=heap[minChild].element)
			break;
		else
		{
			temp.element=heap[p].element;
			heap[p].element=heap[minChild].element;
			heap[minChild].element=temp.element;
			p=minChild;
		}
	}
}

void Append(PriorityQueue *PQ,BTNode *x)
{
	if(IsFULL(PQ))
		return;
	PQ->elements[PQ->n].element=x->element;
	PQ->elements[PQ->n].lchild=x->lchild;
	PQ->elements[PQ->n].rchild=x->rchild;
	PQ->n++;
	AdjustUp(PQ->elements,PQ->n-1);
}

void Serve(PriorityQueue *PQ,BinaryTree *x)
{
	if(IsEmpty(PQ))
		return;
	*x->root=PQ->elements[0];
	PQ->n--;
	PQ->elements[0]=PQ->elements[PQ->n];
	AdjustDown(PQ->elements,0,PQ->n-1);
}

BinaryTree CreateHFMTree(int w[],int m)
{
	PriorityQueue PQ;
	BinaryTree f;
	BinaryTree l,r;
	
	Create(&l);
	Create(&r);
	Create(&f);
	CreatePQ(&PQ,m);
	for(int i=0;i<m;i++)
	{
	
		BinaryTree h;
		Create(&h);
		MakeTree(&h,w[i],&l,&r);
		Append(&PQ,h.root);
	}

	MakeTree(&f,0,&l,&r);
	while(PQ.n>1)
	{
		BinaryTree x,y,z;
		Create(&x);
	    Create(&y);
	    Create(&z);
		MakeTree(&x,0,&l,&r);
		MakeTree(&y,0,&l,&r);
		Serve(&PQ,&x);
		Serve(&PQ,&y);
	if(x.root->element<y.root->element)
		MakeTree(&z,(x.root->element+y.root->element),&x,&y);
	else
		MakeTree(&z,(x.root->element+y.root->element),&y,&x);
	Append(&PQ,z.root);
	}
	Serve(&PQ,&f);
	return f;
}


void HuffManCoding(BTNode *FBT, int len)//len初始值为0  
{  
    static int a[10];//定义静态数组a，保存每个叶子的编码，数组长度至少是树深度减一  
	if (FBT!= NULL)//访问到叶子结点时输出其保存在数组a中的0和1序列编码  
    {  
		if (FBT->lchild == NULL && FBT->rchild == NULL)  
        {  
            int i;  
			printf("结点权值为%d的编码：", FBT->element);  
            for (i = 0; i < len; i++)  
                printf("%d", a[i]);  
            printf("\n");  
        }  
        else//访问到非叶子结点时分别向左右子树递归调用，并把分支上的0、1编码保存到数组a  
        {   //的对应元素中，向下深入一层时len值增1  
            a[len] = 0;  
			HuffManCoding(FBT->lchild, len + 1);  
            a[len] = 1;  
			HuffManCoding(FBT->rchild, len + 1);  
        }  
    }  
}  
void PreOrder(BTNode* t)
{
	if(!t)
		return;
	printf("%d ",t->element);
	PreOrder(t->lchild);
	PreOrder(t->rchild);
}
void PreOrderTree(BinaryTree *bt)
{
	printf("先序遍历:");
	PreOrder(bt->root);
	printf("\n");
}

void main()  
{  
    int n, i;  
    int* a;  
    BinaryTree fbt; 
	Create(&fbt);
    printf("从键盘输入待构造的哈夫曼树中带权叶子结点数n：");  
    while(1)  
    {  
        scanf("%d", &n);  
        if (n > 1)  
            break;  
        else  
            printf("重输n值：");  
    }  
    a = (int *)malloc(n*sizeof(int));  
    printf("从键盘输入%d个整数作为权值：", n);  
    for (i = 0; i < n; i++)  
        scanf("%d", &a[i]);  
    fbt = CreateHFMTree(a, n);  
    printf("广义表形式的哈夫曼树：");  
	PreOrderTree(&fbt);
    printf("\n");  
    printf("树中每个叶子结点的哈夫曼编码：\n");  
	HuffManCoding(fbt.root, 0);  
}  