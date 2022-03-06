// 2018083672 Lab 8
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define order 3

FILE* fp;
FILE* fp2;

typedef struct B_node* nCon;
struct B_node {
	int isLeaf;
	int n_keys;
	nCon parent;
	nCon child[order];
	int key[order - 1];
};

nCon Search(int key, nCon F) {
	nCon temp = F;
	while(1) {
		if (temp->isLeaf == 1) {
			return temp;
		}
		if (key < temp->key[0]) {
			temp = temp->child[0];
		}
		else if (key > temp->key[0] && temp->n_keys == 1) {
			temp = temp->child[1];
		}
		else if (key > temp->key[0] && key < temp->key[1]) {
			temp = temp->child[1];
		}
		else if (key > temp->key[1]) {
			temp = temp->child[2];
		}
	}
}

nCon Insert(int key, nCon B) {
	int tmp;
	nCon new_B1, new_B2;

	if (B == NULL) {
		B = malloc(sizeof(struct B_node));
		B->n_keys = 1;
		B->key[0] = key;
		B->isLeaf = 1;
		B->parent = NULL;
		B->child[0] = NULL;
		B->child[1] = NULL;
		return B; // First Insert
	}
	else if (B->isLeaf == 1 && B->n_keys == 1) {
		(B->n_keys)++;
		B->key[1] = key;
		B->child[2] = NULL;
		if (B->key[0] > B->key[1]) {
			tmp = B->key[0];
			B->key[0] = B->key[1];
			B->key[1] = tmp; // Swap to sort
		}
		else if (B->key[0] == B->key[1]) {
			printf("Error: Cannot insert duplicate value\n");
			exit(2); // Duplicate handling
		}
		return B; // Second insert
	}
	else if (B->isLeaf == 1 && B->n_keys == 2) {
		if (key < B->key[0]) {
			new_B1 = malloc(sizeof(struct B_node));
			new_B1->n_keys = 1;
			new_B1->key[0] = key;
			new_B1->isLeaf = 1;
			new_B1->parent = B;
			new_B1->child[0] = NULL;
			new_B1->child[1] = NULL;
			new_B1->child[2] = NULL;
			new_B2 = malloc(sizeof(struct B_node));
			new_B2->n_keys = 1;
			new_B2->key[0] = B->key[1];
			new_B2->isLeaf = 1;
			new_B2->parent = B;
			new_B2->child[0] = NULL;
			new_B2->child[1] = NULL;
			new_B2->child[2] = NULL;
			(B->n_keys)--;
			B->isLeaf = 0;
			B->child[0] = new_B1;
			B->child[1] = new_B2;
		}
		else if (key > B->key[0] && key < B->key[1]) {
			new_B1 = malloc(sizeof(struct B_node));
			new_B1->n_keys = 1;
			new_B1->key[0] = B->key[0];
			new_B1->isLeaf = 1;
			new_B1->parent = B;
			new_B1->child[0] = NULL;
			new_B1->child[1] = NULL;
			new_B1->child[2] = NULL;
			new_B2 = malloc(sizeof(struct B_node));
			new_B2->n_keys = 1;
			new_B2->key[0] = B->key[1];
			new_B2->isLeaf = 1;
			new_B2->parent = B;
			new_B2->child[0] = NULL;
			new_B2->child[1] = NULL;
			new_B2->child[2] = NULL;
			B->key[0] = key;
			(B->n_keys)--;
			B->isLeaf = 0;
			B->child[0] = new_B1;
			B->child[1] = new_B2;
		}
		else if (key > B->key[1]) {
			new_B1 = malloc(sizeof(struct B_node));
			new_B1->n_keys = 1;
			new_B1->key[0] = B->key[0];
			new_B1->isLeaf = 1;
			new_B1->parent = B;
			new_B1->child[0] = NULL;
			new_B1->child[1] = NULL;
			new_B1->child[2] = NULL;
			new_B2 = malloc(sizeof(struct B_node));
			new_B2->n_keys = 1;
			new_B2->key[0] = key;
			new_B2->isLeaf = 1;
			new_B2->parent = B;
			new_B2->child[0] = NULL;
			new_B2->child[1] = NULL;
			new_B2->child[2] = NULL;
			B->key[0] = B->key[1];
			(B->n_keys)--;
			B->isLeaf = 0;
			B->child[0] = new_B1;
			B->child[1] = new_B2;
		}
		else if (key == B->key[0] || key == B->key[1]) {
			printf("Error: Cannot insert duplicate value\n");
			exit(2); // Duplicate handling
		}
		return B; // Third insert & split
	}
	B = Search(key, B); // Goto Leaf to insert
	if (B->n_keys == 1) {
		if (B->key[0] > key) {
			B->key[1] = B->key[0];
			B->key[0] = key;
		}
		else if (B->key[0] < key) {
			B->key[1] = key;
		}
		else {
			printf("Error: Cannot insert duplicate value\n");
			exit(2);
		}
		B->child[2] = NULL;
		(B->n_keys)++;
	}
	else if (B->n_keys == 2 && B->parent->n_keys == 1) { // Mid를 위로 올려버린다
		int mid;
		nCon new_n;
		if (key < B->key[0]) {
			mid = B->key[0];
			B->key[1] = B->key[0];
			B->key[0] = key;
			if (mid < B->parent->key[0]) {
				B->parent->key[1] = B->parent->key[0];
				B->parent->key[0] = mid;
				new_n = malloc(sizeof(struct B_node));
				new_n->child[0] = NULL;
				new_n->child[1] = NULL;
				new_n->child[2] = NULL;
				new_n->key[0] = B->key[1];
				new_n->n_keys = 1;
				new_n->parent = B->parent;
				new_n->isLeaf = 1;
				(B->n_keys)--;
				B->parent->child[2] = B->parent->child[1];
				B->parent->child[1] = new_n;
			}
			else if (mid > B->parent->key[0]) {
				B->parent->key[1] = mid;
				new_n = malloc(sizeof(struct B_node));
				new_n->child[0] = NULL;
				new_n->child[1] = NULL;
				new_n->child[2] = NULL;
				new_n->key[0] = key;
				new_n->n_keys = 1;
				new_n->parent = B->parent;
				new_n->isLeaf = 1;
				B->key[0] = B->key[1];
				(B->n_keys)--;
				B->parent->child[2] = B->parent->child[1];
				B->parent->child[1] = new_n;
			}
		}
		else if (key > B->key[1]) {
			mid = B->key[1];
			B->key[1] = key;
			if (mid < B->parent->key[0]) {
				B->parent->key[1] = B->parent->key[0];
				B->parent->key[0] = mid;
				new_n = malloc(sizeof(struct B_node));
				new_n->child[0] = NULL;
				new_n->child[1] = NULL;
				new_n->child[2] = NULL;
				new_n->key[0] = B->key[1];
				new_n->n_keys = 1;
				new_n->parent = B->parent;
				new_n->isLeaf = 1;
				(B->n_keys)--;
				B->parent->child[2] = B->parent->child[1];
				B->parent->child[1] = new_n;
			}
			else if (mid > B->parent->key[0]) {
				B->parent->key[1] = mid;
				new_n = malloc(sizeof(struct B_node));
				new_n->child[0] = NULL;
				new_n->child[1] = NULL;
				new_n->child[2] = NULL;
				new_n->key[0] = B->key[0];
				new_n->n_keys = 1;
				new_n->parent = B->parent;
				new_n->isLeaf = 1;
				B->key[0] = B->key[1];
				(B->n_keys)--;
				B->parent->child[2] = B->parent->child[1];
				B->parent->child[1] = new_n;
			}	
		}
		else if (key > B->key[0] && key < B->key[1]) { 
			mid = key;
			if (mid < B->parent->key[0]) {
				B->parent->key[1] = B->parent->key[0];
				B->parent->key[0] = mid;
				new_n = malloc(sizeof(struct B_node));
				new_n->child[0] = NULL;
				new_n->child[1] = NULL;
				new_n->child[2] = NULL;
				new_n->key[0] = B->key[1];
				new_n->n_keys = 1;
				new_n->parent = B->parent;
				new_n->isLeaf = 1;
				(B->n_keys)--;
				B->parent->child[2] = B->parent->child[1];
				B->parent->child[1] = new_n;
			}
			else if (mid > B->parent->key[0]) {
				B->parent->key[1] = mid;
				new_n = malloc(sizeof(struct B_node));
				new_n->child[0] = NULL;
				new_n->child[1] = NULL;
				new_n->child[2] = NULL;
				new_n->key[0] = B->key[0];
				new_n->n_keys = 1;
				new_n->parent = B->parent;
				new_n->isLeaf = 1;
				B->key[0] = B->key[1];
				(B->n_keys)--;
				B->parent->child[2] = B->parent->child[1];
				B->parent->child[1] = new_n;
			}	
		}
		else if (key == B->key[0] || key == B->key[1]) {
			printf("Error: Cannot insert duplicate value\n");
			exit(2);
		}
		(B->parent->n_keys)++;
	}
	else if (B->n_keys == 2 && B->parent->n_keys == 2) { // Parent도 꽉차 있을 시 확장
		nCon new_B1, new_B2;
		if (key < B->key[0]) {
			new_B1 = malloc(sizeof(struct B_node));
			new_B1->n_keys = 1;
			new_B1->key[0] = key;
			new_B1->isLeaf = 1;
			new_B1->parent = B;
			new_B1->child[0] = NULL;
			new_B1->child[1] = NULL;
			new_B1->child[2] = NULL;
			new_B2 = malloc(sizeof(struct B_node));
			new_B2->n_keys = 1;
			new_B2->key[0] = B->key[1];
			new_B2->isLeaf = 1;
			new_B2->parent = B;
			new_B2->child[0] = NULL;
			new_B2->child[1] = NULL;
			new_B2->child[2] = NULL;
			(B->n_keys)--;
			B->isLeaf = 0;
			B->child[0] = new_B1;
			B->child[1] = new_B2;
		}
		else if (key > B->key[0] && key < B->key[1]) {
			new_B1 = malloc(sizeof(struct B_node));
			new_B1->n_keys = 1;
			new_B1->key[0] = B->key[0];
			new_B1->isLeaf = 1;
			new_B1->parent = B;
			new_B1->child[0] = NULL;
			new_B1->child[1] = NULL;
			new_B1->child[2] = NULL;
			new_B2 = malloc(sizeof(struct B_node));
			new_B2->n_keys = 1;
			new_B2->key[0] = B->key[1];
			new_B2->isLeaf = 1;
			new_B2->parent = B;
			new_B2->child[0] = NULL;
			new_B2->child[1] = NULL;
			new_B2->child[2] = NULL;
			B->key[0] = key;
			(B->n_keys)--;
			B->isLeaf = 0;
			B->child[0] = new_B1;
			B->child[1] = new_B2;
		}
		else if (key > B->key[1]) {
			new_B1 = malloc(sizeof(struct B_node));
			new_B1->n_keys = 1;
			new_B1->key[0] = B->key[0];
			new_B1->isLeaf = 1;
			new_B1->parent = B;
			new_B1->child[0] = NULL;
			new_B1->child[1] = NULL;
			new_B1->child[2] = NULL;
			new_B2 = malloc(sizeof(struct B_node));
			new_B2->n_keys = 1;
			new_B2->key[0] = key;
			new_B2->isLeaf = 1;
			new_B2->parent = B;
			new_B2->child[0] = NULL;
			new_B2->child[1] = NULL;
			new_B2->child[2] = NULL;
			B->key[0] = B->key[1];
			(B->n_keys)--;
			B->isLeaf = 0;
			B->child[0] = new_B1;
			B->child[1] = new_B2;
		}
	}
	return B;
}

