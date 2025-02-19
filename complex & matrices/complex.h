#include "essentials.h"

struct Complex {
    double real{}, imag{};
    Complex(double real=0, double imag=0);
    Complex operator=(double r);
    double modulus2();
    double modulus();
    double phase();
    Complex conjugate();
    void round();
};

const Complex i = Complex(0, 1);

Complex operator+(double a, Complex z);
Complex operator+(Complex z, double a);
Complex operator-(double r, Complex z);
Complex operator-(Complex z, double a);
Complex operator*(double a, Complex z);
Complex operator*(Complex z, double a);
Complex operator/(Complex z, double a);
Complex operator/(double a, Complex z);
Complex operator+(Complex a, Complex b);
Complex operator-(Complex a, Complex b);
Complex operator*(Complex a, Complex b);
Complex operator/(Complex a, Complex b);

Complex stoc(string& s);
bool operator==(Complex a, Complex b);

ostream& operator<<(ostream& out, Complex z);
istream& operator>>(istream& in, Complex &z);
Complex rounder(Complex x, float dx=pow(10, -7));
