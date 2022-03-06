#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct {
	int data; //담는 데이터
	struct Node *next; // 그 다음 노드를 가르키기는 next변수
} Node; //노드라는 구조체 생성

Node *head; //노드는 항상 포인터 변수로 선언하자
*/


int main(void) {
	char str[30];
	char* sliced = NULL;
	char* remain = NULL;
	int num = 0;
	FILE* fp;
	fp = fopen("input.txt", "r");
	fgets(str, sizeof(str), fp);
	sliced = strtok_s(str, " ", &remain);
	sliced = strtok_s(NULL, " ", &remain);
	num = atoi(sliced);
	printf("%d\n", num);
	printf("%s\n", remain);
	//sliced = strtok(NULL, " "); // 이게 두번째 주소
	//printf("%s\n", sliced);
	//sliced = strtok(NULL, " "); // 이게 세번째
	//printf("%s", sliced);
	fclose(fp);
	return 0;
}