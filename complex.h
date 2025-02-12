#include "essentials.h"

struct Complex {
    float real{}, imag{};
    Complex(float real, float imag);
    Complex operator=(float r);
    float modulus2();
    float modulus();
    float phase();
    Complex conjugate();
};

const Complex i = Complex(0, 1);

Complex operator+(float a, Complex z);
Complex operator+(Complex z, float a);
Complex operator-(float r, Complex z);
Complex operator-(Complex z, float a);
Complex operator*(float a, Complex z);
Complex operator*(Complex z, float a);
Complex operator/(Complex z, float a);
Complex operator/(float a, Complex z);
Complex operator+(Complex a, Complex b);
Complex operator-(Complex a, Complex b);
Complex operator*(Complex a, Complex b);
Complex operator/(Complex a, Complex b);

Complex stoc(string& s);
bool operator==(Complex a, Complex b);

ostream& operator<<(ostream& out, Complex z);
istream& operator>>(istream& in, Complex &z);
