#include "c_matrix.h"

Matrix::Matrix(int r, int c) {
    this->r = r;
    this->c = c;
    this->matrix = vvc(r, vc(c, Complex(0, 0)));

    if((r == 0) or (c == 0))
        _init_();
};

void Matrix::_init_() {
    cout<<"r, c: ";
    cin>>this->r>>this->c;
    cout<<endl;
    this->matrix = vvc(r, vc(c, Complex(0, 0)));
    Complex x(0, 0);

    rpt(k, 0, r) {
        rpt(j, 0, c) {
            cout<<"a"<<k + 1<<j + 1<<": ";
            cin>>x;
            this->matrix[k][j] = x;
        };
    };

    cout<<"\n"<<endl;
}

void Matrix::print() {
    //std::cout << std::setprecision(2) << std::fixed;

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            matrix[i][j].round();
            cout<<matrix[i][j]<<", ";
        };

        cout<<endl;
    };
    cout<<endl;
};

int Matrix::dim_r() {
    return this->r;
}

int Matrix::dim_c() {
    return this->c;
}

string Matrix::dim() {
    string d = "r: " + to_string(this->r) + "c: " + to_string(this->c);
    return d;
}

vc &Matrix::operator[](int j) {
    return this->matrix[j];
};

Matrix Matrix::transpose() {
    Matrix result(c, r);

    rpt(k, 0, r) {
        rpt(j, 0, c)
            result[j][k] = this->matrix[k][j];
    };

    return result;
}

Matrix Matrix::matrix_conjugate() {
    Matrix result(r, c);

    rpt(k, 0, r) {
        rpt(j, 0, c)
            result[k][j] = this->matrix[k][j].conjugate();
    };

    return result;
}

Matrix Matrix::dagger() {
    Matrix result(r, c);
    result.matrix = this->matrix;
    result = result.transpose();
    result = result.matrix_conjugate();

    return result;
}

Complex Matrix::determinant() {
    int r{this->r}, c{this->c};

    if(r != c)
        throw "error";

    Complex det(1, 0);
    vi index(r, -1);
    int swap = 0;

    Matrix t_matrix(r, c);
    t_matrix.matrix = this->matrix;
    Matrix result = ref(t_matrix, swap);
    cout<<"swap: "<<swap<<endl;

    rpt(k, 0, r) {
        rpt(j, 0, c) {
            if(!(result[k][j] == 0)) {
                index[k] = j;
                break;
            };
        };
    };

    rpt(j, 0, r) {
        if(index[j] == -1)
            throw "error";
        det = det * result[j][j];

        if(result[j][j] == 0)
            break;
    };

    if(swap & 1)
        det = -1 * det;

    return det;
}

Matrix Matrix::inverse() {
    int r{this->r}, c{this->c};
    if(r != c)
        throw "error";

    Matrix identity(r, c);

    rpt(i , 0, r)
        identity.matrix[i][i] = 1;

    Matrix t_matrix(r, c);
    t_matrix.matrix = this->matrix;
    Matrix result = rref(t_matrix, identity);
    
    return identity;
}

Matrix Matrix::adjoint() {
    int r{this->r}, c{this->c};

    Complex det = this->determinant();
    Matrix result = this->inverse();
    
    rpt(i ,0, r) {
        rpt(j , 0, c) {
            result[i][j] = result[i][j] / (det * result[i][j]);
        }
    }

    return result;
}

bool operator==(Matrix &matrix1, Matrix &matrix2) {
    return (&matrix1 == &matrix2);
}

bool isequal(Matrix &matrix1, Matrix &matrix2) {
    int r1{matrix1.r}, c1{matrix1.c}, r2{matrix2.r}, c2{matrix2.c};

    if((r1 != r2) or (c1 != c2))
        return false;

    rpt(k, 0, r1) {
        rpt(j , 0, c2) {
            if(!(matrix1[k][j] == matrix2[k][j]))
                return false;
        };
    };

    return true;
}

