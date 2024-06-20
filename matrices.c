#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#pragma warning(disable:4996)

//initialize a matrix
void initialize_matrix(MAT* mat, int rows, int cols) {
    mat->rows = rows;
    mat->cols = cols;
    mat->size = rows * cols;
    mat->matrix = (int*)malloc(mat->size * sizeof(int));
}

//release the memory allocated for a matrix
void release_matrix(MAT* mat) {
    free(mat->matrix);
}


//print the content of a matrix
void print_matrix(MAT mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%d ", MAT_AT(mat, i, j));
        }
        printf("\n");
    }
}

//add or subtract matrices
void add_subtract_matrix(MAT A, MAT B, MAT* C, int add) {
    if (A.cols != B.rows || A.rows != C->rows || B.cols != C->cols) {
        printf("Incompatible matrix dimensions for multiplication\n");
        return;
    }

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            int result = add ? MAT_AT(A, i, j) + MAT_AT(B, i, j) : MAT_AT(A, i, j) - MAT_AT(B, i, j);
            MAT_AT(*C, i, j) = result;
        }
    }
}

//Strassen's matrix multiplication algorithm
void mat_multiply_strassen(MAT* A, MAT* B, MAT* C) {
    if (A->cols != B->rows || A->rows != C->rows || A->cols != C->cols) {
        printf("Incompatible matrix dimensions for multiplication\n");
        return;
    }

    int n = A->rows; //size of the matrix

    if (n == 1) {
        MAT_AT(*C, 0, 0) = MAT_AT(*A, 0, 0) * MAT_AT(*B, 0, 0);
        return;
    }

    int newSize = n / 2;
    MAT A11, A12, A21, A22, B11, B12, B21, B22, C11, C12, C21, C22;
    initialize_matrix(&A11, newSize, newSize);
    initialize_matrix(&A12, newSize, newSize);
    initialize_matrix(&A21, newSize, newSize);
    initialize_matrix(&A22, newSize, newSize);
    initialize_matrix(&B11, newSize, newSize);
    initialize_matrix(&B12, newSize, newSize);
    initialize_matrix(&B21, newSize, newSize);
    initialize_matrix(&B22, newSize, newSize);
    initialize_matrix(&C11, newSize, newSize);
    initialize_matrix(&C12, newSize, newSize);
    initialize_matrix(&C21, newSize, newSize);
    initialize_matrix(&C22, newSize, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            MAT_AT(A11, i, j) = MAT_AT(*A, i, j);
            MAT_AT(A12, i, j) = MAT_AT(*A, i, j + newSize);
            MAT_AT(A21, i, j) = MAT_AT(*A, i + newSize, j);
            MAT_AT(A22, i, j) = MAT_AT(*A, i + newSize, j + newSize);

            MAT_AT(B11, i, j) = MAT_AT(*B, i, j);
            MAT_AT(B12, i, j) = MAT_AT(*B, i, j + newSize);
            MAT_AT(B21, i, j) = MAT_AT(*B, i + newSize, j);
            MAT_AT(B22, i, j) = MAT_AT(*B, i + newSize, j + newSize);
        }
    }

    MAT M1, M2, M3, M4, M5, M6, M7;
    initialize_matrix(&M1, newSize, newSize);
    initialize_matrix(&M2, newSize, newSize);
    initialize_matrix(&M3, newSize, newSize);
    initialize_matrix(&M4, newSize, newSize);
    initialize_matrix(&M5, newSize, newSize);
    initialize_matrix(&M6, newSize, newSize);
    initialize_matrix(&M7, newSize, newSize);

    MAT temp1, temp2;
    initialize_matrix(&temp1, newSize, newSize);
    initialize_matrix(&temp2, newSize, newSize);

    add_subtract_matrix(B12, B22, &temp1, 0);
    mat_multiply_strassen(&A11, &temp1, &M1);

    add_subtract_matrix(A11, A12, &temp1, 1);
    mat_multiply_strassen(&temp1, &B22, &M2);

    add_subtract_matrix(A21, A11, &temp1, 0);
    add_subtract_matrix(B11, B12, &temp2, 1);
    mat_multiply_strassen(&temp1, &temp2, &M3);

    add_subtract_matrix(A12, A22, &temp1, 0);
    add_subtract_matrix(B21, B11, &temp2, 1);
    mat_multiply_strassen(&temp1, &temp2, &M4);

    add_subtract_matrix(A11, A22, &temp1, 1);
    add_subtract_matrix(B11, B22, &temp2, 1);
    mat_multiply_strassen(&temp1, &temp2, &M5);

    add_subtract_matrix(A21, A22, &temp1, 1);
    mat_multiply_strassen(&temp1, &B11, &M6);

    add_subtract_matrix(B12, B22, &temp1, 0);
    mat_multiply_strassen(&A11, &temp1, &M7);

    add_subtract_matrix(M5, M4, &temp1, 1);
    add_subtract_matrix(temp1, M2, &C11, 0);
    add_subtract_matrix(M1, M2, &C12, 1);
    add_subtract_matrix(M3, M4, &C21, 1);
    add_subtract_matrix(M5, M1, &temp1, 1);
    add_subtract_matrix(temp1, M3, &temp2, 0);
    add_subtract_matrix(temp2, M7, &C22, 0);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            MAT_AT(*C, i, j) = MAT_AT(C11, i, j);
            MAT_AT(*C, i, j + newSize) = MAT_AT(C12, i, j);
            MAT_AT(*C, i + newSize, j) = MAT_AT(C21, i, j);
            MAT_AT(*C, i + newSize, j + newSize) = MAT_AT(C22, i, j);
        }
    }

    release_matrix(&A11);
    release_matrix(&A12);
    release_matrix(&A21);
    release_matrix(&A22);
    release_matrix(&B11);
    release_matrix(&B12);
    release_matrix(&B21);
    release_matrix(&B22);
    release_matrix(&C11);
    release_matrix(&C12);
    release_matrix(&C21);
    release_matrix(&C22);
    release_matrix(&M1);
    release_matrix(&M2);
    release_matrix(&M3);
    release_matrix(&M4);
    release_matrix(&M5);
    release_matrix(&M6);
    release_matrix(&M7);
    release_matrix(&temp1);
    release_matrix(&temp2);
}

//create a matrix with a specific type
void mat_create_with_type(MAT* mat, int rows, int cols, int type) {
    initialize_matrix(mat, rows, cols);
    switch (type) {
    case 1:
        mat_create_with_type(mat, rows, cols, type);
        break;
    case 2:
        mat_unit(mat);
        break;  
    case 3:
        mat_random(mat);
        break;
    default:
        printf("Invalid type\n");
        break;
    }
}

//create a matrix by reading from a file
void mat_create_by_file(MAT* mat, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    fscanf(file, "%d%d", &mat->rows, &mat->cols);
    initialize_matrix(mat, mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fscanf(file, "%d", &MAT_AT(*mat, i, j));
        }
    }

    fclose(file);
}

//save a matrix to a file
void mat_save(MAT* mat, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "%d %d\n", mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fprintf(file, "%d ", MAT_AT(*mat, i, j));
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

//create an identity matrix
void mat_unit(MAT* mat) {
    if (mat->rows != mat->cols) {
        printf("Identity matrix must be square\n");
        return;
    }

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            MAT_AT(*mat, i, j) = (i == j) ? 1 : 0;
        }
    }
}

//populate a matrix with random values
void mat_random(MAT* mat) {
    srand(time(NULL));
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            MAT_AT(*mat, i, j) = rand() % 200 - 100;
        }
    }
}

