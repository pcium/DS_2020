#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp2;

typedef struct HeapStruct* PriorityQueue;
struct HeapStruct
{
	int Capacity;
	int Size;
	int* Elements;
};

void Insert(int X, PriorityQueue H) {
	if (H->Capacity <= H->Size) {
		fprintf(fp2, "Priority queue is full\n");
		return;
	}
	int i = 1;
	for (; i <= H->Size; i++) {
		if (X == H->Elements[i]) {
			fprintf(fp2, "%d is already in the heap.\n", X);
			return;
		}
	}

	int idx = ++(H->Size);
	int temp;
	H->Elements[idx] = X;
	for (; H->Elements[idx / 2] < X; idx /= 2) {
		if (idx <= 1) break;
		temp = H->Elements[idx/2];
		H->Elements[idx / 2] = H->Elements[idx];
		H->Elements[idx] = temp;
	}
	fprintf(fp2, "insert %d\n", X);
}

void Find(int X, PriorityQueue H) {
	int idx = 1;
	int flag = 0;
	for (; idx <= H->Size; idx++) {
		if (X == H->Elements[idx]) flag = 1;
	}
	if (flag == 1) {
		fprintf(fp2, "%d is in the heap.\n", X);
	}
	else {
		fprintf(fp2, "%d is not in the heap.\n", X);
	}
}

void Print(PriorityQueue H) {
	int idx = 1;
	for (; idx <= H->Size; idx++) {
		fprintf(fp2, "%d ", H->Elements[idx]);
	}
	fprintf(fp2, "\n");
}

void main() {
	int num;
	char buffer[10];
	char* sliced = NULL;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	num = atoi(buffer);
	PriorityQueue H = malloc(sizeof(struct HeapStruct));
	H->Capacity = num;
	H->Size = 0;
	H->Elements = malloc(sizeof(int) * (num+1));

	while (1) {
		fgets(buffer, sizeof(buffer), fp);
		sliced = strtok(buffer, " ");

		if (sliced[0] == 'i') {
			sliced = strtok(NULL, " ");
			num = atoi(sliced);
			Insert(num, H);
		}
		else if (sliced[0] == 'f') {
			sliced = strtok(NULL, " ");
			num = atoi(sliced);
			Find(num, H);
		}
		else if (sliced[0] == 'p') {
			Print(H);
		}
		else {
			fprintf(fp2,"INPUT ERROR\n");
			exit(2);
		}
		if (feof(fp)) break;
	}
	fclose(fp);
	fclose(fp2);
}