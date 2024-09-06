//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//int a[10000][10000];
//
////求num个n位Gray码
//void GrayCode(int n, int num);
//
//int main()
//{
//    int n;
//    FILE* fp;
//    char line[100];
//    fp = fopen("input2.txt", "r");
//    fgets(line, 100, fp);
//    fclose(fp);
//    n = atoi(line);
//    //n位Gray码的个数num
//    int num = (int)pow(2.0, n);
//    //求num个n位Gray码
//    GrayCode(n, num);
//    FILE* fp1;
//    fp1 = fopen("output2.txt", "w");
//    for (int i = 0; i < num; ++i)
//    {
//        for (int j = n - 1; j >= 0; --j)
//        {
//            printf("%d", a[i][j]);
//            fprintf_s(fp1, "%d", a[i][j]);
//        }
//        fprintf_s(fp1, "%s", "\n");
//        puts("");
//    }
//    fclose(fp1);
//    return 0;
//}
//
//void GrayCode(int n, int num)
//{
//
//    if (n == 1)
//    {
//        a[0][0] = 0;
//        a[1][0] = 1;
//        return;
//    }
//
//    GrayCode(n - 1, num / 2);
//
//    for (int i = 0; i < num / 2; ++i)
//    {
//        a[i][n - 1] = 0;
//    }
//
//    for (int i = num / 2; i < num; ++i)
//    {
//        a[i][n - 1] = 1;
//        for (int j = 0; j < n - 1; ++j)
//        {
//            a[i][j] = a[num - i - 1][j];
//        }
//    }
//}
//
//
////对于1来说是01 10
////之后2的时候是在1的前面写0并在之后的部分写1，1的上半部分则是翻转形成下半部分