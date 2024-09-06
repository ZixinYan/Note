////#include<stdio.h>
////#include<stdlib.h>
////struct Num {
////	bool op;
////	int num;
////	Num* pre;
////	Num* next;
////};
////bool compare(Num* N1, Num* N2) {
////	if (sizeof(N1) >= sizeof(N2)) {
////		return true;
////	}
////	else {
////		return false
////	}
////}
////Num* calc(Num* N1,Num* N2) {
////	Num* temp1 = N1;
////	Num* temp2 = N2;
////	Num* res;
////	if (temp1->op = true) {
////		if (compare(N1, N2)) {
////			while (temp1 != NULL) {
////				if (temp2 != NULL) {
////					Num* restemp = (Num*)malloc(sizeof(Num*));
////					int i = 0;
////					i = temp1->num + temp2->num;
////					if (i > 9999) {
////						restemp->num = 9999;
////						restemp->pre->num++;
////					}
////					else {
////						restemp->num = i;
////					}
////					res->next = restemp;
////					restemp->pre = res;
////					res = res->next;
////					temp1 = temp1->next;
////					temp2 = temp2->next;
////				}
////				else {
////					Num* restemp = (Num*)malloc(sizeof(Num*));
////					restemp->num = N1->num;
////					res->next = restemp;
////					restemp->pre = res;
////					res = res->next;
////					
////				}
////			}
////		}
////		else {
////
////		}
////	}
////	return res;
////}
////
////int main() {
////	Num* N1;
////	Num* N2;
////	N1->pre = N1->next;
////	N2->pre = N2->next;
////	printf("Please enter N1: ");
////	do {
////		Num* temp = (Num*)malloc(sizeof(Num*));
////		scanf_s("%d", &temp->num);
////	}
////}
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <ctype.h>
//#include <Windows.h>
//
//typedef struct DualNode
//{
//    int data;
//    struct DualNode* prior, * next;
//}DualNode, * DualList;
//
//DualList InitList(int sign)
//{
//    DualList L;
//    L = (DualList)malloc(sizeof(DualNode));
//    L->next = L->prior = L;
//    L->data = sign;
//    return L;
//}
//
//void InsertNodeAtTail(DualList L, int data)
//{
//    DualNode* s;
//    s = (DualList)malloc(sizeof(DualNode));
//    s->data = data;
//    s->next = L;
//    s->prior = L->prior;
//    L->prior->next = s;
//    L->prior = s;
//}
//
//void InsertNodeAtHead(DualList L, int data)
//{
//    DualNode* s;
//    s = (DualList)malloc(sizeof(DualNode));
//    s->data = data;
//    s->next = L->next;
//    s->prior = L;
//    L->next->prior = s;
//    L->next = s;
//}
//
//void PrintList(DualList L)
//{
//    int FirstTime = 1;
//    DualNode* p = L;
//    if (p->data == -1) printf("-");
//    p = p->next;
//    while (p != L)
//    {
//        if (FirstTime)
//        {
//            FirstTime = 0;
//            printf("%d", p->data);
//        }
//        else
//        {
//            printf(",%4d", p->data);
//        }
//        p = p->next;
//    }
//    printf("\n");
//}
//
//DualList InputData()
//{
//    int FirstNum = 1, data;
//    char c;
//    DualList L;
//    L = (DualList)malloc(sizeof(DualNode));
//    L->next = L->prior = L;
//    printf("Please enter data: \n");
//    if ((c = getchar()) == '-')
//        L = InitList(-1);
//    else
//        L = InitList(1);
//    if (isdigit(c))
//        // 退格处理
//        ungetc(c, stdin);
//    do {
//        scanf_s("%d", &data);
//        InsertNodeAtTail(L, data);
//    } while ((c = getchar()) != '\n');
//    printf("Your Input is:\n");
//    PrintList(L);
//    return L;
//}
//
//void DelNode(DualList L, DualNode* p)
//{
//    p->prior->next = p->next;
//    p->next->prior = p->prior;
//    free(p);
//}
//
//void Add(DualList a, DualList b, DualList c)
//{
//    DualList pa, pb;
//    int carry = 0, tmp;
//    pa = a->prior;
//    pb = b->prior;
//    while ((pa != a) && (pb != b))
//    {
//        tmp = pa->data + pb->data + carry;
//        if (tmp >= 10000)
//        {
//            carry = 1;
//            tmp -= 10000;
//        }
//        else
//            carry = 0;
//        InsertNodeAtHead(c, tmp);
//        pa = pa->prior;
//        pb = pb->prior;
//    }
//    while (pa != a)
//    {
//        // pb = b
//        tmp = pa->data + carry;
//        if (tmp >= 1000)
//        {
//            carry = 1;
//            tmp -= 10000;
//        }
//        else
//            carry = 0;
//        InsertNodeAtHead(c, tmp);
//        pa = pa->prior;
//    }
//    while (pb != b)
//    {
//        // pa = a
//        tmp = pb->data + carry;
//        if (tmp >= 1000)
//        {
//            carry = 1;
//            tmp -= 10000;
//        }
//        else
//            carry = 0;
//        InsertNodeAtHead(c, tmp);
//        pb = pb->prior;
//    }
//    if (carry != 0)
//        InsertNodeAtHead(c, 1);
//}
//
//void Sub(DualList a, DualList b, DualList c)
//{
//    DualList pa, pb, pc;
//    int borrow = 0, tmp;
//    pa = a->prior;
//    pb = b->prior;
//    while ((pa != a) && (pb != b))
//    {
//        if (pa->data >= pb->data + borrow)
//        {
//            tmp = pa->data - pb->data - borrow;
//            borrow = 0;;
//        }
//        else
//        {
//            tmp = 10000 + pa->data - pb->data - borrow;
//            borrow = 1;
//        }
//        InsertNodeAtHead(c, tmp);
//        pa = pa->prior;
//        pb = pb->prior;
//    }
//    if (pa != a || (pa == a && pb == b && borrow == 0))
//    {
//        // a >= b
//        c->data = a->data;
//    }
//    if (c->data != a->data)
//    {
//        // a < b
//        pc = c->prior;
//        while (pc != c)
//        {
//            // 结果转换
//            if (pc == c->prior)
//                pc->data = 10000 - pc->data;
//            else
//                pc->data = 9999 - pc->data;
//            pc = pc->prior;
//        }
//        // 因为符号判断错误，所以borrow要取反
//        borrow = borrow ? 0 : 1;
//        while (pb != b)
//        {
//            if (pb->data >= borrow)
//            {
//                tmp = pb->data - borrow;
//                borrow = 0;
//            }
//            // 继续借位
//            else
//            {
//                tmp = 10000 + pb->data + borrow;
//                borrow = 1;
//            }
//            InsertNodeAtHead(c, tmp);
//            pb = pb->prior;
//        }
//    }
//    else {
//        // a>b
//        while (pa != a)
//        {
//            if (pa->data >= borrow)
//            {
//                tmp = pa->data - borrow;
//                borrow = 0;
//            }
//            else
//            {
//                tmp = 10000 - pa->data - borrow;
//                borrow = 1;
//            }
//            InsertNodeAtHead(c, tmp);
//            pa = pa->prior;
//        }
//    }
//    pc = c->next;
//    while (pc->next != c && pc->data == 0)
//    {
//        pc = pc->next;
//        DelNode(c, pc->prior);
//    }
//}
//
//DualList AddList(DualList a, DualList b)
//{
//    DualList c;
//    if (a->data * b->data > 0)
//    {
//        c = InitList(a->data);
//        Add(a, b, c);
//    }
//    else
//    {
//        c = InitList(b->data);
//        Sub(a, b, c);
//    }
//    return c;
//}
//
//int main(int argc, char const* argv[])
//{
//    while (1)
//    {
//        //便于测试
//        DualList a, b, c;
//        a = InputData();
//        b = InputData();
//        c = AddList(a, b);
//        printf("The result is:");
//        PrintList(c);
//        Sleep(5000);
//        system("cls");
//    }
//    return 0;
//}
