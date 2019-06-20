#include <bits/stdc++.h>

using namespace std;

#include "tree_ops.h"

void basicTest() {
    int n = 5;
    //     0
    //    / \
    //   1   2
    //  / \
    // 3   4
    Graph g = {
        {1, 2},
        {0, 3, 4},
        {0},
        {1},
        {1}
    };

    TreeOps ops(g);
    ops.lcaInit();

    assert(ops.getParent(1) == 0);
    assert(ops.getParent(2) == 0);
    assert(ops.getParent(4) == 1);

    assert(ops.lca(1, 2) == 0);
    assert(ops.lca(1, 0) == 0);
    assert(ops.lca(4, 2) == 0);
    assert(ops.lca(3, 4) == 1);

    cout << "Basic correctness OK" << endl;
}

int main() {
    basicTest();
}

