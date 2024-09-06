#include <stdio.h>
#include<windows.h>
#include<stack>
#include <string>
#define Stack_Init_Size 100
#define StackIncrement 10
using namespace std;


//---------------------------------------Based on Array---------------------------------
typedef struct {
	int* base;//nase address of stack
	int* top;//top address
	int stacksize;//max size of stack
}SqStack;

//initial stack
void InitStack(SqStack& S) {
	S.base = (int*)malloc(Stack_Init_Size * sizeof(int));
	if (!S.base) {
		exit(OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = Stack_Init_Size;
}

//Push Stack
void Push(SqStack& S, int e) {
	if (S.top - S.base >= S.stacksize) {
		S.base = (int*)realloc(S.base,(Stack_Init_Size+StackIncrement) * sizeof(int));
		if (!S.base) {
			exit(OVERFLOW);
		}
		S.stacksize += StackIncrement;
	}
	*S.top++ = e;
	printf("OK");
}

//Pop Stack
void Pop(SqStack& S, int& e) {
	if (S.top = S.base) {
		printf("ERROR");
	}
	e = *--S.top;
	printf("OK");
}

//----------------------------------------Based on Linked List------------------------------
//数组快于链表，因为栈调用频繁所以大多数栈通过数组实现；
typedef struct LNode{
	int data;
	struct LNode* next;
}LNode,*LinkList;

//Initial stack
void Init_Stack(LinkList& S) {
	S = NULL;
}

//Push Stack
void Push(int data,LinkList& L) {
	LNode* n = (LNode*)malloc(sizeof(LNode));
	if (!n) {
		printf("ERROR");
	}
	n->data = data;
	n->next = L;
	L = n;
	printf("OK");
}

//Pop Stack
int Pop(LinkList& L) {
	if (!L) { //if stack is empty
		printf("ERROR");
	}
	LNode* temp = L;
	L = L->next;//Remember to move point
	int data = temp->data;
	free(temp);
	return data;
}


//---------------------------Application--------------------------
////Balancing Symbols
//Stauts matching(char* exp) {
//	SqStack S;
//	int state = 1, i = 0;
//	InitStack(S);
//	while (i < length(exp) && state) {
//		switch (exp[i]) {
//		case'[':
//		case'(':
//		{
//			Push(S, exp[i]);
//			i++;
//			break;
//		}
//		case')':
//			char e;
//			GetTop(S, e);
//			if (!StackEmpty(S) && e == '(') {
//				Pop(S, e);
//				i++;
//			}
//			else {
//				state = 0;
//			}
//			break;
//		}
//		case']':
//		{
//			GetTop(S, e);
//			if (!StackEmpty(S) && e == '[') {
//				Pop(S, e);
//				i++;
//			}
//			else {
//				state = 0;
//			}
//			break;
//		}
//		default:
//		{
//			i++;
//			break;
//		}
//	}
//	if (state && IsEmpty(S)) {
//		return OK;
//	}
//	else {
//		return ERROR;
//	}
//
//}


////A Mazing Problem
//typedef struct
//{
//	short int row;             
//	short int col;             
//	short int dir;
//} SElemType;   //element of stack
//typedef struct
//{
//	SElemType* base;    //base address of stack
//	SElemType* top;     //top address
//	int stacksize;     //max size of stack 
//} SqStack;
//void Maze() {
//	while (stack is not empty)
//	{
//		/* move to position at top of stack */
//		<row, col, dir> = delete from top of stack;
//		while (there are more moves from current position)
//		{
//			<next_row, next_col > = coordinates of next move;
//			dir = next direction of move;
//			if ((next_row == EXIT_ROW) && (next_col == EXIT_COL))
//				success;
//			if (maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0)
//			{
//				/* legal move and haven’t been there */
//				mark[next_row][next_col] = 1;
//				/* save current position and direction */
//				add <row, col, dir> to the top of the stack;
//				row = next_row;
//				col = next_col;
//				dir = north;
//			} //end if
//		} //end while
//	} //end while
//	printf("No path found\n");
//}


//Infix to Postfix
//int priority(char op)      //return the precedence of operator 
//{
//	int prio;
//	switch (op)
//	{
//	case ' * ':
//	case ' / ':
//		prio = 2; break;
//	case ' + ':
//	case ' - ':
//		prio = 1; break;
//	case '(':
//	case '#':
//		prio = 0; break;
//	default:                       //nonoperator
//		prio = -1; break;
//	}
//	return prio;
//}
//void translate(char* S1, char* S2)
//{  //convert infix of string S1 to postfix of string S2
//	InitStack(OPTR);      //initialize a stack of operator
//	Push(OPTR, ’#’);         //add ‘#’ to stack
//	i = j = 0;
//	ch = S1[i];
//	while (ch != ‘#’)
//	{
//		switch (ch)
//		{
//		case ‘(‘:
//			Push(OPTR, ch);
//			ch = S1[++i];
//			break;
//		case ‘)’:
//			GetTop(OPTR, e);
//			while (e != ‘(‘)
//			{
//				S2[j++] = e;
//				pop(OPTR, e);
//				GetTop(OPTR, e);
//			}
//			pop(OPTR, e);
//			ch = S1[++i]; break;
//		case ‘ + ’:
//		case ‘ - ’:
//		case ‘* ’:
//		case ‘ / ’:
//			GetTop(OPTR, e);
//			while (priority(e) >= priority(ch))
//			{
//				S2[j++] = e; pop(OPTR, e); GetTop(OPTR, e);
//			}
//			Push(OPTR, ch);
//			ch = S1[++i];
//			break;
//		defaule:
//			S2[j++] = ch; ch = S1[++i];
//			break;
//		}
//	}
//	while (!StackEmpty(OPTR))
//	{
//		pop(OPTR, e); S2[j++] = e;
//	}
//	S2[j] = ‘#’;
//	DestroyStack(S);
//}




//-------------------------------------Circular Queue------------------------------------
#define   MAXQSIZE    100    //Max size 
typedef struct {
	int* base;               //base address 
	int front;               //front index
	int rear;                //rear index
} SqQueue;
//create
void  InitQueue(SqQueue& Q)
{
	Q.base = (int*)malloc(MAXQSIZE * sizeof(int));
	if (!Q.base)
		exit(OVERFLOW);
	Q.front = Q.rear = 0;
	printf("OK");
}
//inster
void InsertQueue(SqQueue& Q, int e)
{
	if (Q.front == (Q.rear + 1) % MAXQSIZE)  //queue q is full
		printf("ERROR");
	Q.base[Q.rear] = e;                //inserts an element
	Q.rear = (Q.rear + 1) % MAXQSIZE; //move rear index
	printf("OK");
}
//delete
void DeleteQueue(SqQueue& Q, int& e)
/*if queue Q is not empty,delete an element in front of the queue */ {
	if (Q.rear == Q.front)     //if queue Q is empty
		printf("ERROR");
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	printf("OK");
}

//-------------------------------Based on Linked List-------------------------
typedef struct QNode //structure of a node 
{
	int data;       //data item
	struct QNode *next;   //pointer to next
}QNode, * QueuePtr;
typedef struct
{ //structure of linked queue
	QueuePtr front;      //pointer to front
	QueuePtr rear;        //pointer to rear
	//int QueueSize;
} LinkQueue;
//create
void InitQueue(LinkQueue& Q)
//construct an empty linked queue
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	printf("OK");
}
//insert
void InsertnQueue(LinkQueue& Q, int e)
{ //insert an element e at the rear of a queue
	QNode* p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	printf("OK");
}
//delete
void DeleteQueue(LinkQueue& Q, int& e)
{ //delete an element in front of a queue 
	if (Q.front == Q.rear)
		printf("ERROR");
	QNode* p = Q.front->next;
	e = p->data;
	if (Q.rear == p)
		Q.rear = Q.front; //when deleted element was the only one 
	Q.front->next = p->next;
	free(p);
	printf("OK");
}