void Inorder(nCon ptr) {
	if (ptr == NULL) return;
	if (ptr->n_keys == 2) {
		Inorder(ptr->child[0]);
		printf("%d ", ptr->key[0]);
		Inorder(ptr->child[1]);
		printf("%d ", ptr->key[1]);
		Inorder(ptr->child[2]);
	}
	if (ptr->n_keys == 1) {
		Inorder(ptr->child[0]);
		printf("%d ", ptr->key[0]);
		Inorder(ptr->child[1]);
	}
}

nCon toParent(nCon B) {
	while (B->parent != NULL) {
		B = B->parent;
	}
	return B;
}

void main() {
	int num;
	char od;
	char buffer[10];
	char* sliced = NULL;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	nCon B = NULL;
	while (1) {
		fgets(buffer, sizeof(buffer), fp);
		sliced = strtok(buffer, " ");
		od = buffer[0];
		if (od == 'i') {
			sliced = strtok(NULL, " ");
			num = atoi(sliced);
			B = Insert(num, B);
			B = toParent(B);
		}
		else if (od == 'p') {
			Inorder(B);
			printf("\n\n");
		}
		else {
			printf("INPUT ERROR\n");
			exit(2);
		}
		if (feof(fp)) break;
	}
	fclose(fp);
	fclose(fp2);
}