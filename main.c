#include <stdio.h> /* Precisamos dessa lib por causa da entrada e sa�da de dados (stdInputOutput) */
#include <stdlib.h> /* Precisamos dessa lib por causa da fun��o malloc (Memory Allocation), permitindo aloca��o din�mica de mem�ria */
#include <locale.h>
#include "calc.h"

typedef enum{false, true} bool; /* Definindo o tipo bool */

bool run = true;

double **createNewMatrix(int rows, int columns){
	int i, j;
	float item;
	double (**matrix) = seed(rows, columns);

	printf("\nAllocation: %p\n", matrix);

	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			printf("Insira o item %dx%d da matriz: ", i+1, j+1);
			scanf("%f", &item);
			matrix[i][j] = item;
		}
	}
	return(matrix);
}

/* Print matrix on program interface */
void print_matrix(int rows, int columns, double (**matrix)){
	int i, j;
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
}

/*
/  Interactive part of program
/  Aqui est� a parte que o usu�rio interage com o programa, inserido os
/  dados requisitados.
*/
void determinant_interface(){
	int size;

	printf("Insira a quantidade de linhas/colunas que a matriz possui: ");
	scanf("%d", &size);
	
	bool check_matrix = verify(2, size, size, 0, 0);
	if(check_matrix = true){
		double (**matrix) = createNewMatrix(size, size);
		print_matrix(size, size, matrix);
		double det = determinant(matrix, size);
		printf("O determinante � %0.03lf\n", det);
	}else{
		printf("Verifica��o da matriz falhou.\nCheque os dados que voc� digitou.\n");
	}
}

void identity_interface(){
	int size;
	
	printf("Insira a quantidade de linhas/colunas que a matriz possui: ");
	scanf("%d", &size);
	
	bool check_matrix = verify(2, size, size, 0, 0);
	if(check_matrix == true){
		double (**matrix) = identity_matrix(size);
		printf("\nA matriz inversa �:\n");
		print_matrix(size, size, matrix);
	}else{
		printf("Verifica��o da matriz falhou.\nCheque os dados que voc� digitou.\n");
	}
}

void multiplication_interface(){
	int matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns;

	printf("N�mero de colunas da matriz 1 deve ser igual a quantidade de linhas da matriz 2.");
	printf("Insira a quantidade de linhas que a matriz 1 possui: ");
	scanf("%d", &matrix1_rows);
	printf("Insira a quantidade de colunas que a matriz 1 possui: ");
	scanf("%d", &matrix1_columns);
	printf("\nInsira a quantidade de linhas que a matriz 2 possui: ");
	scanf("%d", &matrix2_rows);
	printf("Insira a quantidade de colunas que a matriz 2 possui: ");
	scanf("%d", &matrix2_columns);
	
	bool check_matrix = verify(1, matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns);
	if(check_matrix == true){
		int i, j;
		float item;
		
		printf("\nAten��o! A matriz resposta ter� tamanho %dx%d\n", matrix1_rows, matrix2_columns);
		printf("MATRIZ 1 (%dx%d)\n", matrix1_rows, matrix1_columns);
		double (**matrix1) = createNewMatrix(matrix1_rows, matrix1_columns);
		printf("\nMATRIZ 2 (%dx%d)\n", matrix2_rows, matrix2_columns);
		double (**matrix2) = createNewMatrix(matrix2_rows, matrix2_columns);
		printf("A matriz resultado �:\n");
		double (**result) = matricial_multiplication(matrix1, matrix2, matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns);
		print_matrix(matrix1_rows, matrix2_columns, result);
	}else{
		printf("Verifica��o da matriz falhou.\nCheque os dados que voc� digitou.\n");
	}
}

void sum_interface(int type){
	/* Se o tipo for 0 ser� soma
	 * Se o tipo for 1 ser� subtra��o
	 */
	int rows, columns;
	
	printf("Insira a quantidade de linhas que as matrizes possuem: ");
	scanf("%d", &rows);
	printf("Insira a quantidade de colunas que as matrizes possuem: ");
	scanf("%d", &columns);
	
	bool check_matrix = verify(0, rows, columns, 0, 0);
	if(check_matrix == true){
		int i, j;
		float item;

		printf("\nInsira os itens da matriz %dx%d n�mero 1\n", rows, columns);
		double (**matrix1) = createNewMatrix(rows, columns);
		printf("\nInsira os itens da matriz %dx%d n�mero 2\n", rows, columns);
		double (**matrix2) = createNewMatrix(rows, columns);
		printf("A matriz resultado �:\n");
		double (**result) = sum_matrices(matrix1, matrix2, rows, columns, type);
		print_matrix(rows, columns, result);
		
	}else{
		printf("Verifica��o da matriz falhou.\nCheque os dados que voc� digitou.\n");
	}
}

