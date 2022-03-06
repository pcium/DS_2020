#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List; // ���� ������
typedef PtrToNode Position; // ���� ��ġ ������
typedef struct {
	char* studentId; // ���̵� ���� �Ҵ� �� ������ �ʿ�
	char* studentName; // �̸� ���� �Ҵ� �� ������ �ʿ�
} ElementType; // element->studentId �̷� ������ ������ ��� �Ѵ�

struct Node {
	ElementType element;
	PtrToNode next;
};

int isEmpty(List L);
int isLast(Position P, List L);
List MakeEmpty(List L);
void DeleteList(List L);

void Insert(ElementType X, List L, Position P);
void Delete(ElementType X, List L);
Position Find(ElementType X, List L);
void PrintList(List L);

List MakeEmpty(List L) {
	if (L != NULL)
		DeleteList(L); // �̹� ������ ����Ʈ�� ����
	L = MALLOC(sizeof(struct Node)); //����Ʈ �����͸� ���� ��� ��� ���� �Ҵ�
	if (L == NULL)
		printf("ERROR: OUT OF MEMORY");
		exit(1);
	L->next = NULL; //�� L ���� �ּҴ� NULL �����̴�
	return L;
}

int isEmpty(List L) {
	return L->next == NULL;
	// ����Ʈ�� ����ִ��� Ȯ��
}

int isLast(Position P, List L) {
	return P->next == NULL;
	// ���簡 ������ Ȯ��
}

Position Find(ElementType X, List L) {
	// Ư�� ��带 ã�� ���� Position ���� ��ȯ�Ѵ�
	Position P; // ���ο� Tmp ������
	P = L->next; // P�� ù ����� �ּ� ����
	while ((P != NULL) && (P->element.studentId != X)) {
		P = P->next; // ���� �ƴϰ� ã�� �Ͱ� ���� ������ �̵��Ѵ�
	}
	return P;
}

Position FindPrevious(ElementType X, List L) {
	Position P;
	P = L;
	while (P->next != NULL && P->next->element != X)
		P = P->next;
	return P;
}

void Insert(ElementType X, List L, Position P) {
	// ���ο� ��带 ���� ��� �ڿ� �����Ѵ�
	Position TmpCell;

	TmpCell = MALLOC(sizeof(struct Node));
	if (TmpCell == NULL) {
		printf("ERROR: OUT OF SPACE!");
		exit(1);
	}
	TmpCell->element = X; // element type�� �Է����ش�
	TmpCell->next = P->next; //
	P->next = TmpCell; //
}

void Delete(ElementType X, List L) {
	// Ư�� ��带 ã�� ���ش�
	Position P, TmpCell;
	P = FindPrevious(X, L);
	if (!IsLast(P, L)) {
		TmpCell = P->next;
		P->next = TmpCell->next;
		free(TmpCell);
	}
}

void PrintList(List L) {
	Position P = L; // ���ʳ�� ����
	if (IsEmpty(L)) printf("Empty List\n");
	else {
		do {
			P = P->next;
			printf("%s ", P->element.studentId);
			printf("%s\n", P->element.studentName);
		} while (!IsLast(P, L));
		printf("\n");
	}
}

void DeleteList(List L) {
	Position P, Tmp; // �� ���� ������
	P = L->next; // P�� L ���� ���
	L->next = NULL; // L ���� ��带 ���ش�
	while (P != NULL) { //P�� ������ �������� ����
		Tmp = P->next;
		free(P);
		P = Tmp;
		// �� ĭ�� �Űܰ��鼭 ���ش�.
	}
}

void main() {
	FILE* fp;
	char str[30];
	char id[10];
	char name[30];
	char order;
	fp = fopen("input.txt", "r");
	List L; // ����Ʈ ���� ������ ����
	Position P; // ����Ʈ ������ ������ ����
	
	L = MakeEmpty(NULL); // ��� ��� �ϴ� �ϳ� �������
	P = L; // �ϴ� ����� ��ġ
	//nodeCount++; // ��� ��嵵 �ϴ� �ϳ��� ģ��. (�ϴ� �ʿ��� ���� �����Ѵ�)

	while (1) {
		fgets(str, sizeof(str), fp); // str�� �� �� �Է��� �޴´�
		struct Node* tmp = MALLOC(sizeof(struct Node));
		
		if (str[0] == "p") {
			PrintList(L);
		}
		else if (str[0] == "i") {
			do {
				P = P->next;
			} while (P->next != NULL);

			//Insert(, L, P);
		}
		else if (str[0] == "d") {
			//Delete();
		}
		else if (str[0] == "f") {
			//Find();
		}
		else {
			printf("ERROR: WRONG ORDER GIVEN IN INPUT FILE");
			exit(0);
		}

		if (feof(fp)) break;
		free(tmp);
	}
	fclose(fp);
	void DeleteList(L);
}