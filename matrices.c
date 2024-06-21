#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#pragma warning(disable:4996)

// initialize a matrix with given dimensions
int initialize_matrix(MAT* mat, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return -1; // invalid dimensions
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->size = rows * cols;
    mat->matrix = (int*)malloc(mat->size * sizeof(int));

    if (mat->matrix == NULL) {
        return -1; // memory allocation failed
    }

    return 0; // success
}

// release dynamically allocated memory for a matrix
void release_matrix(MAT* mat) {
    free(mat->matrix);
}

// create an identity matrix
int mat_unit(MAT* mat) {
    if (mat->rows != mat->cols) {
        return -1; // identity matrix must be square
    }

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            MAT_AT(*mat, i, j) = (i == j) ? 1 : 0;
        }
    }

    return 0; // success
}

// fill a matrix with random values
void mat_random(MAT* mat) {
    srand(time(NULL));
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            MAT_AT(*mat, i, j) = rand() % 200 - 100;
        }
    }
}

// create a matrix based on the specified type
int mat_create_with_type(MAT* mat, int rows, int cols, int type) {
    // initialize the matrix with the specified dimensions
    if (initialize_matrix(mat, rows, cols) != 0) {
        printf("Failed to initialize matrix.\n");
        return -1;
    }

    switch (type) {
    case 1: {
        // manually create matrix
        printf("Enter matrix elements row by row:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("Enter element at position (%d, %d): ", i, j);
                scanf("%lf", &MAT_AT(*mat, i, j));
            }
        }
        break;
    }
    case 2:
        // create matrix with random values
        mat_random(mat);
        break;
    case 3:
        // create identity matrix
        if (mat_unit(mat) != 0) {
            printf("Failed to create identity matrix.\n");
            return -1;
        }
        break;
    case 4: {
        // load matrix from file
        char filename[100];
        printf("Enter the filename to load the matrix from: ");
        scanf("%s", filename);

        if (mat_create_by_file(mat, filename) != 0) {
            printf("Failed to load matrix from file.\n");
            return -1;
        }

        // check if loaded matrix size matches required size
        int required_size = pow(2, rows);
        if (mat->rows != required_size || mat->cols != required_size) {
            release_matrix(mat);
            if (initialize_matrix(mat, required_size, required_size) != 0) {
                printf("Failed to initialize matrix to the required size.\n");
                return -1;
            }
            printf("Matrix size does not match required size (2^%d x 2^%d). Please choose again.\n", rows, rows);
            return mat_create_with_type(mat, rows, cols, type); // recursively try again
        }
        break;
    }
    default:
        printf("Invalid matrix type.\n");
        return -1;
    }

    return 0; // success
}

// create a matrix from a file
int mat_create_by_file(MAT* mat, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return -1; // return error code
    }

    if (fscanf(file, "%d%d", &mat->rows, &mat->cols) != 2) {
        fclose(file);
        return -1; // return error code
    }

    int result = initialize_matrix(mat, mat->rows, mat->cols);
    if (result != 0) {
        fclose(file);
        return result; // return initialization error
    }

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            if (fscanf(file, "%d", &MAT_AT(*mat, i, j)) != 1) {
                fclose(file);
                release_matrix(mat);
                return -1; // return error code
            }
        }
    }

    fclose(file);
    return 0; // success
}

// save a matrix to a file
int mat_save(MAT* mat, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return -1; // return error code
    }

    fprintf(file, "%d %d\n", mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fprintf(file, "%d ", MAT_AT(*mat, i, j));
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0; // success
}

// print the contents of a matrix
void print_matrix(MAT mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%d ", MAT_AT(mat, i, j));
        }
        printf("\n");
    }
}

// add or subtract two matrices and store the result in C
int add_subtract_matrix(const MAT A, const MAT B, MAT* C, int add) {
    if (A.rows != B.rows || A.cols != B.cols || A.rows != C->rows || A.cols != C->cols) {
        return -1; // return error code for incompatible matrix dimensions
    }

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            int result = add ? MAT_AT(A, i, j) + MAT_AT(B, i, j) : MAT_AT(A, i, j) - MAT_AT(B, i, j);
            MAT_AT(*C, i, j) = result;
        }
    }

    return 0; // success
}

