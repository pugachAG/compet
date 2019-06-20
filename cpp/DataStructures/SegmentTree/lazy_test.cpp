#include <bits/stdc++.h>

using namespace std;

#include "lazy.h"

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

    void upd(int l, int r, int val) {
        for (int i = l; i <= r; i++) {
            a[i] += val;
        }
    }
};

struct SumIncOps {
    static int combine(int a, int b) {
        return a + b;
    }

    static int apply(int cur, int val, int sz) {
        return cur + sz*val;
    }

    static int accumulate(int cur, int val) {
        return cur + val;
    }
};

int perfTest() {
    const int TC_COUNT = 20;
    const int MX_VAL = 100;
    const int N = 1e5;
    const int Q_COUNT = 1e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        vector<int> a(N);

        auto start = std::chrono::high_resolution_clock::now();

        LazySegTree<SumIncOps> st(a);
        for (int q = 0; q < Q_COUNT; q++) {
            int op = rand() % 2;
            int i1 = rand() % N, i2 = rand() % N;
            int l = min(i1, i2), r = max(i1, i2);
            if (op == 0) {
                int val = rand() % MX_VAL;
                st.upd(l, r, val);
            } else {
                st.get(l, r);
            }
        }

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
    
    cout << "Performance: " << totalMs / TC_COUNT << "ms" << endl;
}

bool randTest() {
    const int MX_VAL = 100;
    const int TC_COUNT = 1000;
    const int Q_COUNT = 100;
    const vector<int> MX_NS = {3, 10, 1000};

    for (int mxN: MX_NS) {
        for (int tc = 0; tc < TC_COUNT; tc++) {
            int n = 1 + rand() % mxN;
            vector<int> a(n);
            for (int i = 0; i < n; i++) {
                a[i] = rand() % MX_VAL;
            }
            Naive nv(a);
            LazySegTree<SumIncOps> st(a);
            vector<pair<int, pair<int, int>>> upds;
            for (int q = 0; q < Q_COUNT; q++) {
                int op = rand() % 2;
                int i1 = rand() % n, i2 = rand() % n;
                int l = min(i1, i2), r = max(i1, i2);
                upds.push_back({op, {l, r}});
                if (op == 0) {
                    int val = rand() % MX_VAL;
                    nv.upd(l, r, val);
                    st.upd(l, r, val);
                } else {
                    int expected = nv.get(l, r);
                    int actual = st.get(l, r);
                    if (actual != expected) {
                        cout << "failed for n=" << n << endl;
                        for (int i = 0; i < n; i++) {
                            cout << a[i] << " ";
                        }
                        cout << endl;
                        cout << "updates:" << endl;
                        for (auto upd: upds) {
                            cout << upd.first << " " << upd.second.first << " " << upd.second.second << endl;
                        }
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
