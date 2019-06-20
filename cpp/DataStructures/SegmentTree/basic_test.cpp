#include <bits/stdc++.h>

using namespace std;

#include "basic.h"

struct Naive {
    vector<int> a;
    Naive(const vector<int> &a): a(a) {
    }

    int get(int l, int r) {
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans += a[i];
        }
        return ans;
    }

    void upd(int i, int val) {
        a[i] += val;
    }
};

struct SumIncOps {
    static int combine(int a, int b) {
        return a + b;
    }

    static int update(int cur, int val) {
        return cur + val;
    }
};

int perfTest() {
    const int TC_COUNT = 20;
    const int MX_VAL = 100;
    const int N = 2e5;
    const int Q_COUNT = 2e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        vector<int> a(N);

        auto start = std::chrono::high_resolution_clock::now();

        SegTree<SumIncOps> st(a);
        for (int q = 0; q < Q_COUNT; q++) {
            int op = rand() % 2;
            if (op == 0) {
                int i = rand() % N;
                int val = rand() % MX_VAL;
                st.upd(i, val);
            } else {
                int i1 = rand() % N, i2 = rand() % N;
                int l = min(i1, i2), r = max(i1, i2);
                st.get(l, r);
            }
        }

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
    
    cout << "Performance: " << totalMs / TC_COUNT << "ms" << endl;
}

bool randTest() {
    const int MX_VAL = 1e5;
    const int TC_COUNT = 1000;
    const int Q_COUNT = 100;
    const vector<int> MX_NS = {5, 10, 1000};

    for (int mxN: MX_NS) {
        for (int tc = 0; tc < TC_COUNT; tc++) {
            int n = 1 + rand() % mxN;
            vector<int> a(n);
            for (int i = 0; i < n; i++) {
                a[i] = rand() % MX_VAL;
            }
            Naive nv(a);
            SegTree<SumIncOps> st(a);
            for (int q = 0; q < Q_COUNT; q++) {
                int op = rand() % 2;
                if (op == 0) {
                    int i = rand() % n;
                    int val = rand() % MX_VAL;
                    nv.upd(i, val);
                    st.upd(i, val);
                } else {
                    int i1 = rand() % n, i2 = rand() % n;
                    int l = min(i1, i2), r = max(i1, i2);
                    int expected = nv.get(l, r);
                    int actual = st.get(l, r);
                    if (actual != expected) {
                        cout << "failed for n=" << n << endl;
                        cout << "expected: " << expected << endl;
                        cout << "actual: " << actual << endl;
                        return false;
                    }
                }
            }
        }
    }

    cout << "Correctness OK" << endl;
    return true;
}

int main() {
    if (randTest()) {
        perfTest();
    }
}
