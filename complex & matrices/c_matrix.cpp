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

Matrix dot(Matrix &matrix1, Matrix &matrix2) {
    int r1{matrix1.r}, r2{matrix2.r};
    if(r1 != r2) {
        cout<<"Dimension Error: Dot(r1 != r2)"<<endl;
        throw 101;
    };

    Matrix result = matrix1.dagger();
    result = result * matrix2;
        
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

vc eigenvalues(Matrix &matrix, Complex x) {
    int r{matrix.r}, c{matrix.c};
    vc sol(0, Complex(0, 0));
    int n{r};
    double dx = pow(10, -7);

    while(n) {
        while(f(matrix, x, sol).modulus() > dx)
            x = x_intercept(matrix, x, sol);
        
        sol.push_back(x.round(dx));
        n -= 1;
    };
    return sol;
}

int Matrix::rank() {
    int r(this->r), c(this->r);
    int result{};
    Matrix t_matrix(r, c);
    t_matrix.matrix = this->matrix;
    Matrix rref_r = rref(t_matrix);

    rpt(x, 0, r) {
        rpt(j, 0, c) {
            if(rref_r[x][j] == Complex(1, 0))
                result++;
        };
    };

    return result;
}

int rref_rank(Matrix &matrix) {
    int r(matrix.r), c(matrix.r);
    int result{};

    rpt(x, 0, r) {
        rpt(j, 0, c) {
            if(matrix[x][j] == Complex(1, 0))
                result++;
        };
    };

    return result;
}

Matrix asker(int r, int c) {
    cout<<"n ";
    rpt(j, 0, c)
        cout<<"x"<<j + 1<<" ";
    cout<<":val"<<endl;

    Matrix aug_matrix(r, c + 1);

    rpt(j, 0, r) {
        cout<<j + 1<<" ";
        rpt(k, 0, c + 1) {
            cin>>aug_matrix[j][k];
            cout<<" ";
        };
        cout<<endl;
    }; 

    return aug_matrix;
}

Matrix solver(Matrix &matrix) {
    int r{matrix.r}, c{matrix.c - 1};
    Matrix aug_matrix = matrix;

    if(matrix == defm) {
        cout<<"r, c: ";
        cin>>r>>c;

        Matrix aug_matrix = asker(r, c);
    };

    Matrix rref_s = rref(aug_matrix);
    Matrix coeff_matrix(r, c);

    rpt(j, 0, r) {
        rpt(k, 0, c)
            coeff_matrix[j][k] = aug_matrix[j][k];
    };

    int aug_rank = rref_rank(rref_s);
    int coeff_rank = coeff_matrix.rank();

    if(aug_rank != coeff_rank) {
        cout<<"Linear Symstem is inconsistant!"<<endl;
        throw 101;
    };

    Matrix max_sq(c, c + 1);
    rpt(j, 0, r) {
        rpt(k, 0, c + 1)
            max_sq[j][k] = rref_s[j][k];
    };

    vvc sol(1, vc(c, Complex(0, 0)));
    rpt(j, 0, c)
        sol[0][j] = rref_s[j][c].round();

    rpt(j, 0, c) {
        if(max_sq[j][j] == Complex(0, 0)) {
            vc push(0, Complex(0, 0));
            rpt(k, 0, c)
                push.push_back(-1 * max_sq[k][j]);
            push[j] = 1;
            sol.push_back(push);
        };
    };

    Matrix result(sol.size(), c);
    result.matrix = sol;

    return result;
}

Matrix eigenvec(Matrix &matrix) {
    int r{matrix.r}, c{matrix.c};
    vc eigval = eigenvalues(matrix);
    vvc e_vec(0, vc(c, Complex(0, 0)));

    rpt(x, 0, eigval.size()) {
        Matrix id = identity(r, c, eigval[x]);
        Matrix e_aug(r, c + 1);

        rpt(j, 0, r) {
            rpt(k, 0, c)
                e_aug[j][k] = matrix[j][k] - id[j][k];
        };

        Matrix sol = solver(e_aug);
        rpt(j, 1, sol.matrix.size()) {
            e_vec.push_back(sol[j]);
        }
    };

    if(e_vec.size() == 0){
        cout<<"No. Error: Eig(No eiganvalue exist!)"<<endl;
        Matrix result(1, c);
        return result;
    }

    Matrix result(e_vec.size(), c);
    result.matrix = e_vec;
    return result;
}

Matrix Matrix::operator+(Matrix matrix0) {
    int r{this->r}, c{this->c};
    int r0{matrix0.r}, c0{matrix0.c};
    if(r0 != r or c0 != c) {
        cout<<"Dimension Error: +(r1 != r2 or c1 != c2)";
        throw 101;
    };

    Matrix result(r, c);
    rpt(j, 0, r) {
        rpt(k, 0, c)
            result[j][k] = this->matrix[j][k] + matrix0[j][k];
    };

    return result;
}

Matrix Matrix::operator-(Matrix matrix0) {
    int r{this->r}, c{this->c};
    int r0{matrix0.r}, c0{matrix0.c};
    if(r0 != r or c0 != c) {
        cout<<"Dimension Error: -(r1 != r2 or c1 != c2)";
        throw 101;
    };

    Matrix result(r, c);
    rpt(j, 0, r) {
        rpt(k, 0, c)
            result[j][k] = this->matrix[j][k] - matrix0[j][k];
    };

    return result;
}

Matrix Matrix::operator*(Matrix matrix0) {
    int r{this->r}, c{this->c};
    int r0{matrix0.r}, c0{matrix0.c};
    if(c != r0) {
        cout<<"Dimension Error: *(c1 != r2)"<<endl;
        throw 101;
    };

    Matrix result(r, c0);
    rpt(l, 0, r) {
        rpt(j, 0, c0) {
            Complex sum(0, 0);

            rpt(k, 0, c0)
                sum = sum + (this->matrix[l][k] * matrix0[k][j]);
            result[l][j] = sum;
        };
    };

    return result;
}

/*Matrix Matrix::operator/(Matrix matrix0) {
    Matrix it(this->r, this->c);
    it.matrix = this->matrix;
    Matrix inv = matrix0.inverse();
    Matrix result = this->matrix * inv;
    return result;
}*/


int main() {
    Matrix matrix(0, 0);
    matrix.print();

    Matrix result = ref(matrix);
    result.print();

    cin.get();
    return 0;
}
