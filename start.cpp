#include "c_matrix.h"

int main() {
    Matrix matrix(0, 0);
    matrix.print();
    Matrix result = rref(matrix);
    result.print();
    result = matrix.transpose();
    result.print();
    
    try{
        result = dot(matrix, matrix);
        result.print();
    }
    catch(const char *err) {
        cout<<"Error-> "<<err<<"\n"<<endl;
    };

    cin.get();
    return 0;
}
