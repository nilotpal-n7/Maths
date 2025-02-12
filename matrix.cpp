#include "essentials.h"

void matrix_init(vvi &matrix) {
    int r = matrix.size();
    int c = matrix[0].size();

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            int x{};
            cout<<"a"<<i<<j<<": ";
            cin>>x;
            matrix[i][j] = x;
        };
    };

    cout<<"\n";
}

void print_matrix(vvi &matrix) {
    int r = matrix.size();
    int c = matrix[0].size();

    rpt(i, 0, r) {
        rpt(j, 0, c)
            cout<<matrix[i][j]<<", ";

        cout<<"\n";
    };

    cout<<"\n";
}

void matrix_mul(vvi &matrix1, vvi &matrix2, vvi &result) {
    int r1 = matrix1.size();
    int c1 = matrix1[0].size();
    int r2 = matrix2.size();
    int c2 = matrix2[0].size();

    if(c1 != r2)
        cout<<"Dimension Error!";
    else {
        rpt(i, 0, r1) {
            rpt(j, 0, c2) {
                int sum{0};
                rpt(k, 0, c1)
                    sum += matrix1[i][k] * matrix2[k][j];

                result[i][j] = sum;
            };
        };
    };
}

int lead_swap(vvi &matrix, int n, int m, int r, int c) {
    if(matrix[n][m] != 0)
        return 1;
    vi matrix_n = matrix[n];
    
    rpt(i, n + 1, r) {
        if(matrix[i][m] != 0) {
            matrix[n] = matrix[i];
            matrix[i] = matrix_n;
            
            return 1;
        };
    };
    return 0;
}

void lead_unity(vvi &matrix, int n, int m, int r, int c) {
    int div = matrix[n][m];
    
    rpt(i, m, c) 
        matrix[n][i] /= div;
}

void lead_sub(vvi &matrix, int n, int m, int r, int c) {
    rpt(i, n + 1, r) {
        int sub = matrix[i][m];
        
        rpt(j, m, c)
            matrix[i][j] -= (matrix[n][j] * sub);
    };
}

void rest_sub(vvi &matrix, int n, int m, int r, int c) {
    vi zeros(c, 0);

    rpt(i, n, r) 
        matrix[i] = zeros;
}

void ref(vvi &matrix, int n, int m, int r, int c) {
    if(n == r)
        return;
    if(m == c) {
        rest_sub(matrix, n , m, r, c);
        return;
    };

    int returned = lead_swap(matrix, n, m, r, c);

    if(returned) {
        lead_unity(matrix, n ,m, r, c);
        lead_sub(matrix, n, m, r, c);
        n += 1;
    };

    ref(matrix, n, m + 1, r, c);
}

void rref(vvi &matrix) {
    int r = matrix.size();
    int c = matrix[0].size();

    ref(matrix, 0, 0, r, c);
    print_matrix(matrix);
    vi index(r, -1);

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            if(matrix[i][j] == 1) {
                index[i] = j;
                break;
            };
        };
    };

    rpt(i, 1, r) {
        rpt(k, 1, i + 1) {
            if(index[r - k] == -1)
                continue;        
            int mul{matrix[r - (i + 1)][index[r - k]]};

            rpt(j, index[r - k], c)
                matrix[r - (i + 1)][j] -= matrix[r - k][j] * mul;
        };
    };
}
