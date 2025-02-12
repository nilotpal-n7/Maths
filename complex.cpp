#include "essentials.h"
#include "complex.h"

Complex::Complex(float real, float imag) {
    this->real = real;
    this->imag = imag;
};

Complex Complex::operator=(float r) {
    this->real = r;
    return Complex(real, imag);
};

float Complex::modulus2() {
    return ((this->real * this->real) + (this->imag * this->imag));
};

float Complex::modulus() {
    return sqrt(modulus2());
};

float Complex::phase() {
    return atan2(this->imag, this->real);
};

Complex Complex::conjugate() {
    return Complex(this->real, -1 * this->imag);
};

Complex operator+(float a, Complex z) {
    return Complex(z.real + a, z.imag);
}

Complex operator+(Complex z, float a) {
    return Complex(z.real + a, z.imag);
}

Complex operator-(float r, Complex z) {
    return Complex(z.real - r, -1 * z.imag);
}

Complex operator-(Complex z, float a) {
    return Complex(z.real - a, z.imag);
}

Complex operator*(float a, Complex z) {
    return Complex(z.real * a, z.imag * a);
}

Complex operator*(Complex z, float a) {
    return Complex(z.real * a, z.imag * a);
}

Complex operator/(Complex z, float a) {
    return Complex(z.real / a, z.imag / a);
}

Complex operator/(float a, Complex z) {
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
        if(s[j] == '+') {
            index = j;
            break;
        };

        real += s[j];
    };

    if(index < s_len - 3) {
        rpt(j, index + 3, s_len)
            imag += s[j];
    };

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
