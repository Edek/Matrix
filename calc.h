#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED
double determinant(double **matrix, int size);
double **seed(int rows, int columns);
double **identity_matrix(int size);
double **transpose(double **matrix, int rows, int columns);
double **scalar_multiplication(double **matrix, int rows, int columns, long number);
double **sum_matrices(double **matrix1, double **matrix2, int rows, int columns, int type);
double **matricial_multiplication(double **matrix1, double **matrix2, int matrix1_rows, int matrix1_columns, int matrix2_rows, int matrix2_columns);
double **inverse_matrix(double **matrix, int size);
#endif

