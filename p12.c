#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode* Position;  
typedef Position List;
typedef struct HashTbl* HashTable;

struct ListNode {
	int Element;
};

struct HashTbl {
	int TableSize;
	int* TheLists;
};

FILE* fp;
FILE* fp2;


int Hash(int value, int Size, int i, int solution) {
	if (solution == 0) {
		return (value % Size) + i;
	}
	else if (solution == 1) {
		return (value % Size) + i * i;
	}
	else if (solution == 2) {
		return((value % Size) + i * (7 - (value % 7))) % Size;
	}
	else {
		printf("Error: Wrong solution code!\n");
		exit(6);
	}
}

int find(HashTable H, int value, int solution) {
	if (solution == 0) {
		int i = 0;
		for (; i < H->TableSize; i++) {
			if (H->TheLists[i] == value) {
				return i;
			}
		}
		return -1;
	}
	else if (solution == 1) {
		int i = 0, index;
		for (; i < H->TableSize; i++) {
			index = Hash(value, H->TableSize, i, solution);
			if (H->TheLists[index] == value) {
				return index;
			}
		}
		return -1;
	}
	else if (solution == 2) {
		int i = 0, index;
		for (; i < H->TableSize; i++) {
			index = Hash(value, H->TableSize, i, solution);
			if (H->TheLists[index] == value) {
				return index;
			}
		}
		return -1;
	}
	else {
		printf("Error: Wrong solution code!\n");
		exit(4);
	}
	return -1;
}

void insert(HashTable H, int value, int solution) {
	int idx, i=0;
	if (solution == 0) {
		if (find(H, value, solution) != -1) {
			fprintf(fp2, "Already exists\n");
			return;
		}
		while (1) {
			idx = Hash(value, H->TableSize, i, solution);
			if (H->TheLists[idx] == 0) {
				H->TheLists[idx] = value;
				fprintf(fp2, "Inserted %d\n", value);
				return;
			}
			else {
				i++;
				if (i >= H->TableSize) {
					printf("Error: Hash Table is Full\n");
					return;
				}
			}
		}
	}
	else if (solution == 1) {
		if (find(H, value, solution) != -1) {
			fprintf(fp2, "Already exists\n");
			return;
		}
		while (1) {
			idx = Hash(value, H->TableSize, i, solution);
			if (H->TheLists[idx] == 0) {
				H->TheLists[idx] = value;
				fprintf(fp2, "Inserted %d\n", value);
				return;
			}
			else {
				i++;
				if (i >= H->TableSize) {
					printf("Error: Hash Table is Full\n");
					return;
				}
			}
		}
	}
	else if (solution == 2) {
		if (find(H, value, solution) != -1) {
			fprintf(fp2, "Already exists\n");
			return;
		}
		while (1) {
			idx = Hash(value, H->TableSize, i, solution);
			if (H->TheLists[idx] == 0) {
				H->TheLists[idx] = value;
				fprintf(fp2, "Inserted %d\n", value);
				return;
			}
			else {
				i++;
				if (i >= H->TableSize) {
					printf("Error: Hash Table is Full\n");
					return;
				}
			}
		}
	}
	else {
		printf("Error: Wrong solution code!\n");
		exit(2);
	}
}

void delete(HashTable H, int value, int solution) {
	int idx;
	if (solution == 0) {
		idx = find(H, value, solution);
		if (idx == -1) {
			fprintf(fp2, "%d not exists\n" , value);
			return;
		}
		H->TheLists[idx] = 0;
		fprintf(fp2, "Deleted %d\n", value);
	}
	else if (solution == 1) {
		idx = find(H, value, solution);
		if (idx == -1) {
			fprintf(fp2, "%d not exists\n", value);
			return;
		}
		H->TheLists[idx] = 0;
		fprintf(fp2, "Deleted %d\n", value);
	}
	else if (solution == 2) {
		idx = find(H, value, solution);
		if (idx == -1) {
			fprintf(fp2, "%d not exists\n", value);
			return;
		}
		H->TheLists[idx] = 0;
		fprintf(fp2, "Deleted %d\n", value);
	}
	else {
		printf("Error: Wrong solution code!\n");
		exit(3);
	}
}

void print(HashTable H) {
	int i = 0;
	for (; i < H->TableSize; i++) {
		fprintf(fp2, "%d ", H->TheLists[i]);
	}
	fprintf(fp2, "\n\n");
}

void main() {
	int num, size, solution=-1;
	char* sliced = NULL;
	char buffer[10];
	char letter, order;
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	fgets(buffer, sizeof(buffer), fp);
	num = atoi(buffer);
	int i = 0;
	while (i < num) {
		fgets(buffer, sizeof(buffer), fp);
		letter = buffer[0];
		if (letter == 'L') {
			fprintf(fp2, "Linear\n");
			solution = 0;
		}
		else if (letter == 'Q') {
			fprintf(fp2, "Quadratic\n");
			solution = 1;
		}
		else if (letter == 'D') {
			fprintf(fp2, "Double\n");
			solution = 2;
		}
		if (solution == -1) {
			printf("Error: Wrong Hash typed!\n");
			exit(100);
		}

		fgets(buffer, sizeof(buffer), fp);
		if (i == 1) {
			fgets(buffer, sizeof(buffer), fp);
		}
		size = atoi(buffer);
		HashTable H = malloc(sizeof(struct HashTbl));
		H->TableSize = size;
		H->TheLists = malloc(sizeof(int) * H->TableSize);
		int j = 0;
		for (; j < size; j++) {
			H->TheLists[j] = 0;
		}

		fgets(buffer, sizeof(buffer), fp);
		order = buffer[0];
		while (1) {
			int val, val2;
			if (order == 'i') {
				sliced = strtok(buffer, " ");
				sliced = strtok(NULL, " ");
				val = atoi(sliced);
				insert(H, val, solution);
			}
			else if (order == 'd') {
				sliced = strtok(buffer, " ");
				sliced = strtok(NULL, " ");
				val = atoi(sliced);
				delete(H, val, solution);
			}
			else if (order == 'f') {
				sliced = strtok(buffer, " ");
				sliced = strtok(NULL, " ");
				val = atoi(sliced);
				val2 = find(H, val, solution);
				if (val2 != -1) {
					fprintf(fp2, "Found %d\n", val);
				}
				else {
					fprintf(fp2, "Not found\n");
				}
			}
			else if (order == 'p') {
				print(H);
			}
			else if (order == 'q') {
				break;
			}
			else {
				printf("Error: Wrong input order!\n");
				exit(10);
			}
			fgets(buffer, sizeof(buffer), fp);
			order = buffer[0];
		}
		i++;
		free(H);
	}
	fclose(fp);
	fclose(fp2);
}