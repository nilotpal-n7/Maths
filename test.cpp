#include "essentials.h"

vvf test_fn() {
    vvf test(2, vf(2, 0));

    rpt(i, 0, 2) {
        rpt(j, 0, 2)
            test[i][j] = i + j + 2;
    };

    return test;
}

int main() {
    vvf result = test_fn();

    rpt(i, 0, 2) {
        rpt(j, 0, 2)
            cout<<"r"<<i + 1<<j + 1<<": "<<result[i][j]<<", ";
        cout<<endl;
    };

    return 0;
}
