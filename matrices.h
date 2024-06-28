#ifndef MATRICES_H
#define MATRICES_H

#define MAT_AT(mat, row, col) ((mat).matrix[(row) * (mat).cols + (col)])

typedef struct {
    int rows;      // number of rows
    int cols;      // number of columns
    int* matrix;   // pointer to a one-dimensional array representing the matrix
} MAT;

/**
 * Initialize a matrix with given dimensions
 *
 * @param mat Pointer to a MAT structure
 * @param rows Number of rows for the matrix
 * @param cols Number of columns for the matrix
 * @return 0 on success, -1 on failure (e.g., memory allocation failure)
 */
int initialize_matrix(MAT* mat, int rows, int cols);

/**
 * Release dynamically allocated memory for a matrix
 *
 * @param mat Pointer to a MAT structure
 */
void release_matrix(MAT* mat);

/**
 * Create an identity matrix
 *
 * @param mat Pointer to a MAT structure
 * @param size Size of the identity matrix (i.e., number of rows and columns)
 * @return 0 on success, -1 on failure
 */
void create_identity_matrix(MAT* mat);
/**
 * Fill a matrix with random values
 *
 * @param mat Pointer to a MAT structure
 * @param rows Number of rows for the matrix
 * @param cols Number of columns for the matrix
 * @return 0 on success, -1 on failure
 */
void create_random_matrix(MAT* mat);
/**
 * Create a matrix from a file
 *
 * @param mat Pointer to a MAT structure
 * @param filename Name of the file to load the matrix from
 * @return 0 on success, -1 on failure (e.g., file not found, memory allocation failure)
 */
MAT* load_matrix_from_file(const char* filename);
/**
 * Save a matrix to a file
 *
 * @param mat Pointer to a MAT structure
 * @param filename Name of the file to save the matrix to
 * @return 0 on success, -1 on failure (e.g., file cannot be opened)
 */
char save_matrix_to_file(MAT* mat, char* filename);

/**
 * Print the contents of a matrix
 *
 * @param mat Pointer to a MAT structure
 */
void print_matrix(const MAT* mat);

/**
 * Add two matrices and store the result in the third matrix
 *
 * @param A Pointer to the first MAT structure
 * @param B Pointer to the second MAT structure
 * @param C Pointer to the MAT structure where the result will be stored
 * @return 0 on success, -1 on failure (e.g., dimensions do not match)
 */
int add_matrices(const MAT* A, const MAT* B, MAT* C);

/**
 * Subtract two matrices and store the result in the third matrix
 *
 * @param A Pointer to the first MAT structure
 * @param B Pointer to the second MAT structure
 * @param C Pointer to the MAT structure where the result will be stored
 * @return 0 on success, -1 on failure (e.g., dimensions do not match)
 */
int subtract_matrices(const MAT* A, const MAT* B, MAT* C);

/**
 * Multiply matrix A by matrix B using the Strassen algorithm and store the result in the third matrix
 *
 * @param A Pointer to the first MAT structure
 * @param B Pointer to the second MAT structure
 * @param C Pointer to the MAT structure where the result will be stored
 * @return 0 on success, -1 on failure (e.g., dimensions do not match)
 */
int multiply_matrices_strassen(const MAT* A, const MAT* B, MAT* C);

/**
 * Create a matrix with specified dimensions
 *
 * @param rows Number of rows for the matrix
 * @param cols Number of columns for the matrix
 * @return Pointer to the created MAT structure, or NULL on failure
 */
MAT* mat_create_with_type(unsigned int rows, unsigned int cols);


#endif // MATRICES_H
