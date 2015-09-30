/*
 * Matrix functions
 * Thiago Luis Baldissarelli - 2015
 *
 * Implementation of the matrixlib.c
 * Example 01 - Basic program
 *
 */

#include <stdio.h> /* stdInputOutput */
#include <stdlib.h> /* Memory Allocation */
#include "matrixlib.h" /* Matrix calculation lib */

typedef enum{false, true} bool; /* Define bool type */
 
bool run = true;

/* Basic part of program */
double **createNewMatrix(int rows, int columns){
	/* Allocate an new matrix on memory */
	int i, j;
	float item;
	double (**matrix) = seed(rows, columns);

	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			printf("Insert the item %dx%d: ", i+1, j+1);
			scanf("%f", &item);
			matrix[i][j] = item;
		}
	}
	return(matrix);
}

void print_matrix(int rows, int columns, double (**matrix)){
	/* Print matrix on program interface */
	int i, j;

	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++)
			printf("%lf ", matrix[i][j]);
		printf("\n");
	}
}

/* Interactive interface */
void determinant_interface(){
	/* Interface to calculate determinant */
	int size;

	printf("Insert how many line/columns your matrix have: ");
	scanf("%d", &size);
	
	bool check_matrix = verify(2, size, size, 0, 0);
	if(check_matrix = true){
		double (**matrix) = createNewMatrix(size, size);
		print_matrix(size, size, matrix);
		double det = determinant(matrix, size);
		printf("\nThe determinant is: %lf\n", det);
	}else{
		printf("There is an error with your input data.\nCheck them please.\n");
	}
}

void identity_interface(){
	/* Interface to create the identity matrix */
	int size;
	
	printf("Insert how many line/columns your matrix have: ");
	scanf("%d", &size);
	
	bool check_matrix = verify(2, size, size, 0, 0);
	if(check_matrix == true){
		double (**matrix) = identity_matrix(size);
		printf("\nThe identity matrix is:\n");
		print_matrix(size, size, matrix);
	}else{
		printf("There is an error with your input data.\nCheck them please.\n");
	}
}

void multiplication_interface(){
	/* Interface to calculate matrix multiplication */
	int matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns;

	printf("Matrix 1 number of rows have to be equal to matrix 2 number of columns.");
	printf("Insert how many lines matrix 1 have: ");
	scanf("%d", &matrix1_rows);
	printf("Insert how many columns matrix 1 have: ");
	scanf("%d", &matrix1_columns);
	printf("\nInsert how many lines matrix 2 have: ");
	scanf("%d", &matrix2_rows);
	printf("Insert how many columns matrix 2 have: ");
	scanf("%d", &matrix2_columns);
	
	bool check_matrix = verify(1, matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns);
	if(check_matrix == true){
		int i, j;
		float item;
		
		printf("\nThe result will be %dx%d\n", matrix1_rows, matrix2_columns);
		printf("MATRIX 1 (%dx%d)\n", matrix1_rows, matrix1_columns);
		double (**matrix1) = createNewMatrix(matrix1_rows, matrix1_columns);
		printf("\nMATRIX 2 (%dx%d)\n", matrix2_rows, matrix2_columns);
		double (**matrix2) = createNewMatrix(matrix2_rows, matrix2_columns);
		printf("The result matrix is:\n");
		double (**result) = matricial_multiplication(matrix1, matrix2, matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns);
		print_matrix(matrix1_rows, matrix2_columns, result);
	}else{
		printf("There is an error with your input data.\nCheck them please.\n");
	}
}

void sum_interface(int type){
	/*
	 * Interface to add or subtract matrices.
	 * - Type 0 --> Add
	 * - Type 1 --> Subtract
	 *
	 */
	int rows, columns;
	
	printf("Insert how many lines your matrix have: ");
	scanf("%d", &rows);
	printf("Inert how many columns your matrix have: ");
	scanf("%d", &columns);
	
	bool check_matrix = verify(0, rows, columns, 0, 0);
	if(check_matrix == true){
		int i, j;
		float item;

		printf("\nInsert item %dx%d of matrix 1\n", rows, columns);
		double (**matrix1) = createNewMatrix(rows, columns);
		printf("\nInsert item %dx%d of matrix 2\n", rows, columns);
		double (**matrix2) = createNewMatrix(rows, columns);
		printf("The result matrix is:\n");
		double (**result) = sum_matrices(matrix1, matrix2, rows, columns, type);
		print_matrix(rows, columns, result);
		
	}else{
		printf("There is an error with your input data.\nCheck them please.\n");
	}
}

