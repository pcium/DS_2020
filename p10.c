// 2018083672 Lab 10
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp2;
int once = 1;

typedef struct Graph* GRP;
typedef struct Queue* QUE;
struct Graph{
	int size;
	int* node;
	int** matrix;
};

struct Queue {
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

int idx_of_Node(GRP G, int x) {
	int i = 0;
	while (G->size > i) {
		if (G->node[i] == x) return i;
		i++;
	}
	printf("Error: Out of range\n");
	exit(100);
}

void initGraph(GRP G) {
	int i = 0;
	for (; i < G->size; i++) {
		int j = 0;
		for (; j < G->size; j++) {
			G->matrix[i][j] = 0;
		}
	} // Pad everything into 0
}

GRP InsertEdge(GRP G, int a, int b) {
	a = idx_of_Node(G,a);
	b = idx_of_Node(G,b);
	G->matrix[a][b] = 1;
	return G;
}

QUE MakeNewQueue(int X) {
	QUE Q = malloc(sizeof(struct Queue));
	Q->key = malloc(sizeof(int) * X);
	Q->max_queue_size = X;
	Q->qsize = 0;
	Q->first = 0;
	Q->rear = 0;
	int i = 0;
	for (; i < Q-> max_queue_size; i++) {
		Q->key[i] = -1;
	}
	return Q;
}

void Enqueue(QUE Q, int X) {
	if (Q->max_queue_size <= Q->qsize) {
		printf("Error: Queue is full\n");
		exit(10);
	}
	else if (once) {
		Q->qsize++;
		Q->key[Q->rear] = X;
		once = 0;
	}
	else {
		Q->qsize++;
		Q->rear = Q->rear + 1;
		Q->key[Q->rear] = X;
	}	
}

int Dequeue(QUE Q, GRP G) {
	if (Q->qsize <= 0) {
		printf("Error: Queue is empty\n");
		exit(30);
	}
	Q->qsize--;
	printf("%d ", G->node[Q->key[Q->first]]);
	return (Q->key[Q->first]);
}

void DegreeCount(GRP G,int* list) {
	int i = 0;
	int j;
	for (; i < G->size; i++) {
		int count = 0;
		j = 0;
		for (; j < G->size; j++) {
			if (G->matrix[j][i] == 1) {
				count++;
			}
		}
		list[i] = count;
	}
}

int isEmpty(QUE Q) {
	if (Q->qsize <= 0)
		return 1;
	else
		return 0;
}

void TopSort(GRP G) {
	QUE Q;
	int v, w;
	int count;
	int* indegree;
	indegree = malloc(sizeof(int) * G->size); // Degree 포현
	printf("\nTopSort Result : \n");

	Q = MakeNewQueue(G->size);
	DegreeCount(G, indegree);

	count = 0;
	for (; count < G->size; count++) {
		v = count; // 노드 값을 가져옴
		if (indegree[v] == 0) {
			Enqueue(Q, v);
		}
	}

	while (!isEmpty(Q)) {
		v = Dequeue(Q, G);
		Q->first = Q->first + 1;
		w = 0;
		for (; w < G->size; w++) {
			if (G->matrix[v][w]) {
				G->matrix[v][w] = 0;
				if (--indegree[w] == 0) {
					Enqueue(Q, w);
				}
			}
		}
	}
}

void Print(GRP G) {
	printf("Adjacency matrix\n  ");
	int i = 0;
	for (; i < G->size; i++) {
		printf("%d ", G->node[i]);
	}
	i = 0;
	printf("\n");
	for (; i < G->size; i++) {
		int j = 0;
		printf("%d ", G->node[i]);
		for (; j < G->size; j++) {
			printf("%d ", G->matrix[i][j]);
		}
		printf("\n");
	}
}

void main() {
	int element_idx=0;
	int n1;
	int x, y;
	char arr[2];
	arr[1] = '\0';
	char buffer[200];
	char* sliced = NULL;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	sliced = strtok(buffer, " ");
	GRP G = malloc(sizeof(struct Graph));
	G->node = malloc(sizeof(int) * 9);
	n1 = atoi(sliced);
	G->node[element_idx] = n1;
	sliced = strtok(NULL, " ");
	
	while (sliced != NULL) {
		if (element_idx == 9) {
			printf("Cannot Eneter more than 10\n");
			exit(10);
		}
		
		element_idx++;
		n1 = atoi(sliced);
		G->node[element_idx] = n1;
		sliced = strtok(NULL, " ");
	}
	G->size = (element_idx+1);
	G->matrix = (int**)malloc(G->size * sizeof(int*));
	int i = 0;
	for (; i < G->size; i++) {
		G->matrix[i] = (int*)malloc(G->size * sizeof(int));
	}
	initGraph(G);

	fgets(buffer, sizeof(buffer), fp);
	sliced = strtok(buffer, " ");
	arr[0] = sliced[0];
	x = atoi(arr);
	arr[0] = sliced[2];
	y = atoi(arr);
	G = InsertEdge(G, x, y);
	sliced = strtok(NULL, " ");
	while (sliced != NULL) {
		arr[0] = sliced[0];
		x = atoi(arr);
		arr[0] = sliced[2];
		y = atoi(arr);
		G = InsertEdge(G, x, y);
		sliced = strtok(NULL, " ");
	}
	Print(G); // Graph Complete
	TopSort(G);

	fclose(fp);
	fclose(fp2);
}