#include "matrix.h"
#include "complex.h"
#include "quaternion.h"

int main() {
    int N{}, M{};
    cin>>N>>M;
    vvf matrix(N, vf(M, 0));
    //4 5 1 3 3 8 5 0 1 3 10 8 0 0 0 -1 -4 0 0 0 2 8
    matrix_init(matrix);
    print_matrix(matrix);
    vvf result = rref(matrix);
    print_matrix(result);
    result = dot(matrix, result);

    Complex c1 = (2.01 + i*-3.5) * (2.01 + i*3);
    cout<<c1<<"\nPhase: "<<c1.phase()<<endl;
    cin>>c1;
    cout<<c1<<"\nPhase: "<<c1.conjugate()<<endl;

    Quaternion c2 = (2.01 + q*-3.5 + j*2.3 + k*-3.33) * (2.01 + q*3 + j*3.2 + k*-3);
    cout<<c2<<"\nPhase: "<<c2.unit()<<endl;
    cin>>c2;
    cout<<c2<<"\nPhase: "<<c2.conjugate()<<endl;

    cin.get();
    return 0;
}
