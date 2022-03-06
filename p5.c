#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp2;

typedef struct TreeNode* SearchTree; // 트리 노드 포인터
typedef struct TreeNode* Node;
struct TreeNode {
	int value;
	SearchTree left, right;
}; // 구조체 변수

SearchTree InsertNode(int val, SearchTree T) {
	if (T == NULL) {
		T = malloc(sizeof(struct TreeNode));
		if (T == NULL) {
			printf("ERROR: Out of space!");
			exit(1);
		}
		else {
			T->value = val;
			T->left = NULL;
			T->right = NULL;
		}
	}
	else if (val < T->value) {
		T->left = InsertNode(val, T->left);
	}
	else if (val > T->value) {
		T->right = InsertNode(val, T->right);
	}
	else {
		printf("%d already exists.\n", val);
	}
	return T;
}

Node FindNode(int val, SearchTree T) {
	if (T == NULL) {
		return NULL;
	}
	if (val < T->value) {
		return FindNode(val, T->left);
	}
	else if (val > T->value) {
		return FindNode(val, T->right);
	}
	else {
		return T;
	}
}

Node FindMax(SearchTree T) {
	if (T == NULL) return NULL;
	else {
		while (T->right != NULL)
			T = T->right;
	}
	return T;
}

SearchTree DeleteNode(int val, SearchTree T) {
	Node TmpCell = NULL;
	//printf("%d is going to be deleted\n", val);
	if (T == NULL) {
		printf("Deletion failed. %d does not exist.\n", val);
		return T;
	}
	else if (val < T->value){
		//printf("Go to Left\n");
		T->left = DeleteNode(val, T->left);
	}
	else if (val > T->value) {
		//printf("Go to Right\n");
		T->right = DeleteNode(val, T->right);
	}
	else if (T->right && T->left) {
		//printf("Found the Node\n");
		TmpCell = FindMax(T->left);
		T->value = TmpCell->value;
		T->left = DeleteNode(T->value, T->left);
	}
	else {
		//printf("Found the Node with 1 or 0 child\n");
		TmpCell = T;
		if (T->left == NULL) T = T->right;
		else if (T->right == NULL) T = T->left;
		free(TmpCell);
	}
	return T;
}

void PrintInorder(SearchTree root) {
	if (root == NULL) return;
	PrintInorder(root->left);
	printf("%d ", root->value);
	PrintInorder(root->right);
}

void PrintPreorder(SearchTree root) {
	if (root == NULL) return;
	printf("%d ", root->value);
	PrintPreorder(root->left);
	PrintPreorder(root->right);
}

void PrintPostorder(SearchTree root) {
	if (root == NULL) return;
	PrintPostorder(root->left);
	PrintPostorder(root->right);
	printf("%d ", root->value);
}

void main() {
	int num;
	char order;
	char printorder;
	char* sliced = NULL;
	char* remain = NULL;
	char buffer[10];
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	SearchTree T = NULL;
	/*
	T = malloc(sizeof(struct TreeNode));
	T->right = NULL;
	T->left = NULL; // 초기 루트 노드 만들기
	fgets(buffer, sizeof(buffer), fp);
	while (buffer[0] != 'i') {
		printf("ERROR: EMPTY TREE");
		fgets(buffer, sizeof(buffer), fp);
	}
	*/
	
	while (1) {
		fgets(buffer, sizeof(buffer), fp);
		//printf("\n- %s \n", buffer);
		order = buffer[0];
		printorder = buffer[1];
		Node N = NULL;
		
		if (order == 'i') {
			sliced = strtok_s(buffer, " ", &remain);
			num = atoi(remain);
			T = InsertNode(num, T);
		}
		else if (order == 'd') {
			sliced = strtok_s(buffer, " ", &remain);
			num = atoi(remain);
			//printf("%d is going to be deleted\n", num); // ERROR
			T = DeleteNode(num, T);
		}
		else if (order == 'f') {
			sliced = strtok_s(buffer, " ", &remain);
			num = atoi(remain);
			N = FindNode(num, T);
			if (N != NULL) {
				printf("%d is in the tree.\n", num);
			}
			else {
				printf("%d is not in the tree.\n", num);
			}
		}
		else {
			if (printorder == 'i') {
				printf("pi - ");
				PrintInorder(T);
				printf("\n");
			}
			else if (printorder == 'r') {
				printf("pr - ");
				PrintPreorder(T);
				printf("\n");
			}
			else if (printorder == 'o'){
				printf("po - ");
				PrintPostorder(T);
				printf("\n");
			}
			else {
				printf("INPUT ERROR \n");
				exit(2);
			}
		}
		if (feof(fp)) break;
	}
	fclose(fp);
	fclose(fp2);
}