void inverse_interface(){
	int size;

	printf("Insert how many line/columns your matrix have: ");
	scanf("%d", &size);
 
	bool check_matrix = verify(0, size, size, 0, 0);
	if(check_matrix == true){
		double (**matrix) = createNewMatrix(size, size);
		if(determinant(matrix, size) != 0.0){
			double (**result) = inverse_matrix(matrix, size);
			printf("The inverse matrix is:\n");
			print_matrix(size, size, result);
		}else{
			printf("Your matrix do not have an inverse\n");
		}
	}else{
		printf("There is an error with your input data.\nCheck them please.\n");
	}
}

void transpose_interface(){
	int rows, columns;
	
	printf("Insert how many lines your matrix have: ");
	scanf("%d", &rows);
	printf("Inert how many columns your matrix have: ");
	scanf("%d", &columns);
	
	bool check_matrix = verify(2, rows, columns, 0, 0);
	if(check_matrix == true){
		int i, j;
		float item;
		double (**matrix) = createNewMatrix(rows, columns);
		double (**result) = transpose(matrix, rows, columns);
		print_matrix(columns, rows, result);
	}else{
		printf("There is an error with your input data.\nCheck them please.\n");
	}
}

void scalar_multiplication_interface(){
	int rows, columns;
	float scalar;
	
	printf("Type the scalar number: ");
	scanf("%f", &scalar);
	printf("Insert how many lines your matrix have: ");
	scanf("%d", &rows);
	printf("Inert how many columns your matrix have: ");
	scanf("%d", &columns);
	
	bool check_matrix = verify(2, rows, columns, 0, 0);
	if(check_matrix == true){
		int i, j;
		float item;

		double (**matrix) = createNewMatrix(rows, columns);
		double (**result) = scalar_multiplication(matrix, rows, columns, scalar);
		print_matrix(rows, columns, result);
	}else{
		printf("There is an error with your input data.\nCheck them please.\n");
	}
}

void options(int option){
	/* Switch router */ 
	if(option <= 9){
		if(option == 1)
			determinant_interface();
		if(option == 2)
			identity_interface();
		if(option == 3)
			multiplication_interface();
		if(option == 4)
			sum_interface(0); /* Type 0 --> Add matrices */
		if(option == 5)
			sum_interface(1); /* Type 1 --> Add matrices */
		if(option == 6)
			inverse_interface();
		if(option == 7)
			transpose_interface();
		if(option == 8)
			scalar_multiplication_interface();
		if(option == 9){
			printf("¦¦¦+   ¦¦¦+ ¦¦¦¦¦+ ¦¦¦¦¦¦¦¦+¦¦¦¦¦¦+ ¦¦+¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+\n");
			printf("¦¦¦¦+ ¦¦¦¦¦¦¦+--¦¦++--¦¦+--+¦¦+--¦¦+¦¦¦+--¦¦¦++¦¦+----+¦¦+----+\n");
			printf("¦¦+¦¦¦¦+¦¦¦¦¦¦¦¦¦¦¦   ¦¦¦   ¦¦¦¦¦¦++¦¦¦  ¦¦¦++ ¦¦¦¦¦+  ¦¦¦¦¦¦¦+\n");
			printf("¦¦¦+¦¦++¦¦¦¦¦+--¦¦¦   ¦¦¦   ¦¦+--¦¦+¦¦¦ ¦¦¦++  ¦¦+--+  +----¦¦¦\n");
			printf("¦¦¦ +-+ ¦¦¦¦¦¦  ¦¦¦   ¦¦¦   ¦¦¦  ¦¦¦¦¦¦¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+¦¦¦¦¦¦¦¦\n");
			printf("+-+	 +-++-+  +-+   +-+   +-+  +-++-++------++------++------+\n");
			printf("\n");
			printf("Type the number of what you want:\n");
			printf("\n");
			printf("[1] - Determinant	||	[2] - Identity\n");
			printf("[3] - Multiply matrices	||	[4] - Add matrices\n");
			printf("[5] - Subtract matrices	||	[6] - Inverse matrix\n");
			printf("[7] - Transpose matrix		||	[8] - Scalar multiplication\n");
			printf("[9] - Reshow menu		||	[10] - Quit\n");
		}
	}else{
		printf("Invalid option\n");
	}
	printf("\n");
}

int main() {
	/* Start program */
	int option;

	options(9);
	while(run == true){
		printf("Option: ");
		scanf("%d", &option);
		if(option == 10){ 
			run = false; 
		else 
			options(option);
	}
}
