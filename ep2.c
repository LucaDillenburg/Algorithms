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

		/* Amnt Matrix */
		scanf("%d %d", &m, &n);
		if (m==0 && n==0)
			break;

		/* Alloc and Populate matrix */
		matrix = (char**)malloc(sizeof(char*) * m);
		for (i=0; i<m; i++) {
			int j;
			matrix[i] = (char*)malloc(sizeof(char) * n);
			for (j=0; j<n; j++)
				scanf("%c", &matrix[i][j]);
		}

		/* Amnt Words */
		scanf("%d", &p);

		/* Alloc and Populate Words */
		maxLengthWord = max(m,n) + 1;
		words = (char**)malloc(sizeof(char*) * p);
		for (i=0; i<p; i++) {
			words[i] = (char*)malloc(sizeof(char) * maxLengthWord);
			scanf("%s", words[i]);
		}

		/* #################################################################################### */
		
		/*
		Print 
		printMatrix(matrix, m, n);
		printf("\n");
		printStrArray(words, p);
		*/

		/* #################################################################################### */
		printf("Processing...\n");

		/* TODO: PROCESSING... */

		/* #################################################################################### */
		printf("Freeing...\n");

		/* Free Words */
		for (i=0; i<p; i++) {
			free(words[i]);
		}
		free(words);

		/* Free Matrix */
		for (i=0; i<m; i++) {
			free(matrix[i]);
		}
		free(matrix);
	}
	
	return 0;
}
