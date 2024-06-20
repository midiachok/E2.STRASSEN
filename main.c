#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#pragma warning(disable:4996)

void display_menu() {
    printf("\nMatrix Operations Menu:\n1. Add matrices\n2. Subtract matrices\n3. Multiply matrices using Strassen's algorithm\n0. Exit\n");
}

void print_matrix_info(MAT matrix) {
    printf("Matrix %dx%d:\n", matrix.rows, matrix.cols);
    print_matrix(matrix);
}

void choose_matrix_creation_method(MAT* matrix, int n) {
    int type;
    printf("Choose how to populate the matrix:\n1. Manually\n2. Random values\n3. Identity matrix\n4. Load from file\nEnter your choice: ");
    scanf("%d", &type);

    switch (type) {
    case 1:
        printf("Creating matrix manually:\n");
        mat_unit(matrix);
        break;
    case 2:
        printf("Creating matrix with random values:\n");
        mat_random(matrix);
        break;
    case 3:
        printf("Creating identity matrix:\n");
        mat_unit(matrix);
        break;
    case 4: {
        char filename[100];
        printf("Enter the filename to load the matrix from: ");
        scanf("%s", filename);
        mat_create_by_file(matrix, filename);


        int required_size = pow(2, n);
        if (matrix->rows != required_size || matrix->cols != required_size) {
            release_matrix(matrix);
            initialize_matrix(matrix, pow(2, n), pow(2, n));
            printf("Matrix size does not match required size (2^%d x 2^%d). Please choose again.\n", n, n);
            choose_matrix_creation_method(matrix, n);
        }
        break;
    }
    default:
        printf("Invalid matrix type.\n");
        break;
    }

    printf("Matrix created:\n");
    print_matrix_info(*matrix);
}



void save_matrix_with_prompt(MAT* matrix) {
    char save_choice;
    printf("Do you want to save matrix C? (y/n): ");
    scanf(" %c", &save_choice);
    if (!(save_choice == 'y' || save_choice == 'Y')) {
        return;
    }

    char filename[100];
    printf("Enter filename to save the matrix: ");
    scanf("%s", filename);
    mat_save(matrix, filename);
    printf("Matrix saved to %s successfully.\n", filename);
}

int main() {
    MAT A, B, C;
    int choice, n;

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter n for matrix size (matrix will be 2^n x 2^n): ");
            scanf("%d", &n);

            initialize_matrix(&A, pow(2, n), pow(2, n));
            initialize_matrix(&B, pow(2, n), pow(2, n));
            initialize_matrix(&C, pow(2, n), pow(2, n));

            printf("Matrix A:\n");
            choose_matrix_creation_method(&A, n);
            save_matrix_with_prompt(&A);

            printf("Matrix B:\n");
            choose_matrix_creation_method(&B, n);
            save_matrix_with_prompt(&B);

            add_subtract_matrix(A, B, &C, 1);

            printf("Result of addition:\n");
            print_matrix_info(C);
            save_matrix_with_prompt(&C);

            release_matrix(&A);
            release_matrix(&B);
            release_matrix(&C);
            break;

        case 2:
            printf("Enter n for matrix size (matrix will be 2^n x 2^n): ");
            scanf("%d", &n);

            initialize_matrix(&A, pow(2, n), pow(2, n));
            initialize_matrix(&B, pow(2, n), pow(2, n));
            initialize_matrix(&C, pow(2, n), pow(2, n));

            printf("Matrix A:\n");
            choose_matrix_creation_method(&A, n);
            save_matrix_with_prompt(&A);

            printf("Matrix B:\n");
            choose_matrix_creation_method(&B, n);
            save_matrix_with_prompt(&B);

            add_subtract_matrix(A, B, &C, 0);

            printf("Result of subtraction:\n");
            print_matrix_info(C);
            save_matrix_with_prompt(&C);


            release_matrix(&A);
            release_matrix(&B);
            release_matrix(&C);
            break;

        case 3:
            printf("Enter n for matrix size (matrix will be 2^n x 2^n): ");
            scanf("%d", &n);

            initialize_matrix(&A, pow(2, n), pow(2, n));
            initialize_matrix(&B, pow(2, n), pow(2, n));
            initialize_matrix(&C, pow(2, n), pow(2, n));

            printf("Matrix A:\n");
            choose_matrix_creation_method(&A, n);
            save_matrix_with_prompt(&A);

            printf("Matrix B:\n");
            choose_matrix_creation_method(&B, n);
            save_matrix_with_prompt(&B);


            mat_multiply_strassen(&A, &B, &C);

            printf("Result of multiplication using Strassen's algorithm:\n");
            print_matrix_info(C);
            save_matrix_with_prompt(&C);


            release_matrix(&A);
            release_matrix(&B);
            release_matrix(&C);
            break;

        case 4:
            choose_matrix_creation_method(&A, 0);
            printf("Matrix loaded:\n");
            print_matrix_info(A);
            release_matrix(&A);
            break;

        case 0:
            printf("Exiting...\n");
            exit(0);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}
