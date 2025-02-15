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
    rpt(i, 0, r) {
        rpt(j, 0, c)
            cout<<matrix[i][j]<<", ";
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

Matrix Matrix::transpose() {
    Matrix result(c, r);

    rpt(k, 0, r) {
        rpt(j, 0, c)
            result.matrix[j][k] = this->matrix[k][j];
    };

    return result;
}

Matrix Matrix::matrix_conjugate() {
    Matrix result(r, c);

    rpt(k, 0, r) {
        rpt(j, 0, c)
            result.matrix[k][j] = this->matrix[k][j].conjugate();
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

bool isequal(Matrix &matrix1, Matrix &matrix2) {
    int r1{matrix1.r}, c1{matrix1.c}, r2{matrix2.r}, c2{matrix2.c};

    if((r1 != r2) or (c1 != c2))
        return false;

    rpt(k, 0, r1) {
        rpt(j , 0, c2) {
            if(!(matrix1.matrix[k][j] == matrix2.matrix[k][j]))
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
                    sum = sum + (matrix1.matrix[l][k] * matrix2.matrix[k][j]);

                result.matrix[l][j] = sum;
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

int lead_swap(Matrix &matrix, int n, int m, int r, int c) {
    if(!(matrix.matrix[n][m] == 0))
        return 1;
    vc matrix_n = matrix.matrix[n];
    
    rpt(i, n + 1, r) {
        if(!(matrix.matrix[i][m] == 0)) {
            matrix.matrix[n] = matrix.matrix[i];
            matrix.matrix[i] = matrix_n;
            
            return 1;
        };
    };
    return 0;
}

void lead_unity(Matrix &matrix, int n, int m, int r, int c) {
    Complex div = matrix.matrix[n][m];
    
    rpt(i, m, c) 
        matrix.matrix[n][i] = matrix.matrix[n][i] / div;
}

void lead_sub(Matrix &matrix, int n, int m, int r, int c) {
    rpt(i, n + 1, r) {
        Complex sub = matrix.matrix[i][m] / matrix.matrix[n][m];
        
        rpt(j, m, c)
            matrix.matrix[i][j] = matrix.matrix[i][j] - (matrix.matrix[n][j] * sub);
    };
}

void rest_sub(Matrix &matrix, int n, int m, int r, int c) {
    vc zeros(c, Complex(0 ,0));

    rpt(i, n, r) 
        matrix.matrix[i] = zeros;
}

Matrix ref(Matrix &matrix, int n, int m) {
    int r{matrix.r}, c{matrix.c};
    Matrix result = matrix;

    if(n == r)
        return result;
    if(m == c) {
        rest_sub(result, n , m, r, c);
        return result;
    };

    int returned = lead_swap(result, n, m, r, c);

    if(returned) {
        lead_sub(result, n, m, r, c);
        n += 1;
    };

    result = ref(result, n, m + 1);
    return result;
}

Matrix rref(Matrix &matrix) {
    int r{matrix.r}, c{matrix.c};
    Matrix result = ref(matrix, 0, 0);
    vi index(r, -1);

    rpt(i, 0, r) {
        rpt(j, 0, c) {
            if(!(result.matrix[i][j] == Complex(0, 0))) {
                index[i] = j;
                lead_unity(result, i, j, r, c);
                break;
            };
        };
    };

    rpt(i, 1, r) {
        rpt(k, 1, i + 1) {
            if(index[r - k] == -1)
                continue;        
            Complex mul{result.matrix[r - (i + 1)][index[r - k]]};

            rpt(j, index[r - k], c)
                result.matrix[r - (i + 1)][j] = result.matrix[r - (i + 1)][j] - result.matrix[r - k][j] * mul;
        };
    };

    return result;
}
