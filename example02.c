/*
 * Matrix functions
 * Thiago Luis Baldissarelli - 2015
 *
 * Implementation of the matrixlib.c
 * Example 02 - Linear equation solver
 *
 */

#include <stdio.h> /* stdInputOutput */
#include <stdlib.h> /* Memory Allocation */
#include "matrixlib.h"

void print_matrix(int rows, int columns, double (**matrix)){
	/* Print matrix on program interface */
	int i, j;

	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++)
			printf("%lf ", matrix[i][j]);
		printf("\n");
	}
}

int main(){
	int totalVariables;
	int i, j, k, l; /* Pivots */
	float item;
	char *variable;

	printf("How many variables your system have? ");
	scanf("%d", &totalVariables);

	char (**variables) = malloc(totalVariables * sizeof(char *));
	double (*determinantArray) = (double *)malloc(sizeof(double *)*(totalVariables+1));

	/* Allocate variables */
	for(i = 0; i < totalVariables; i++){
		printf("Insert the variable %d (Max of 99 characters): ", i+1);
		variables[i] = malloc(100*sizeof(char)); /* 99 characters + /0x0 */
		scanf("%s", variables[i]);
	}

	double (**matrixA) = seed(totalVariables, totalVariables);
	double (**matrixB) = seed(totalVariables, 1);

	for(i = 0; i < totalVariables; i++){
		for(j = 0; j < totalVariables; j++){
			printf("Insert item %dx%d of equation (%s): ", i+1, j+1, variables[j]);
			scanf("%f", &item);
			matrixA[i][j] = item;
		}
		printf("Insert the independent term of equation %d: ", i+1);
		scanf("%f", &item);
		matrixB[i][0] = item;
	}

	determinantArray[0] = determinant(matrixA, totalVariables);
	if(determinantArray[0] != 0.0){
		double (**newMatrixA) = seed(totalVariables, totalVariables);
		for(i = 0; i < totalVariables; i++){
			for(j = 0; j < totalVariables; j++)
				for(k = 0; k < totalVariables; k++)
					newMatrixA[j][k] = matrixA[j][k];
			for(l = 0; l < totalVariables; l++)
				newMatrixA[l][i] = matrixB[l][0];
			determinantArray[i+1] = determinant(newMatrixA, totalVariables);
			/* Print result */
			printf("%s = %f\n", variables[i], determinantArray[i+1]/determinantArray[0]);
		}
	}else{
		printf("This system do not have an solution.");
	}
}
