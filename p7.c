#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

FILE* fp;
FILE* fp2;

typedef struct Edge* edge_set;
struct Edge {
	int number;
	int e1;
	int e2;
	char shape;
	edge_set Next;
};

int dj[100] = { 0 }; // 전역 disjoint

void randomize(int* arr, int num)
{
	srand(time(NULL));
	int tmp, rn, i = 0;
	for (; i < num - 1; i++) {
		rn = rand() % (num - i) + i;
		tmp = arr[i];
		arr[i] = arr[rn];
		arr[rn] = tmp;
	}
}

void Create_Vertical(int i, edge_set v, int count) {
	edge_set ns = malloc(sizeof(struct Edge));
	ns->e1 = i;
	ns->e2 = i + 1;
	ns->shape = '|';
	ns->number = count;
	while (v->Next != NULL) {
		v = v->Next;
	}
	v->Next = ns;
	ns->Next = NULL;
}

void Create_Horizontal(int i, edge_set h, int num) {
	edge_set ns = malloc(sizeof(struct Edge));
	ns->e1 = i;
	ns->e2 = i + num;
	ns->shape = '-';
	ns->number = i + 12;
	while (h->Next != NULL) {
		h = h->Next;
	}
	h->Next = ns;
	ns->Next = NULL;
}

edge_set Find_List(edge_set v, int n) {
	edge_set fnd = v;
	while (fnd->number != n) {
		fnd = fnd->Next;
	}
	return fnd;
}

int Find(int x) {
	if (dj[x] <= 0)
		return x;
	else return (dj[x] = Find(dj[x]));
}

void Union(int a, int b) {
	if (dj[b] < dj[a])
		dj[a] = b;
	else
	{
		if (dj[b] == dj[a])
			dj[a]--;
		dj[b] = a; // add r2 to r1
	}
}

void print(int n, edge_set vertical, edge_set horizontal) {
	edge_set ver = vertical;
	edge_set hor = horizontal;
	int i = 1;
	for (; i <= n; i++) fprintf(fp2, "+ - ");
	fprintf(fp2, "+\n|   ");
	while (1) {
		i = 1;
		for (; i < n; i++) {
			ver = ver->Next;
			fprintf(fp2, "%c   ", ver->shape);
		}
		if (ver->Next == NULL) {
			fprintf(fp2, "|\n");
			break;
		}
		fprintf(fp2, "|\n+");
		i = 1;
		for (; i <= n; i++) {
			hor = hor->Next;
			fprintf(fp2, " %c +", hor->shape);
		}
		fprintf(fp2, "\n|   ");
	}
	i = 1;
	for (; i <= n; i++) fprintf(fp2, "+ - ");
	fprintf(fp2, "+\n");
}

void main() {
	int* arr;
	char buffer[3];
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	int num = atoi(buffer); // 이 예제에서는 4 (4 * 4)
	int edge_num = 2 * num * (num - 1);
	arr = (int*)malloc(sizeof(int) * edge_num);
	int i = 0;
	for (; i < edge_num; i++) {
		arr[i] = i + 1; // Initialize
	}
	randomize(arr, edge_num); // 24 크기의 랜덤 숫자 배열

	edge_set ver = malloc(sizeof(struct Edge));
	edge_set hor = malloc(sizeof(struct Edge));
	ver->Next = NULL;
	hor->Next = NULL;

	i = 1;
	int count = 1;
	for (; i <= num * num; i++) {
		if (i % num == 0) continue;
		else {
			Create_Vertical(i, ver, count);
			count++;
		}
	}
	i = 1;
	for (; i <= num * (num - 1); i++) {
		Create_Horizontal(i, hor, num);
	}

	i = 0;
	for (; i < edge_num; i++) {
		edge_set Temp = NULL;
		int now = arr[i];
		int a, b;
		if (now <= edge_num / 2) { // Vertical
			Temp = Find_List(ver, now);
			a = Temp->e1;
			b = Temp->e2;
			if (Find(a) != Find(b)) {
				Temp->shape = ' ';
				Union(Find(a), Find(b));
			}
		}
		else { // Horizontal
			Temp = Find_List(hor, now);
			a = Temp->e1;
			b = Temp->e2;
			if (Find(a) != Find(b)) {
				Temp->shape = ' ';
				Union(Find(a), Find(b));
			}
		}

		int k = 1;
		count = 0;

		for (; k <= num * num; k++) {
			if (dj[k] <= 0) count++;
		}

		if (count <= 1) break; // 다 합쳐지면 빠져나옴
	}
	print(num, ver, hor);

	free(arr);
	fclose(fp);
	fclose(fp2);
}