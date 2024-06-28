#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#pragma warning(disable:4996)

int initialize_matrix(MAT* mat, int rows, int cols) {
    mat->rows = rows;
    mat->cols = cols;
    mat->matrix = (int*)malloc(rows * cols * sizeof(int));
    if (mat->matrix == NULL) {
        return -1;  // memory allocation failure
    }
    return 0;  // success
}


void release_matrix(MAT* mat) {
    if (mat->matrix != NULL) {
        free(mat->matrix);
        mat->matrix = NULL;
    }
}

void create_identity_matrix(MAT* mat) {
    int size = mat->rows;  // assuming mat is already initialized with size x size
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            MAT_AT(*mat, i, j) = (i == j) ? 1 : 0;
        }
    }
}


void create_random_matrix(MAT* mat) {
    int rows = mat->rows;
    int cols = mat->cols;
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            MAT_AT(*mat, i, j) = (rand() % 201) - 100;  // random number between -100 and 100
        }
    }
}


MAT* load_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;  // file not found
    }
    MAT* mat = (MAT*)malloc(sizeof(MAT));
    if (mat == NULL) {
        fclose(file);
        return NULL;  // memory allocation failure
    }
    fscanf(file, "%d %d", &mat->rows, &mat->cols);
    if (initialize_matrix(mat, mat->rows, mat->cols) != 0) {
        fclose(file);
        free(mat);
        return NULL;  // failed to initialize matrix
    }
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fscanf(file, "%d", &MAT_AT(*mat, i, j));
        }
    }
    fclose(file);
    return mat;  // success
}



char save_matrix_to_file(MAT* mat, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return -1;  // failed to open file
    }
    fprintf(file, "%d %d\n", mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fprintf(file, "%d ", MAT_AT(*mat, i, j));
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;  // success
}


void print_matrix(const MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%d ", MAT_AT(*mat, i, j));
        }
        printf("\n");
    }
}

int add_matrices(const MAT* A, const MAT* B, MAT* C) {
    if (A->rows != B->rows || A->cols != B->cols) {
        return -1;
    }
    if (initialize_matrix(C, A->rows, A->cols) != 0) {
        return -1;
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            MAT_AT(*C, i, j) = MAT_AT(*A, i, j) + MAT_AT(*B, i, j);
        }
    }
    return 0;
}

int subtract_matrices(const MAT* A, const MAT* B, MAT* C) {
    if (A->rows != B->rows || A->cols != B->cols) {
        return -1;
    }
    if (initialize_matrix(C, A->rows, A->cols) != 0) {
        return -1;
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            MAT_AT(*C, i, j) = MAT_AT(*A, i, j) - MAT_AT(*B, i, j);
        }
    }
    return 0;
}

// function to create a matrix with specified dimensions
MAT* mat_create_with_type(unsigned int rows, unsigned int cols) {
    MAT* matrix = (MAT*)malloc(sizeof(MAT));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = (int*)malloc(rows * cols * sizeof(int));
    if (matrix->matrix == NULL) {
        printf("Memory allocation failed.\n");
        free(matrix);
        return NULL;
    }

    return matrix;
}



// multiply matrix A by matrix B using the Strassen algorithm
int multiply_matrices_strassen(const MAT* A, const MAT* B, MAT* C) {
    int n = A->rows;
    if (n != B->rows || n != B->cols || n != C->rows || n != C->cols) {
        return -1;
    }

    if (n == 1) {
        MAT_AT(*C, 0, 0) = MAT_AT(*A, 0, 0) * MAT_AT(*B, 0, 0);
        return 0;
    }

    int newSize = n / 2;
    MAT A11, A12, A21, A22;
    MAT B11, B12, B21, B22;
    MAT P1, P2, P3, P4, P5, P6, P7;
    MAT temp1, temp2;
    MAT C11, C12, C21, C22;

    initialize_matrix(&A11, newSize, newSize);
    initialize_matrix(&A12, newSize, newSize);
    initialize_matrix(&A21, newSize, newSize);
    initialize_matrix(&A22, newSize, newSize);
    initialize_matrix(&B11, newSize, newSize);
    initialize_matrix(&B12, newSize, newSize);
    initialize_matrix(&B21, newSize, newSize);
    initialize_matrix(&B22, newSize, newSize);

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

    initialize_matrix(&P1, newSize, newSize);
    initialize_matrix(&P2, newSize, newSize);
    initialize_matrix(&P3, newSize, newSize);
    initialize_matrix(&P4, newSize, newSize);
    initialize_matrix(&P5, newSize, newSize);
    initialize_matrix(&P6, newSize, newSize);
    initialize_matrix(&P7, newSize, newSize);
    initialize_matrix(&temp1, newSize, newSize);
    initialize_matrix(&temp2, newSize, newSize);

    // P1 = (A11 + A22) * (B11 + B22)
    add_matrices(&A11, &A22, &temp1);
    add_matrices(&B11, &B22, &temp2);
    multiply_matrices_strassen(&temp1, &temp2, &P1);

    // P2 = (A21 + A22) * B11
    add_matrices(&A21, &A22, &temp1);
    multiply_matrices_strassen(&temp1, &B11, &P2);

    // P3 = A11 * (B12 - B22)
    subtract_matrices(&B12, &B22, &temp1);
    multiply_matrices_strassen(&A11, &temp1, &P3);

    // P4 = A22 * (B21 - B11)
    subtract_matrices(&B21, &B11, &temp1);
    multiply_matrices_strassen(&A22, &temp1, &P4);

    // P5 = (A11 + A12) * B22
    add_matrices(&A11, &A12, &temp1);
    multiply_matrices_strassen(&temp1, &B22, &P5);

    // P6 = (A21 - A11) * (B11 + B12)
    subtract_matrices(&A21, &A11, &temp1);
    add_matrices(&B11, &B12, &temp2);
    multiply_matrices_strassen(&temp1, &temp2, &P6);

    // P7 = (A12 - A22) * (B21 + B22)
    subtract_matrices(&A12, &A22, &temp1);
    add_matrices(&B21, &B22, &temp2);
    multiply_matrices_strassen(&temp1, &temp2, &P7);

    initialize_matrix(&C11, newSize, newSize);
    initialize_matrix(&C12, newSize, newSize);
    initialize_matrix(&C21, newSize, newSize);
    initialize_matrix(&C22, newSize, newSize);

    // C11 = P1 + P4 - P5 + P7
    add_matrices(&P1, &P4, &temp1);
    subtract_matrices(&temp1, &P5, &temp2);
    add_matrices(&temp2, &P7, &C11);

    // C12 = P3 + P5
    add_matrices(&P3, &P5, &C12);

    // C21 = P2 + P4
    add_matrices(&P2, &P4, &C21);

    // C22 = P1 - P2 + P3 + P6
    subtract_matrices(&P1, &P2, &temp1);
    add_matrices(&temp1, &P3, &temp2);
    add_matrices(&temp2, &P6, &C22);

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
    release_matrix(&P1);
    release_matrix(&P2);
    release_matrix(&P3);    
    release_matrix(&P4);
    release_matrix(&P5);
    release_matrix(&P6);
    release_matrix(&P7);
    release_matrix(&temp1);
    release_matrix(&temp2);
    release_matrix(&C11);
    release_matrix(&C12);
    release_matrix(&C21);
    release_matrix(&C22);

    return 0;
}
