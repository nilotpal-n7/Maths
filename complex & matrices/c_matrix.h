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
    Complex determinant();
    Matrix inverse();
    Matrix adjoint();
    vc &operator[](int j);
    int rank();
};
int defi = 0;
vc dev(0, Complex(0, 0));
Matrix defm(1, 1);

bool operator==(Matrix &matrix1, Matrix &matrix2);
bool isequal(Matrix &matrix1, Matrix &matrix2);
Matrix mul(Matrix &matrix1, Matrix &matrix2);
Matrix dot(Matrix &matrix1, Matrix &matrix2);
Matrix ref(Matrix &matrix, int &swap=defi, Matrix &id=defm, int n=0, int m=0);
Matrix rref(Matrix &matrix, Matrix &id=defm);
Matrix identity(int r, int c, Complex x=1);
vc eigenvalues(Matrix &matrix, Complex x=Complex(0, 0));
int rref_rank(Matrix &matrix);
Matrix solver(Matrix &matrix=defm);
Matrix eigenvec(Matrix &matrix);
