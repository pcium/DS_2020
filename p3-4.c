#define _CRT_SECURE_NO_WARNINGS
#define EmptyTOS -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct StackRecord* Stack;
FILE* fp;
FILE* fp2;

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	int Precedence;
	char* Array;
};

Stack CreateStack(int MaxElements)
{
	Stack S;

	S = malloc(sizeof(struct StackRecord));
	if (S == NULL)
		//fprintf(fp2, "Out of space!!!\n");

	S->Array = malloc(sizeof(char) * MaxElements); // array 포인터에 array를 위한 공간 만들어줌
	if (S->Array == NULL)
		//fprintf(fp2, "Out of space!!!\n");

	S->Capacity = MaxElements;
	S->TopOfStack = EmptyTOS;
	S->Precedence = 0;

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

void Push(char X, Stack S)
{
	if (IsFull(S))
		//fprintf(fp2, "Full\n");
		printf("Full\n");
	else {
		printf("Not Full yet! \n");
		S->Array[++S->TopOfStack] = X; // Causing Problem here!
		printf("No Problem");
	}

}

char Pop(Stack S)
{
	char temp;
	temp = S->Array[S->TopOfStack];
	if (IsEmpty(S)) {
		//fprintf(fp2, "Empty\n");
		printf("Empty\n");
	} else {
		//fprintf(fp2, "%d\n", S->Array[S->TopOfStack]);
		//printf("%c", temp);
		S->TopOfStack--;
		return temp;
	}
}

char InfToPost(char* infix, int length, Stack S)
{
	printf("Entered InfToPost\n");
	int i;
	int count=0;
	char popped = ' ';
	char post[100] = {'#'};
	char* postfix= NULL;
	for (i = 0; i < length; i++) {
		printf("Counting %d, %c\n", i, infix[i]);
		if (isdigit(infix[i])) {
			printf("Entered isDigit\n");
			post[count] = infix[i];
			count++;
		}
		else {
			printf("Entered Else\n");
			if (infix[i] == '+' || infix[i] == '-') 
			{
				if (S->Precedence <= 0) {
					Push(infix[i], S);
				}
				else {
					popped = Pop(S);
					post[count] = popped;
					count++;
				}
				S->Precedence = 1;
			}
			else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '%')
			{
				printf("Entered Pr2\n");
				if (S->Precedence <= 1) {
					printf("Pushing\n");
					Push(infix[i], S); // 여기 문제
					printf("Pushed\n");
				}
				else {
					popped = Pop(S);
					post[count] = popped;
					count++;
				}
				S->Precedence = 2;
			}
			else if (infix[i] == '(')
			{
				Push(infix[i], S); // 좌괄호는 집어넣는다
				S->Precedence = 0;
			}
			else if (infix[i] == ')')
			{
				while (popped != '(') {
					popped = Pop(S);
					post[count] = popped;
					count++;
				}
				Pop(S); // ( 까지 Pop 해준다.
			}
			else {
				while (!IsEmpty(S)) {
					popped = Pop(S); // #일때 있는 연산자 다 뺀다. 표시는 함수 안에서
					post[count] = popped;
					count++;
				} // 끝날 때는 괄호 걱정은 없다
			}
		}
	}
	printf("\n");
	postfix = strtok(post, "#");
	return postfix;
}

/*
void PostfixCal(char postfix)
{
	int result=0;

	printf("Evaluation Result: %d", result);
}
*/


void main() {
	int length=0;
	char buffer[100] = {'x'};
	char* infix = NULL;
	char* infixed = NULL;
	char* postfix = NULL;
	fp = fopen("input.txt", "r");
	//fp2 = fopen("output.txt", "w");
	Stack S = CreateStack(100);

	if (fp == NULL) {
		//fprintf(fp2, "Error: FILE NULL");
		exit(1);
	}
		
	fp = fgets(buffer, sizeof(buffer), fp);
	
	infix = strtok(buffer, "x");
	infixed = strtok(buffer, "#");
	printf("Infix Form : %s\n", infixed);
	length = strlen(infix);
	postfix = InfToPost(infix, length, S);
	printf("Postfix Form : %s", postfix);
	//PostfixCal(postfix);
	fclose(fp);
	//fclose(fp2);
}

//4*(7+3%6)-(4/2)+9-(2*3)# input.txt