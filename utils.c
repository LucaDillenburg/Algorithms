#include <stdio.h>
#include "utils.h"

int max(int a, int b) {
	if (a>b)
		return a;
	else
		return b;
}

void printMatrix(char **matrix, int m, int n) {
	int i;
	for (i=0; i<m; i++) {
		int j;
		for (j=0; j<n; j++)
			printf("%c ", matrix[i][j]);
		printf("\n");
	}
}

void printStrArray(char **matrix, int length) {
	int i;
	for (i=0; i<length; i++)
		printf("%s\n", matrix[i]);
}
