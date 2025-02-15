#include "essentials.h"
vvf defv(0, vf(0, 0));
int defi = 0;

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
vvf ref(vvf &matrix, int &swap=defi, vvf &id=defv, int n=0, int m=0);
vvf rref(vvf &matrix, vvf &id=defv);
float determinant(vvf &matrix);
vvf inverse(vvf &matrix);
vvf adjoint(vvf &matrix);
