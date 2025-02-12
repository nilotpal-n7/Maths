#include <bits/stdc++.h>
using namespace std;
#define rpt(i, a) for(int i{0}; i<a; i++)

void matrix_init(vector<vector<int>> &matrix0) {
    int n = matrix0.size();
    int m = matrix0[0].size();

    rpt(i, n) {
        rpt(j, m) {
            int x{};
            cout<<"a"<<i<<j<<": ";
            cin>>x;
            matrix0[i][j] = x;
        };
    };

    cout<<"\n";
}

void print_matrix(vector<vector<int>> matrix0) {
    int n = matrix0.size();
    int m = matrix0[0].size();

    rpt(i, n) {
        rpt(j, m)
            cout<<matrix0[i][j]<<", ";

        cout<<"\n";
    };

    cout<<"\n";
}

void matrix_mul(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2, vector<vector<int>> &result) {\
    int row1 = matrix1.size();
    int col1 = matrix1[0].size();
    int row2 = matrix2.size();
    int col2 = matrix2[0].size();

    if(col1 != row2)
        cout<<"Dimension Error!";
    else {
        rpt(i, row1) {
            rpt(j, col2) {
                int sum{0};
                rpt(k, col1)
                    sum += matrix1[i][k] * matrix2[k][j];

                result[i][j] = sum;
            };
        };
    };
}

int main() {
    int n1{}, m1{}, n2{}, m2{};
    cin>>n1>>m1>>n2>>m2;

    vector<vector<int>> matrix1(n1, vector<int>(m1, 0));
    vector<vector<int>> matrix2(n2, vector<int>(m2, 0));
    vector<vector<int>> result(n1, vector<int>(m2, 0));

    matrix_init(matrix1);
    matrix_init(matrix2);
    matrix_mul(matrix1, matrix2, result);

    print_matrix(matrix1);
    print_matrix(matrix2);
    print_matrix(result);

    return 0;
}
