#include <stdio.h>
#include<math.h>
#include <algorithm>
#include <process.h>
//------------------------------BiTree------------------------------------
typedef struct tree_node {
	int element;
	tree_node* left;
	tree_node* right;
}BiTNode,*BiTree;
//create
void CreateBiTree(BiTree n) {
	int ch;
	scanf_s("%d", &ch);
	if (!(n = (BiTree)malloc(sizeof(BiTNode)))) {
		exit(OVERFLOW);
	}
	else {
		n->element = ch;
		CreateBiTree(n->left);
		CreateBiTree(n->right);
	}
}
//Traversal
//Preorder Traversal
//Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))
//{
//	if (T)
//	{
//		if (visit(T->data))								//if T pointers to a node
//			if (PreOrderTraverse(T->lchild, visit))
//				if (PreOrderTraverse(T->rchild, visit))
//					return OK;
//		return ERROR;
//	}
//	return OK;
//}
bool PreOrderTraverse(BiTree B) {
	if (B == NULL) {
		printf("ERROR");
		return false; // Added return statement when the tree is empty
	}

	// Visit the current node
	printf("%d", B->element);

	// Recursively traverse the left subtree
	bool left = PreOrderTraverse(B->left);
	if (!left) {
		return false; // Return false if the left subtree traversal fails
	}

	// Recursively traverse the right subtree
	bool right = PreOrderTraverse(B->right);
	if (!right) {
		return false; // Return false if the right subtree traversal fails
	}

	printf("OK");
	return true; // Return true if both left and right subtree traversals are successful
}


//Inorder Traversal
//Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e))
//{
//	if (T)     //if T pointers to a node
//	{
//		if (InOrderTraverse(T->lchild, visit))
//			if (visit(T->data))
//				if (InOrderTraverse(T->rchild, visit))
//					return OK;
//		return ERROR;
//	}
//	return OK;
//}
bool InorderTraverse(BiTree B) {
	if (B == NULL) {
		printf("ERROR");
		return false; // Added return statement when the tree is empty
	}

	// Recursively traverse the left subtree
	bool left = InorderTraverse(B->left);

	if (!left) {
		return false; // Return false if the left subtree traversal fails
	}

	// Visit the current node
	printf("%d", B->element);

	// Recursively traverse the right subtree
	bool right = InorderTraverse(B->right);

	if (!right) {
		return false; // Return false if the right subtree traversal fails
	}

	printf("OK");
	return true; // Return true if both left and right subtree traversals are successful
}


//Postorder Traversal
//Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e))
//{
//	if (T) //if T pointers to a node
//	{
//		if (PostOrderTraverse(T->lchild, visit))
//			if (PostOrderTraverse(T->rchild, visit))
//				if (visit(T->data))
//					return OK;
//		return ERROR;
//	}
//	return OK;
//}
bool PostOrderTraverse(BiTree B) {
	if (B == NULL) {
		printf("ERROR");
		return false; // Added return statement when the tree is empty
	}
	bool left = PostOrderTraverse(B->left);  // Recursively traverse the left subtree
	bool right = PostOrderTraverse(B->right); // Recursively traverse the right subtree

	// Visit the current node
	printf("%d", B->element);

	// If any subtree traversal failed, return false
	if (!left || !right) {
		return false;
	}

	printf("OK");
	return true; // Return true if both left and right subtree traversals were successful
}

//Height of Tree
int max(int a, int b) {
	return (a > b) ? a : b;
}
int Height(BiTree T) {
	if (T == NULL) // if T points to a null node
		return -1; // return -1 for an empty tree, or use 0 if you prefer
	else
		return 1 + max(Height(T->left), Height(T->right)); // height is 1 + max of left and right subtree heights
}

//Searching an element
BiTree PreorderTraverse(BiTree T, int e)
{
	BiTree pt;
	if (T)
	{
		if (T->element == e) return T;
		if (pt = PreorderTraverse(T->left, e))
			return pt;
		return PreorderTraverse(T->right, e);
	}
	return NULL;
}

//Non Recursive Traversal      ---Traversal based on Stack
typedef int Status;
#define OK 1
#define ERROR 0
typedef struct {
	BiTree* base;
	BiTree* top;
	int stacksize;
} SqStack;

Status InitStack(SqStack* S) {
	S->base = (BiTree*)malloc(100 * sizeof(BiTree));
	if (!S->base) return ERROR;
	S->top = S->base;
	S->stacksize = 100;
	return OK;
}

Status StackEmpty(SqStack S) {
	return S.top == S.base;
}

Status Push(SqStack* S, BiTree e) {
	if (S->top - S->base >= S->stacksize) {
		S->base = (BiTree*)realloc(S->base, (S->stacksize + 10) * sizeof(BiTree));
		if (!S->base) return ERROR;
		S->top = S->base + S->stacksize;
		S->stacksize += 10;
	}
	*(S->top++) = e;
	return OK;
}

