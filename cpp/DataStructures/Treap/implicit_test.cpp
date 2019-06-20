#include <bits/stdc++.h>

using namespace std;

#include "implicit.h"

void basicTest() {
    ImplicitTreap<int> treap;

    auto node10 = treap.insert(0, 10);
    // [10]
    assert(treap.get(0) == 10);
    assert(node10->pos() == 0);

    auto node22 = treap.insert(1, 22);
    // [10, 22]
    assert(treap.get(0) == 10);
    assert(node10->pos() == 0);
    assert(treap.get(1) == 22);
    assert(node22->pos() == 1);

    auto node9 = treap.insert(0, 9);
    // [9, 10, 22]
    assert(treap.get(0) == 9);
    assert(node9->pos() == 0);
    assert(treap.get(1) == 10);
    assert(node10->pos() == 1);

    treap.insert(2, 12);
    // [9, 10, 12, 22]
    assert(treap.get(2) == 12);
    assert(treap.get(3) == 22);
    assert(treap.size() == 4);

    treap.remove(0);
    // [10, 12, 22]
    assert(treap.get(0) == 10);

    treap.remove(1);
    // [10, 22]
    assert(treap.get(1) == 22);
    assert(treap.size() == 2);
    assert(node10->pos() == 0);
    assert(node22->pos() == 1);

    cout << "Basic correctness OK" << endl;
}

bool randTest() {
    const int MX_VAL = 1e5;
    const int TC_COUNT = 500;
    const vector<int> Q_COUNTS = {3, 10, 200};

    for (int qCnt: Q_COUNTS) {
        for (int tc = 0; tc < TC_COUNT; tc++) {
            vector<int> state;
            ImplicitTreap<int> treap;

            for (int qi = 0; qi < qCnt; qi++) {
                int sz = state.size();
                int op = sz > 0 ? rand() % 4 : 1;

                if (treap.size() != sz) {
                    cout << "invalid size" << endl;
                    cout << "expected: " << sz << endl;
                    cout << "actual: " << treap.size() << endl;
                    return false;
                }

                if (op == 0) {
                    int pos = rand() % sz;
                    int expected = state[pos];
                    int actual = treap.get(pos);
                    if (expected != actual) {
                        cout << "retrieved invalid value" << endl;
                        cout << "expected: " << expected << endl;
                        cout << "actual: " << actual << endl;
                        return false;
                    }
                } else if (op == 1) {
                    int pos = rand() % (sz + 1);
                    int val = rand() % MX_VAL;
                    state.insert(state.begin() + pos, val);
                    auto node = treap.insert(pos, val);
                    int treapPos = node->pos();
                    if (treapPos != pos) {
                        cout << "reported invalid node position" << endl;
                        cout << "expected: " << pos << endl;
                        cout << "actual: " << treapPos << endl;
                        return false;
                    }
                } else if (op == 2) {
                    int i1 = rand() % sz, i2 = rand() % sz;
                    int l = min(i1, i2), r = max(i1, i2);
                    state.erase(state.begin() + l, state.begin() + r + 1);
                    treap.removeRange(l, r);
                } else if (op == 3) {
                    int pos = rand() % sz;
                    state.erase(state.begin() + pos);
                    treap.remove(pos);
                }
            }
        }
    }

    cout << "Rand correctness OK" << endl;
    return true;
}

struct MaxTreapOps {
    static int combine(int left, int cur, int right) {
        return max(max(left, right), cur);
    }
};

