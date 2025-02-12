#include "matrix.h"

int main() {
    int N{}, M{};
    cin>>N>>M;
    vvi matrix(N, vi(M, 0));

    matrix_init(matrix);
    print_matrix(matrix);
    rref(matrix);
    print_matrix(matrix);

    cin.get();
    return 0;
}

//4 5 1 3 3 8 5 0 1 3 10 8 0 0 0 -1 -4 0 0 0 2 8