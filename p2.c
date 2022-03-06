#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *PtrToNode; // ��� �����͸� PtrToNode�� ǥ��
typedef PtrToNode List; // ��� �����͸� ����Ʈ�� ǥ��
typedef PtrToNode Position; // ��� �����͸� ���������� ǥ��
int nodeCount = 0;

typedef struct
{
	char* studentId;
	char* studentName;
} ElementType; // ElemenType�̶� ����ü

struct Node
{
	ElementType element; // ID�� �̸��� ����ִ� ����
	PtrToNode next; // ������ �ִ� �ּ�
}; // Node ����ü (����ü �̸��� ����)

struct Node *header; //header ���� ���

/*
List MakeEmpty(List L)
{
	// Header ��带 �����
	L = (List)MALLOC(sizeof(struct Node)); //���� ����
	L->element = header; // ���ο� list�� element�� ������
	L->next = NULL; // ó���̹Ƿ� NULL ��ȯ
	return L;
}
*/


int IsEmpty(List L)
{
	return L->next == NULL;
} // ����Ʈ�� ����ִ��� Ȯ��

int IsLast(Position P, List L)
{
	return P->next == NULL;
} // ���簡 ������ Ȯ��

void Insert(ElementType X, List L, Position P) 
{
	Position TmpCell;
	TmpCell = malloc(sizeof(struct Node)); // �ӽ� ��� �ϳ� ����
	if (TmpCell == NULL) {
		printf("FATAL ERROR: Out of space!");
		exit(0);
	} // �뷮 �����ؼ� ������ ��
	TmpCell->element = X; //�� ��� element �� X�� �ִ´�
	TmpCell->next = P->next; //TmpCell�� Next�� ���� P�� Next�� ����
	P->next = TmpCell; //���� ������ ������ ���� �ּҸ� TmpCell��
	free(TmpCell);
}

void Delete(ElementType X, List L)
{
	// X ��带 ����� ���� ��ǥ�� �Ѵ�
	Position P, TmpCell; // P �����Ϳ� �ӽ� ������
	P = FindPrevious(X, L); //������� �ϴ� ���� ��� ã��
	if (!IsLast(P, L)) // ������ ��尡 �ƴҶ� �۵�
	{
		TmpCell = P->next; // �ӽ������Ͱ� ������� �ϴ� ��ǥ
		P->next = TmpCell->next; // �ٴ��� ���� �������ش�
		free(TmpCell); // �޸� Ǯ��
	}
}

Position Find(ElementType X, List L)
{
	Position P; // � ������ �ϳ�. ����� NULL Pointer
	P = L->next; // Header Node ����Ű�� �ִµ� �� ���� �ּ�
	while ( (P != NULL) && (P->element != X))
	{
		// List�� ������ �ʾҰų�, 
		P = P->next; // �ϳ��� �Ⱦ��
	}
	return P;
}

Position FindPrevious(ElementType X, List L)
{

}

void PrintList(List L) 
{
	//��ũ�� ����Ʈ�� ���� ����Ѵ�
	printf("*****LIST*****\n");

	printf("**************\n");
}

List nodeLink()
{
	List L = MALLOC(sizeof(struct Node));
	Position P = L;
	P->next = NULL;
	return L;
}

void main() 
{
	FILE* fp; // ���� ������
	char str[30]; // ������ ū ���ڿ� �Ҵ�
	char* temp;
	int count;
	int number[7];
	fp = fopen("input.txt", "r"); // ���� ����
	List L = nodeLink(); // ��� ��� �Ҵ�
	Position P = L;
	nodeCount++;
	while (1) 
	{
		fgets(str, sizeof(str), fp); // �� �ϳ��� �д´�

		if (str[0] == "p") 
		{
			PrintList(L);
		}
		else 
		{
			for (count = 2; str[count] != " "; count++) {
				number[count - 2] = str[count];
			}

		}


		/*
		
		if (str[0] == "i")
		{
			Insert(,L,P);
		}
		else if (str[0] == "d")
		{

		}
		else if (str[0] == "f")
		{

		}
		else
		{
			printf("ERROR: WRONG ORDER GIVEN IN INPUT FILE");
		}
		*/
		if (feof(fp)) break;
	}
	fclose(fp);
	FILE* fp = fopen("output.txt", "w");
	while (1)
	{

		scanf_s("");
		if (feof(fp)) break;
	}

}