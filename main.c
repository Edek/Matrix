#include <stdio.h> /* Precisamos dessa lib por causa da entrada e saída de dados (stdInputOutput) */
#include <stdlib.h> /* Precisamos dessa lib por causa da função malloc (Memory Allocation), permitindo alocação dinâmica de memória */
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
/  Aqui está a parte que o usuário interage com o programa, inserido os
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
		printf("O determinante é %0.03lf\n", det);
	}else{
		printf("Verificação da matriz falhou.\nCheque os dados que você digitou.\n");
	}
}

void identity_interface(){
	int size;
	
	printf("Insira a quantidade de linhas/colunas que a matriz possui: ");
	scanf("%d", &size);
	
	bool check_matrix = verify(2, size, size, 0, 0);
	if(check_matrix == true){
		double (**matrix) = identity_matrix(size);
		printf("\nA matriz inversa é:\n");
		print_matrix(size, size, matrix);
	}else{
		printf("Verificação da matriz falhou.\nCheque os dados que você digitou.\n");
	}
}

void multiplication_interface(){
	int matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns;

	printf("Número de colunas da matriz 1 deve ser igual a quantidade de linhas da matriz 2.");
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
		
		printf("\nAtenção! A matriz resposta terá tamanho %dx%d\n", matrix1_rows, matrix2_columns);
		printf("MATRIZ 1 (%dx%d)\n", matrix1_rows, matrix1_columns);
		double (**matrix1) = createNewMatrix(matrix1_rows, matrix1_columns);
		printf("\nMATRIZ 2 (%dx%d)\n", matrix2_rows, matrix2_columns);
		double (**matrix2) = createNewMatrix(matrix2_rows, matrix2_columns);
		printf("A matriz resultado é:\n");
		double (**result) = matricial_multiplication(matrix1, matrix2, matrix1_rows, matrix1_columns, matrix2_rows, matrix2_columns);
		print_matrix(matrix1_rows, matrix2_columns, result);
	}else{
		printf("Verificação da matriz falhou.\nCheque os dados que você digitou.\n");
	}
}

void sum_interface(int type){
	/* Se o tipo for 0 será soma
	 * Se o tipo for 1 será subtração
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

		printf("\nInsira os itens da matriz %dx%d número 1\n", rows, columns);
		double (**matrix1) = createNewMatrix(rows, columns);
		printf("\nInsira os itens da matriz %dx%d número 2\n", rows, columns);
		double (**matrix2) = createNewMatrix(rows, columns);
		printf("A matriz resultado é:\n");
		double (**result) = sum_matrices(matrix1, matrix2, rows, columns, type);
		print_matrix(rows, columns, result);
		
	}else{
		printf("Verificação da matriz falhou.\nCheque os dados que você digitou.\n");
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
			printf("A matriz inversa é:\n");
			print_matrix(size, size, result);
		}else{
			printf("Este sistema não possui resolução\n");
		}
	}else{
		printf("Verificação da matriz falhou.\nCheque os dados que você digitou.");
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
		printf("Verificação da matriz falhou.\nCheque os dados que você digitou.");
	}
}

void scalar_multiplication_interface(){
	int rows, columns;
	float scalar;
	
	printf("Insira o número da multiplicação (pertencente aos reais): ");
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
		printf("Verificação da matriz falhou.\nCheque os dados que você digitou.");
	}
}

/* 
/  Aqui fica a guia do programa.
/  Pense como um tunel que direciona o programa para a função desejada.
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
			sum_interface(1); // Tipo 1 = Inverte o operador para virar subtração
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
			printf("Precisão travada em 3 casas decimais\n");
			printf("Digite a opção que você deseja:\n");
			printf("\n");
			printf("[1] - Determinante de matriz	||	[2] - Matriz identidade\n");
			printf("[3] - Multiplicação de matrizes	||	[4] - Soma de matrizes\n");
			printf("[5] - Subtração de matrizes	||	[6] - Matriz inversa\n");
			printf("[7] - Matriz transposta		||	[8] - Multiplicação por número\n");
			printf("[9] - Reexibir menu		||	[10] - Sair do programa\n");
		}
	}else{
		printf("Opção inválida\n");
	}
	printf("\n");
}

/* 
/  Parte inicial do programa.
/  Aqui roda o seletor de opção, define o local do programa para português
*/
int main() {
	int option;
	setlocale(LC_CTYPE,"");
	
	while(run == true){
		options(9);
		printf("Opção: ");
		scanf("%d", &option);
		if(option == 10){ 
			run = false; 
		}else{ 
			options(option);
			printf("\n");
		}
	}
}
