#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/*
Observavoes
- Backtracking com Pilha
- Podem sobrar palavras na lista
- Outro: verificar se a palavra nao se cruza com nenhuma outra
- Otimizacao: Ter um vetor de vetores em que em cada posicao do vetor maior ha as palavras do vetor menor
*/

int main() {
	for (;;) {
		int m,n;
		int p;
		char **matrix;
		char **words;
		int i;
		int maxLengthWord;

		printf("Waiting input...\n");

		// Amnt Matrix
		// printf("Amnt Matrix...\n");
		scanf("%d %d", &m, &n);
		if (m==0 && n==0)
			break;

		// Alloc and Populate matrix
		// printf("Alloc and Populate matrix...\n");
		matrix = (char**)malloc(sizeof(char*) * m);
		for (i=0; i<m; i++) {
			int j;
			matrix[i] = (char*)malloc(sizeof(char) * n);
			for (j=0; j<n; j++) {
				// int a;
				scanf("%c", &matrix[i][j]);
				// scanf("%d", &a);
			}
		}

		// Amnt Words
		// printf("Amnt Words...\n");
		scanf("%d", &p);

		// Alloc and Populate Words
		// printf("Alloc and Populate Words...\n");
		maxLengthWord = max(m,n) + 1;
		words = (char**)malloc(sizeof(char*) * p);
		for (i=0; i<p; i++) {
			// char a[100];
			words[i] = (char*)malloc(sizeof(char) * maxLengthWord);
			scanf("%s", words[i]);
			// scanf("%s", &a);
		}

		//////////////////////////////////////////////////////////////////////////////////////////
		
		// Print 
		// printMatrix(matrix, m, n);
		// printf("\n");
		// printStrArray(words, p);

		//////////////////////////////////////////////////////////////////////////////////////////
		printf("Processing...\n");

		// ...
		// TODO: PROCESSING...
		// ...

		//////////////////////////////////////////////////////////////////////////////////////////
		printf("Freeing...\n");

		// Free Words
		// printf("Free Words...\n");
		for (i=0; i<p; i++) {
			free(words[i]);
		}
		free(words);

		// Free Matrix
		// printf("Free Matrix...\n");
		for (i=0; i<m; i++) {
			free(matrix[i]);
		}
		free(matrix);
	}
	
	return 0;
}
