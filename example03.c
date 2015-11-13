/*
 * Matrix functions
 * Thiago Luis Baldissarelli - 2015
 *
 * Fibonacci Generator via matrix
 *
 * 0, 1, 1, 2, 3, 5, 8, 13, 21...ad infinitum.
 *
 * [[1, 1]^n  [[F(n+1), F(n)  ],
 *  [1, 0]] =  [F(n)  , F(N-1)] 
 */

#include <stdio.h> /* stdInputOutput */
#include <stdlib.h> /* Memory Allocation */
#include "matrixlib.h" /* Matrix calculation lib */

double fibonacci(int n){
	int i;
	double (**matrix) = seed(2, 2);
	matrix[0][0] = 1.0;
	matrix[0][1] = 1.0;
	matrix[1][0] = 1.0;
	matrix[1][1] = 0.0;

	double (**originalMatrix) = reallocMatrix(matrix, 2, 2);

	for(i = 0; i < n; i++)
		matrix = matricial_multiplication(matrix, originalMatrix, 2, 2, 2, 2);
	return(matrix[1][1]);
}

int main(){
	int n;
	printf("0, 1, 1, 2, 3, 5... - First term will be 0\n");
	printf("Generate till the term number: ");
	scanf("%i", &n);

	printf("%lf\n", fibonacci(n));
}