#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <iostream>
using namespace std;

//-----------------------------------------Linked list-----------------------------
//Create Link list
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, * Linklist;

void CreateList_L(Linklist& L, int n) {
	L = (Linklist)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = 1; i <= n; i++) {
		Linklist p = (Linklist)malloc(sizeof(LNode));
		scanf_s("%d", p->data);
		p->next = L->next;
		L->next = p;
	}
}

//DisplayList
void DisplayList_L(Linklist L) {
	Linklist& p = L->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
}

//InsertNode
void InsertList_L(Linklist& L, int i, int value) {
	Linklist& p = L;
	int j = 0;
	//find Location£»£»£»£»£»£»
	while (p && (j < i - 1)) {
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) {
		printf("ERROR");
	}
	//insert
	Linklist s = (Linklist)malloc(sizeof(LNode));
	s->data = value;
	s->next = p->next;
	p->next = s;
	printf("OK");
}

//Findlist
Linklist FindList_L(int value, Linklist& L) {
	Linklist& p = L->next;
	while (p != NULL && p->data != value) {
		p->next;
	}
	if (p != NULL) {
		return p;
	}
	else {
		printf("ERROR");
	}
}

//DeletNode
void ListDelete_L(Linklist& L, int i, int value) {
	Linklist& p = L;
	int j = 0;
	while ((p->next) && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1) {
		printf("ERROR");
	}
	Linklist& q = p->next;
	p->next = q->next;
	value = q->data;
	free(q);
	printf("OK");
}

//merging two ordered list 
Linklist merge_link(Linklist& head_a, Linklist& head_b)
{
	Linklist pa, pb, head,p;
	head = (Linklist)malloc(sizeof(LNode));
	head->next = NULL;     //initialize a new  empty list
	pa = head_a->next;
	pb = head_b->next;
	p = head;
	while (pa && pb)
	{
		if (pa->data <= pb->data) {
			head_a->next = pa->next;   //remove the node from A
			pa->next = NULL;
			p->next = pa; //insert into              
			pa = head_a->next;   //get the next node
			p = p->next;
		}
		else {
			head_b->next = pb->next;
			pb->next = NULL;
			p->next = pb;
			pb = head_b->next;
			p = p->next;
		}
	}
	if (pa) {
		p->next = pa;
	}
	if (pb)
	{
		p->next = pb;
	}
	free(head_a);
	free(head_b);
	return(head);
}

//-----------------------------------Circular Linked List--------------------------------

//Circular Linked Lists
typedef struct CLNode {
	int data;
	struct CLNode* next;
}CLNode, * CLinkList;

//create Linked Lists
void CreateList_CL(CLinkList& CL) {
	CL = (CLinkList)malloc(sizeof(CLNode));
	CL->next = CL;
}

//display
void DisplayList_CL(CLinkList& CL) {
	CL = CL->next;
	while (CL != NULL) {      //CLNode head = CL;  while(CL!=head)
		printf("%d", CL->data);
		CL = CL->next;
	}
}


//-----------------------------------Doubly Linked lists----------------------------------

typedef struct DLNode {
	int data;
	struct DLNode* next;
	struct DLNode* prior;
}DLNode,*DLinkList;

//create
void CreateList_DL(DLinkList& DL) {
	DL = (DLinkList)malloc(sizeof(DLNode));
	DL->next = DL->prior = NULL;
}

//Insert
void ListInsert_DL(DLinkList& L, int i, int value) {
	int j = 0;
	if (L != NULL && j < (i - 1)) {
		L = L->next;
	}
	else {
		printf("ERROR");
	}
	DLNode* s = (DLinkList)malloc(sizeof(DLNode));
	s->data = value;
	s->prior = L->prior;
	L->prior->next = s;
	s->next = L;
	L->prior = s;
	printf("OK");
}

//delete
void ListDelete_DL(DLinkList& L, int i, int value) {
	int j = 0;
	if (L != NULL && j < (i - 1)) {
		L = L->next;
	}
	else {
		printf("ERROR");
	}
	L->prior->next = L->next;
	L->next->prior = L->prior;
	free(L);
	printf("OK");
}

