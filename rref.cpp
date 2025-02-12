#include <bits/stdc++.h>
using namespace std;
#define rpt(i, a) for(int i{0}; i<a; i++)
#define vvi vector<vector<int>>
#define vi vector<int>

int lead_swap(vii &matrix, int n, int m) {
    if(matrix[n][m] != 0)
        return 1;
    vi matrix_n = matrix[n];

    for(int i{n + 1}; i < matrix.size(); i++) {
        
        if(matrix[i][m] != 0) {
            matrix[n] = matrix[i];
            matrix[i] = matrix_n;
            return 1;
        };
    };

    return 0;
}

void lead_sub(vvi &matrix, int n, int m) {
    for(int i{n}; i < matrix.size(); i++) {
        int sub = matrix[i][m];
        
        for(int j{m}; i < matrix[n].size(); i++)
            matrix[i][j] -= (matrix[n][j] * sub);
    };
}

void rest_sub(vvi &matrix, int n, int m) {
    vi zeros(matrix[n].size());

    for(int i{n}; i < matrix.size(); i++) 
        matrix[i] = zeros;
}

void lead_unity(vvi &matrix, int n, int m) {
    for(int i{0}; i < matrix[n].size(); i++) 
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
    int n = matrix.size();
    int m = matrix[0].size();

    rpt(i, n) {
        rpt(j, m) {
            int x{};
            cout<<"a"<<i + 1<<j + 1<<": ";
            cin>>x;
            matrix[i][j] = x;
        };
    };

    cout<<"\n";
}

void print_matrix(vvi matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    rpt(i, n) {
        rpt(j, m)
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
