#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List; // 시작 포인터
typedef PtrToNode Position; // 현재 위치 포인터
typedef struct {
	char* studentId; // 아이디 공간 할당 후 포인팅 필요
	char* studentName; // 이름 공간 할당 후 포인팅 필요
} ElementType; // element->studentId 이런 식으로 접근해 줘야 한다

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
		DeleteList(L); // 이미 있으면 리스트를 비운다
	L = MALLOC(sizeof(struct Node)); //리스트 포인터를 위한 헤더 노드 공간 할당
	if (L == NULL)
		printf("ERROR: OUT OF MEMORY");
		exit(1);
	L->next = NULL; //단 L 다음 주소는 NULL 상태이다
	return L;
}

int isEmpty(List L) {
	return L->next == NULL;
	// 리스트가 비어있는지 확인
}

int isLast(Position P, List L) {
	return P->next == NULL;
	// 현재가 끝인지 확인
}

Position Find(ElementType X, List L) {
	// 특정 노드를 찾고 값을 Position 값을 반환한다
	Position P; // 새로운 Tmp 포인터
	P = L->next; // P는 첫 노드의 주소 지님
	while ((P != NULL) && (P->element.studentId != X)) {
		P = P->next; // 끝이 아니고 찾는 것과 같지 않으면 이동한다
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
	// 새로운 노드를 기존 노드 뒤에 연결한다
	Position TmpCell;

	TmpCell = MALLOC(sizeof(struct Node));
	if (TmpCell == NULL) {
		printf("ERROR: OUT OF SPACE!");
		exit(1);
	}
	TmpCell->element = X; // element type를 입력해준다
	TmpCell->next = P->next; //
	P->next = TmpCell; //
}

void Delete(ElementType X, List L) {
	// 특정 노드를 찾아 없앤다
	Position P, TmpCell;
	P = FindPrevious(X, L);
	if (!IsLast(P, L)) {
		TmpCell = P->next;
		P->next = TmpCell->next;
		free(TmpCell);
	}
}

void PrintList(List L) {
	Position P = L; // 최초노드 복수
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
	Position P, Tmp; // 두 개의 포인터
	P = L->next; // P는 L 다음 노드
	L->next = NULL; // L 다음 노드를 없앤다
	while (P != NULL) { //P가 끝까지 갈때까지 진행
		Tmp = P->next;
		free(P);
		P = Tmp;
		// 한 칸씩 옮겨가면서 없앤다.
	}
}

void main() {
	FILE* fp;
	char str[30];
	char id[10];
	char name[30];
	char order;
	fp = fopen("input.txt", "r");
	List L; // 리스트 고정 포인터 생성
	Position P; // 리스트 포지션 포인터 생성
	
	L = MakeEmpty(NULL); // 헤더 노드 일단 하나 만들었다
	P = L; // 일단 헤더에 배치
	//nodeCount++; // 헤더 노드도 일단 하나로 친다. (일단 필요할 지는 보류한다)

	while (1) {
		fgets(str, sizeof(str), fp); // str에 한 줄 입력을 받는다
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