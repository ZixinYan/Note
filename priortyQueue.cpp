#include<stdio.h>
#include <stdlib.h>

#define MinPQsize 10   // Define the minimum priority queue size
#define MinData -32767 // Define a sentinel value for MinData

typedef int ElementType;

//unsorted Linked list[array]: insert O(1)£¬delete O(n)
//sorted lined list[array]: insert O(n),delete O(1)


//------------------------------------Binary Heap---------------------------------------
//complete binary tree:The tree is perfectly balanced and leaves in the 
//						last level are all in the leftmost positions
// For the perfect binary tree of height h containing 2^(h+1) - 1 nodes,
//  the sum of the heights of the nodes is 2^(h + 1) - 1 - (h + 1).
//Min Heap,Max Heap

//------------------------------------Priorty Queue-------------------------------------
//create Top-Down: O(nlogN)   Bottom-Top:O(n)
typedef struct HeapStruct {
    int Capacity;
    int Size;
    ElementType* Elements;
}HeapStruct, *PriorityQueue;

void FatalError(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void Error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}

PriorityQueue Initialize(int MaxElements) {
    PriorityQueue H;
    if (MaxElements < MinPQsize) {
        Error("Priority queue size is too small");
        return NULL;
    }
    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if (H == NULL) {
        FatalError("Out of space!");
    }
    H->Elements = (ElementType*)malloc((MaxElements + 1) * sizeof(ElementType));
    if (H->Elements == NULL) {
        FatalError("Out of space.");
    }
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;
    return H;
}

//insert    Worse case:O(logN)   Best case: 0
//Max-Heap[for Min-Heap, change > to <]
void insert(ElementType X, PriorityQueue H) {
    int i;
    if (H->Size < H->Capacity) {
        Error("Priority queue is full");
    }
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2) {
        H->Elements[i] = H->Elements[i / 2];
    }
    H->Elements[i] = X;
}

//Delete    Worse case:O(logN)    Best case: 0
//Min-Heap[for Max-Heap, change < to >
ElementType DeleteMin(PriorityQueue H) {
    int i=1, Child;
    ElementType MinElement, LastElement;
    if (H->Size == 0) {
        Error("Priority queue is empty");
        return H->Elements[0];
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for (i; i * 2 < H->Size; i = Child) {
        Child = i * 2;
        //find a smaller child
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child]) {
            Child++;
        }
        //percolate one level
        if (LastElement > H->Elements[Child]) {
            H->Elements[i] = H->Elements[Child];
        }
        else {
            break;
        }
    }
    H->Elements[i] = LastElement;
    return MinElement;
}


//------------------------------------Application-----------------------------------
//Heap Sort!!!    O(NlogN)



//------------------------------Binomial Queue Operation----------------------------
//find minimum element O(logN)
//merge two Queue      O(logN)s