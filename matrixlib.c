/*
 * Matrix functions
 * Thiago Luis Baldissarelli
 *
 *  25/06/2014 - Initial code
 *  18/06/2015 - Code revision
 *  11/09/2015 - Determinant bug fix
 *  16/09/2015 - File split
 *	17/09/2015 - Better determinant algorithm (fixed zero errors)
 *  23/09/2015 - Fixed allocation errors, gaussian upper/down functions
 *
 *  Implemented functions:
 *	  Gaussian Upper                NOT 100%
 *    Gaussian Lower                TESTED
 *	  Matrix multiplication         TESTED
 *	  Add and subtract matrices     TESTED
 * 	  Identity matrix               TESTED
 *	  Transpose                     TESTED
 *	  Determinant                   TESTED
 *	  Inverse matrix                TESTED
 *	  Scalar multiplication         TESTED
 *
 */

#include <stdio.h> /* stdInputOutput */
#include <stdlib.h> /* Memory Allocation */
#include "matrixlib.h"

typedef enum{false, true} bool; /* Define bool type */

/*
 * Basic part of program
 * Allocate, reallocate and verify matrices.
 */
double **seed(int rows, int columns){
	/* Create an seed matrix (allocate) */
	int i, j;
	double (**matrix) = (double **)malloc(sizeof(double *)*rows); /* Allocate rows */
	
	for(i = 0; i < rows; i++)
		matrix[i] = (double *)malloc(sizeof(double)*columns); /* Allocate columns */
	return(matrix);
}

double **reallocMatrix(double (**original), int rows, int columns){
	/* Reallocate matrix in memory */
	int i, j;
	double (**newMatrix) = seed(rows, columns);

	for(i = 0; i < rows; i++)
		for(j = 0; j < columns; j++)
			newMatrix[i][j] = original[i][j];
	return(newMatrix);
}

bool verify(int type, int matrix1_rows, int matrix1_columns, int matrix2_rows, int matrix2_columns){
	/* Verify matrix limitations */
	bool isValid = false;
	
	if(matrix1_rows > 0 && matrix1_columns > 0)
		if((type == 0 && (matrix1_rows == matrix1_columns)) || (type == 1 && (matrix1_columns == matrix2_rows)) || (type == 2))
			/*
			 * Type 0
			 * Lines and columns are equal.
			 * Work only with one matrix.
			 * Used for determinants, sum, and inverse matrices.
			 *
			 * Type 1
			 * Matrix1 columns are equal to Matrix2 rows.
			 * Works with two matrices.
			 * Used for multiply matrices.
			 *
			 * Type 2
			 * Without line/column restrictions.
			 * Works with one or two matrices.
			 * Used to create identity matrix and scalar multiplication.
			 */
			isValid = true;
	return(isValid);
}

/*
 * Mathematical operations
 * 
 */
double **gaussian_lower(int matrix_size, double (**matrix), int (*permutations)){
	/* Gaussian lower elimination */
	/* NOT FINISHED */
	int i, j, k;
	double factor, temp;
	double (**newMatrix) = reallocMatrix(matrix, matrix_size, matrix_size);

	for(i = matrix_size; i > 1; i--){
		for(j = i - 1; j >= 0; j--){
			factor = newMatrix[j][i]/newMatrix[i][i];
			for(k = 0; k < matrix_size + 1; k++){
				newMatrix[j][k] -= factor*newMatrix[i][k];
			}
		}
	}
	return(newMatrix);
}

