#include <bits/stdc++.h>

using namespace std;

#include "fft.h"

const long long MOD = 1e9 + 7;

vector<long long> multiplyNaive(vector<long long> a, vector<long long> b) {
    int n = a.size(), m = b.size();
    vector<long long> res(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i+j] += a[i] * b[j];
        }
    }
    return res;
}

vector<long long> multiplyModNaive(vector<long long> a, vector<long long> b) {
    int n = a.size(), m = b.size();
    vector<long long> res(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            auto &cur = res[i+j];
            cur = (cur + a[i] * b[j] % MOD) % MOD;
        }
    }
    return res;
}

void printVec(const vector<long long> &a) {
    int n = a.size();
    cout << "size: " << n << ", elements: ";
    for (int i = 0; i < min(n, 30); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void checkMultiply(vector<long long> a, vector<long long> b) {
    auto expected = multiplyNaive(a, b);
    auto actual = FFT<double>::multiply(a, b);
    if (expected != actual) {
        cout << "Failed for:" << endl;
        printVec(a);
        printVec(b);
        cout << "Expected:" << endl;
        printVec(expected);
        cout << "Actual:" << endl;
        printVec(actual);
        assert(0);
    }
}

void checkSquare(vector<long long> a) {
    auto expected = multiplyNaive(a, a);
    auto actual = FFT<double>::square(a);
    if (expected != actual) {
        cout << "Failed for:" << endl;
        printVec(a);
        cout << "Expected:" << endl;
        printVec(expected);
        cout << "Actual:" << endl;
        printVec(actual);
        assert(0);
    }
}

void checkMultiplyMod(vector<long long> a, vector<long long> b) {
    auto expected = multiplyModNaive(a, b);
    auto actual = FFT<double>::multiplyMod(a, b, MOD);
    if (expected != actual) {
        cout << "Failed for:" << endl;
        printVec(a);
        printVec(b);
        cout << "Expected:" << endl;
        printVec(expected);
        cout << "Actual:" << endl;
        printVec(actual);
        assert(0);
    }
}

void basicMultiplyTest() {
    checkMultiply({2}, {3});
    checkMultiply({3, 1}, {2});
    checkMultiply({1, 2}, {2, 3});
    cout << "Basic multiply tests OK" << endl;
}

void basicMultiplyModTest() {
    const long long BIL = 1e9;
    checkMultiplyMod({2}, {3});
    checkMultiplyMod({1, 2}, {2, 3});
    checkMultiplyMod({BIL}, {2, 3});
    checkMultiplyMod({BIL}, {BIL});
    checkMultiplyMod({BIL, 3, 1000}, {2, 17, BIL});
    cout << "Basic multiply modulo tests OK" << endl;
}


vector<long long> genRandVec(int n, int mxVal) {
    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = rand() % mxVal;
    }
    return res;
}

void randMultiplyTest() {
    const int MX_VAL = 1e6;
    const int MX_SZ = 100;
    const int N_TESTS = 3000;
    for (int qi = 0; qi < N_TESTS; qi++) {
        int szA = 1 + rand() % MX_SZ, szB = 1 + rand() % MX_SZ;
        auto a = genRandVec(szA, MX_VAL), b = genRandVec(szB, MX_VAL);
        checkMultiply(a, b);
    }
    cout << "Rand multiply tests OK" << endl;
}

void randMultiplyModTest() {
    const int MX_VAL = 1e9;
    const int MX_SZ = 100;
    const int N_TESTS = 1000;
    for (int qi = 0; qi < N_TESTS; qi++) {
        int szA = 1 + rand() % MX_SZ, szB = 1 + rand() % MX_SZ;
        auto a = genRandVec(szA, MX_VAL), b = genRandVec(szB, MX_VAL);
        checkMultiplyMod(a, b);
    }
    cout << "Rand multiply modulo tests OK" << endl;
}

void randSquareTest() {
    const int MX_VAL = 1e6;
    const int MX_SZ = 100;
    const int N_TESTS = 3000;
    for (int qi = 0; qi < N_TESTS; qi++) {
        int szA = 1 + rand() % MX_SZ;
        auto a = genRandVec(szA, MX_VAL);
        checkSquare(a);
    }
    cout << "Rand square tests OK" << endl;
}

void multiplyPerfTest() {
    const int TC_COUNT = 20;
    const int MX_VAL = 1000;
    const int N = 2e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        vector<long long> a = genRandVec(N, MX_VAL), b = genRandVec(N, MX_VAL);
        auto start = std::chrono::high_resolution_clock::now();

        FFT<double>::multiply(a, b);

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
    
    cout << "Multiply with <double> performance: " << totalMs / TC_COUNT << "ms" << endl;
}

void multiplyModPerfTest() {
    const int TC_COUNT = 20;
    const int MX_VAL = 1e9;
    const int N = 2e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        vector<long long> a = genRandVec(N, MX_VAL), b = genRandVec(N, MX_VAL);
        auto start = std::chrono::high_resolution_clock::now();

        FFT<double>::multiplyMod(a, b, MOD);

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
    
    cout << "Multiply modulo with <double> performance: " << totalMs / TC_COUNT << "ms" << endl;
}

int main() {
    basicMultiplyTest();
    basicMultiplyModTest();
    randMultiplyTest();
    randMultiplyModTest();
    randSquareTest();
    multiplyPerfTest();
    multiplyModPerfTest();
}
