#ifndef MATRICES_H
#define MATRICES_H

#define MAT_AT(mat, row, col) ((mat).matrix[(row) * (mat).cols + (col)])
#define MAT_SET(mat, row, col, value) ((mat).matrix[(row) * (mat).cols + (value)])

// Štruktúra pre maticu
typedef struct {
    int rows;      // Počet riadkov
    int cols;      // Počet stĺpcov
    int* matrix;   // Ukazovateľ na jednorozmerné pole reprezentujúce maticu
    int size;      // Celková veľkosť matice (rows * cols)
} MAT;

// Inicializácia matice
void initialize_matrix(MAT* mat, int rows, int cols);

// Uvoľnenie pamäte alokovanej pre maticu
void release_matrix(MAT* mat);

// Naplnenie matice hodnotami
void mat_unit(MAT* mat);
void mat_random(MAT* mat);
void mat_create_with_type(MAT* mat, int rows, int cols, int type);
void mat_create_by_file(MAT* mat, const char* filename);

// Výpis obsahu matice
void print_matrix(MAT mat);

// Sčítanie a odčítanie matíc
void add_subtract_matrix(MAT A, MAT B, MAT* C, int add);

// Prístup k prvku matice pomocou dvoch indexov
int at(MAT mat, int row, int col);

// Násobenie matíc podľa algoritmu Štrassena
void mat_multiply_strassen(MAT* A, MAT* B, MAT* C);



void mat_save(MAT* mat, const char* filename);





#endif // MATRICES_H
