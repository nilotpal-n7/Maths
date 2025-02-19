#include "complex.h"

Complex::Complex(double real, double imag) {
    this->real = real;
    this->imag = imag;
};

Complex Complex::operator=(double a) {
    this->real = a;
    this->imag = 0;
    return Complex(this->real, this->imag);
};

double Complex::modulus2() {
    return ((this->real * this->real) + (this->imag * this->imag));
};

double Complex::modulus() {
    return sqrt(this->modulus2());
};

double Complex::phase() {
    return atan2(this->imag, this->real);
};

Complex Complex::conjugate() {
    return Complex(this->real, -1 * this->imag);
};

void Complex::round() {
    int r = this->real;
    int k = this->imag;

    if(abs(this->real - r) < pow(10, -3))
        this->real = r;
    if(abs(this->imag - k) < pow(10, -3))
        this->imag = k;
}

Complex operator+(double a, Complex z) {
    return Complex(z.real + a, z.imag);
}

Complex operator+(Complex z, double a) {
    return Complex(z.real + a, z.imag);
}

Complex operator-(double r, Complex z) {
    return Complex(z.real - r, -1 * z.imag);
}

Complex operator-(Complex z, double a) {
    return Complex(z.real - a, z.imag);
}

Complex operator*(double a, Complex z) {
    return Complex(z.real * a, z.imag * a);
}

Complex operator*(Complex z, double a) {
    return Complex(z.real * a, z.imag * a);
}

Complex operator/(Complex z, double a) {
    return Complex(z.real / a, z.imag / a);
}

Complex operator/(double a, Complex z) {
    return (a * z.conjugate() / z.modulus2());
}

Complex operator+(Complex a, Complex b) {
    return Complex(a.real + b.real, b.imag + a.imag);
}

Complex operator-(Complex a, Complex b) {
    return Complex(a.real - b.real, a.imag - b.imag);
}

Complex operator*(Complex a, Complex b) {
    return Complex((a.real * b.real) - (a.imag * b.imag), (a.real * b.imag) + (a.imag * b.real));
}

Complex operator/(Complex a, Complex b) {
    return (a * b.conjugate() / b.modulus2());
}

bool operator==(Complex a, Complex b) {
    if((a.real == b.real) and (a.imag == b.imag))
        return true;
    else
        return false;
}

Complex stoc(string& s) {
    int s_len = s.size();
    int index{s_len};
    string real = "", imag = "";

    rpt(j, 0, s_len) {
        if(s[j] == 'i') {
            index = j;
            break;
        };

        real += s[j];
    };

    if(index < s_len - 2) {
        rpt(j, index + 2, s_len)
            imag += s[j];
    };

    if(index == (s_len - 1))
        imag ="1";
    if(imag == "")
        imag = "0";
    if(real == "")
        real = "0";

    return Complex(stof(real), stof(imag));
}

ostream& operator<<(ostream& out, Complex z) {
    cout<<z.real<<" + "<<z.imag<<"i";
    return out;
};

istream& operator>>(istream& in, Complex &z) {
    string z_c = "";
    cin>>z_c;

    z = stoc(z_c);
    return in;
};

Complex rounder(Complex x, float dx) {
    if(abs(x.real - floor(x.real)) < dx)
        x.real = floor(x.real);
    else if(abs(x.real - ceil(x.real)) < dx)
        x.real = ceil(x.real);

    if(abs(x.imag - floor(x.imag)) < dx)
        x.imag = floor(x.imag);
    else if(abs(x.imag - ceil(x.imag)) < dx)
        x.imag = ceil(x.imag);
    
    return x;
}
