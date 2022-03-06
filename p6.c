#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;

FILE* fp;
FILE* fp2;

struct AVLNode
{
	int Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int Height(Position P) {
	if (P == NULL) return -1;
	else return P->Height;
}

Position SingleRotateWithLeft(Position K2) {
	Position K1;
	
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), K2->Height) + 1;
	return K1;
}

Position SingleRotateWithRight(Position K2) {
	Position K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Right), K2->Height);
	return K1;
}

Position DoubleRotateWithLeft(Position K3) {
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position K3) {
	K3->Right = SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);
}

AVLTree Insert(int X, AVLTree T) {
	if (T == NULL) {
		T = malloc(sizeof(struct AVLNode));
		if (T == NULL) {
			printf("FATAL ERROR: CREATION FAIL!\n");
			exit(2);
		}
		else {
			T->Element = X;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (X < T->Element) {
		T->Left = Insert(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (X < T->Left->Element) {
				T = SingleRotateWithLeft(T);
			}
			else {
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if (X > T->Element) {
		T->Right = Insert(X, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2) {
			if (X > T->Right->Element) {
				T = SingleRotateWithRight(T);
			}
			else {
				T = DoubleRotateWithRight(T);
			}
		}
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

int FindNode(int num, AVLTree T) {
	if (T == NULL) {
		return 0;
	}
	if (num < T->Element) {
		return FindNode(num, T->Left);
	}
	else if (num > T->Element) {
		return FindNode(num, T->Right);
	}
	else return 1;
}

void PrintInorder(AVLTree T) {
	if (T == NULL) return;
	PrintInorder(T->Left);
	printf("%d(%d) ", T->Element, T->Height);
	PrintInorder(T->Right);
}

void main() 
{
	int dup;
	int num;
	char buffer[128];
	char* ptr = NULL;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	AVLTree T = NULL;
	ptr = strtok(buffer, " ");
	num = atoi(ptr);
	T = Insert(num, T);
	PrintInorder(T);
	printf("\n");
	while (1) {
		ptr = strtok(NULL, " ");
		if (ptr == NULL) break;
		num = atoi(ptr);
		dup = FindNode(num, T);
		if (dup == 1) {
			printf("%d is already in the tree!\n", num);
			continue;
		}
		T = Insert(num, T);
		PrintInorder(T);
		printf("\n");
	}
	fclose(fp);
	fclose(fp2);
}