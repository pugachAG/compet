#include <bits/stdc++.h>

using namespace std;

#include "eratosthenes.h"

void basicMobiusFunctionTest() {
    Eratosthenes e(1000);
    assert(e.mobius(1) == 1);
    assert(e.mobius(2) == -1);
    assert(e.mobius(3) == -1);
    assert(e.mobius(4) == 0);
    assert(e.mobius(5) == -1);
    assert(e.mobius(6) == 1);
    cout << "Baisc Mobius function OK" << endl;
}


bool randTestPrimeFactorizeFlat() {
    const int MX = 1e6;
    const int QUERIES = 1e6;
    Eratosthenes e(MX);
    for (int q = 0; q < QUERIES; q++) {
        int k = 1 + rand()%MX;
        auto vec = e.primeFactorizeFlat(k);
        int num = 1;
        for (int v: vec) {
            num *= v;
        }
        if (num != k) {
            cout << "failed to factorize " << k << endl;
            return false;
        }
    }
    cout << "Prime factorization OK" << endl;
    return true;
}

vector<int> allDivsNaive(int k) {
    set<int> res;
    for (int d = 1; d <= k; d++) {
        if (k%d == 0) {
            res.insert(d);
        }
    }
    return vector<int>(res.begin(), res.end());
}

bool randTestAllDivs() {
    const int MX = 1e1;
    const int QUERIES = 1e3;
    Eratosthenes e(MX);
    for (int q = 0; q < QUERIES; q++) {
        int k = 1 + rand()%MX;
        auto actual = e.allDivs(k);
        auto expected = allDivsNaive(k);
        if (actual != expected) {
            cout << "failed get all divisors for " << k << endl;
            cout << "expected: " ;
            for (int v: expected) {
                cout << v << " ";
            }
            cout << endl;
            cout << "actual: ";
            for (int v: actual) {
                cout << v << " ";
            }
            cout << endl;
            return false;
        }
    }
    cout << "Get all divisors OK" << endl;
    return true;
}


int main() {
    randTestPrimeFactorizeFlat();
    basicMobiusFunctionTest();
    randTestAllDivs();
}

