#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct {
	int data; //��� ������
	struct Node *next; // �� ���� ��带 ����Ű��� next����
} Node; //����� ����ü ����

Node *head; //���� �׻� ������ ������ ��������
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
	//sliced = strtok(NULL, " "); // �̰� �ι�° �ּ�
	//printf("%s\n", sliced);
	//sliced = strtok(NULL, " "); // �̰� ����°
	//printf("%s", sliced);
	fclose(fp);
	return 0;
}