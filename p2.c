#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *PtrToNode; // 노드 포인터를 PtrToNode로 표현
typedef PtrToNode List; // 노드 포인터를 리스트로 표시
typedef PtrToNode Position; // 노드 포인터를 포지션으로 표시
int nodeCount = 0;

typedef struct
{
	char* studentId;
	char* studentName;
} ElementType; // ElemenType이란 구조체

struct Node
{
	ElementType element; // ID랑 이름이 들어있는 변수
	PtrToNode next; // 다음에 있는 주소
}; // Node 구조체 (구조체 이름은 생략)

struct Node *header; //header 노드로 사용

/*
List MakeEmpty(List L)
{
	// Header 노드를 만든다
	L = (List)MALLOC(sizeof(struct Node)); //공간 생성
	L->element = header; // 새로운 list의 element란 곳에는
	L->next = NULL; // 처음이므로 NULL 반환
	return L;
}
*/


int IsEmpty(List L)
{
	return L->next == NULL;
} // 리스트가 비어있는지 확인

int IsLast(Position P, List L)
{
	return P->next == NULL;
} // 현재가 끝인지 확인

void Insert(ElementType X, List L, Position P) 
{
	Position TmpCell;
	TmpCell = malloc(sizeof(struct Node)); // 임시 노드 하나 생성
	if (TmpCell == NULL) {
		printf("FATAL ERROR: Out of space!");
		exit(0);
	} // 용량 부족해서 에러날 시
	TmpCell->element = X; //새 노드 element 에 X를 넣는다
	TmpCell->next = P->next; //TmpCell의 Next를 원래 P의 Next랑 연결
	P->next = TmpCell; //현재 포지션 포인터 다음 주소를 TmpCell로
	free(TmpCell);
}

void Delete(ElementType X, List L)
{
	// X 노드를 지우는 것을 목표로 한다
	Position P, TmpCell; // P 포인터와 임시 포인터
	P = FindPrevious(X, L); //지우고자 하는 이전 노드 찾음
	if (!IsLast(P, L)) // 마지막 노드가 아닐때 작동
	{
		TmpCell = P->next; // 임시포인터가 지우고자 하는 목표
		P->next = TmpCell->next; // 다다음 노드랑 연결해준다
		free(TmpCell); // 메모리 풀기
	}
}

Position Find(ElementType X, List L)
{
	Position P; // 어떤 포인터 하나. 현재는 NULL Pointer
	P = L->next; // Header Node 가리키고 있는데 그 다음 주소
	while ( (P != NULL) && (P->element != X))
	{
		// List가 끝나지 않았거나, 
		P = P->next; // 하나씩 훑어간다
	}
	return P;
}

Position FindPrevious(ElementType X, List L)
{

}

void PrintList(List L) 
{
	//링크드 리스트를 전부 출력한다
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
	FILE* fp; // 파일 포인터
	char str[30]; // 적당히 큰 문자열 할당
	char* temp;
	int count;
	int number[7];
	fp = fopen("input.txt", "r"); // 파일 열기
	List L = nodeLink(); // 헤더 노드 할당
	Position P = L;
	nodeCount++;
	while (1) 
	{
		fgets(str, sizeof(str), fp); // 열 하나를 읽는다

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