// multiply matrix A by matrix B using the Strassen algorithm
int mat_multiply_strassen(const MAT* A, const MAT* B, MAT* C) {
    if (A->cols != B->rows || A->rows != C->rows || A->cols != C->cols) {
        return -1; // return error code for incompatible matrix dimensions
    }

    int n = A->rows; // size of the matrix

    if (n == 1) {
        MAT_AT(*C, 0, 0) = MAT_AT(*A, 0, 0) * MAT_AT(*B, 0, 0);
        return 0; // success
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

    MAT P1, P2, P3, P4, P5, P6, P7;
    initialize_matrix(&P1, newSize, newSize);
    initialize_matrix(&P2, newSize, newSize);
    initialize_matrix(&P3, newSize, newSize);
    initialize_matrix(&P4, newSize, newSize);
    initialize_matrix(&P5, newSize, newSize);
    initialize_matrix(&P6, newSize, newSize);
    initialize_matrix(&P7, newSize, newSize);

    MAT temp1, temp2;
    initialize_matrix(&temp1, newSize, newSize);
    initialize_matrix(&temp2, newSize, newSize);

    // P1 = (A11 + A22) * (B11 + B22)
    add_subtract_matrix(A11, A22, &temp1, 1);
    add_subtract_matrix(B11, B22, &temp2, 1);
    mat_multiply_strassen(&temp1, &temp2, &P1);

    // P2 = (A21 + A22) * B11
    add_subtract_matrix(A21, A22, &temp1, 1);
    mat_multiply_strassen(&temp1, &B11, &P2);

    // P3 = A11 * (B12 - B22)
    add_subtract_matrix(B12, B22, &temp1, 0);
    mat_multiply_strassen(&A11, &temp1, &P3);

    // P4 = A22 * (B21 - B11)
    add_subtract_matrix(B21, B11, &temp1, 0);
    mat_multiply_strassen(&A22, &temp1, &P4);

    // P5 = (A11 + A12) * B22
    add_subtract_matrix(A11, A12, &temp1, 1);
    mat_multiply_strassen(&temp1, &B22, &P5);

    // P6 = (A21 - A11) * (B11 + B12)
    add_subtract_matrix(A21, A11, &temp1, 0);
    add_subtract_matrix(B11, B12, &temp2, 1);
    mat_multiply_strassen(&temp1, &temp2, &P6);

    // P7 = (A12 - A22) * (B21 + B22)
    add_subtract_matrix(A12, A22, &temp1, 0);
    add_subtract_matrix(B21, B22, &temp2, 1);
    mat_multiply_strassen(&temp1, &temp2, &P7);

    // C11 = P1 + P4 - P5 + P7
    add_subtract_matrix(P1, P4, &temp1, 1);
    add_subtract_matrix(temp1, P5, &temp2, 0);
    add_subtract_matrix(temp2, P7, &C11, 1);

    // C12 = P3 + P5
    add_subtract_matrix(P3, P5, &C12, 1);

    // C21 = P2 + P4
    add_subtract_matrix(P2, P4, &C21, 1);

    // C22 = P1 - P2 + P3 + P6
    add_subtract_matrix(P1, P2, &temp1, 0);
    add_subtract_matrix(temp1, P3, &temp2, 1);
    add_subtract_matrix(temp2, P6, &C22, 1);

    // collect the result into matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            MAT_AT(*C, i, j) = MAT_AT(C11, i, j);
            MAT_AT(*C, i, j + newSize) = MAT_AT(C12, i, j);
            MAT_AT(*C, i + newSize, j) = MAT_AT(C21, i, j);
            MAT_AT(*C, i + newSize, j + newSize) = MAT_AT(C22, i, j);
        }
    }

    // free allocated memory
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
    release_matrix(&P1);
    release_matrix(&P2);
    release_matrix(&P3);
    release_matrix(&P4);
    release_matrix(&P5);
    release_matrix(&P6);
    release_matrix(&P7);
    release_matrix(&temp1);
    release_matrix(&temp2);

    return 0; // success
}
