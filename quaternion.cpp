#include "quaternion.h"

Quaternion::Quaternion(float real, float imag, float imag_j, float imag_k) {
    this->real = real;
    this->imag_i = imag_i;
    this->imag_j = imag_j;
    this->imag_k = imag_k;
};

Quaternion Quaternion::operator=(float a) {
    this->real = a;
    this->imag_i = 0;
    this->imag_j = 0;
    this->imag_k = 0;
    return Quaternion(this->real, this->imag_i, this->imag_j, this->imag_k);
}

float Quaternion::modulus2() {
    return ((this->real * this->real) + (this->imag_i * this->imag_i) + (this->imag_j * this->imag_j) + (this->imag_k * this->imag_k));
};

float Quaternion::modulus() {
    return sqrt(modulus2());
};

Quaternion Quaternion::conjugate() {
    return Quaternion(this->real, -this->imag_i, -this->imag_j, -this->imag_k);
};

Quaternion Quaternion::unit() {
    return (Quaternion(this->real, this->imag_i, this->imag_j, this->imag_k) / modulus());
}






Quaternion operator+(float a, Quaternion z) {
    return Quaternion(z.real + a, z.imag_i, z.imag_j, z.imag_k);
}

Quaternion operator+(Quaternion z, float a) {
    return Quaternion(z.real + a, z.imag_i, z.imag_j, z.imag_k);
}

Quaternion operator-(float r, Quaternion z) {
    return Quaternion(z.real - r, -z.imag_i, -z.imag_j, -z.imag_k);
}

Quaternion operator-(Quaternion z, float a) {
    return Quaternion(z.real - a, z.imag_i, z.imag_j, z.imag_k);
}

Quaternion operator*(float a, Quaternion z) {
    return Quaternion(z.real * a, z.imag_i * a, z.imag_j * a, z.imag_k * a);
}

Quaternion operator*(Quaternion z, float a) {
    return Quaternion(z.real * a, z.imag_i * a, z.imag_j * a, z.imag_k * a);
}

Quaternion operator/(Quaternion z, float a) {
    return Quaternion(z.real / a, z.imag_i / a, z.imag_j / a, z.imag_k /a);
}

Quaternion operator/(float a, Quaternion z) {
    return (a * z.conjugate() / z.modulus2());
}

Quaternion operator+(Quaternion a, Quaternion b) {
    return Quaternion(a.real + b.real, a.imag_i + b.imag_i, a.imag_j + b.imag_j, a.imag_k + b.imag_k);
}

Quaternion operator-(Quaternion a, Quaternion b) {
    return Quaternion(a.real - b.real, a.imag_i - b.imag_i, a.imag_j - b.imag_j, a.imag_k - b.imag_k);
}

Quaternion operator*(Quaternion a, Quaternion b) {
    return Quaternion((a.real * b.real) - (a.imag * b.imag), (a.real * b.imag) + (a.imag * b.real));
}

Quaternion operator/(Quaternion a, Quaternion b) {
    return (a * b.conjugate() / b.modulus2());
}

bool operator==(Quaternion a, Quaternion b) {
    if((a.real == b.real) and (a.imag_i == b.imag_j) and (a.imag_j == b.imag_j) and (a.imag_k == b.imag_k))
        return true;
    else
        return false;
}

Quaternion stoc(string& s) {
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

    return Quaternion(stof(real), stof(imag_i), stof(imag_j), stof(imag_k));
}

ostream& operator<<(ostream& out, Quaternion z) {
    cout<<z.real<<" + "<<z.imag_i<<"i + "<<z.imag_j<<"j + "<<z.imag_k<<"k";
    return out;
};

istream& operator>>(istream& in, Quaternion &z) {
    string z_c = "";
    cin>>z_c;

    z = stoc(z_c);
    return in;
};


int main() {
    return 0;
}
