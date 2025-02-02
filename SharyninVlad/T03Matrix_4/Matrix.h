#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef double MatrixItem;

struct Matrix {
    size_t rows;
    size_t cols;
    MatrixItem *data;
};

enum MatrixType { zero, ones, random, I};
enum ErrorType { memory_alloccation_error, false_matrix, false_rows_or_cols, empty_matrix};

int matrix_print(struct Matrix* M);
struct Matrix memory_allocation(const size_t rows, const size_t cols);
struct Matrix matrix_create(const size_t rows, size_t cols, enum MatrixType mat_type);
void matrix_free(struct Matrix* M);
struct Matrix matrix_subst(const struct Matrix A, const struct Matrix B);
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B);
struct Matrix matrix_mult_on_number(const struct Matrix A, double multiplier);
struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B);
struct Matrix transposition(const struct Matrix A);
double determinant(struct Matrix A);
struct Matrix matrix_exponential(struct Matrix M, double level);
void matrix_print_free(struct Matrix* M);
