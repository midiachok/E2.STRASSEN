#ifndef MATRICES_H
#define MATRICES_H

#define MAT_AT(mat, row, col) ((mat).matrix[(row) * (mat).cols + (col)])
#define MAT_SET(mat, row, col, value) ((mat).matrix[(row) * (mat).cols + (value)])

typedef struct {
    int rows;      // number of rows
    int cols;      // number of columns
    int* matrix;   // pointer to a one-dimensional array representing the matrix
    int size;      // total size of the matrix (rows * cols)
} MAT;

// initialize a matrix with given dimensions
int initialize_matrix(MAT* mat, int rows, int cols);

// release dynamically allocated memory for a matrix
void release_matrix(MAT* mat);

// create an identity matrix
int mat_unit(MAT* mat);

// fill a matrix with random values
void mat_random(MAT* mat);

// create a matrix based on the specified type
int mat_create_with_type(MAT* mat, int rows, int cols, int type);

// create a matrix from a file
int mat_create_by_file(MAT* mat, const char* filename);

// save a matrix to a file
int mat_save(MAT* mat, const char* filename);

// print the contents of a matrix
void print_matrix(MAT mat);

// add or subtract two matrices and store the result in C
int add_subtract_matrix(const MAT A, const MAT B, MAT* C, int add);

// multiply matrix A by matrix B using the Strassen algorithm
int mat_multiply_strassen(const MAT* A, const MAT* B, MAT* C);





#endif // MATRICES_H
