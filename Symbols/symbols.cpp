#include "symbols.h"

Symbols::Symbols (string symbol) {
    this->symbol = symbol;
}

void Symbols::operator=(string s) {
    this->symbol = s;
}

bool check(char c) {
    char num[10] = {'0','1','2','3','4','5','6','7','8','9'};

    rpt(i, 0, 10) {
        if(c == num[i])
            return true;
    }
    return false;
}

float p_solver(string &s, int i1, int i2) {
    
}

float Symbols::evaluate(float n1, float n2) {
    rpt(i, 0, symbol.length()) {
        if(symbol[i] == 'x')
            symbol[i] = n1;
        else if(symbol[i] == 'y')
            symbol[i] = n2;
    }
    
    float sum{};

    rpt(i, 0, symbol.length()) {
        if(check(symbol[i])) {
            sum += symbol[i] - '0';
        }
    }

    return stof(symbol);
}

Symbols operator+(Symbols s1, Symbols s2) {
    return Symbols(s1.symbol + " + " + s2.symbol);
}

Symbols operator-(Symbols s1, Symbols s2) {
    return Symbols(s1.symbol + " - " + s2.symbol);
}

Symbols operator*(Symbols s1, Symbols s2) {
    return Symbols(s1.symbol + "*" + s2.symbol);
}

Symbols operator/(Symbols s1, Symbols s2) {
    return Symbols(s1.symbol + "/" + s2.symbol);
}

Symbols operator+(float s1, Symbols s2) {
    return Symbols(to_string(s1) + " + " + s2.symbol);
}

Symbols operator-(float s1, Symbols s2) {
    return Symbols(to_string(s1) + " - " + s2.symbol);
}

Symbols operator*(float s1, Symbols s2) {
    return Symbols(to_string(s1) + "*" + s2.symbol);
}

Symbols operator/(float s1, Symbols s2) {
    return Symbols(to_string(s1) + "/" + s2.symbol);
}

Symbols operator+(Symbols s1, float s2) {
    return Symbols(s1.symbol + " + " + to_string(s2));
}

Symbols operator-(Symbols s1, float s2) {
    return Symbols(s1.symbol + " - " + to_string(s2));
}

Symbols operator*(Symbols s1, float s2) {
    return Symbols(s1.symbol + "*" + to_string(s2));
}

Symbols operator/(Symbols s1, float s2) {
    return Symbols(s1.symbol + "/" + to_string(s2));
}

Symbols operator+(int s1, Symbols s2) {
    return Symbols(to_string(s1) + " + " + s2.symbol);
}

Symbols operator-(int s1, Symbols s2) {
    return Symbols(to_string(s1) + " - " + s2.symbol);
}

Symbols operator*(int s1, Symbols s2) {
    return Symbols(to_string(s1) + "*" + s2.symbol);
}

Symbols operator/(int s1, Symbols s2) {
    return Symbols(to_string(s1) + "/" + s2.symbol);
}

Symbols operator+(Symbols s1, int s2) {
    return Symbols(s1.symbol + " + " + to_string(s2));
}

Symbols operator-(Symbols s1, int s2) {
    return Symbols(s1.symbol + " - " + to_string(s2));
}

Symbols operator*(Symbols s1, int s2) {
    return Symbols(s1.symbol + "*" + to_string(s2));
}

Symbols operator/(Symbols s1, int s2) {
    return Symbols(s1.symbol + "/" + to_string(s2));
}

ostream& operator<<(ostream& out, Symbols &s) {
    cout<<s.symbol;
    return out;
}





int main() {
    Symbols x("x");
    Symbols y("y");
    Symbols z = x * y + x;
    z = z + 2;
    cout<<z<<endl;
    float e = z.evaluate(1, 1);
    cout<<e<<endl;

    cin.get();
    return 0;
}
