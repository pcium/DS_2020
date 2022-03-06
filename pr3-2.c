#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUE_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueRecord* Queue;
FILE* fp;
FILE* fp2;

struct QueueRecord {
	int Capacity;
	int Front;
	int Rear;
	int Size;
	int* Array;
};

void MakeEmpty(Queue Q) {
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
	Q->Capacity = MAX_QUEUE_SIZE;
}

int IsFull(Queue Q) {
	if (Q->Size >= Q->Capacity)
		return 1;
	else
		return 0;
}

int IsEmpty(Queue Q) {
	if (Q->Size <= 0)
		return 1;
	else
		return 0;
}

void enQ(int X, Queue Q) {
	if (IsFull(Q))
		fprintf(fp2, "Full\n");
	else {
		Q->Size++;
		Q->Rear = (Q->Rear + 1) % (Q->Capacity); //Rear Pointer�� ������Ŵ
		Q->Array[Q->Rear] = X;
	}
}

void deQ(Queue Q) {
	if (IsEmpty(Q))
		fprintf(fp2, "Empty\n");
	else {
		Q->Size--;
		fprintf(fp2, "%d\n", Q->Array[Q->Front]);
		Q->Front = (Q->Front + 1) % Q->Capacity; //Front pointer�� ������Ŵ
	}
}

void main()
{
	int OrderNum = 0; // ����Ǵ� ��ɰ��
	char buffer[10];
	char* sliced = NULL;
	char* remain = NULL;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	
	if (fp != NULL) {
		fgets(buffer, sizeof(buffer), fp);
		OrderNum = atoi(buffer);
	} // ��ɾ� ���� �޴� �κ�

	Queue Q;
	Q = malloc(sizeof(struct QueueRecord));
	if (Q == NULL) {
		fprintf(fp2, "Out of space!!!\n");
		exit(1);
	}
	Q->Array = malloc(sizeof(int) * MAX_QUEUE_SIZE); // array �����Ϳ� array�� ���� ���� �������
	if (Q->Array == NULL) {
		fprintf(fp2, "Out of space!!!\n");
		exit(2);
	}
	MakeEmpty(Q);

	int n;
	for (n = 0; n < OrderNum; n++) {
		int num = 0;
		fgets(buffer, sizeof(buffer), fp); // ���پ� �о����#
		if (strlen(buffer) <= 4) {
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