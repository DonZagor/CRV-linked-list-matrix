#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	int c, r, v;
	struct node* next;
}Node;
Node* formMatrixList(int** matrix, int m, int n)
{
	Node* head = NULL, * tail = NULL;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				Node* new = malloc(sizeof(Node));
				if (!new) exit(-2);
				new->c = j;
				new->r = i;
				new->v = matrix[i][j];
				new->next = NULL;
				if (!head) head = new;
				else tail->next = new;
				tail = new;
			}
		}
	}
	return head;
}
void printMatrixList(Node* head)
{
	Node* temp = head;
	printf("\n|ROW|COL|VAL\n");
	while (temp) {
		printf("  %d    %d    %d\n", temp->r, temp->c, temp->v);
		temp = temp->next;
	}
}
void deallocateMatrixList(Node* head)
{
	Node* temp = head, * p = NULL;
	while (temp) {
		p = temp;
		temp = temp->next;
		free(p);
	}
	printf("\nUspesna dealokacija matrice liste.\n");
}
size_t matrixListMemory(Node* head)
{
	Node* temp = head;
	size_t total = 0;
	while (temp) {
		total += sizeof(Node);
		temp = temp->next;
	}
	return total;
}
int** allocateMatrixVector(int** matrix, int m, int n)
{
	matrix = malloc(m * sizeof(int*));
	if (!matrix) exit(-1);
	for (int i = 0; i < m; i++) {
		matrix[i] = malloc(n * sizeof(int));
		if (!matrix[i]) exit(-1);
	}
	return matrix;
}
void loadMatrixVector(int** matrix, int m, int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("Unesite [%d, %d] element matrice: ", i, j);
			int p = scanf("%d", &matrix[i][j]);
		}
	}
}
void printMatrixVector(int** matrix, int m, int n)
{
	printf("\nUneta matrica: \n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; printf("%d ", matrix[i][j++]));
		printf("\n");
	}
}
void deallocateMatrixVector(int** matrix, int m)
{
	for (int i = 0; i < m; free(matrix[i++]));
	free(matrix);
	printf("\nUspesna dealokacija matrice vektora.\n");
}
size_t matrixVectorMemory(int m, int n)
{
	size_t total = 0;
	total += m * sizeof(int*);
	for (int i = 0; i < m; i++) {
		total += n * sizeof(int);
	}
	return total;
}
int savedMemory(int m, int n, Node* head)
{
	size_t total1 = matrixVectorMemory(m, n);
	size_t total2 = matrixListMemory(head);
	size_t total = 0;
	if (total2 > total1) {
		total = total2 - total1;
		total = (int)total;
		total *= -1;
	}
	else if (total1 > total2) {
		total = total1 - total2;
		total = (int)total;
	}
	return total;
}
int main()
{
	int** a = NULL;
	int m, n;
	printf("Unesite broj vrsta i kolona matrice: ");
	int p = scanf("%d%d", &m, &n);
	if (m <= 0 || n <= 0) return 1;
	a = allocateMatrixVector(a, m, n);
	loadMatrixVector(a, m, n);
	printMatrixVector(a, m, n);
	Node* head = NULL;
	head = formMatrixList(a, m, n);
	deallocateMatrixVector(a, m);
	printMatrixList(head);
	size_t total1 = matrixVectorMemory(m, n);
	size_t total2 = matrixListMemory(head);
	printf("\n%zu %zu\n", total1, total2);
	int total = savedMemory(m, n, head);
	if (total > 0) printf("Saved memory: %d bytes", total);
	else if (total < 0) printf("Lost memory: %d bytes", total * (-1));
	deallocateMatrixList(head);
	return 0;
}
//matrica 5x7
//0 0 4 0 0 0 0
//0 0 0 5 0 11 0
//0 0 0 0 0 0 0
//9 0 0 8 0 0 0
//0 0 0 0 0 0 15