Status Pop(SqStack* S, BiTree* e) {
	if (S->top == S->base) return ERROR;
	*e = *(--S->top);
	return OK;
}

Status DestroyStack(SqStack* S) {
	free(S->base);
	S->base = S->top = NULL;
	S->stacksize = 0;
	return OK;
}

Status InorderTraverse(BiTree T, Status(*visit)(int e)) {
	SqStack S;
	InitStack(&S);
	BiTree p = T;
	while (p || !StackEmpty(S)) {
		if (p) {
			Push(&S, p);
			p = p->left;
		}
		else {
			Pop(&S, &p);
			if (!visit(p->element)) return ERROR;
			p = p->right; // visit its right subtree
		}
	}
	DestroyStack(&S);
	return OK;
}




//-----------------------------Decision Tree-------------------------------
//-----------------------------Threaded Tree-------------------------------
// create ThreadTree
typedef struct BiThrNode {
	int data;
	struct BiThrNode* lchild, * rchild;
	int Ltag, Rtag; 
	// Ltag==0 means lchild points to left child, Ltag==1 means lchild is a thread
	// Rtag==0 means rchild points to right child, Rtag==1 means rchild is a thread
} BiThrNode, * BiThrTree;
typedef int Status;
#define OK 1
#define ERROR 0
#define Link 0
#define Thread 1
Status InorderTraverse_Thr(BiThrTree T, Status(*visit)(int e)) {
	BiThrTree p = T->lchild;  // Start from the root's left child
	while (p != T) {  // Do until returning to the root
		// Go to the leftmost node
		while (p->Ltag == Link) p = p->lchild;

		// Visit the current node
		if (!visit(p->data)) return ERROR;

		// While the current node's right link is a thread and not pointing to the root
		while (p->Rtag == Thread && p->rchild != T) {
			p = p->rchild;  // Go to the successor
			if (!visit(p->data)) return ERROR;
		}
		// Move to the right subtree
		p = p->rchild;
	}
	return OK;
}


//-----------------------------Huffman Code-------------------------------
#define infinity 10
typedef unsigned int Index;
typedef struct
{    //definition of a node
	unsigned int weight;
	Index parent, lchild, rchild;
} HTNode, * HuffmanTree;
typedef char** HuffmanCode;
//dynamic array to store huffman tree
void  select(HuffmanTree& HT, Index m, Index& S1, Index& S2)
{
	int S1 = 0;
	int S2 = 0;
	int m1 = infinity;
	int m2 = infinity;//infinity is the maximum weight
	for (int j = 1; j <= m; j++)
	{
		if (HT[j].parent == 0)
		{
			if (HT[j].weight < m1)
			{
				m2 = m1; S2 = S1;
				m1 = HT[j].weight; S1 = j;
			}
			else
				if (HT[j].weight < m2) { m2 = HT[j].weight; S2 = j; }
		}
	}
}
void CreateBT(HuffmanTree& HT, Index& NR,
	Index l, Index r)
{//root store to HT[NR]
  //HT[l]and HT[r] points to left child and right child
	HT[NR].weight = HT[l].weight + HT[r].weight;
	HT[NR].parent = 0;
	HT[NR].lchild = l;
	HT[NR].rchild = r;
	HT[l].parent = NR; HT[r].parent = NR;
}
void Huffman(HuffmanTree& HT, unsigned int WA[], int n)
{//construct a huffman tree save to HT[1..2n-1] 
  //weights to n leaf nodes n save to array WA
  //root of Huffman is in HT[2n-1]
	HT = (HTNode*)malloc(2 * n * sizeof(HTNode));
	for (int i = 1; i <= n; i++)  //initilize Huffman tree
	{
		HT[i].weight = WA[i];
		HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
	}
	//construct internal nodes of huffman tree
	for (int i = 1; i < n; i++)
	{//find two smallest element in HT[1~n+i-1]
		   //save its index to variables l and r
		Index l;
		Index r;
		select(HT, n + i - 1, l, r);
		Index temp = n + i;
		//create a new tree£¬root in HT[n+i]£¬
	   //left child in HT[l] and right in HT[r]
		CreateBT(HT, temp, l, r);
	}
}



//-----------------------------Application---------------------------------
//Print Arithmetic Expressions
void Outputexpress(BiTree T)
{
	if (T)
	{
		if (T->left != NULL)
		{
			printf("(");
			Outputexpress(T->left);
		}
		printf("%d", T->element);
		if (T->right != NULL)
		{
			Outputexpress(T->right);
			printf(")");
		}
	}
}

