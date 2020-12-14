#include<stdio.h>
#include<stdlib.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef struct btnode
{
    ElemType element;
    struct btnode* lChild;
    struct btnode* rChild;
}BTNode;
typedef struct binarytree
{
    BTNode* root;
}BinaryTree;

//创造一个根节点（新二叉树）
void Create(BinaryTree* bt)
{
    bt->root = NULL;
}

//先序遍历创建二叉树
BTNode* PreCreatBT(BTNode* t)
{
    char ch;
    ch = getchar();
    if (ch == '#')//空二叉树
        t = NULL;
    else
    {
        t = (BTNode*)malloc(sizeof(BTNode));
        t->element = ch;
        t->lChild = PreCreatBT(t->lChild);
        t->rChild = PreCreatBT(t->rChild);
    }
    return t;
}
void PreMakeTree(BinaryTree* bt)
{
    bt->root = PreCreatBT(bt->root);
}


//创建新节点时所用函数
BTNode* NewNode(ElemType x, BTNode* ln, BTNode* rn)
{
    BTNode* p = (BTNode*)malloc(sizeof(BTNode));
    p->element = x;
    p->lChild = ln;
    p->rChild = rn;
    return p;
}

//用x取出bt节点元素
BOOL Root(BinaryTree* bt, ElemType* x)
{
    if (bt->root)
    {
        x = &bt->root->element;
        return TRUE;
    }
    else
        return FALSE;
}

//构建二叉树
void MakeTree(BinaryTree* bt, ElemType e, BinaryTree* left, BinaryTree* right)
{
    if (bt->root || left == right)//bt必须为空（新）节点，bt的值为e，左右子树分别为left与right
        return;
    bt->root = NewNode(e, left->root, right->root);
    left->root = right->root = NULL;//释放左右子树的空间
}

//先序遍历
void PreOrder(BTNode* t);
void PreOrderTree(BinaryTree* bt)
{
    PreOrder(bt->root);
}
void PreOrder(BTNode* t)
{
    if (!t)
        return;
    printf("%c", t->element);
    PreOrder(t->lChild);
    PreOrder(t->rChild);
}

//中序遍历
void MidOrder(BTNode* t);
void MidOrderTree(BinaryTree* bt)
{
    MidOrder(bt->root);
}
void MidOrder(BTNode* t)
{
    if (!t)
        return;
    MidOrder(t->lChild);
    printf("%c", t->element);
    MidOrder(t->rChild);
}

//后序遍历
void PosOrder(BTNode* t);
void PosOrderTree(BinaryTree* bt)
{
    PosOrder(bt->root);
}
void PosOrder(BTNode* t)
{
    if (!t)
        return;
    PosOrder(t->lChild);
    PosOrder(t->rChild);
    printf("%c", t->element);
}

//2.求二叉树结点数
int Size(BTNode* t)
{
    if (!t)
        return 0;
    else
        return Size(t->lChild) + Size(t->rChild) + 1;//好递归~~
}
int TreeSize(BinaryTree* bt)
{
    return Size(bt->root);
}

//2.求二叉树叶子结点数
int lSize(BTNode* t, int* num)
{
    if (!t)
        return 0;
    if (!(t->lChild) && !(t->rChild))
        (*num)++;
    lSize(t->lChild, num);
    lSize(t->rChild, num);
}
int LeafSize(BinaryTree* bt)
{
    int num = 0;
    lSize(bt->root, &num);
    return num;
}

//2.求二叉树高度
int Height(BTNode* t)
{
    int HL, HR, MaxH;
    if (!t)
        return 0;
    else
    {
        HL = Height(t->lChild);
        HR = Height(t->rChild);
        MaxH = HL > HR ? HL : HR;
        return (MaxH + 1);
    }
}
int TreeHeight(BinaryTree* bt)
{
    return Height(bt->root);
}

//2.交换二叉树所有左右子树
void swap(BTNode* t)
{
    BTNode* temp;
    if (!t)
        return;
    else
    {
        temp = t->lChild;
        t->lChild = t->rChild;
        t->rChild = temp;
        swap(t->lChild);
        swap(t->rChild);
    }
}
void SwapTree(BinaryTree* bt)
{
    swap(bt->root);
}

//清空二叉树
void Clear(BTNode* t);
void TreeClear(BinaryTree* bt)
{
    Clear(bt->root);
}
void Clear(BTNode* t)
{
    if (!t)
        return;
    Clear(t->lChild);
    Clear(t->rChild);
    free(t);
}


//typedef ElemType char;
void main()
{
    BinaryTree z;
    /*Create(&a);
    Create(&b);
    Create(&x);
    Create(&y);
    Create(&z);
    MakeTree(&y,'E',&a,&b);
    MakeTree(&z,'F',&a,&b);
    MakeTree(&x,'C',&y,&z);
    MakeTree(&y,'D',&a,&b);
    MakeTree(&z,'B',&y,&x);*/
    PreMakeTree(&z);
    printf("先序遍历：");
    PreOrderTree(&z);
    printf("\n");
    printf("中序遍历：");
    MidOrderTree(&z);
    printf("\n");
    printf("后序遍历：");
    PosOrderTree(&z);
    printf("\n");
    printf("交换左右子树先序遍历：");
    SwapTree(&z);
    PreOrderTree(&z);
    printf("\n");
    
    printf("%d", TreeSize(&z));
    printf("\n");
    printf("%d", LeafSize(&z));
    printf("\n");
    printf("%d", TreeHeight(&z));
    TreeClear(&z);
}