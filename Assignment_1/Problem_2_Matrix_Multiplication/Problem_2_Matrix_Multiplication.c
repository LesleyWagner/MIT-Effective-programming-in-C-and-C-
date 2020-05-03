// Problem_2_Matrix_Multiplication.cpp : Source file for your target.
//

#include <stdio.h>

#define MAXN 300

typedef struct Matrix_s {
	size_t R, C;
	int index[MAXN][MAXN];
} Matrix;

// read matrices A and B from input file
void readMatrices(Matrix* A, Matrix* B, const char const* fileName) {
	FILE* inputFile = fopen(fileName, "r");

	fscanf(inputFile, "%u %u", &(A->R), &(A->C)); // get column and row count for matrix A (1 <= (R, C) <= 300)

	for (size_t r = 0; r < A->R; r++) {
		for (size_t c = 0; c < A->C; c++) {
			fscanf(inputFile, "%d", &(A->index[r][c])); // get entry[i][j] in matrix A (entry[i][j] < 1000)
		}
	}

	fscanf(inputFile, "%u %u", &(B->R), &(B->C)); // get column and row count for matrix B (1 <= (R, C) <= 300)

	for (size_t r = 0; r < B->R; r++) {
		for (size_t c = 0; c < B->C; c++) {
			fscanf(inputFile, "%d", &(B->index[r][c])); // get entry[i][j] in matrix B (entry[i][j] < 1000)
		}
	}

	fclose(inputFile);
}

// compute matrix product C of matrices A and B
// Preconditions: Matrices A and B must be initialised with 1 <= RA, RB, CA, CB <= 300 and 
//				  absolute value of all entries in the matrix < 1000,
//		          Matrix C must be initialised
// Postconditions: if CA = RB then C = AB
//                 else RC, CC = 0					
// Matrix C: matrix product C = AB
Matrix multiply(const Matrix const* A, const Matrix const* B, Matrix* C) {
	if (A->C == B->R) {
		(size_t)C->R = A->R;
		(size_t)C->C = B->C;
		for (size_t rc = 0; rc < C->R; rc++) {
			for (size_t cc = 0; cc < C->C; cc++) {
				// C[rc][cc] is dot product of row rc of matrix A by column cc of matrix B
				int entry_C = 0;
				for (size_t k = 0; k < A->C; k++) {
					entry_C += (A->index[rc][k] * B->index[k][cc]);
				}
				(int)C->index[rc][cc] = entry_C;
			}
		}
	}
}

// write matrix C to output file
void writeMatrix(const Matrix const* C, const char* fileName) {
	FILE* outputFile = fopen(fileName, "w");

	fprintf(outputFile, "%d %d\n", C->R, C->C);
	for (size_t r = 0; r < C->R; r++) {
		for (size_t c = 0; c < C->C; c++) {
			fprintf(outputFile, "%d ", C->index[r][c]);
		}
		fprintf(outputFile, "\n");
	}

	fclose(outputFile);
}

// Write matrix product of two matrices to an output file. 
int main() {
	const char* inputFile = "matrix.data/matrix.2.in";
	const char* outputFile = "matrix.out";
	Matrix A;
	Matrix B;
	Matrix C;
	A.R = 0;
	A.C = 0;
	B.R = 0;
	B.C = 0;
	C.R = 0;
	C.C = 0;

	readMatrices(&A, &B, inputFile);
	multiply(&A, &B, &C);
	writeMatrix(&C, outputFile);

	/*printf("Matrix A:\n");
	for (size_t r = 0; r < A.R; r++) {
		for (size_t c = 0; c < A.C; c++) {
			printf("%d ", A.index[r][c]);
		}
		printf("\n");
	}

	printf("Matrix B:\n");
	for (size_t r = 0; r < B.R; r++) {
		for (size_t c = 0; c < B.C; c++) {
			printf("%d ", B.index[r][c]);
		}
		printf("\n");
	}*/

	return 0;
}