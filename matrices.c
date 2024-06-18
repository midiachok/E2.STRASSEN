#include "matrices.h"
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// inicializacia matice
void initialize_matrix(MAT* mat, int rows, int cols) {
    mat->rows = rows;
    mat->cols = cols;
    mat->size = rows * cols;
    mat->matrix = (int*)malloc(mat->size * sizeof(int));
}

// uvolnenie pamate alokovanej pre maticu
void release_matrix(MAT* mat) {
    free(mat->matrix);
}

// naplnenie matice hodnotami
void populate_matrix(MAT* mat) {
    int choice;

    do {
        printf("Vyberte sposob naplnenia matice: 1 - rucne, 2 - automaticky: ");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);

    populate_matrix_keyboard_automatically(mat, choice);
}

void populate_matrix_keyboard_automatically(MAT* mat, int choice) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            switch (choice) {
            case 1:
                printf("[%d][%d]: ", i + 1, j + 1);
                scanf("%d", &mat->matrix[i * mat->cols + j]);
                break;
            case 2:
                mat->matrix[i * mat->cols + j] = rand() % 200 - 100;
                break;
            }
        }
    }
}

// vypis obsahu matice
void print_matrix(MAT mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%d ", at(mat, i, j));
        }
        printf("\n");
    }
}

// scitanie a odcitanie matic
void add_subtract_matrix(MAT A, MAT B, MAT* C, int add) {
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            int result;
            if (add) {
                result = at(A, i, j) + at(B, i, j);
            }
            else {
                result = at(A, i, j) - at(B, i, j);
            }
            C->matrix[i * A.cols + j] = result;
        }
    }
}

// pristup k prvku matice pomocou dvoch indexov
int at(MAT mat, int row, int col) {
    // kontrola spravnosti indexov
    if (row < 0 || row >= mat.rows || col < 0 || col >= mat.cols) {
        printf("Index mimo rozsah\n");
        return 0; // bud ina predvolena hodnota alebo spracovanie chyby
    }
    // vypocet indexu v jednorozmernom poli
    return mat.matrix[row * mat.cols + col];
}

// nasobenie matic podla algoritmu strassena
void mat_multiply_strassen(MAT* A, MAT* B, MAT* C) {
    if (A->cols != B->rows || A->rows != B->cols || A->cols != C->cols || A->rows != C->rows) {
        printf("Nekompatibilne rozmery matic pre nasobenie\n");
        return;
    }

    int n = A->rows; // vel¾kost matice

    if (n == 1) {
        C->matrix[0] = at(*A, 0, 0) * at(*B, 0, 0);
        return;
    }

    // rozdelenie matic A a B na styri podmatice
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
            A11.matrix[i * newSize + j] = at(*A, i, j);
            A12.matrix[i * newSize + j] = at(*A, i, j + newSize);
            A21.matrix[i * newSize + j] = at(*A, i + newSize, j);
            A22.matrix[i * newSize + j] = at(*A, i + newSize, j + newSize);

            B11.matrix[i * newSize + j] = at(*B, i, j);
            B12.matrix[i * newSize + j] = at(*B, i, j + newSize);
            B21.matrix[i * newSize + j] = at(*B, i + newSize, j);
            B22.matrix[i * newSize + j] = at(*B, i + newSize, j + newSize);
        }
    }

    // vypocet submatic pre nasobenie podla algoritmu strassena
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

    add_subtract_matrix(B12, B22, &temp1, 0); // temp1 = B12 - B22
    mat_multiply_strassen(&A11, &temp1, &M1); // M1 = A11 * temp1

    add_subtract_matrix(A11, A12, &temp1, 1); // temp1 = A11 + A12
    mat_multiply_strassen(&temp1, &B22, &M2); // M2 = temp1 * B22

    add_subtract_matrix(A21, A11, &temp1, 0); // temp1 = A21 - A11
    add_subtract_matrix(B11, B12, &temp2, 1); // temp2 = B11 + B12
    mat_multiply_strassen(&temp1, &temp2, &M3); // M3 = temp1 * temp2

    add_subtract_matrix(A12, A22, &temp1, 0); // temp1 = A12 - A22
    add_subtract_matrix(B21, B11, &temp2, 1); // temp2 = B21 + B11
    mat_multiply_strassen(&temp1, &temp2, &M4); // M4 = temp1 * temp2

    add_subtract_matrix(A11, A22, &temp1, 1); // temp1 = A11 + A22
    add_subtract_matrix(B11, B22, &temp2, 1); // temp2 = B11 + B22
    mat_multiply_strassen(&temp1, &temp2, &M5); // M5 = temp1 * temp2

    add_subtract_matrix(A21, A22, &temp1, 1); // temp1 = A21 + A22
    mat_multiply_strassen(&temp1, &B11, &M6); // M6 = temp1 * B11

    add_subtract_matrix(B12, B22, &temp1, 0); // temp1 = B12 - B22
    mat_multiply_strassen(&A11, &temp1, &M7); // M7 = A11 * temp1

    // vypocet prvkov vyslednej matice C
    add_subtract_matrix(M5, M4, &temp1, 1); // temp1 = M5 + M4
    add_subtract_matrix(temp1, M2, &C11, 0); // C11 = temp1 - M2
    add_subtract_matrix(M1, M2, &C12, 1); // C12 = M1 + M2
    add_subtract_matrix(M3, M4, &C21, 1); // C21 = M3 + M4
    add_subtract_matrix(M1, M5, &temp1, 1); // temp1 = M1 + M5
    add_subtract_matrix(temp1, M3, &C22, 0); // C22 = temp1 - M3

    // spojenie vysledkov do matice C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C->matrix[i * C->cols + j] = C11.matrix[i * newSize + j];
            C->matrix[i * C->cols + j + newSize] = C12.matrix[i * newSize + j];
            C->matrix[(i + newSize) * C->cols + j] = C21.matrix[i * newSize + j];
            C->matrix[(i + newSize) * C->cols + j + newSize] = C22.matrix[i * newSize + j];
        }
    }

    // uvolnenie pamate alokovanej pre pomocne matice
    release_matrix(&A11); release_matrix(&A12); release_matrix(&A21); release_matrix(&A22);
    release_matrix(&B11); release_matrix(&B12); release_matrix(&B21); release_matrix(&B22);
    release_matrix(&C11); release_matrix(&C12); release_matrix(&C21); release_matrix(&C22);
    release_matrix(&M1); release_matrix(&M2); release_matrix(&M3); release_matrix(&M4);
    release_matrix(&M5); release_matrix(&M6); release_matrix(&M7);
    release_matrix(&temp1); release_matrix(&temp2);
}
