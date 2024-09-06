////计算中位数
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>  
//#include <stdlib.h>  
//#include <string.h>  
//
//#define MAX_LINES 100  
//#define MAX_LENGTH 100  
//void prepart(int& s, int& t)
//{
//	int m = (s + t) / 2; 
//	t = m;
//}
//
//void postpart(int& s, int& t)
//{
//	int m = (s + t) / 2;  
//	if ((s + t) % 2 == 0)  
//		s = m;
//	else  
//		s = m + 1;
//}
//
//int mid(int a[], int s1, int t1, int b[], int s2, int t2) {
//	int m1, m2;
//	if (s1 == t1 && s2 == t2)
//		return a[s1] < b[s2] ? a[s1] : b[s2]; 
//	else
//	{
//		m1 = (s1 + t1) / 2;  //求a 、b中位数 
//		m2 = (s2 + t2) / 2;
//		if (a[m1] == b[m2])
//			return a[m1];
//		if (a[m1] < b[m2]) {
//			postpart(s1, t1);  //取a后半部分
//			prepart(s2, t2);  //取b前半部分
//			return mid(a, s1, t1, b, s2, t2);
//		}
//		else {
//			prepart(s1, t1);  //取a半部分
//			postpart(s2, t2); //取b后半部分
//			return mid(a, s1, t1, b, s2, t2);
//		}
//	}
//}
//
//int main() {
//        FILE* fp;
//        char line[MAX_LENGTH];
//        char* token;
//        int array1[MAX_LINES];
//        int array2[MAX_LINES];
//        int line_count = 0;
//        //提供更改n方法
////        int n = 4;
////        printf("Please enter n: ");
////        scanf_s("%d", &n);
//        // 打开文件  
//        fp = fopen("input1.txt", "r");
//        if (fp == NULL) {
//            perror("Error opening file");
//            return 1;
//        }
//        char line1[10];
//        char line2[100];
//        char line3[100];
//        fgets(line1, 10, fp);
//        fgets(line2, 100, fp);
//        fgets(line3, 150, fp);
//        int n = atoi(line1);
//        // 读取文件内容  
//
// //       printf("%s", line1);
// //       printf("%s", line2);
//        token = strtok(line2, " ");
//        int count = 0;
//        while (token != NULL) {
//
//            array1[count] = atoi(token);
//            token = strtok(NULL, " ");
//            count++;
//        }
//        token = strtok(line3, " ");
//        count = 0;
//        while (token != NULL) {
//
//            array2[count] = atoi(token);
//            token = strtok(NULL, " ");
//            count++;
//        }
//
//    fclose(fp);
//
//    FILE* fp1;
//    fp1 = fopen("output1.txt", "w");
//    printf("中位数：%d\n", mid(array1, 0, n - 1, array2, 0, n - 1));
//    fprintf(fp1, "%d", mid(array1, 0, n - 1, array2, 0, n - 1));
//    fclose(fp1);
//}
//
//
