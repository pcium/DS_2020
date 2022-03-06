#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 99999;

FILE* fp;
FILE* fp2;

int size;
int** adj; // Adjacancy List
int* dist; // Distance
int* prev; // Previous
int* visit; // Visited
int temp[100] = { -1 }; // Temporary Verticle Storage

typedef struct Node* node;
typedef struct Heap* heap;
struct Node {
	int key;
	int weight;
};

struct Heap {
	int capacity;
	int size;
	node* element; // Node* 노드 리스트
};

int findIndex(int num) {
	int i = 0;
	for (; i < size; i++) {
		if (temp[i] == num) return i;
	}
	printf("Error: Wrong input in vertex");
	exit(2); // Error Code 2
}

int minDistance(int* d) {
	int min = INF;
	int min_index = -1;
	int i = 0;
	for (; i < size; i++) {
		if (visit[i] == 0 && dist[i] <= min) {
			min = dist[i];
			min_index = i;
		}
	}
	return min_index;
}

heap createMinHeap() {
	heap H = malloc(sizeof(struct Heap));
	H->capacity = size;
	H->size = 0;
	H->element = malloc(sizeof(struct Node) * (size + 1));
	int i = 0;
	for (; i <= size; i++) {
		node P = malloc(sizeof(struct Node));
		H->element[i] = P;
	}
	H->element[0]->weight = 100000;
	return H;
}

void insertHeap(heap H, int vertex, int distance) {
	if (H->capacity <= H->size) {
		fprintf(fp2, "Priority queue is full\n");
		return;
	}
	int i = 1;
	for (; i <= H->size; i++) {
		if (vertex == H->element[i]->key) {
			fprintf(fp2, "%d is already in the heap.\n", vertex);
			return;
		}
	}

	node temp = NULL;
	int idx = ++(H->size);
	H->element[idx]->key = vertex;
	H->element[idx]->weight = distance; // 방금 들어온 노드
	if (idx <= 1) return;
	for (; H->element[idx / 2]->weight > distance; idx /= 2) {
		if (idx <= 1) break;
		temp = H->element[idx / 2]; // 부모 저장
		H->element[idx / 2] = H->element[idx]; // 자식을 부모로
		H->element[idx] = temp;
	}
}

int deleteMin(heap H) {
	int i, Child;
	node MinElement, LastElement;
	MinElement = H->element[1];
	LastElement = H->element[H->size--];

	for (i = 1; i * 2 <= H->size; i = Child){
		Child = i * 2;
		if (Child != H->size && H->element[Child + 1]->weight < H->element[Child]->weight)
			Child++;
		if (LastElement->weight > H->element[Child]->weight)
			H->element[i] = H->element[Child];
		else
			break;
	}
	H->element[i] = LastElement;
	return minDistance(dist);
}

void printShortest(int x) {
	if (prev[x] == -1) {
		printf("%d ", temp[x]);
		return;
	}
	printShortest(prev[x]);
	printf("%d ", temp[x]);
}

void Dijkstra(int start_idx) {
	heap H = createMinHeap();
	dist[start_idx] = 0;
	
	int k = 1;
	for (; k <= size; k++) {
		insertHeap(H, temp[k-1], dist[k-1]);
	}

	k = 0;
	for (; k < size - 1; k++) {
		int u = deleteMin(H);
		visit[u] = 1;
		int i = 0;
		for (; i < size; i++) {
			if (!visit[i] && adj[u][i] != 99999 && dist[u] + adj[u][i] < dist[i]) {
				prev[i] = u;
				dist[i] = dist[u] + adj[u][i];
			}
			if (H->size <= 0) break;
		}
	}
}

void main() {
	size = 0;
	int num, x, y;

	char buffer[1200];
	char* sliced = NULL;
	char cut[1200];
	char* cut2 = NULL;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	sliced = strtok(buffer, " ");
	num = atoi(sliced);
	temp[0] = num;
	size++;
	sliced = strtok(NULL, " ");
	while (sliced != NULL) {
		if (size >= 100) {
			printf("Error: Exceeded max verticle size");
			exit(100);
		}

		num = atoi(sliced);
		temp[size] = num;
		size++;
		sliced = strtok(NULL, " ");
	}

	adj = (int**)malloc(size * sizeof(int*));
	int i = 0;
	for (; i < size; i++) {
		adj[i] = (int*)malloc(size * sizeof(int));
	}
	i = 0;
	for (; i < size; i++) {
		int j = 0;
		for (; j < size; j++) {
			adj[i][j] = INF;
		}
	}

	fgets(buffer, sizeof(buffer), fp); // Adjancy Graph Descriptions
	int count = 0;
	char* elem[100];
	sliced = strtok(buffer, " ");
	elem[0] = sliced;
	sliced = strtok(NULL, " ");
	while (sliced != NULL) {
		elem[++count] = sliced;
		sliced = strtok(NULL, " ");
	}
	int k = 0;
	for (; k <= count; k++) {
		strcpy(cut, elem[k]);
		cut2 = strtok(cut, "-");
		x = atoi(cut2);
		x = findIndex(x);
		cut2 = strtok(NULL, "-");
		y = atoi(cut2);
		y = findIndex(y);
		cut2 = strtok(NULL, "-");
		num = atoi(cut2);
		adj[x][y] = num;
	}

	fgets(buffer, sizeof(buffer), fp);
	sliced = strtok(buffer, " ");
	num = atoi(sliced); // Starting Point
	int n = findIndex(num);
	dist = malloc(sizeof(int) * size);
	prev = malloc(sizeof(int) * size);
	visit = malloc(sizeof(int) * size);
	i = 0;
	for (; i < size; i++) {
		dist[i] = INF;
		prev[i] = -1;
		visit[i] = 0;
	}

	sliced = strtok(NULL, " ");
	num = atoi(sliced);
	x = findIndex(num); // End Point

	Dijkstra(n); // 출발점 넣어줌
	printShortest(x);

	fclose(fp);
	fclose(fp2);
}