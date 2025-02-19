/*#include <Eigen/Dense> // uncomment this, and check the result

#include <functional>
#include <iostream>
#include <limits>
#include <cmath>

typedef std::function<double(double)> RealFunc;
typedef std::function<double(std::function<double(double)>, double)> RealFuncDerivative;

double FibonacciFunc(double x) {
    return pow(x, 3) + 2.0 * pow(x, 2) + 10.0 * x - 20.0;
}

double derivative(RealFunc f, double x) {
    double h = sqrt(std::numeric_limits<double>::epsilon());
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

double NewtonsMethod(RealFunc f, RealFuncDerivative d, double x0, double precision) {
    double x = x0;
    for (size_t i = 0;; i++) {
        x = x - (f(x) / d(f, x));

        if (abs(f(x)) < precision) {
            return x;
        }
    }
}

int main() {
    RealFunc f{FibonacciFunc};
    RealFuncDerivative d{derivative};

    std::cout << NewtonsMethod(f, d, 1.0, 10e-4) << "\n";
}*/
