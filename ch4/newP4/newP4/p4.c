#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp2;

// Tree�� ����ü
typedef struct threaded_tree* threaded_ptr;
struct threaded_tree {
	short int left_thread;
	threaded_ptr left_child;
	char data;
	threaded_ptr right_child;
	short int right_thread;
};

// Linked List ����ü
typedef struct LNode* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct LNode
{
	int idx;
	int leaf;
	int CN;
	int passed;
	char data;
	PtrToNode Next;
	PtrToNode Prev;
	PtrToNode Parent;
	PtrToNode Child_Left;
	PtrToNode Child_Right;
};

// ���� ��带 ���󰡴� �˰���
threaded_ptr insucc(threaded_ptr tree) 
{
	threaded_ptr temp;
	temp = tree->right_child;
	if (!tree->right_thread) {
		while (!temp->left_thread) {
			temp = temp->left_child;
		}
	} // Thread Pointer�� �ƴ� ��쿡 �������� ���󰡴� �˰���
	return temp;
}

// Tree�� inorder Traverse �� ����Ѵ�
void tinorder(threaded_ptr tree) 
{
	threaded_ptr temp = tree;
	for (;;) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%c ", temp->data);
	}
}

threaded_ptr Create() 
{
	threaded_ptr temp;
	temp = malloc(sizeof(struct threaded_tree));
	temp->left_child = NULL;
	temp->right_child = NULL;
	temp->left_thread = TRUE;
	temp->right_thread = TRUE;
	return temp;
}

// Ʈ�� ����� (���� ������)
void InsertNode(threaded_ptr node, threaded_ptr tree) 
{
	if (tree->left_child == NULL) {
		tree->left_child = node;
	}
	else {
		tree->right_child = node;
	}
}

// Doubly Linked List
void LLInsert(char d, int index, int Nodenum,Position P) 
{
	Position TmpCell;
	TmpCell = malloc(sizeof(struct LNode));
	TmpCell->idx = index+1;
	TmpCell->data = d;
	TmpCell->Next = NULL;
	TmpCell->CN = 0;
	TmpCell->passed = 0;
	TmpCell->Child_Left = NULL;
	TmpCell->Child_Right = NULL;
	if (index > (Nodenum / 2)) {
		TmpCell->leaf = 1;
	}
	else {
		TmpCell->leaf = 0;
	}
	P->Next = TmpCell;
	TmpCell->Prev = P;
}

