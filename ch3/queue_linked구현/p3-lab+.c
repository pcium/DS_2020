// 이건 Lab3 추가연습용
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* PtrToNode;
typedef PtrToNode Queue;

FILE* fp;
FILE* fp2;

struct Node
{
	int element;
	PtrToNode Next;
};

void enQ(int num, Queue Q)
{

}

void deQ()
{

}

void main()
{
	Queue Q;
	Q = malloc(sizeof(struct Node)); // 헤드노드 생성
	Q->Next = NULL;

	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int num = 0;
	char order;
	char buffer[10];
	char* sliced = NULL;
	char* remain = NULL;
	fgets(buffer, sizeof(buffer), fp); // array용은 한번 넘긴다

	while (1)
	{
		fgets(buffer, sizeof(buffer), fp);
		if (feof(fp)) {
			break;
		}
		else if (strlen(buffer) <= 4) {
			deQ(Q);
		}
		else {
			sliced = strtok_s(buffer, " ", &remain);
			num = atoi(remain);
			enQ(num, Q);
		}
	}
	fclose(fp);
	fclose(fp2);
}