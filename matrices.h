#ifndef MATRICES_H
#define MATRICES_H

#define MAT_AT(mat, row, col) ((mat).matrix[(row) * (mat).cols + (col)])

typedef struct {
    int rows;      // number of rows
    int cols;      // number of columns
    int* matrix;   // pointer to a one-dimensional array representing the matrix
} MAT;

// initialize a matrix with given dimensions
int initialize_matrix(MAT* mat, int rows, int cols);

// release dynamically allocated memory for a matrix
void release_matrix(MAT* mat);

// create an identity matrix
int create_identity_matrix(MAT* mat, int size);

// fill a matrix with random values
int create_random_matrix(MAT* mat, int rows, int cols);

// create a matrix from a file
int load_matrix_from_file(MAT* mat, const char* filename);

// save a matrix to a file
int save_matrix_to_file(const MAT* mat, const char* filename);

// print the contents of a matrix
void print_matrix(const MAT* mat);

// add two matrices and store the result in the third matrix
int add_matrices(const MAT* A, const MAT* B, MAT* C);

// subtract two matrices and store the result in the third matrix
int subtract_matrices(const MAT* A, const MAT* B, MAT* C);

// multiply matrix A by matrix B using the Strassen algorithm and store the result in the third matrix
int multiply_matrices_strassen(const MAT* A, const MAT* B, MAT* C);

// create a matrix based on the specified type
int mat_create_with_type(MAT* mat, int rows, int cols, int type);

#endif // MATRICES_H
