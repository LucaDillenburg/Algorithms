#include <stdio.h>
#include "utils.h"

int max(int a, int b) {
	if (a>b)
		return a;
	else
		return b;
}

void printStrArray(char **matrix, int length) {
	int i;
	for (i=0; i<length; i++)
		printf("%s\n", matrix[i]);
}
