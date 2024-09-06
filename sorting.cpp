#include<stdio.h>
#include<stdlib.h>
typedef int Element;
typedef struct {
	Element* r;
	int length;
}SqList;
//The average number of inversions in an array of n distinct numbers is n(n - 1)/4.
//-----------------------------Insertion Sorting----------------------------
//O(nlogn)   worst: O(n^2)   best: O(n)
void InsertSort(SqList& L)  // from little to big
{
    int i, j;
    for (i = 2; i <= L.length; i++)
    {
        if (L.r[i] < L.r[i - 1])
        {
            L.r[0] = L.r[i];    //set a flag
            for (j = i - 1; L.r[0] < L.r[j]; --j)
                L.r[j + 1] = L.r[j];  //move right
        }
        L.r[j + 1] = L.r[0]; //find the right position 
    }
}

//-----------------------transposition sorting-------------------------------
//O(n^2)

//Bubble Sort
void BubbleSort(SqList& L) {
    for (int i = 0; i < L.length - 1; ++i) {  // 外层循环控制排序次数
        bool swapped = false;                   // 提前退出冒泡循环的标志位
        for (int j = 0; j < L.length - 1 - i; ++j) {  // 内层循环进行元素的比较和交换
            if (L.r[j] > L.r[j + 1]) {  // 如果前一个元素比后一个元素大，则交换
                int temp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = temp;
                swapped = true;  // 设置标志位，表示有元素交换
            }
        }
        if (!swapped) {  // 如果没有发生交换，提前退出循环
            break;
        }
    }
}


//------------------------Shell sort-----------------------------------
// O(N^1.25)
void ShellSort(SqList& L) {
    int n = L.length;
    // 选择一个初始的间隔增量序列，这里使用 n/2, n/4, ..., 1 的方式
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 对每一个间隔进行插入排序
        for (int i = gap; i < n; ++       i) {
            int temp = L.r[i];
            int j;
            for (j = i; j >= gap && L.r[j - gap] > temp; j -= gap) {
                L.r[j] = L.r[j - gap];
            }
            L.r[j] = temp;
        }
    }
}


//------------------------Quick sort-----------------------------------
//average O(nlogN)    worst(n^2)
int Partition(SqList& L, int low, int high) {
    int pivot = L.r[low];  // 选择第一个元素作为枢轴
    while (low < high) {
        while (low < high && L.r[high] >= pivot) --high;  // 从右向左找小于pivot的元素
        L.r[low] = L.r[high];  // 将小于pivot的元素移到左边
        while (low < high && L.r[low] <= pivot) ++low;  // 从左向右找大于pivot的元素
        L.r[high] = L.r[low];  // 将大于pivot的元素移到右边
    }
    L.r[low] = pivot;  // 将pivot放到正确位置
    return low;  // 返回pivot的位置
}

void QuickSort(SqList& L, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(L, low, high);  // 分区操作，返回枢轴位置
        QuickSort(L, low, pivotIndex - 1);  // 递归排序左半部分
        QuickSort(L, pivotIndex + 1, high);  // 递归排序右半部分
    }
}


//------------------------Selection Sorting---------------------------------
//O(n^2)
void SelectionSort(SqList& L) {
    for (int i = 0; i < L.length - 1; ++i) {
        int minIndex = i;  // 假设第i个元素是最小的
        for (int j = i + 1; j < L.length; ++j) {
            if (L.r[j] < L.r[minIndex]) {  // 找到比当前假设的最小值更小的元素
                minIndex = j;
            }
        }
        if (minIndex != i) {  // 交换元素
            int temp = L.r[i];
            L.r[i] = L.r[minIndex];
            L.r[minIndex] = L.r[i];
        }
    }
}


//-----------------------Heap Sort-------------------------------------------
//O(nlogN)
//1.create a heap use max heap
//2.delete root and output to array


//--------------------------Merge Sort--------------------------------------
//Average O(nlogN)  worst O(n^2)
// 
// 合并两个子数组到原数组中
void Merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;  // 左子数组的大小
    int n2 = right - mid;  // 右子数组的大小

    // 动态分配内存给左、右子数组
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 将数据复制到左、右子数组
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;  // 初始化子数组索引和合并数组的索引
    // 合并两个子数组到原数组中
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {  // 如果左子数组元素较小或相等
            arr[k] = L[i];
            ++i;
        }
        else {  // 如果右子数组元素较小
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // 将左子数组中剩余的元素复制到原数组
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // 将右子数组中剩余的元素复制到原数组
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    // 释放分配的内存
    free(L);
    free(R);
}

// 递归地进行归并排序
void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // 计算中间索引，防止溢出
        MergeSort(arr, left, mid);  // 递归排序左半部分
        MergeSort(arr, mid + 1, right);  // 递归排序右半部分
        Merge(arr, left, mid, right);  // 合并两部分
    }
}

//----------------------------------Bucket Sort-------------------------------
//O(n).

//---------------------------------Radix Sort---------------------------------
//按照个十百位数大小排序

//---------------------------------External Sort------------------------------