/* Gaussian upper elimination */
double **gaussian_upper(double (**matrix), int matrix_size, int (*permutations)){
	/*
	 * - Calculate determinant via Gaussian upper elimination (Calculate an
	 * Triangular equivalent matrix, then multiply the diagonal principal)
	 * - Example:
	 * [[0, 1, 1],   [[1, 0,  1],
	 *  [1, 0, 1], =  [0, 1,  1],
	 *  [1, 1, 0]]    [0, 0, -2]]
	 *
	 */
	int i, j, k; /* Pivots */
	double factor, temp; /* Workaround variables */
	double (**newMatrix) = reallocMatrix(matrix, matrix_size, matrix_size); /* Reallocate matrix */

	for(i = 0; i < matrix_size - 1; i++){
		if(newMatrix[i][i] == 0){
			for(k = i; k < matrix_size; k++){
				if(newMatrix[k][i] != 0){
					for(j = 0; j < matrix_size; j++){
						temp = newMatrix[i][j];
						newMatrix[i][j] = newMatrix[k][j];
						newMatrix[k][j] = temp;
					}
				k = matrix_size;
				}
			}
			(*permutations) += 1;
		}
		if(newMatrix[i][i] != 0){
			for(k = i+1; k < matrix_size; k++){
				factor = -1.0 * newMatrix[k][i]/newMatrix[i][i];
				for(j = i; j < matrix_size; j++)
					newMatrix[k][j] += (factor * newMatrix[i][j]);
			}
		}
	}
	return(newMatrix);
}

double determinant(double (**matrix), int size){
	/*
	 * - Calculate determinant via Gaussian upper elimination (Calculate an
	 * Triangular equivalent matrix, then multiply the diagonal principal)
	 * - Example:
	 * [[0, 1, 1],   [[1, 0,  1],
	 *  [1, 0, 1], =  [0, 1,  1],
	 *  [1, 1, 0]]    [0, 0, -2]]
	 * Multiplying diagonal principal will result in -2
	 * But permutations will be 1, 1%2 is equal 1
	 * then we will multiply by -1, then determinant is 2
	 *
	 */
	int i; /* Pivot */
	int permutations = 0; /* Number of columns-line permutations */
	double determinant = 1; /* Neutral term of multiplication. */

	/* Gaussian upper elimination */
	double (**newMatrix) = gaussian_upper(matrix, size, &permutations);

	/* Multiply elements in principal diagonal */
	for(i = 0; i < size; i++)
		determinant *= newMatrix[i][i];

	/* If permutations are impar, multiply by -1 */
	if(permutations%2 != 0)
		determinant *= -1;

	/* Return determinant result */
	return(determinant);
}

double **identity_matrix(int size){
	/*
	 * Create an matrix, of size NxN, where the diagonal elements are all 1.0
	 * Example:
	 *  [[1, 0, 0],
	 *   [0, 1, 0],
	 *   [0, 0, 1]]
	 *
	 */
	int i, j; /* Pivots */
	double (**newMatrix) = seed(size, size); /* Do a new memory allocation */

	for(i = 0; i < size; i++)
		newMatrix[i][i] = 1.0;
	return(newMatrix);
}

double **transpose(double (**matrix), int rows, int columns){
	/*
	 * Transpose an matrix
	 * Example:
	 * ([[1, 2, 3],)t  [[1, 4, 7],
	 * ( [4, 5, 6],) =  [2, 5, 8],
	 * ( [7, 8, 9]])    [3, 6, 9]]
	 *
	 */
	int i, j;
	double (**newMatrix) = seed(columns, rows);

	for(i = 0; i < rows; i++)
		for(j = 0; j < columns; j++)
			newMatrix[j][i] = matrix[i][j];
	return(newMatrix);
}

double **scalar_multiplication(double (**matrix), int rows, int columns, long number){ 
	/*
	 * Multiplicate a matrix by an scalar number.
	 *     [[1, 2, 3],    [[02, 04, 06],
	 * 2 * 	[4, 5, 6],  =  [08, 10, 12],
	 *      [7, 8, 9]]     [14, 16, 18]]
	 *
	 */
	int i, j; /* Pivots */
	double (**newMatrix) = reallocMatrix(matrix, rows, columns); /* Reallocate matrix */
	
	for(i = 0; i < rows; i++)
		for(j = 0; j < columns; j++)
			newMatrix[i][j] *= number; 	
	return(newMatrix);
}

double **sum_matrices(double (**matrix1), double (**matrix2), int rows, int columns, int type){
	/* 
	 * Sum two matrices.
	 * Example:
	 * [[1, 1, 1],  [[4, 4, 4],  [[5, 5, 5],
	 *  [2, 2, 2], + [5, 5, 5], = [7, 7, 7],
	 *  [3, 3, 3]]   [6, 6, 6]]   [9, 9, 9]]
	 *
	 */
	int i, j;
	double (**result) = seed(rows, columns);
	
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			if(type == 0) /* Sum (+) */
				result[i][j] = matrix1[i][j]+matrix2[i][j];
			if(type == 1) /* Subtract (-) */
				result[i][j] = matrix1[i][j]-matrix2[i][j];
		}
	}
	return(result);
}