void inverse_interface(){
	int size;

	printf("Insira a quantidade de linhas/colunas que a matriz possui: ");
	scanf("%d", &size);
 
	bool check_matrix = verify(0, size, size, 0, 0);
	if(check_matrix == true){
		double (**matrix) = createNewMatrix(size, size);
		if(determinant(matrix, size) != 0.0){
			double (**result) = inverse_matrix(matrix, size);
			printf("A matriz inversa �:\n");
			print_matrix(size, size, result);
		}else{
			printf("Este sistema n�o possui resolu��o\n");
		}
	}else{
		printf("Verifica��o da matriz falhou.\nCheque os dados que voc� digitou.");
	}
}

void transpose_interface(){
	int rows, columns;
	
	printf("Insira a quantidade de linhas que a matriz possui: ");
	scanf("%d", &rows);
	printf("Insira a quantidade de colunas que a matriz possui: ");
	scanf("%d", &columns);
	
	bool check_matrix = verify(2, rows, columns, 0, 0);
	if(check_matrix == true){
		int i, j;
		float item;
		double (**matrix) = createNewMatrix(rows, columns);
		double (**result) = transpose(matrix, rows, columns);
		print_matrix(columns, rows, result);
	}else{
		printf("Verifica��o da matriz falhou.\nCheque os dados que voc� digitou.");
	}
}

void scalar_multiplication_interface(){
	int rows, columns;
	float scalar;
	
	printf("Insira o n�mero da multiplica��o (pertencente aos reais): ");
	scanf("%f", &scalar);
	printf("Insira a quantidade de linhas que a matriz possui: ");
	scanf("%d", &rows);
	printf("Insira a quantidade de colunas que a matriz possui: ");
	scanf("%d", &columns);
	
	bool check_matrix = verify(2, rows, columns, 0, 0);
	if(check_matrix == true){
		int i, j;
		float item;

		double (**matrix) = createNewMatrix(rows, columns);
		double (**result) = scalar_multiplication(matrix, rows, columns, scalar);
		print_matrix(rows, columns, result);
	}else{
		printf("Verifica��o da matriz falhou.\nCheque os dados que voc� digitou.");
	}
}

/* 
/  Aqui fica a guia do programa.
/  Pense como um tunel que direciona o programa para a fun��o desejada.
*/ 
void options(int option){
	if(option <= 9){
		if(option == 1)
			determinant_interface();
		if(option == 2)
			identity_interface();
		if(option == 3)
			multiplication_interface();
		if(option == 4)
			sum_interface(0); // Tipo 0 = Soma
		if(option == 5)
			sum_interface(1); // Tipo 1 = Inverte o operador para virar subtra��o
		if(option == 6)
			inverse_interface();
		if(option == 7)
			transpose_interface();
		if(option == 8)
			scalar_multiplication_interface();
		if(option == 9){
			printf("���+   ���+ �����+ ��������+������+ ��+�������+�������+�������+\n");
			printf("����+ �������+--��++--��+--+��+--��+���+--���++��+----+��+----+\n");
			printf("��+����+�����������   ���   ������++���  ���++ �����+  �������+\n");
			printf("���+��++�����+--���   ���   ��+--��+��� ���++  ��+--+  +----���\n");
			printf("��� +-+ ������  ���   ���   ���  �������������+�������+��������\n");
			printf("+-+	 +-++-+  +-+   +-+   +-+  +-++-++------++------++------+\n");
			printf("\n");
			printf("Precis�o travada em 3 casas decimais\n");
			printf("Digite a op��o que voc� deseja:\n");
			printf("\n");
			printf("[1] - Determinante de matriz	||	[2] - Matriz identidade\n");
			printf("[3] - Multiplica��o de matrizes	||	[4] - Soma de matrizes\n");
			printf("[5] - Subtra��o de matrizes	||	[6] - Matriz inversa\n");
			printf("[7] - Matriz transposta		||	[8] - Multiplica��o por n�mero\n");
			printf("[9] - Reexibir menu		||	[10] - Sair do programa\n");
		}
	}else{
		printf("Op��o inv�lida\n");
	}
	printf("\n");
}

/* 
/  Parte inicial do programa.
/  Aqui roda o seletor de op��o, define o local do programa para portugu�s
*/
int main() {
	int option;
	setlocale(LC_CTYPE,"");
	
	while(run == true){
		options(9);
		printf("Op��o: ");
		scanf("%d", &option);
		if(option == 10){ 
			run = false; 
		}else{ 
			options(option);
			printf("\n");
		}
	}
}
