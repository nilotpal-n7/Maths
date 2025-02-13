#include "essentials.h"

struct Quaternion{
    float real{}, imag_i{}, imag_j{}, imag_k{};
    Quaternion(float real, float imag_i, float imag_j, float imag_k);
    Quaternion operator=(float a);
    float modulus2();
    float modulus();
    Quaternion conjugate();
    Quaternion unit();
};

const Quaternion i = Quaternion(0, 1, 0, 0);
const Quaternion j = Quaternion(0, 0, 1, 0);
const Quaternion k = Quaternion(0, 0, 0, 1);

Quaternion operator+(float a, Quaternion z);
Quaternion operator+(Quaternion z, float a);
Quaternion operator-(float r, Quaternion z);
Quaternion operator-(Quaternion z, float a);
Quaternion operator*(float a, Quaternion z);
Quaternion operator*(Quaternion z, float a);
Quaternion operator/(Quaternion z, float a);
Quaternion operator/(float a, Quaternion z);
Quaternion operator+(Quaternion a, Quaternion b);
Quaternion operator-(Quaternion a, Quaternion b);
Quaternion operator*(Quaternion a, Quaternion b);
Quaternion operator/(Quaternion a, Quaternion b);

Quaternion stoc(string& s);
bool operator==(Quaternion a, Quaternion b);

ostream& operator<<(ostream& out, Quaternion z);
istream& operator>>(istream& in, Quaternion &z);
