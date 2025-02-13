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
    Quaternion v(this->real, this->imag_i, this->imag_j, this->imag_k);
    return sqrt(v.modulus2());
};

Quaternion Quaternion::conjugate() {
    return Quaternion(this->real, -this->imag_i, -this->imag_j, -this->imag_k);
};

Quaternion Quaternion::unit() {
    Quaternion v(this->real, this->imag_i, this->imag_j, this->imag_k);
    return (v / v.modulus());
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
    return Quaternion(a.real * b.real - a.imag_i * b.imag_i - a.imag_j * b.imag_j - a.imag_k * b.imag_k,
        a.real * b.imag_i + a.imag_i * b.real + a.imag_j * b.imag_k - a.imag_k * b.imag_j,
        a.real * b.imag_j + a.imag_j * b.real + a.imag_k * b.imag_i - a.imag_i * b.imag_k,
        a.real * b.imag_k + a.imag_k * b.real + a.imag_i * b.imag_j - a.imag_j * b.imag_i);
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

Quaternion stoq(string& s) {
    int s_len = s.size(), w{0};
    int index[3] = {s_len};
    string real = "", imag_i = "", imag_j = "", imag_k = "";

    rpt(x, 0, s_len) {
        if(s[x] == '+') {
            index[w] = x;
            w++;
            if(w == 3)
                break;
        };

        real += s[x];
    };

    if(index[0] < s_len - 3) {
        rpt(x, index[0] + 3, index[1] + 1)
            imag_i += s[x];
    };

    if(index[1] < s_len - 3) {
        rpt(x, index[1] + 3, index[2] + 1)
            imag_j += s[x];
    };

    if(index[2] < s_len - 3) {
        rpt(x, index[2] + 3, s_len)
            imag_k += s[x];
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

    z = stoq(z_c);
    return in;
};
