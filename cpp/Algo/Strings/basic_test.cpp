#include <bits/stdc++.h>

using namespace std;

#include "basic.h"

bool basicTestZFunction() {
    assert(zFunction("aaaaaa") == vector<int>({0, 5, 4, 3, 2, 1}));
    assert(zFunction("aabaacd") == vector<int>({0, 1, 0, 2, 1, 0, 0}));
    assert(zFunction("abababab") == vector<int>({0, 0, 6, 0, 4, 0, 2, 0}));
    cout << "Basic Z-function OK" << endl;
}

int main() {
    basicTestZFunction();
}
