#ifndef MATRICES_H
#define MATRICES_H

// struktura pre maticu
typedef struct {
    int rows;      // pocet riadkov
    int cols;      // pocet stlpcov
    int* matrix;   // smernik na jednorozmerne pole reprezentujuce maticu
    int size;      // celkova vel¾kost matice (rows * cols)
} MAT;

// inicializacia matice
void initialize_matrix(MAT* mat, int rows, int cols);

// uvolnenie pamate alokovanej pre maticu
void release_matrix(MAT* mat);

// naplnenie matice hodnotami
void populate_matrix(MAT* mat);
void populate_matrix_keyboard_automatically(MAT* mat, int choice);

// vypis obsahu matice
void print_matrix(MAT mat);

// scitanie a oditanie matic
void add_subtract_matrix(MAT A, MAT B, MAT* C, int add);

// pristup k prvku matice pomocou dvoch indexov
int at(MAT mat, int row, int col);

// nasobenie matic podla algoritmu strassena
void mat_multiply_strassen(MAT* A, MAT* B, MAT* C);

#endif // MATRICES_H
