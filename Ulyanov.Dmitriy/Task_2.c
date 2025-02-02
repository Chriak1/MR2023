#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef double MatrixItem;

struct Matrix {
    size_t cols;
    size_t rows;
    MatrixItem *data;
};

const struct Matrix MATRIX_NULL = { .cols = 0, .rows = 0, .data = NULL };


// Function returns MATRIX_NULL if fail
struct Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
        return A;
    };
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return MATRIX_NULL;

    struct Matrix A = { .cols = cols, .rows = rows, .data = NULL };
    A.data = (MatrixItem *)malloc(A.cols * A.rows * sizeof(MatrixItem));
    if (A.data == NULL) return MATRIX_NULL;
    return A;
}


// Function return MATRIX_NULL if fail
struct Matrix matrix_create(const size_t rows, const size_t cols, const MatrixItem *values)
{
    struct Matrix A = matrix_allocate(rows, cols);
    if (A.data == NULL) {
        return A;
    };

    memcpy(A.data, values, A.cols * A.rows * sizeof(MatrixItem));
    return A;
}


void matrix_set_zero(struct Matrix A)
{
    memset(A.data, 0, sizeof(double) * A.rows * A.cols);
}


void matrix_set_one(struct Matrix A)
{
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 1.;
}


void matrix_print(const struct Matrix A)
{

    for (size_t row = 0; row < A.rows; ++row) {
        printf("[ ");
        for (size_t col = 0; col < A.cols; ++col) {
            printf(" %4.2f ", A.data[A.cols * row + col]);
        }
        printf(" ]\n");
    }
    printf("\n");


}

// A += B
// Function returns 0 if success
int matrix_add(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] += B.data[idx];
    return 0;
}


// Function returns new matrix C = A + B or MATRIX_NULL if fail
struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B) 
{
    if (A.cols != B.cols || A.rows != B.rows) {
        return MATRIX_NULL;
    }
    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == 0) return MATRIX_NULL;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_add(C, B);
    return C;
}

// A -= B
// Function return 0 if success
int matrix_subs(const struct Matrix A, const struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return 1;

    for (unsigned int idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] -= B.data[idx];
    return 0;
}


// C = A - B
// Function return C = A - B or MATRIX_NULL if fail 
struct Matrix matrix_minus(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.cols, A.rows);
    if (C.data == NULL) return MATRIX_NULL;

    memcpy(C.data, A.data, C.cols * C.rows * sizeof(MatrixItem));
    matrix_subs(C, B);
    return C;
}

//C = A * B
// Function return C = A * B or C if fail
struct Matrix matrix_mult(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.rows) return MATRIX_NULL;

    struct Matrix C = matrix_allocate(A.rows, B.cols);
    if (C.data == NULL) return C;

    for (size_t colB = 0; colB < B.cols; ++colB) {
        for (size_t rowA = 0; rowA < A.rows; ++rowA) {
            C.data[rowA * C.cols + colB] = 0;
            for (size_t idx = 0; idx < A.cols; ++idx) {
                C.data[rowA * C.cols + colB] += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];
            }
        }
    };
    return C;
}



struct Matrix matrix_trans(struct Matrix A)
{
    struct Matrix B = matrix_allocate(A.cols, A.rows);
    if (B.data == 0) return B;

    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            B.data[col * A.cols + row] = A.data[row * A.cols +col];
        }
    }
    return B;
}


// det(A), A[1][1]
// Function return det or NAN if fail
double matrix_det1x1(struct Matrix A)
{
    if (A.rows != 1 || A.cols != 1) return NAN;
    double det = A.data[0];
    return det; 
}


// det(A), A[2][2]
// Function return det(A) or NAN if fail
double matrix_det2x2(struct Matrix A)
{
    if (A.rows != 2 || A.cols != 2) return NAN;
    
    double det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
    return det;
}

// det(A), A[3][3]
// Function return det(A) or NAN if fail
double matrix_det3x3(struct Matrix A)
{
    if (A.rows != 3 || A.cols != 3) return NAN;

    double det = 
        + A.data[0] * A.data[4] * A.data[8] 
        + A.data[1] * A.data[5] * A.data[6] 
        + A.data[3] * A.data[7] * A.data[2] 
        - A.data[2] * A.data[4] * A.data[6] 
        - A.data[1] * A.data[3] * A.data[8] 
        - A.data[5] * A.data[7] * A.data[0];
    return det;
}

