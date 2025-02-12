#include <bits/stdc++.h>
using namespace std;
#define rpt(i, a) for(int i{0}; i<a; i++)
#define vvi vector<vector<int>>
#define vi vector<int>

int lead_swap(vii &matrix, int n, int m) {
    if(matrix[n][m] != 0)
        return 1;
    vi matrix_n = matrix[n];
    int i_s{n + 1};
    
    rpt(i, matrix.size() - i_s) {
        if(matrix[i + i_s][m] != 0) {
            matrix[n] = matrix[i + i_s];
            matrix[i + i_s] = matrix_n;
            
            return 1;
        };
    };
    return 0;
}

void lead_sub(vvi &matrix, int n, int m) {
    int i_s{n}, j_s{m};
    
    rpt(i, matrix.size() - i_s) {
        int sub = matrix[i + i_s][m];
        
        rpt(j, matrix[0].size() - j_s)
            matrix[i + i_s][j + j_s] -= (matrix[n][j + j_s] * sub);
    };
}

void rest_sub(vvi &matrix, int n, int m) {
    vi zeros(matrix[n].size());
    int i_s{n};

    rpt(i, matrix.size() - i_s) 
        matrix[i + i_s] = zeros;
}

void lead_unity(vvi &matrix, int n, int m) {
    rpt(i, matrix[0].size()) 
        matrix[n][i] /= matrix[n][m];
}

void rref(vvi &matrix, int n, int m) {
    if(n == matrix.size())
        return;
    if(m == matrix[n].size()) {
        rest_sub(matrix, n , m);
        return;
    };

    int returned = lead_swap(matrix, n, m);

    if(returned) {
        lead_unity(matrix, n ,m);
        lead_sub(matrix, n, m);
        n += 1;
    };

    rref(matrix, n, m + 1);
}

void matrix_init(vvi &matrix) {
    rpt(i, matrix.size()) {
        rpt(j, matrix[0].size()) {
            int x{};
            cout<<"a"<<i + 1<<j + 1<<": ";
            cin>>x;
            matrix[i][j] = x;
        };
    };

    cout<<"\n";
}

void print_matrix(vvi matrix) {
    rpt(i, matrix.size()) {
        rpt(j, matrix[0].size())
            cout<<matrix[i][j]<<", ";

        cout<<"\n";
    };
    cout<<"\n";
}

int main() {
    int n{}, m{};
    cin>>n>>m;
    vvi matrix(n, vi(m, 0));

    matrix_init(matrix);
    print_matrix(matrix);
    rref(matrix, 0, 0);
    print_matrix(matrix);

    return 0;
}
