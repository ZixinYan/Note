//#define _CRT_SECURE_NO_WARNING
//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
//#define MaxSize 100
//typedef char ElemType;
//typedef struct
//{
//	ElemType data[MaxSize];
//	int top;				
//} SqStack;					
//void InitStack(SqStack*& s) 
//{
//	s = (SqStack*)malloc(sizeof(SqStack));
//	s->top = -1;
//}
//
//void DestroyStack(SqStack*& s)
//{
//	free(s);
//}
//
//bool StackEmpty(SqStack* s) 
//{
//	return(s->top == -1);
//}
//
//bool Push(SqStack*& s, ElemType e)
//{
//	if (s->top == MaxSize - 1)
//		return false;
//	s->top++;
//	s->data[s->top] = e;
//	return true;
//}
//
//bool Pop(SqStack*& s, ElemType& e)
//{
//	if (s->top == -1)
//		return false;
//	e = s->data[s->top];
//	s->top--;
//	return true;
//}
//
//bool GetTop(SqStack* s, ElemType& e)
//{
//	if (s->top == -1) 
//		return false;
//	e = s->data[s->top];
//	return true;
//}
//void trans(char* exp, char postexp[])
//{
//	char e;
//	SqStack* Optr;
//	InitStack(Optr);
//	int i = 0;
//	while (*exp != '\0')
//	{
//		switch (*exp)
//		{
//		case '(':
//			Push(Optr, '(');
//			exp++;
//			break;
//		case ')':
//			Pop(Optr, e);
//			while (e != '(')
//			{
//				postexp[i++] = e;
//				Pop(Optr, e);
//			}
//			exp++;
//			break;
//		case '+':
//		case '-':
//			while (!StackEmpty(Optr))
//			{
//				GetTop(Optr, e);
//				if (e != '(')
//				{
//					postexp[i++] = e;
//					Pop(Optr, e);
//				}
//				else
//					break;
//			}
//			Push(Optr, *exp);
//			exp++;
//			break;
//		case '*':
//		case '/':
//			while (!StackEmpty(Optr))
//			{
//				GetTop(Optr, e);
//				if (e == '*' || e == '/')
//				{
//					postexp[i++] = e;
//					Pop(Optr, e);
//				}
//				else
//					break;
//			}
//			Push(Optr, *exp);
//			exp++;
//			break;
//		default:
//			while (*exp >= '0' && *exp <= '9')
//			{
//				postexp[i++] = *exp;
//				exp++;
//			}
//			postexp[i++] = '#';
//		}
//	}
//	while (!StackEmpty(Optr))
//	{
//		Pop(Optr, e);
//		postexp[i++] = e;
//	}
//	postexp[i] = '\0';
//	DestroyStack(Optr);
//}
//double compvalue(char* postexp)
//{
//	ElemType d, a, b, c, e;
//	SqStack* Opnd;
//	InitStack(Opnd);
//	while (*postexp != '\0')
//	{
//		switch (*postexp)
//		{
//		case '+':
//			Pop(Opnd, a);
//			Pop(Opnd, b);
//			c = b + a;
//			Push(Opnd, c);
//			break;
//		case '-':
//			Pop(Opnd, a);
//			Pop(Opnd, b);
//			c = b - a;
//			Push(Opnd, c);
//			break;
//		case '*':
//			Pop(Opnd, a);
//			Pop(Opnd, b);
//			c = b * a;
//			Push(Opnd, c);
//			break;
//		case'/':
//			Pop(Opnd, a);
//			Pop(Opnd, b);
//			if (a != 0)
//			{
//				c = b / a;
//				Push(Opnd, c);
//				break;
//			}
//			else
//			{
//				printf("\n\tERROR！\n");
//				exit(0);
//			}
//			break;
//		default:
//			d = 0;
//			while (*postexp >= '0' && *postexp <= '9')
//			{
//				d = 10 * d + *postexp - '0';
//				postexp++;
//			}
//			Push(Opnd, d);
//			break;
//		}
//		postexp++;
//	}
//	GetTop(Opnd, e);
//	DestroyStack(Opnd);
//	return e;
//}
//
//
//
//int main()
//{
//	char exp[MaxSize];
//	printf("请输入表达式：");
//	int i;
//	for (i = 0; i < MaxSize; i++)
//	{
//		scanf_s("%c", &exp[i]);
//		if (exp[i] == '\n')
//		{
//			exp[i] = NULL;
//			break;
//		}
//	}
//	char postexp[MaxSize];
//	trans(exp, postexp);
//	printf("%s\n", postexp);
//	printf("表达式的值：%g\n", compvalue(postexp));
//	return 1;
//}