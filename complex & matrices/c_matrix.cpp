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
    if(r != c) {
        cout<<"Dimension Error: Det(r != c)"<<endl;
        throw 101;
    };
    Complex det(1, 0);
    int swap = 0;

    Matrix t_matrix(r, c);
    t_matrix.matrix = this->matrix;
    Matrix result = ref(t_matrix, swap);

    rpt(j, 0, r) {
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
    if(r != c) {
        cout<<"Dimension Error: Inverse(r != c)"<<endl;
        throw 101;
    };
    Matrix result = identity(r, c);

    Matrix t_matrix(r, c);
    t_matrix.matrix = this->matrix;
    result = rref(t_matrix, result);
    
    return result;
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

Matrix mul(Matrix &matrix1, Matrix &matrix2) {
    int r1{matrix1.r}, c1{matrix1.c}, r2{matrix2.r}, c2{matrix2.c};
    if(c1 != r2) {
        cout<<"Dimension Error: Mul(c1 != r2)"<<endl;
        throw 101;
    };
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

Matrix dot(Matrix &matrix1, Matrix &matrix2) {
    int r1{matrix1.r}, r2{matrix2.r};
    if(r1 != r2) {
        cout<<"Dimension Error: Dot(r1 != r2)"<<endl;
        throw 101;
    };

    Matrix result = matrix1.dagger();
    result = mul(result, matrix2);
        
    return result;
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

Matrix identity(int r, int c, Complex x) {
    Matrix result(r, c);
    if(r != c) {
        cout<<"Dimension Error: Identity(c != r)"<<endl;
        throw 101;
    };

    rpt(i, 0, r)
        result[i][i] = x;

    return result;
}

Complex f(Matrix &matrix, Complex x, vc &sol=dev, double dx=pow(10, -9)) {
    int r{matrix.r}, c{matrix.c};
    Matrix result_e(r, c);
    result_e.matrix = matrix.matrix;
    Matrix iden = identity(r, c, x);

    rpt(j, 0, r) {
        result_e[j][j] = result_e[j][j] - iden[j][j];
    }
    Complex det_f = result_e.determinant();

    rpt(j, 0, sol.size()) {
        if(x == sol[j]) {
            det_f = det_f / ((x + dx) - sol[j]);
        }
        else 
            det_f = det_f / (x - sol[j]);
    };

    return det_f;
}

Complex df_dx(Matrix &matrix, Complex x, double dx=pow(10, -9), vc &sol=dev) {
    Complex df = (f(matrix, x + dx, sol) - f(matrix, x - dx, sol));

    return (df / (2 * dx));
}

Complex x_intercept(Matrix &matrix, Complex x, vc &sol=dev) {
    Complex y = f(matrix, x, sol);
    Complex dy_dx = df_dx(matrix, x, pow(10, -9), sol);

    return (x - (y / dy_dx));
}

vc eigenvalues(Matrix &matrix, Complex x=Complex(0, 0)) {
    int r{matrix.r}, c{matrix.c};
    vc sol(0, Complex(0, 0));
    int n{r};
    double dx = pow(10, -7);

    while(n) {
        while(f(matrix, x, sol).modulus() > dx)
            x = x_intercept(matrix, x, sol);
        
        x = rounder(x, dx);
        sol.push_back(x);
        n -= 1;
    };
    return sol;
}

int main() {
    Matrix matrix(0, 0);
    matrix.print();
    vc result = eigenvalues(matrix, Complex(0, 0));
    for(Complex x: result)
        cout<<x<<", ";

    cin.get();
    return 0;
}