Matrix matrix_mul(Matrix &matrix1, Matrix &matrix2) {
    int r1{matrix1.r}, c1{matrix1.c}, r2{matrix2.r}, c2{matrix2.c};

    if(c1 == r2) {
        Matrix result(r1, c2);

        rpt(l, 0, r1) {
            rpt(j, 0, c2) {
                Complex sum(0, 0);
                rpt(k, 0, c1)
                    sum = sum + (matrix1[l][k] * matrix2[k][j]);

                result[l][j] = sum;
            };
        };

        return result;
    }
    else
        throw "Dimension Error: Mul(c1 != r2)";
}

Matrix dot(Matrix &matrix1, Matrix &matrix2) {
    int r1 = matrix1.r;
    int r2 = matrix2.r;

    if(r1 == r2) {
        Matrix result = matrix1.dagger();
        result = matrix_mul(result, matrix2);
        
        return result;
    }
    else
        throw "Dimension Error: Dot(r1 != r2)";
}

int lead_swap(Matrix &matrix, int n, int m, int r, int c, int &swap=defi, Matrix &id=defm) {
    if(!(matrix.matrix[n][m] == 0))
        return 1;
    
    rpt(k, n + 1, r) {
        if(!(matrix.matrix[k][m] == 0)) {
            vc matrix_n = matrix.matrix[n];
            matrix.matrix[n] = matrix.matrix[k];
            matrix.matrix[k] = matrix_n;

            if(!(id == defm)){
                vc id_n = id[n];
                id[n] = id[k];
                id[k] = id_n;
            };

            if(swap != defi)
                swap++;
            return 1;
        };
    };

    return 0;
}

void lead_sub(Matrix &matrix, int n, int m, int r, int c, Matrix &id=defm) {
    rpt(k, n + 1, r) {
        Complex sub = matrix.matrix[k][m] / matrix.matrix[n][m];
        
        rpt(j, 0, c) {
            matrix.matrix[k][j] = matrix.matrix[k][j] - (matrix.matrix[n][j] * sub);
            if(!(id == defm))
                id[k][j] = id[k][j] - (id[n][j] * sub);
        };
    };
}

void rest_sub(Matrix &matrix, int n, int m, int r, int c, Matrix &id=defm) {
    vc zeros(c, Complex(0 ,0));

    rpt(j, n, r) {
        matrix.matrix[j] = zeros;
        if(!(id == defm))
            id[j] = zeros;
    };
}

Matrix ref(Matrix &matrix, int &swap, Matrix &id, int n, int m) {
    int r{matrix.r}, c{matrix.c};
    Matrix result = matrix;

    if(n == r)
        return result;
    if(m == c) {
        rest_sub(result, n , m, r, c);
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

Matrix rref(Matrix &matrix, Matrix &id) {
    int r{matrix.r}, c{matrix.c};
    Matrix result = ref(matrix, defi, id);
    vi index(r, -1);

    rpt(x, 0, r) {
        rpt(j, 0, c) {
            if(!(result[x][j] == Complex(0, 0))) {
                index[x] = j;
                Complex div = result[x][j];

                rpt(k, 0, c) {
                    result[x][k] = result[x][k] / div;
                    if(!(id == defm))
                        id[x][k] = id[x][k] / div;
                };
                
                break;
            };
        };
    };

    rpt(x, 1, r) {
        rpt(k, 1, x + 1) {
            if(index[r - k] == -1)
                continue;        
            Complex mul{result[r - (x + 1)][index[r - k]]};

            rpt(j, 0, c) {
                result[r - (x + 1)][j] = result[r - (x + 1)][j] - (result[r - k][j] * mul);
                if(!(id == defm))
                    id[r - (x + 1)][j] = id[r - (x + 1)][j] - (id[r - k][j] * mul);
            };
        };
    };

    return result;
}

int main() {
    Matrix matrix(0, 0);
    matrix.print();
    Matrix result = matrix.inverse();
    result.print();
    result = matrix_mul(matrix, result);
    result.print();

    cin.get();
    return 0;
}