void main()
{
	int NodeNum = 0;
	char buffer[200];
	fp = fopen("input.txt", "r");
	//fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	NodeNum = atoi(buffer);
	if (NodeNum > 100) {
		printf("ERROR : Exceeded Limit of 100\n");
		exit(100);
	}

	fgets(buffer, sizeof(buffer), fp);
	int n;
	threaded_ptr R; // Root
	threaded_ptr T; // Tree Node Pointer
	R = malloc(sizeof(struct threaded_tree)); // ����Ȯ��
	T = Create();
	R->left_child = T;
	R->right_child = R;
	R->left_thread = FALSE;
	R->right_thread = FALSE;
	T->data = buffer[0];
	//T->left_thread = R;
	//T->right_child = R;

	List L;
	L = malloc(sizeof(struct LNode));
	L->Next = NULL;
	L->Prev = NULL;

	// Linked List ����
	for (n = 1; n <= NodeNum; n++) {
		Position P = L;
		while (P->Next != NULL) {
			P = P->Next;
		}
		char d = buffer[n * 2];
		printf("��ǥ: %c %d\n", d,P->idx);
		LLInsert(d, n, NodeNum, P);
		
	}
	printf("Insertion to LL Complete\n");

	Position E = L;
	while (E->Next->Next != NULL) {
		E = E->Next;
	} // End Pointer E
	printf("%c %d\n", E->data, E->idx);
	Position Temp = E;
	while (Temp->Prev != NULL) {
		printf("Reentered\n");
		int prt;
		Position Find = L;
		prt = (Temp->idx) / 2;
		printf("Checked %d\n", prt);
		while (Find->idx != prt) {
			Find = Find->Next;
		}
		printf("Checked\n");
		Temp->Parent = Find;
		if ((Temp->idx) % 2 == 1) {
			Find->Child_Right = Temp;
			(Find->CN)++;
		}
		else {
			Find->Child_Left = Temp;
			(Find->CN)++;
		}
		Temp = Temp->Prev;
		printf("Previous %c\n", Temp->data);
	}
	Temp->Parent = NULL;
	// ��ũ�� ����Ʈ���� �θ� �ڽ� ���� �� ����!
	printf("Connected every LL \n");

	// ��ũ�� ����Ʈ�� Ʈ���� ������!
	Temp = L->Next;
	threaded_ptr higher = T; // ó�� ���� Head
	while (Temp->leaf != TRUE) { // ��� ���鸸 �ѷ�����
		threaded_ptr ch1 = NULL;
		threaded_ptr ch2 = NULL;
		if (Temp->CN == 2) {
			ch1 = Create(); // Tree ���� ����
			ch1->data = Temp->Child_Left->data; // Tree ���� ��忡 data ����ֱ�
			//Temp->Child_Left->passed = 1; // �������� �˷���
			InsertNode(ch1, higher); // ����

			ch2 = Create();
			ch2->data = Temp->Child_Right->data;
			//Temp->Child_Right->passed = 1; // �������� �˷���
			//Temp->passed = 1;
			InsertNode(ch2, higher);
			higher->left_thread = FALSE;
			higher->right_thread = FALSE;
		}
		else if (Temp->CN == 1) {
			ch1 = Create();
			ch1->data = Temp->Child_Left->data;
			//Temp->Child_Left->passed = 1;
			InsertNode(ch1, higher);
			higher->left_thread = FALSE;
			higher->right_thread = FALSE;
		}

		// T���� ���� subtree�� �̵���Ŵ
		threaded_ptr search = T; // ��ġ�� reset �ʿ���
		int target = Temp->Next->idx; // ���� �����Ͱ� target
		int now = 1; // T������ ������
		int gj = 4; // ���� (��� �������� ����)
		int move = 1;
		while (target >= gj) {
			move++;
			gj = gj * 2;
		}
		for (move; move > 0; move--) {
			if (move == 1) {
				if (target % 2 == 0) {
					search = search->left_child;
				}
				else {
					search = search->right_child;
				}
			}
			else {
				gj = gj / 2;
				if ((target % gj) < (gj / 2)) {
					search = search->left_child;
				}
				else {
					search = search->right_child;
				}
			}
		}
		higher = search; // higher�� ���� 1,2,3,4 �̷��� �����Ѵ�
		Temp = Temp->Next; // �������� ����
	} // subtree�� �߽� ���� �Ϸ�

	Temp = L->Next;
	threaded_ptr trd = T;
	while (trd->left_child == NULL) {
		trd = trd->left_child;
	}
	trd->left_child = R;
	while (trd->right_child == NULL) {
		trd = trd->right_child;
	}
	trd->right_child = R; // �ֿܰ� �������̽�

	trd = T->left_child;
	while (trd->right_child != NULL) {
		trd = trd->right_child;
	}
	trd->right_child = T;
	(Temp->passed)++;
	trd = T->right_child;
	while (trd->left_child != NULL) {
		trd = trd->left_child;
	}
	trd->left_child = T;
	(Temp->passed)++;// �߾� ����

	while (Temp->leaf != 1) { // Leaf���� ���ϱ�
		Temp = Temp->Next;
	}
	while (Temp->idx <= NodeNum) { // ���⼭���� leaf position
		int i = Temp->idx; // target
		trd = T; // Tree Pointer Reset
		int now = 1; // T������ ������
		int gj = 4; // ���� (��� �������� ����)
		int move = 1;
		while (i >= gj) {
			move++;
			gj = gj * 2;
		}
		for (move; move > 0; move--) {
			if (move == 1) {
				if (i % 2 == 0) {
					trd->left_child->right_child = trd;
					(Temp->Parent->passed)++;
					trd = trd->left_child;
				}
				else {
					trd->right_child->left_child = trd;
					(Temp->Parent->passed)++;
					trd = trd->right_child;
				}
			}
			else {
				gj = gj / 2;
				if ((i % gj) < (gj / 2)) {
					trd = trd->left_child;
				}
				else {
					trd = trd->right_child;
				}
			}
		}
		// Trd ��ǥ �������� ���� �Ϸ� (�д��� �־���)
		Temp = Temp->Next;
	}

	Temp = L->Next;

	while (Temp->leaf != 1) {
		threaded_ptr trv = T;
		threaded_ptr dis = T;
		if (Temp->passed == 0) {
			int target = Temp->idx;
			int now = 1;
			int gj = 4;
			int move = 1;
			while (target >= gj) {
				move++;
				gj = gj * 2;
			}
			for (move; move > 0; move--) {
				if (move == 1) {
					if (target % 2 == 0) {
						trv = trv->left_child;
					}
					else {
						trv = trv->right_child;
					}
				}
				else {
					gj = gj / 2;
					if ((target % gj) < (gj / 2)) {
						trv = trv->left_child;
					}
					else {
						trv = trv->right_child;
					}
				}
			}
			while (dis->left_child != R) {
				dis = dis->left_child;
			}
			while (insucc(dis) != NULL) {
				dis = insucc(dis);
			}
			dis->right_child = trv;
			(Temp->passed)++;
			continue;
		}
		else if (Temp->passed == 1) {
			threaded_ptr trv = T;
			threaded_ptr dis = T;
			if (Temp->passed == 0) {
				int target = Temp->idx;
				int now = 1;
				int gj = 4;
				int move = 1;
				while (target >= gj) {
					move++;
					gj = gj * 2;
				}
				for (move; move > 0; move--) {
					if (move == 1) {
						if (target % 2 == 0) {
							trv = trv->left_child;
						}
						else {
							trv = trv->right_child;
						}
					}
					else {
						gj = gj / 2;
						if ((target % gj) < (gj / 2)) {
							trv = trv->left_child;
						}
						else {
							trv = trv->right_child;
						}
					}
				}
				while (dis->left_child != R) {
					dis = dis->left_child;
				}
				while (insucc(dis) != NULL) {
					dis = insucc(dis);
				}
				dis->right_child = trv;
				(Temp->passed)++;
			}
			Temp = Temp->Next;
		}

		tinorder(R);
		fclose(fp);
		//fclose(fp2)
	}
}