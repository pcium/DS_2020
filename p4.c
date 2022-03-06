#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp2;
int sign;

typedef struct threaded_tree* threaded_ptr;
struct threaded_tree {
	short int left_thread;
	threaded_ptr left_child;
	char data;
	int index;
	int pointed;
	threaded_ptr right_child;
	short int right_thread;
	threaded_ptr parent;
};

// successor pointer를 찾아간다. 전부 배치 끝나고 적용
threaded_ptr insucc(threaded_ptr tree) {
	threaded_ptr temp;
	temp = tree->right_child;
	if (!tree->right_thread) {
		while (!temp->left_thread) {
			temp = temp->left_child;
		}
	} // Thread Pointer가 아닌 경우에 다음으로 따라가는 알고리즘
	return temp;
}


void InsertNode(threaded_ptr node, threaded_ptr tree)
{
	threaded_ptr travel = tree; //여행 포인터 초기화
	int id = node->index; // Target ID
	int gj = 4; // 기준 (몇번 움직일지 결정)
	int move = 1; // 움직이는 횟수
	while (id >= gj) {
		move++;
		gj=gj*2;
	}
	for (; move > 0; move--) {
		if (move == 1) 
		{
			if (id % 2 == 0) {
				travel->left_thread = FALSE;
				travel->left_child = node;
				node->parent = travel;
				travel = travel->left_child;
			}
			else {
				travel->right_thread = FALSE;
				travel->right_child = node;
				node->parent = travel;
				travel = travel->right_child;
			}
		}
		else
		{
			gj = gj / 2;
			if ((id % gj) < (gj / 2)) {
				travel = travel->left_child;
			}
			else {
				travel = travel->right_child;
			}
		}
	}
}
// 들어갈 노드와 tree 호출 후 대입


// Inorder traversal인 Tree를 읽고 출력한다. 안 건드려도 가능
void tinorder(threaded_ptr tree) {
	threaded_ptr temp = tree;
	for (;;) {
		temp = insucc(temp);
		if (temp == tree) break;
		fprintf(fp2, "%c ", temp->data);
	}
}

threaded_ptr Location(threaded_ptr tree, int index) {
	threaded_ptr temp = tree;
	if (index == 1) {
		return temp;
	}
	else {
		int gj = 4;
		int move = 1;
		while (index >= gj) {
			move++;
			gj = gj * 2;
		}
		for (; move > 0; move--) {
			if (move == 1)
			{
				if (index % 2 == 0) {
					temp = temp->left_child;
				}
				else {
					temp = temp->right_child;
				}
			}
			else
			{
				gj = gj / 2;
				if ((index % gj) < (gj / 2)) {
					temp = temp->left_child;
				}
				else {
					temp = temp->right_child;
				}
			}
		}
	}
	return temp;
}

void main()
{
	int NodeNum = 0;
	char buffer[200];
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	NodeNum = atoi(buffer);
	if (NodeNum > 100) {
		printf("ERROR : Exceeded Limit of 100\n");
		exit(100);
	}

	fgets(buffer, sizeof(buffer), fp);
	int n;
	threaded_ptr R; // Root Node
	threaded_ptr T; // Tree Head Node
	R = malloc(sizeof(struct threaded_tree)); // 공간확보
	R->right_child = R;
	R->left_thread = FALSE;
	R->right_thread = FALSE;
	T = malloc(sizeof(struct threaded_tree));
	R->left_child = T;
	T->data = buffer[0];
	T->index = 1;
	T->pointed = 0;
	T->left_thread = TRUE;
	T->right_thread = TRUE;
	T->left_child = NULL;
	T->right_child = NULL; // 초반 설정

	for (n = 1; n < NodeNum; n++) {
		threaded_ptr TmpCell = malloc(sizeof(struct threaded_tree));
		char d = buffer[n*2];
		TmpCell->data = d;
		TmpCell->index = n+1;
		TmpCell->pointed = 0;
		TmpCell->left_child = NULL;
		TmpCell->right_child = NULL;
		TmpCell->left_thread = TRUE;
		TmpCell->right_thread = TRUE;
		InsertNode(TmpCell, T);
	}
	 

	// Thread 이어붙이기 - 최외각을 Root로!
	threaded_ptr L = T;
	while (L->left_child != NULL) {
		L = L->left_child;
	}
	L->left_child = R;
	L = T;
	while (L->right_child != NULL) {
		L = L->right_child;
	}
	L->right_child = R;
	//Thread 이어붙이기 - 정중앙
	L = T->left_child;
	while (L->right_child != NULL) {
		L = L->right_child;
	}
	L->right_child = T;
	(T->pointed)++;
	L = T->right_child;
	while (L->left_child != NULL) {
		L = L->left_child;
	}
	L->left_child = T;
	(T->pointed)++;
	// Thread 이어붙이기 - 나머지 경우의 수
	for (n = 1; n <= NodeNum; n++) {
		L = Location(T, n);
		if (L->left_thread == 0 && L->right_thread == 0) {
			continue;
		}
		else {
			if (n % 2 == 0 && L->right_child == NULL) {
				L->right_child = L->parent;
				(L->parent->pointed)++;
			}
			else if (n % 2 == 1 && L->left_child == NULL) {
				L->left_child = L->parent;
				(L->parent->pointed)++;
			}
		}
	}
	L = T;

	threaded_ptr missing;
	for (n = 1; n <= NodeNum; n++) {
		L = T;
		L = Location(L, n);
		if (n == NodeNum / 2 && L->pointed == 1) {
			continue;
		}
		else if (L->pointed == 2) {
			continue;
		}
		else if (n<=NodeNum/2){
			missing = L;
			missing = missing->left_child;
			while (missing->right_thread != TRUE) {
				missing = missing->right_child;
			}
			if (missing->right_child == NULL) {
				missing->right_child = L;
			}
			(L->pointed)++;
			if (L->pointed == 2) {
				continue;
			}
			
			missing = L;
			missing = missing->right_child;
			while (missing->left_thread != TRUE) {
				missing = missing->left_child;
			}
			if (missing->left_child == NULL) {
				missing->left_child = L;
			}
			(L->pointed)++;
		}
		else if (n > NodeNum / 2) {
			if (L->left_child == NULL || L->right_child == NULL) {
				printf("Error in %d\n", n);
				if (L->left_child == NULL) {
					printf("좌측 부족\n");
				}
				if (L->right_child == NULL) {
					printf("우측 부족\n");
				}
			}
		}
	}
	tinorder(R);
	fclose(fp);
	fclose(fp2);
}