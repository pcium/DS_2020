#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
typedef struct Node2* PtrToList;
typedef PtrToList List;
typedef PtrToList Position;
FILE* fp;
FILE* fp2;

struct Node
{
	char Element;
	int Precedence;
	PtrToNode Next;
};

struct Node2
{
	char Element;
	PtrToList Next;
};

Stack CreateStack()
{
	Stack S;
	S = malloc(sizeof(struct Node));
	if (S == NULL) {
		fprintf(fp2, "Out of space!!!\n");
		exit(1);
	}
	S->Next = NULL;
	// S->Next 가 곧 Stack의 Top이다
	return S;
}

List CreateList()
{
	List L;
	L = malloc(sizeof(struct Node2));
	if (L == NULL) {
		fprintf(fp2, "Out of space!!!\n");
		exit(1);
	}
	L->Next = NULL;
	return L;
}

Position EndPointer(List L)
{
	Position P = L;
	while (P->Next != NULL) {
		P = P->Next;
	}
	return P;
}

void PushList(char C, List L, Position P)
{
	Position TmpCell;
	TmpCell = malloc(sizeof(struct Node2));
	if (TmpCell == NULL) {
		fprintf(fp2, "Out of space!!!");
		exit(1);
	}
	TmpCell->Element = C;
	TmpCell->Next = NULL;
	P->Next = TmpCell;
}

void PushStack(char C, Stack S, int pc)
{
	PtrToNode TmpCell;
	TmpCell = malloc(sizeof(struct Node));
	if (TmpCell == NULL) {
		fprintf(fp2, "Out of space!!!");
		exit(1);
	}
	TmpCell->Element = C;
	TmpCell->Precedence = pc;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
}

char PopStack(Stack S)
{
	PtrToNode FirstCell = S->Next;
	char temp;
	if (S->Next == NULL) {
		fprintf(fp2, "ERROR: Tried to Pop Empty Stack\n");
		return ' ';
	}
	else {
		temp = FirstCell->Element;
		S->Next = FirstCell->Next;
		free(FirstCell);
		return temp;
	}
}

void PrintList(List L)
{
	Position P = L;
	fprintf(fp2, "Postfix Form : ");
	do {
		P = P->Next;
		fprintf(fp2, "%c", P->Element);
	} while (P->Next != NULL);
	fprintf(fp2, "\n");
}

int Arith(int op1, int op2, char C)
{
	switch (C) {
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	case '%':
		return op1 % op2;
	default:
		fprintf(fp2, "WRONG OPERATOR");
		exit(3);
	}
}

void Result(List L)
{
	Position P = L;
	P = P->Next;
	int stk[100] = { 0 };
	int op1, op2, result;
	int stktop = -1;
	char oprt;
	char ch;
	char* chbuf;
	int intbuf;
	while (P->Next != NULL) {
		if (isdigit(P->Element)) {
			ch = P->Element;
			chbuf = &ch;
			intbuf = atoi(chbuf);
			stktop++;
			stk[stktop] = intbuf;
		}
		else {
			oprt = P->Element;
			op2 = stk[stktop];
			stktop--;
			op1 = stk[stktop];
			stktop--;
			result = Arith(op1, op2, oprt);
			stktop++;
			stk[stktop] = result;
		}
		P = P->Next;
	}
	//마지막 연산
	oprt = P->Element;
	op2 = stk[stktop];
	stktop--;
	op1 = stk[stktop];
	stktop--;
	result = Arith(op1, op2, oprt);
	fprintf(fp2, "%d", result);
}

void main()
{
	int length;
	char buffer[100];
	char infix[100];
	char* infixprint = NULL;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(infix, sizeof(infix), fp);
	strcpy(buffer, infix);
	infixprint = strtok(buffer, "#");
	fprintf(fp2, "Infix Form : %s\n", infixprint);

	Stack S = CreateStack();
	List L = CreateList();
	Position P;

	length = strlen(infix);
	int i;
	for (i = 0; i < length; i++)
	{
		char now = infix[i];
		char popped = ' ';
		if (isdigit(infix[i])) {
			P = EndPointer(L);
			PushList(infix[i], L, P);
		}
		else if (infix[i] == '+' || infix[i] == '-') {
			if (S->Next == NULL || S->Next->Precedence <= 0) {
				PushStack(infix[i], S, 1);
			}
			else {
				popped = PopStack(S);
				P = EndPointer(L);
				PushList(popped, L, P);
				PushStack(infix[i], S, 1);
			}
		}
		else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '%') {
			if (S->Next == NULL || S->Next->Precedence <= 1) {
				PushStack(infix[i], S, 2);
			}
			else {
				popped = PopStack(S);
				P = EndPointer(L);
				PushList(popped, L, P);
				PushStack(infix[i], S, 2);
			}
		}
		else if (infix[i] == '(') {
			PushStack(infix[i], S, 0);
		}
		else if (infix[i] == ')') {
			while (S->Next->Element != '(') {
				popped = PopStack(S);
				P = EndPointer(L);
				PushList(popped, L, P);
			}
			popped = PopStack(S);
		}
		else {
			while (S->Next != NULL) {
				popped = PopStack(S);
				P = EndPointer(L);
				PushList(popped, L, P);
			}
		}
	}
	free(S);
	PrintList(L); // Postfix 출력
	fprintf(fp2, "Evaluation Result: ");
	Result(L);

	fclose(fp);
	fclose(fp2);
}

//4*(7+3%6)-(4/2)+9-(2*3)# input.txt