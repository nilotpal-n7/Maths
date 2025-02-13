#include "essentials.h"

int dim_r(vvf &matrix);
int dim_c(vvf &matrix);
void dim(vvf &matrix, int *r, int *c);
vvf matrix_init();
void print_matrix(vvf &matrix);
bool isequal(vvf &matrix1, vvf &matrix2);
vvf transpose(vvf &matrix);
vvf matrix_conjugate(vvf &matrix);
vvf matrix_mul(vvf &matrix1, vvf &matrix2);
vvf dot(vvf &matrix1, vvf &matrix2);
vvf ref(vvf &matrix, int n, int m);
vvf rref(vvf &matrix);
