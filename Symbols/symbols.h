#include "essentials.h"

class Symbols {
    public:
        string symbol = "";
        Symbols(string symbol);
        void operator=(string s);
        float evaluate(float n1, float n2);

};

Symbols operator+(Symbols s1, Symbols s2);
Symbols operator-(Symbols s1, Symbols s2);
Symbols operator*(Symbols s1, Symbols s2);
Symbols operator/(Symbols s1, Symbols s2);
Symbols operator+(float s1, Symbols s2);
Symbols operator-(float s1, Symbols s2);
Symbols operator*(float s1, Symbols s2);
Symbols operator/(float s1, Symbols s2);
Symbols operator+(Symbols s1, float s2);
Symbols operator-(Symbols s1, float s2);
Symbols operator*(Symbols s1, float s2);
Symbols operator/(Symbols s1, float s2);
Symbols operator+(int s1, Symbols s2);
Symbols operator-(int s1, Symbols s2);
Symbols operator*(int s1, Symbols s2);
Symbols operator/(int s1, Symbols s2);
Symbols operator+(Symbols s1, int s2);
Symbols operator-(Symbols s1, int s2);
Symbols operator*(Symbols s1, int s2);
Symbols operator/(Symbols s1, int s2);
ostream& operator<<(ostream& out, Symbols &s);
