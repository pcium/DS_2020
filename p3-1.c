#define _CRT_SECURE_NO_WARNINGS
#define EmptyTOS -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackRecord *Stack;
FILE* fp;
FILE* fp2;

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	int* Array;
};

Stack CreateStack(int MaxElements)
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	if (S == NULL)
		fprintf(fp2, "Out of space!!!\n");

	S->Array = malloc(sizeof(int) * MaxElements); // array �����Ϳ� array�� ���� ���� �������
	if (S->Array == NULL)
		fprintf(fp2, "Out of space!!!\n");
	
	S->Capacity = MaxElements;
	S->TopOfStack = EmptyTOS;

	return S;
}

int IsEmpty(Stack S) {
	if (S->TopOfStack == -1)
		return 1;
	else
		return 0;
}

int IsFull(Stack S) {
	if (S->TopOfStack == S->Capacity)
		return 1;
	else
		return 0;
}

void Push(int X, Stack S)
{
	if (IsFull(S))
		fprintf(fp2, "Full\n");
	else {
		S->Array[++S->TopOfStack] = X;
	}
		
}

void Pop(Stack S)
{
	if (IsEmpty(S))
		fprintf(fp2, "Empty\n");
	else
		fprintf(fp2, "%d\n", S->Array[S->TopOfStack]);
		S->TopOfStack--;
		
}

void main() {
	
	int OrderNum=0;
	char buffer[10];
	char* sliced = NULL;
	char* remain = NULL;
	fp=fopen("input.txt", "r");
	fp2=fopen("output.txt", "w");
	Stack S = CreateStack(100); // �뷮 100�� stack ��ȯ

	if (fp != NULL) {
		fgets(buffer, sizeof(buffer), fp);
		OrderNum = atoi(buffer);

	} // ��ɾ� ���� �޴� �κ�
	
	for (int n = 0; n < OrderNum; n++) {
		int num = 0;
		fgets(buffer, sizeof(buffer), fp); // ���پ� �о����#
		if (strlen(buffer) <= 4) {
			Pop(S);
		}
		else {
			sliced = strtok_s(buffer, " ", &remain);
			num = atoi(remain);
			Push(num, S);
		}
	}

	fclose(fp);
	fclose(fp2);
}