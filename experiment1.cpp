//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<malloc.h>
//#include<string.h>
//
//typedef struct Polynomial {
//    float coef; //系数
//    int expn;   //指数
//    struct Polynomial* next;//指针
//} Polynomial, * Polyn;
//
//Polyn CreatPolyn(Polyn head, int m) {
//    head = (Polyn)malloc(sizeof(struct Polynomial));
//    head->next = NULL;
//    for (int i = 1; i <= m; i++) {
//        Polyn p = (Polyn)malloc(sizeof(struct Polynomial));
//        printf("请输入系数与指数：");
//        scanf("%f%d", &p->coef, &p->expn);
//        if (p->coef == 0) {
//            free(p);
//            continue;
//        }
//        else {
//            Polyn q1, q2;
//            q1 = head;
//            q2 = head->next;
//            while (q2 != NULL && p->expn < q2->expn) {
//                q1 = q2;
//                q2 = q2->next;
//            }
//            if (q2 != NULL && p->expn == q2->expn) {
//                q2->coef += p->coef;
//                if (q2->coef == 0) {
//                    q1->next = q2->next;
//                    free(q2);
//                }
//                free(p);
//            }
//            else {
//                p->next = q2;
//                q1->next = p;
//            }
//        }
//    }
//    return head;
//}
//
//void printPoLlyn(Polyn head) {
//    Polyn q = head->next;
//    int flag = 0;
//    if (!q) {
//        puts("0");
//        puts("\n");
//        return;
//    }
//    while (q) {
//        if (q->coef > 0 && flag == 1) {
//            printf("+");
//        }
//        flag = 1;
//        if (q->coef != 1 && q->coef != -1) {
//            printf("%g", q->coef);
//            if (q->expn == 1) {
//                printf("x");
//            }
//            else if (q->expn != 0) {
//                printf("x^%d", q->expn);
//            }
//        }
//        else {
//            if (q->coef == 1) {
//                if (q->expn == 0) printf("1");
//                else if (q->expn == 1) printf("x");
//                else printf("x^%d", q->expn);
//            }
//            if (q->coef == -1) {
//                if (q->expn == 0) printf("-1");
//                else if (q->expn == 1) printf("-x");
//                else printf("-x^%d", q->expn);
//            }
//        }
//        q = q->next;
//    }
//    printf("\n");
//}
//
//int compare(Polyn a, Polyn b) {
//    if (a && b) {
//        if (a->expn > b->expn) return 1;
//        else if (a->expn < b->expn) return -1;
//        else return 0;
//    }
//    else if (!a && b) return -1;
//    else if (a && !b) return 1;
//    else if (!a && !b)return 0;
//}
//
//Polyn addPolyn(Polyn a, Polyn b) {
//    Polyn head, temp;
//    Polyn qa = a->next;
//    Polyn qb = b->next;
//    Polyn hc = (Polyn)malloc(sizeof(Polynomial));
//    hc->next = NULL;
//    head = hc;
//    while (qa || qb) {
//        temp = (Polyn)malloc(sizeof(Polynomial));
//        if (compare(qa, qb) == 1) {
//            temp->coef = qa->coef;
//            temp->expn = qa->expn;
//            qa = qa->next;
//        }
//        else if (compare(qa, qb) == 0) {
//            temp->coef = qa->coef + qb->coef;
//            temp->expn = qa->expn;
//            qa = qa->next;
//            qb = qb->next;
//        }
//        else {
//            temp->coef = qb->coef;
//            temp->expn = qb->expn;
//            qb = qb->next;
//        }
//
//        if (temp->coef != 0) {
//            temp->next = hc->next;
//            hc->next = temp;
//            hc = temp;
//        }
//        else free(temp);
//    }
//    return head;
//}
//
//Polyn subPolyn(Polyn a, Polyn b) {
//    Polyn h = b;
//    Polyn p = b->next;
//    while (p) {
//        p->coef *= -1;
//        p = p->next;
//    }
//    Polyn head = addPolyn(a, h);
//    for (Polyn i = h->next; i != 0; i = i->next) {
//        i->coef *= -1;
//    }
//    return head;
//}
//
//double value(Polyn head, int x) {
//    double sum = 0;
//    for (Polyn p = head->next; p != 0; p = p->next) {
//        int tmp = 1;
//        int expn = p->expn;
//        while (expn != 0) {
//            if (expn < 0)   tmp /= x, expn++;
//            else if (expn > 0) tmp *= x, expn--;
//        }
//        sum += p->coef * tmp;
//    }
//    return sum;
//}
//
//Polyn removeDuplicates(Polyn head) {
//    if (head == NULL) {
//        return NULL;
//    }
//
//    Polyn resultHead = (Polyn)malloc(sizeof(Polynomial));
//    resultHead->next = NULL;
//    Polyn prev = resultHead;
//
//    Polyn current = head->next;
//    while (current != NULL) {
//        Polyn temp = prev;
//        while (temp->next != NULL && temp->next->expn != current->expn) {
//            temp = temp->next;
//        }
//        if (temp->next != NULL) {
//            temp->next->coef += current->coef;
//            if (temp->next->coef == 0) {
//                Polyn del = temp->next;
//                temp->next = del->next;
//                free(del);
//            }
//        }
//        else {
//            Polyn newNode = (Polyn)malloc(sizeof(Polynomial));
//            newNode->coef = current->coef;
//            newNode->expn = current->expn;
//            newNode->next = NULL;
//            prev->next = newNode;
//            prev = newNode;
//        }
//        current = current->next;
//    }
//
//    return resultHead;
//}
//
//Polyn mulPolyn(Polyn a, Polyn b) {
//    Polyn head = (Polyn)malloc(sizeof(Polynomial));
//    head->next = NULL;
//    Polyn qa = a->next;
//    while (qa) {
//        Polyn qb = b->next;
//        while (qb) {
//            Polyn temp = (Polyn)malloc(sizeof(Polynomial));
//            temp->coef = qa->coef * qb->coef;
//            temp->expn = qa->expn + qb->expn;
//            temp->next = head->next;
//            head->next = temp;
//            qb = qb->next;
//        }
//        qa = qa->next;
//    }
//    head = removeDuplicates(head);
//    return head;
//}
//
//int main() {
//    int m;
//    Polyn a = NULL, b = NULL;
//    printf("请输入a的项数:");
//    scanf("%d", &m);
//    a = CreatPolyn(a, m);
//    printPoLlyn(a);
//    printf("请输入b的项数:");
//    scanf("%d", &m);
//    b = CreatPolyn(b, m);
//    printPoLlyn(b);
//    printf("输出 a+b：");
//    printPoLlyn(addPolyn(a, b));
//    printf("输出 a-b：");
//    printPoLlyn(subPolyn(a, b));
//    printf("输出 a*b：");
//    printPoLlyn(mulPolyn(a, b));
//    printf("请输入x的值：");
//    int x;
//    scanf("%d", &x);
//    printf("输出a的多项式的值为：%.2lf\n", value(a, x));
//    printf("输出b的多项式的值为：%.2lf\n", value(b, x));
//
//    return 0;
//}