struct Matrix matrix_division(struct Matrix A, const size_t k)
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] = A.data[idx] / k;
    return A;
}


size_t factorial(size_t n)
{
    int result = 1; 
    int i;
    for (i = 2; i <= n; ++i) {
        result *= i;
    };
    return result;
}

// возведение в степень
struct Matrix matrix_power(struct Matrix A, int power)
{
    if (A.cols != A.rows) return MATRIX_NULL;

    struct Matrix result = matrix_allocate(A.rows, A.cols);
    if (result.data == 0) return MATRIX_NULL;
    memcpy(result.data, A.data, result.cols * result.rows * sizeof(MatrixItem));

    if (power < 0) return MATRIX_NULL;
    if (power == 0) {
        struct Matrix C = matrix_allocate(A.cols, A.rows);
        if (C.data == 0) return MATRIX_NULL;
        matrix_set_one(C);
        return C;
    };

    if (power == 1) {
        
        return result;
    }
    int i;
    
    struct Matrix temp = matrix_allocate(A.rows, A.cols);
    if (temp.data == 0) return MATRIX_NULL;
    //memcpy(temp.data, A.data, temp.cols * temp.rows * sizeof(MatrixItem));

    for (i = 2; i < power || i == power; ++i) {
        temp = matrix_mult(result, A);
        if (temp.data == NULL) {
            return MATRIX_NULL;
        };

        memcpy(result.data, temp.data, result.cols * result.rows * sizeof(MatrixItem));
        free(temp.data);
        //не работает
        
    };
    return result;
}

// e^A
// Return e^A or MATRIX_NULL if fail
struct Matrix matrix_exp(struct Matrix A, struct Matrix B)
{
    if (A.cols != A.rows) return MATRIX_NULL;

    struct Matrix I = matrix_allocate(A.rows, A.cols);
    if (I.data == 0) return MATRIX_NULL;
    matrix_set_one(I);

    struct Matrix temp = matrix_allocate(A.rows, A.cols);
    if (temp.data == 0) return MATRIX_NULL;
    matrix_set_one(temp);

    struct Matrix temp2 = matrix_allocate(A.rows, A.cols);
    if (temp2.data == 0) return MATRIX_NULL;
    matrix_set_one(temp2);

    /*struct Matrix Exp = matrix_allocate(A.rows, A.cols);
    if (Exp.data == 0) return MATRIX_NULL;*/
    
    //size_t k = 1;

    int idx;

    for (idx = 1; idx < 100; ++idx) {
        temp = matrix_power(A, idx);
        temp2 = matrix_division(temp, factorial(idx));
        matrix_add(I, temp2);
        free(temp.data);
        free(temp2.data);
    }
    return I;

}


void matrix_delete(struct Matrix *A)
{
    free(A->data);
    A->data = NULL;
}


int main()
{
    struct Matrix  A, B, C, D;
    double values[] = { 2., 2., 2., 2. };
    double values2[] = { 2., 2., 2., 2. };
    double values3[] = { 1., 2., 3., 4., 1., 1., 1., 1., 1.};
    A = matrix_create(2, 2, values);
    B = matrix_create(2, 2, values2);
    D = matrix_create(3, 3, values3);

    C = matrix_power(A, 2);
    matrix_print(C);
    
    //matrix_print(A);
    

   /* matrix_add(B, A);
    matrix_print(B);*/

    /*C = matrix_sum(A, B);
    //matrix_print(C);

    matrix_subs(B, A);
    matrix_print(B);

    C = matrix_minus(A, B);
    matrix_print(C);*/

   /* C = matrix_mult(A, B);
    matrix_print(C);*/

    /*A = matrix_trans(A);
    matrix_print(A);

    double det = matrix_det2x2(A);
    printf("\n%d\n", det);

    double det3 = matrix_det3x3(D);
    printf("\n%d\n", det3);*/

    //matrix_set_one(A);


    matrix_delete(&A);
    matrix_delete(&B);
    matrix_delete(&C);
    //matrix_delete(&D);

    return 0;
}
