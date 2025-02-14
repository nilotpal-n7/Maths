#include "essentials.h"
#include "complex.h"
#define vvc vector<vector<Complex>>
#define vc vector<Complex>

struct Matrix {
    int r{}, c{};
    vvc matrix = vvc(r, vc(c, Complex(0, 0)));
    Matrix(int r=0, int c=0);
    void _init_();
    void print();
    int dim_r();
    int dim_c();
    string dim();
    Matrix transpose();
    Matrix matrix_conjugate();
    Matrix dagger();
};

bool isequal(Matrix &matrix1, Matrix &matrix2);
Matrix matrix_mul(Matrix &matrix1, Matrix &matrix2);
Matrix dot(Matrix &matrix1, Matrix &matrix2);
Matrix ref(Matrix &matrix, int n, int m);
Matrix rref(Matrix &matrix);
