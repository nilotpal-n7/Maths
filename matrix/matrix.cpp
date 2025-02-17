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

    if(c1 != r2)
        throw "Dimension Error: Mul(c1 != r2)";
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

vvf dot(vvf &matrix1, vvf &matrix2) {
    int r1 = dim_r(matrix1);
    int r2 = dim_r(matrix2);

    if(r1 != r2)
        throw "Dimension Error: Dot(r1 != r2)";

    vvf t_result = transpose(matrix1);
    vvf result = matrix_mul(t_result, matrix2);
    
    return result;

}

int lead_swap(vvf &matrix, int n, int m, int r, int c, int &swap=defi, vvf &id=defv) {
    if(matrix[n][m] != 0)
        return 1;        
    
    rpt(i, n + 1, r) {
        if(matrix[i][m] != 0) {
            vf matrix_n = matrix[n];
            matrix[n] = matrix[i];
            matrix[i] = matrix_n;

            if(id != defv){
                vf id_n = id[n];
                id[n] = id[i];
                id[i] = id_n;
            };

            cout<<"R["<<n + 1<<"] <-> ["<<i + 1<<"]"<<endl;
            rpt(i, 0, r) {
                rpt(j, 0, c)
                    cout<<id[i][j]<<" ";
                cout<<endl;
            };
            cout<<endl;

            if(swap != defi)
                swap++; 
            
            return 1;
        };
    };
    return 0;
}

void lead_sub(vvf &matrix, int n, int m, int r, int c, vvf &id=defv) {
    rpt(i, n + 1, r) {
        float sub = matrix[i][m] / matrix[n][m];
        
        rpt(j, 0, c){ //0->m
            matrix[i][j] -= (matrix[n][j] * sub);
            if(id != defv)
                id[i][j] -= (id[n][j] * sub);
        };

        cout<<"R["<<i + 1<<"] -> R["<<i + 1<<"] - R["<<n + 1<<"]*"<<sub<<endl;
        rpt(i, 0, r) {
            rpt(j, 0, c)
                cout<<id[i][j]<<" ";
            cout<<endl;
        };
        cout<<endl;
    };
}

void rest_sub(vvf &matrix, int n, int m, int r, int c, vvf &id=defv) {
    vf zeros(c, 0);

    rpt(i, n, r) {
        matrix[i] = zeros;
        if(id != defv)
            id[i] = zeros;
        
        cout<<"R["<<i + 1<<"] -> R["<<i + 1<<"] * "<<0<<endl;
        rpt(i, 0, r) {
            rpt(j, 0, c)
                cout<<id[i][j]<<" ";
            cout<<endl;
        };
        cout<<endl;
    };
}

vvf ref(vvf &matrix, int &swap, vvf &id, int n, int m) {
    int r{}, c{};
    dim(matrix, &r, &c);
    vvf result = matrix;

    if(n == r)
        return result;
    if(m == c) {
        rest_sub(result, n , m, r, c, id);
        return result;
    };

    int returned = lead_swap(result, n, m, r, c, swap, id);

    if(returned) {
        lead_sub(result, n, m, r, c, id);
        n += 1;
    };

    result = ref(result, swap, id, n, m + 1);
    return result;
}

vvf rref(vvf &matrix, vvf &id) {
    int r{}, c{};
    dim(matrix, &r, &c);
    vvf result = ref(matrix, defi, id);
    vi index(r, -1);

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            if(result[i][j] != 0) {
                index[i] = j;
                float div = result[i][j];

                rpt(k, 0, c) { //0->m
                    result[i][k] /= div;
                    if(id != defv)
                        id[i][k] /= div;
                };
            
                cout<<"R["<<i + 1<<"] -> R["<<i + 1<<"] / "<<div<<endl;
                rpt(k, 0, r) {
                    rpt(l, 0, c)
                        cout<<id[k][l]<<" ";
                    cout<<endl;
                };
                cout<<endl;
                break;
            };
        };
    };

    rpt(i, 1, r) {
        rpt(k, 1, i + 1) {
            if(index[r - k] == -1)
                continue;        
            float mul = result[r - (i + 1)][index[r - k]];

            rpt(j, 0, c) { //0->index[r - k]
                result[r - (i + 1)][j] -= result[r - k][j] * mul;
                if(id != defv)
                    id[r - (i + 1)][j] -= id[r - k][j] * mul;
            };

            cout<<"R["<<r - (i + 1) + 1<<"] -> R["<<r - (i + 1) + 1<<"] - R["<<r - k + 1<<"]*"<<mul<<endl;
            rpt(i, 0, r) {
                rpt(j, 0, c)
                    cout<<id[i][j]<<" ";
                cout<<endl;
            };
            cout<<endl;
        };
    };

    return result;
}

float determinant(vvf &matrix) {
    int r{}, c{};
    dim(matrix, &r, &c);

    if(r != c)
        throw "error";

    float det{1};
    vi index(r, -1);
    int swap = 0;
    vvf result = ref(matrix, swap);
    cout<<"swap: "<<swap<<endl;

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            if(result[i][j] != 0) {
                index[i] = j;
                break;
            };
        };
    };

    rpt(i, 0, r) {
        if(index[i] == -1)
            throw "error";
        det *= result[i][i];

        if(result[i][i] == 0)
            break;
    };

    if(swap & 1)
        det *= -1;

    return det;
}

vvf inverse(vvf &matrix) {
    int r{}, c{};
    dim(matrix, &r, &c);
    if(r != c)
        throw "error";

    vvf identity(r, vf(c, 0));

    rpt(i , 0, r)
        identity[i][i] = 1;

    vvf result = rref(matrix, identity);
    
    return identity;
}

vvf adjoint(vvf &matrix) {
    int r{}, c{};
    dim(matrix, &r, &c);
    float det = determinant(matrix);
    vvf result = inverse(matrix);
    
    rpt(i ,0, r) {
        rpt(j , 0, c) {
            result[i][j] /= det * result[i][j];
        }
    }

    return result;
}

vf eigenvalues(vvf &matrix) {
    vf result(0);
    


    return result;
}

int main() {
    int r{}, c{};
    cin>>r>>c;
    vvf matrix_i(r, vf(c, 0));

    rpt(i, 0, r) {
        rpt(j, 0, c)
            cin>>matrix_i[i][j];
    };
    cout<<endl;

    vvf result = inverse(matrix_i);

    rpt(i, 0, r) {
        rpt(j, 0, c)
            cout<<matrix_i[i][j]<<" ";
        cout<<endl;
    };
    cout<<endl;

    rpt(i, 0, r) {
        rpt(j, 0, c)
            cout<<result[i][j]<<" ";
        cout<<endl;
    };
    cout<<endl;

    return 0;
}
