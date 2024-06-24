#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

void display_menu() {
    printf("\nMatrix Operations Menu:\n1. Add matrices\n2. Subtract matrices\n3. Multiply matrices using Strassen's algorithm\n0. Exit\n");
}

void print_matrix_info(const MAT* matrix) {
    printf("Matrix %dx%d:\n", matrix->rows, matrix->cols);
    print_matrix(matrix);
}

void choose_matrix_creation_method(MAT* matrix, int n) {
    int type;
    int size = pow(2, n);
    char check_print = 1;

    printf("Choose how to populate the matrix:\n1. Manually\n2. Random values\n3. Identity matrix\n4. Load from file\nEnter your choice: ");
    scanf("%d", &type);

    switch (type) {
    case 1:
        if (mat_create_with_type(matrix, size, size, 1) != 0) {
            printf("Failed to create matrix\n");
            check_print = 0;
            choose_matrix_creation_method(matrix,n);
        }
        break;
    case 2:
        if (create_random_matrix(matrix, size, size) != 0) {
            printf("Failed to create matrix with random values\n");
            check_print = 0;
            choose_matrix_creation_method(matrix,n);
        }
        break;
    case 3:
        if (create_identity_matrix(matrix, size) != 0) {
            printf("Failed to create identity matrix\n");
            check_print = 0;
            choose_matrix_creation_method(matrix,n);
        }
        break;
    case 4: {
        char filename[100];
        printf("Enter the filename to load the matrix from: ");
        scanf("%s", filename);

        if (load_matrix_from_file(matrix, filename) != 0) {
            printf("Failed to load matrix from file\n");
            check_print = 0;
            choose_matrix_creation_method(matrix,n);
        }

        if (matrix->rows != size || matrix->cols != size) {
            printf("Loaded matrix size does not match required size (2^%d x 2^%d).\n", n, n);
            check_print = 0;
            choose_matrix_creation_method(matrix,n);
        }
        break;
    }
    default:
        printf("Invalid matrix creation type.\n");
        check_print = 0;
        choose_matrix_creation_method(matrix,n);
    }

    
    if (check_print) {
        printf("Matrix created:\n");
        print_matrix(matrix);
    }
}

void save_matrix_with_prompt(MAT* matrix) {
    char save_choice;
    printf("Do you want to save matrix? (y/n): ");
    scanf(" %c", &save_choice);
    if (save_choice == 'y' || save_choice == 'Y') {
        char filename[100];
        printf("Enter filename to save the matrix: ");
        scanf("%s", filename);
        if (save_matrix_to_file(matrix, filename) == 0) {
            printf("Matrix saved to %s successfully.\n", filename);
        }
        else {
            printf("Failed to save the matrix.\n");
        }
    }
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

            if (initialize_matrix(&A, pow(2, n), pow(2, n)) != 0 ||
                initialize_matrix(&B, pow(2, n), pow(2, n)) != 0 ||
                initialize_matrix(&C, pow(2, n), pow(2, n)) != 0) {
                printf("Failed to initialize matrices\n");
                return -1;
            }

            printf("Matrix A:\n");
            choose_matrix_creation_method(&A, n);
            save_matrix_with_prompt(&A);

            printf("Matrix B:\n");
            choose_matrix_creation_method(&B, n);
            save_matrix_with_prompt(&B);

            if (add_matrices(&A, &B, &C) != 0) {
                printf("Matrix addition failed\n");
                return -1;
            }

            printf("Result of addition:\n");
            print_matrix_info(&C);
            save_matrix_with_prompt(&C);

            release_matrix(&A);
            release_matrix(&B);
            release_matrix(&C);
            break;

        case 2:
            printf("Enter n for matrix size (matrix will be 2^n x 2^n): ");
            scanf("%d", &n);

            if (initialize_matrix(&A, pow(2, n), pow(2, n)) != 0 ||
                initialize_matrix(&B, pow(2, n), pow(2, n)) != 0 ||
                initialize_matrix(&C, pow(2, n), pow(2, n)) != 0) {
                printf("Failed to initialize matrices\n");
                return -1;
            }

            printf("Matrix A:\n");
            choose_matrix_creation_method(&A, n);
            save_matrix_with_prompt(&A);

            printf("Matrix B:\n");
            choose_matrix_creation_method(&B, n);
            save_matrix_with_prompt(&B);

            if (subtract_matrices(&A, &B, &C) != 0) {
                printf("Matrix subtraction failed\n");
                return -1;
            }

            printf("Result of subtraction:\n");
            print_matrix_info(&C);
            save_matrix_with_prompt(&C);

            release_matrix(&A);
            release_matrix(&B);
            release_matrix(&C);
            break;

        case 3:
            printf("Enter n for matrix size (matrix will be 2^n x 2^n): ");
            scanf("%d", &n);

            if (initialize_matrix(&A, pow(2, n), pow(2, n)) != 0 ||
                initialize_matrix(&B, pow(2, n), pow(2, n)) != 0 ||
                initialize_matrix(&C, pow(2, n), pow(2, n)) != 0) {
                printf("Failed to initialize matrices\n");
                return -1;
            }

            printf("Matrix A:\n");
            choose_matrix_creation_method(&A, n);
            save_matrix_with_prompt(&A);

            printf("Matrix B:\n");
            choose_matrix_creation_method(&B, n);
            save_matrix_with_prompt(&B);

            if (multiply_matrices_strassen(&A, &B, &C) != 0) {
                printf("Matrix multiplication failed\n");
                return -1;
            }

            printf("Result of multiplication using Strassen's algorithm:\n");
            print_matrix_info(&C);
            save_matrix_with_prompt(&C);

            release_matrix(&A);
            release_matrix(&B);
            release_matrix(&C);
            break;

        case 0:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
