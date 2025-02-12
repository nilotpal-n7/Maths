#include <bits/stdc++.h>
using namespace std;

#define rpt(i, a, b) for(int i{a}; i < b; i++)
#define vvi vector<vector<int>>
#define vi vector<int>

int N{0}, M{0};

void matrix_init(vvi &matrix) {
    cout<<"\n";

    rpt(i, 0, N) {
        rpt(j, 0, M) {
            int x{};
            cout<<"a"<<i + 1<<j + 1<<": ";
            cin>>x;
            matrix[i][j] = x;
        };
    };

    cout<<"\n\n";
}

void print_matrix(vvi matrix) {
    rpt(i, 0, N) {
        rpt(j, 0, M)
            cout<<matrix[i][j]<<", ";

        cout<<"\n";
    };
    cout<<"\n";
}

int lead_swap(vvi &matrix, int n, int m) {
    if(matrix[n][m] != 0)
        return 1;
    vi matrix_n = matrix[n];
    
    rpt(i, n + 1, N) {
        if(matrix[i][m] != 0) {
            matrix[n] = matrix[i];
            matrix[i] = matrix_n;
            
            return 1;
        };
    };
    return 0;
}

void lead_unity(vvi &matrix, int n, int m) {
    int div = matrix[n][m];
    
    rpt(i, m, M) 
        matrix[n][i] /= div;
}

void lead_sub(vvi &matrix, int n, int m) {
    rpt(i, n + 1, N) {
        int sub = matrix[i][m];
        
        rpt(j, m, M)
            matrix[i][j] -= (matrix[n][j] * sub);
    };
}

void rest_sub(vvi &matrix, int n, int m) {
    vi zeros(M, 0);

    rpt(i, n, N) 
        matrix[i] = zeros;
}

void ref(vvi &matrix, int n, int m) {
    if(n == N)
        return;
    if(m == M) {
        rest_sub(matrix, n , m);
        return;
    };

    int returned = lead_swap(matrix, n, m);

    if(returned) {
        lead_unity(matrix, n ,m);
        lead_sub(matrix, n, m);
        n += 1;
    };

    ref(matrix, n, m + 1);
}

void rref(vvi &matrix, int n, int m) {
    ref(matrix, n, m);
    print_matrix(matrix);
    vector<int> index(N, -1);

    rpt(i, 0, N) {
        rpt(j, 0, M) {
            if(matrix[i][j] == 1) {
                index[i] = j;
                break;
            };
        };
    };

    rpt(i, 1, N) {
        rpt(k, 1, i + 1) {
            if(index[N - k] == -1)
                continue;        
            int mul{matrix[N - (i + 1)][index[N - k]]};

            rpt(j, index[N - k], M)
                matrix[N - (i + 1)][j] -= matrix[N - k][j] * mul;
        };
    };
}

int main() {
    cin>>N>>M;
    vvi matrix(N, vi(M, 0));

    matrix_init(matrix);
    print_matrix(matrix);
    rref(matrix, 0, 0);
    print_matrix(matrix);

    return 0;
}

//4 5 1 3 3 8 5 0 1 3 10 8 0 0 0 -1 -4 0 0 0 2 8