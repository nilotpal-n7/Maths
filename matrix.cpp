#include "matrix.h"

int dim_r(vvf &matrix) {
    int r = matrix.size();
    return r;
}

int dim_c(vvf &matrix) {
    int c = matrix[0].size();
    return c;
}

void dim(vvf &matrix, int *r, int *c) {
    *r = dim_r(matrix);
    *c = dim_c(matrix);
}

vvf matrix_init() {
    int r{}, c{};
    cout<<"r, c: ";
    cin>>r>>c;
    cout<<endl;
    vvf matrix(r, vf(c, 0));

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            float x{};
            cout<<"a"<<i + 1<<j + 1<<": ";
            cin>>x;
            matrix[i][j] = x;
        };
    };
    
    cout<<"\n"<<endl;
    return matrix;
}

void print_matrix(vvf &matrix) {
    int r{}, c{};
    dim(matrix, &r, &c);

    rpt(i, 0, r) {
        rpt(j, 0, c)
            cout<<matrix[i][j]<<", ";
        cout<<endl;
    };
    cout<<endl;
}

bool isequal(vvf &matrix1, vvf &matrix2) {
    int r1{}, c1{}, r2{}, c2{};
    dim(matrix1, &r1, &c1);
    dim(matrix2, &r2, &c2);

    if((r1 != r2) or (c1 != c2))
        return false;

    rpt(i, 0, r1) {
        rpt(j , 0, c2) {
            if(matrix1[i][j] != matrix2[i][j])
                return false;
        };
    };

    return true;
}

vvf transpose(vvf &matrix) {
    int r{}, c{};
    dim(matrix, &r, &c);
    vvf result(c, vf(r, 0));

    rpt(i, 0, r) {
        rpt(j, 0, c)
            result[j][i] = matrix[i][j];
    };

    return result;
}

vvf matrix_conjugate(vvf &matrix) {
    int r{}, c{};
    dim(matrix, &r, &c);
    vvf result(r, vf(c, 0));

    rpt(i, 0, r) {
        rpt(j, 0, c)
            result[i][j] = matrix[i][j];
    };

    return result;
}

vvf matrix_mul(vvf &matrix1, vvf &matrix2) {
    int r1{}, c1{}, r2{}, c2{};
    dim(matrix1, &r1, &c1);
    dim(matrix2, &r2, &c2);

    if(c1 == r2) {
        vvf result(r1, vf(c2, 0));

        rpt(i, 0, r1) {
            rpt(j, 0, c2) {
                int sum{0};
                rpt(k, 0, c1)
                    sum += matrix1[i][k] * matrix2[k][j];

                result[i][j] = sum;
            };
        };

        return result;
    }
    else
        throw "Dimension Error!";
}

vvf dot(vvf &matrix1, vvf &matrix2) {
    int r1 = dim_r(matrix1);
    int r2 = dim_r(matrix2);

    if(r1 == r2) {
        vvf t_result = transpose(matrix1);
        vvf result = matrix_mul(t_result, matrix2);
        
        return result;
    }
    else
        throw "Dimension Error";
}

int lead_swap(vvf &matrix, int n, int m, int r, int c) {
    if(matrix[n][m] != 0)
        return 1;
    vf matrix_n = matrix[n];
    
    rpt(i, n + 1, r) {
        if(matrix[i][m] != 0) {
            matrix[n] = matrix[i];
            matrix[i] = matrix_n;
            
            return 1;
        };
    };
    return 0;
}

void lead_unity(vvf &matrix, int n, int m, int r, int c) {
    float div = matrix[n][m];
    
    rpt(i, m, c) 
        matrix[n][i] /= div;
}

void lead_sub(vvf &matrix, int n, int m, int r, int c) {
    rpt(i, n + 1, r) {
        float sub = matrix[i][m];
        
        rpt(j, m, c)
            matrix[i][j] -= (matrix[n][j] * sub);
    };
}

void rest_sub(vvf &matrix, int n, int m, int r, int c) {
    vf zeros(c, 0);

    rpt(i, n, r) 
        matrix[i] = zeros;
}

vvf ref(vvf &matrix, int n, int m) {
    int r{}, c{};
    dim(matrix, &r, &c);
    vvf result = matrix;

    if(n == r)
        return result;
    if(m == c) {
        rest_sub(result, n , m, r, c);
        return result;
    };

    int returned = lead_swap(result, n, m, r, c);

    if(returned) {
        lead_unity(result, n ,m, r, c);
        lead_sub(result, n, m, r, c);
        n += 1;
    };

    result = ref(result, n, m + 1);
    return result;
}

vvf rref(vvf &matrix) {
    int r{}, c{};
    dim(matrix, &r, &c);
    vvf result = ref(matrix, 0, 0);
    vi index(r, -1);

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            if(result[i][j] == 1) {
                index[i] = j;
                break;
            };
        };
    };

    rpt(i, 1, r) {
        rpt(k, 1, i + 1) {
            if(index[r - k] == -1)
                continue;        
            float mul{result[r - (i + 1)][index[r - k]]};

            rpt(j, index[r - k], c)
                result[r - (i + 1)][j] -= result[r - k][j] * mul;
        };
    };

    return result;
}