double **matricial_multiplication(double (**matrix1), double (**matrix2), int matrix1_rows, int matrix1_columns, int matrix2_rows, int matrix2_columns){
	/* 
	 * Usual method used in matricial multiplications
	 * Example
	 * [[1, 2],                  [[14],
	 *  [3, 4], * [[1, 2, 3]], =  [32],
	 *  [5, 6]]                   [50]]
	 *
	 */
	int i, j, k;
	double (**result) = seed(matrix1_rows, matrix2_columns);

	for(i = 0; i < matrix1_rows; i++)
		for(j = 0; j < matrix2_columns; j++)
			for(k = 0; k < matrix1_columns; k++)
				result[i][j] += matrix1[i][k]*matrix2[k][j];
	return(result);
}

double **inverse_matrix(double (**matrix), int matrix_size){
	/* 
	 * - Calculate an inverse matrix via Gaussian-Jordan upper elimination and Gaussian-Jordan 
	 *   lower elimination.
	 * - A*B = B*A = I where A is an user-inputted matrix, B will be the result matrix and
	 *   I is an identity matrix.
	 * - Example
	 * [[1, 2], * [[a, b], = [[1, 0], --> [[a, b], = [[-2.0,  1.0],
	 *  [3, 4]] *  [c, d]] =  [0, 1]] -->  [c, d]] =  [ 1.5, -0.5]] 
	 *
	 */
	int i, j, k, up, left;
	double factor, temp;
	double (**workspace) = seed(matrix_size*2, matrix_size);
	double (**identity) = identity_matrix(matrix_size);
	double (**result) = seed(matrix_size, matrix_size);

	for(i = 0; i < matrix_size; i++)
		for(j = 0; j < matrix_size; j++)
			workspace[i][j] = matrix[i][j];

	for(i = matrix_size; i < matrix_size*2; i++)
		for(j = 0; j < matrix_size; j++)
			workspace[i][j] = identity[i-matrix_size][j];
	
	workspace = transpose(workspace, matrix_size*2, matrix_size); /* Transpose workspace */

	/* Gaussian-Jordan upper elimination */ 
	for(i = 0; i < matrix_size-1; i++){
		if(workspace[i][i] == 0){
			for(k = i; k < matrix_size; k++){
				if(workspace[k][i] != 0){
					for(j = 0; j < matrix_size; j++){
						/* Change lines inside original matrix */
						temp = workspace[i][j];
						workspace[i][j] = workspace[k][j];
						workspace[k][j] = temp;
						/* Change lines inside identity */
						temp = workspace[i][j+3];
						workspace[i][j+3] = workspace[k][j+3];
						workspace[k][j+3] = temp;
					}
				k = matrix_size;
				}
			}
		}
		if(workspace[i][i] != 0){
			for(k = i+1; k < matrix_size; k++){
				factor = -1.0 * (workspace[k][i]/workspace[i][i]);
				for(j = 0; j < matrix_size*2; j++){
					workspace[k][j] += (factor*workspace[i][j]);
				}
			}
		}
	}
	for(i = matrix_size-1; i >= 0; i--){
		if((workspace[i][i] == 0) && (workspace[i][matrix_size*2 - 1] == 0)){
			continue;	
		}else{
			for(k = matrix_size*2-1; k > i-1; k--)
				workspace[i][k] /= workspace[i][i];
			if(i != 0){
				for(up = i-1; up >= 0; up--){
					for(left = matrix_size*2-1 ; left >= i; left--){
						factor = -1.0 * (workspace[up][i]/workspace[i][i]);
						workspace[up][left] += factor*workspace[i][left];
					}
				}
			}
		}
	}
	for(i = 0; i < matrix_size; i++)
		for(j = matrix_size; j < matrix_size*2; j++)
			result[i][j-matrix_size] = workspace[i][j];
	
	result = transpose(result, matrix_size, matrix_size);
	return(result);
}