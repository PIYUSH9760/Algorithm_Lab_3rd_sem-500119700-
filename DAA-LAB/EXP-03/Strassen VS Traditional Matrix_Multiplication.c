#include<stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int** , int );
void fillMatrix(int** , int );
void strassenMatrixMultiplication(int** , int** , int** , int );
int** allocateMatrix(int );
void freeMatrix(int** , int );
void traditionalMatrixMultiplication(int** , int** , int** , int );
void addMatrix(int** , int** , int** , int );
void subtractMatrix(int** , int** , int** , int );

int main(){
    int n;
    clock_t end_time,start_time;
    double Traditional_time,Strassen_time;

    printf("Enter the size of the matrix (must be a power of 2): ");
    scanf("%d", &n);

    // Allocate matrices A, B, and C
    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    // Fill matrices A and B with random numbers
    fillMatrix(A, n);
    fillMatrix(B, n);

    start_time = clock();
    traditionalMatrixMultiplication(A, B, C, n);
    end_time = clock();
    Traditional_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print time taken by  traditional multiplication
    printf("Time taken by Traditional Multiplication: %f seconds\n", Traditional_time);

    // Strassen's matrix multiplication
    start_time = clock();
    strassenMatrixMultiplication(A, B, C, n);
    end_time = clock();
    Strassen_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print time taken by Strassen multiplication
    printf("Time taken by Strassen's Multiplication: %f seconds\n", Strassen_time);

    // Free allocated matrices
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}

// Function to allocate a matrix of size n x n
int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free the allocated matrix
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Traditional matrix multiplication
void traditionalMatrixMultiplication(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Add two matrices
void addMatrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Subtract two matrices
void subtractMatrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's matrix multiplication (recursive)
void strassenMatrixMultiplication(int** A, int** B, int** C, int n) {
    // Base case for recursion: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Divide matrices into 4 submatrices
    int newSize = n / 2;
    int** A11 = allocateMatrix(newSize);
    int** A12 = allocateMatrix(newSize);
    int** A21 = allocateMatrix(newSize);
    int** A22 = allocateMatrix(newSize);
    int** B11 = allocateMatrix(newSize);
    int** B12 = allocateMatrix(newSize);
    int** B21 = allocateMatrix(newSize);
    int** B22 = allocateMatrix(newSize);
    int** C11 = allocateMatrix(newSize);
    int** C12 = allocateMatrix(newSize);
    int** C21 = allocateMatrix(newSize);
    int** C22 = allocateMatrix(newSize);
    int** M1 = allocateMatrix(newSize);
    int** M2 = allocateMatrix(newSize);
    int** M3 = allocateMatrix(newSize);
    int** M4 = allocateMatrix(newSize);
    int** M5 = allocateMatrix(newSize);
    int** M6 = allocateMatrix(newSize);
    int** M7 = allocateMatrix(newSize);
    int** tempA = allocateMatrix(newSize);
    int** tempB = allocateMatrix(newSize);

    // Filling submatrices A11, A12, A21, A22, B11, B12, B21, B22
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculate M1 = (A11 + A22) * (B11 + B22)
    addMatrix(A11, A22, tempA, newSize);
    addMatrix(B11, B22, tempB, newSize);
    strassenMatrixMultiplication(tempA, tempB, M1, newSize);

    // Calculate M2 = (A21 + A22) * B11
    addMatrix(A21, A22, tempA, newSize);
    strassenMatrixMultiplication(tempA, B11, M2, newSize);

    // Calculate M3 = A11 * (B12 - B22)
    subtractMatrix(B12, B22, tempB, newSize);
    strassenMatrixMultiplication(A11, tempB, M3, newSize);

    // Calculate M4 = A22 * (B21 - B11)
    subtractMatrix(B21, B11, tempB, newSize);
    strassenMatrixMultiplication(A22, tempB, M4, newSize);

    // Calculate M5 = (A11 + A12) * B22
    addMatrix(A11, A12, tempA, newSize);
    strassenMatrixMultiplication(tempA, B22, M5, newSize);

    // Calculate M6 = (A21 - A11) * (B11 + B12)
    subtractMatrix(A21, A11, tempA, newSize);
    addMatrix(B11, B12, tempB, newSize);
    strassenMatrixMultiplication(tempA, tempB, M6, newSize);

    // Calculate M7 = (A12 - A22) * (B21 + B22)
    subtractMatrix(A12, A22, tempA, newSize);
    addMatrix(B21, B22, tempB, newSize);
    strassenMatrixMultiplication(tempA, tempB, M7, newSize);

    // Calculate C11 = M1 + M4 - M5 + M7
    addMatrix(M1, M4, tempA, newSize);
    subtractMatrix(tempA, M5, tempB, newSize);
    addMatrix(tempB, M7, C11, newSize);

    // Calculate C12 = M3 + M5
    addMatrix(M3, M5, C12, newSize);

    // Calculate C21 = M2 + M4
    addMatrix(M2, M4, C21, newSize);

    // Calculate C22 = M1 - M2 + M3 + M6
    subtractMatrix(M1, M2, tempA, newSize);
    addMatrix(tempA, M3, tempB, newSize);
    addMatrix(tempB, M6, C22, newSize);

    // Combine submatrices into final result matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free allocated memory
    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);
    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);
    freeMatrix(C11, newSize);
    freeMatrix(C12, newSize);
    freeMatrix(C21, newSize);
    freeMatrix(C22, newSize);
    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);
    freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);
    freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(tempA, newSize);
    freeMatrix(tempB, newSize);
}

// Function to fill a matrix with random integers
void fillMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}