bool randRangeQueryTest() {
    const int MX_VAL = 1e5;
    const int TC_COUNT = 500;
    const vector<int> Q_COUNTS = {3, 10, 200};

    for (int qCnt: Q_COUNTS) {
        for (int tc = 0; tc < TC_COUNT; tc++) {
            vector<int> state;
            ImplicitTreap<int, MaxTreapOps> treap;

            for (int qi = 0; qi < qCnt; qi++) {
                int op = state.size() > 0 ? rand() % 2 : 1;

                if (op == 0) {
                    int i1 = rand() % state.size();
                    int i2 = rand() % state.size();
                    int l = min(i1, i2), r = max(i1, i2);
                    int expected = -1;
                    for (int i = l; i <= r; i++) {
                        expected = max(expected, state[i]);
                    }
                    int actual = treap.rangeQuery(l, r);
                    if (expected != actual) {
                        cout << "invalid range query value" << endl;
                        cout << "expected: " << expected << endl;
                        cout << "actual: " << actual << endl;
                        return false;
                    }
                } else {
                    int pos = rand() % (state.size() + 1);
                    int val = rand() % MX_VAL;
                    state.insert(state.begin() + pos, val);
                    treap.insert(pos, val);
                }
            }
        }
    }

    cout << "Rand range query correctness OK" << endl;
    return true;
}

void perfRandTest() {
    const int TC_COUNT = 20;
    const int MX_VAL = 10000;
    const int Q_COUNT = 2e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        auto start = std::chrono::high_resolution_clock::now();

        ImplicitTreap<int> treap;
        int sz = 0;
        for (int qi = 0; qi < Q_COUNT; qi++) {
            int op = sz > 0 ? rand() % 3 : 1;

            if (op == 0) {
                int pos = rand() % sz;
                treap.get(pos);
            } else if (op == 1) {
                int pos = rand() % (sz + 1);
                int val = rand() % MX_VAL;
                treap.insert(pos, val);
                sz++;
            } else {
                int pos = rand() % sz;
                treap.remove(pos);
                sz--;
            }
        }

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }

    cout << "Mixed performance: " << totalMs / TC_COUNT << "ms" << endl;
}

void perfInsert1nTest() {
    const int TC_COUNT = 20;
    const int Q_COUNT = 2e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        auto start = std::chrono::high_resolution_clock::now();

        ImplicitTreap<int> treap;
        for (int i = 0; i < Q_COUNT; i++) {
            treap.insert(i, i);
        }

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }

    cout << "Insert 1..n performance: " << totalMs / TC_COUNT << "ms" << endl;
}

void perfRemoveTest() {
    const int TC_COUNT = 20;
    const int Q_COUNT = 2e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        ImplicitTreap<int> treap;
        vector<int> perm;
        for (int i = 0; i < Q_COUNT; i++) {
            treap.insert(i, i);
            perm.push_back(i);
        }
        random_shuffle(perm.begin(), perm.end());

        auto start = std::chrono::high_resolution_clock::now();

        for (int v: perm) {
            treap.remove(v);
        }

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }

    cout << "Remove performance: " << totalMs / TC_COUNT << "ms" << endl;
}

void perfGetTest() {
    const int TC_COUNT = 20;
    const int Q_COUNT = 2e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        ImplicitTreap<int> treap;
        for (int i = 0; i < Q_COUNT; i++) {
            treap.insert(i, i);
        }

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < Q_COUNT; i++) {
            treap.get(i);
        }

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }

    cout << "Get performance: " << totalMs / TC_COUNT << "ms" << endl;
}


void perfRangeQueryTest() {
    const int TC_COUNT = 20;
    const int Q_COUNT = 1e5;

    int totalMs = 0;
    for (int tc = 0; tc < TC_COUNT; tc++) {
        ImplicitTreap<int, MaxTreapOps> treap;
        for (int i = 0; i < Q_COUNT; i++) {
            treap.insert(i, i);
        }
        int sz = treap.size();

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < Q_COUNT; i++) {
            int i1 = rand() % sz, i2 = rand() % sz;
            int l = min(i1, i2), r = max(i1, i2);
            treap.rangeQuery(l, r);
        }

        auto finish = std::chrono::high_resolution_clock::now();
        totalMs += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }

    cout << "Range query performance: " << totalMs / TC_COUNT << "ms" << endl;
}

int main() {
    basicTest();
    if (randTest() && randRangeQueryTest()) {
        perfRandTest();
        perfInsert1nTest();
        perfRemoveTest();
        perfGetTest();
        perfRangeQueryTest();
    }
}
