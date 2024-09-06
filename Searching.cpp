#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef int ElemType;
typedef struct node {
	ElemType* elem;//elem[0] is for Sentinel
	int length;//size of elements
}SSTable;

//-------------------------------Sequential Searching-----------------------------------
//successful:  Best: 1    worst:n    average: (n+1)/2
//Unsuccessful: n
//AverageSearch: 3*(n+1)/4
int Search_Seq(SSTable St, int key) {
	for (int i = St.length; i > 0; i--) {
		if (St.elem[i] == key) {
			return i;
			break;
		}
	}
}

//-------------------------------Binary Searching------------------------------------
//successful: logN+1
//unsuccessful: logN+1
int Search_Binary(SSTable st, int key, int low, int high) {
	int mid;
	if (low > high)
		return 0;
	else {
		mid = (low + high) / 2;
		if (key == st.elem[mid]) {
			return mid;
		}
		else if(key>st.elem[mid]) {
			return Search_Binary(st, key, mid+1, high);
		}
		else {
			return Search_Binary(st, key, low, mid-1);
		}
	}
	return 0;
}

//-------------------------------Binary Search Trees----------------------------------
typedef struct tree_node {
	ElemType element;
	tree_node* left;
	tree_node* right;
}TNode, *Tree;
//
//Degenerate ¨C only one child    -O(n)
//Balanced ¨C mostly two children - O(log2n)
//Complete ¨C always two children - O(log2n)
//
Tree find(ElemType x, Tree T) {
	if (T == NULL) {
		return NULL;
	}
	if (x < T->element) {
		return find(x, T->left);
	}
	else if (x > T->element) {
		return find(x, T->right);
	}
	else {
		return T;
	}
}
Tree findMin(Tree T) {
	if (T->left == NULL) {
		return T;
	}
	else {
		return findMin(T->left);
	}
}
Tree findMax(Tree T) {
	if (T->right == NULL) {
		return T;
	}
	else {
		return findMin(T->right);
	}
}

//insert
Tree insert(ElemType x, Tree T) {
	//create
	if (T == NULL) {
		T = (Tree)malloc(sizeof(TNode));
		if (T == NULL) {
			printf("out of space");
		}
		else {
			T->element = x;
			T->left = T->right = NULL;
		}
	}
	else {
		if (x < T->element) {
			T->left = insert(x, T->left);
		}
		else if (x > T->element) {
			T->right = insert(x, T->right);
		}
	}
	return T;
}
//delete
Tree del(ElemType x, Tree T) {
	Tree tmp_cell, child;
	if (T == NULL) {
		printf("Tree is Null");
	}
	else {
		if (x < T->element) { /* Go left */
			T->left = del(x, T->left);
		}
		else if (x > T->element) { /* Go right */
			T->right = del(x, T->right);
		}
		else if (T->left && T->right) {
				tmp_cell = findMin(T->right);
				T->element = tmp_cell->element;
				T->right = del(T->element, T->right);
		}
		else {
			tmp_cell = T;
			if (T->left == NULL)      /* Only a right child */
				child = T->right;
			if (T->right == NULL)     /* Only a left child */
				child = T->left;
			free(tmp_cell);
			return child;
			}
		return T;
		
	}
}


//-----------------------------------AVL Tree--------------------------------
//An AVL tree is identical to a binary search tree, 
// except that for every node in the tree, 
// the height of the left and right subtrees can differ by at most 1. 


//--------------------------------Table---------------------------------------
// unsorted sequential array
// insert:O(1)
// find:O(n)
// remove:O(n)
//
// sorted sequential array
// insert:O(n)
// find:O(logN)
// remove:O(n)
//
// linked list (unsorted or sorted)
// insert:O(1) or O(n) for a sorted list
// find:O(n)
// remove:O(n)
// 
// AVL Tree
// insert:O(logN)
// find:O(logN)
// remove:O(logN)
//
// hash !!!!
// insert:O(1)
// find:O(1)
// remove:O(1)
//