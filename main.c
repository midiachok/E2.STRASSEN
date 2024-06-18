#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "matrices.h"

void run_program() {
    MAT m1, m2, m3;
    int size = 0;

    do {
        printf("Zadajte velkost n matice 2^n x 2^n: ");
        scanf("%d", &size);
    } while (size < 1);

    initialize_matrix(&m1, (int)pow(2, size), (int)pow(2, size));
    populate_matrix(&m1);
    printf("Matica A:\n");
    print_matrix(m1);

    initialize_matrix(&m2, (int)pow(2, size), (int)pow(2, size));
    populate_matrix(&m2);
    printf("Matica B:\n");
    print_matrix(m2);

    initialize_matrix(&m3, (int)pow(2, size), (int)pow(2, size));
    mat_multiply_strassen(&m1, &m2, &m3);

    printf("Vysledok nasobenia matic A a B:\n");
    print_matrix(m3);

    release_matrix(&m1);
    release_matrix(&m2);
    release_matrix(&m3);
}

void test_strassen_multiplication(int max_n) {
    for (int n = 1; n <= max_n; ++n) {
        MAT m1, m2, m3;

        initialize_matrix(&m1, (int)pow(2, n), (int)pow(2, n));
        initialize_matrix(&m2, (int)pow(2, n), (int)pow(2, n));

        populate_matrix_keyboard_automatically(&m1, 2);
        populate_matrix_keyboard_automatically(&m2, 2);

        printf("Test pre n = %d:\n", n);
        printf("Matica A:\n");
        print_matrix(m1);

        printf("Matica B:\n");
        print_matrix(m2);

        initialize_matrix(&m3, (int)pow(2, n), (int)pow(2, n));
        mat_multiply_strassen(&m1, &m2, &m3);

        printf("Vysledok nasobenia matic A a B:\n");
        print_matrix(m3);

        release_matrix(&m1);
        release_matrix(&m2);
        release_matrix(&m3);

        printf("Stlacte Enter pre pokracovanie...");
        getchar();
        printf("\n");
    }
}

int main() {
    srand(time(0));
    int choice;
    int max_test_size;

    do {
        printf("\nMENU:\n1. Spustit program\n2. Test strassenovho nasobenia\n0. Koniec programu\nVyberte moznost: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            run_program();
            break;
        case 2:
            printf("Zadajte maximalnu velkost n pre test (2^n x 2^n): ");
            scanf("%d", &max_test_size);
            test_strassen_multiplication(max_test_size);
            break;
        case 0:
            printf("Koniec programu.\n");
            break;
        default:
            printf("Neplatna volba. Skuste znova.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}
