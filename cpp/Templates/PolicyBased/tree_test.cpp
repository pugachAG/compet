#include <bits/stdc++.h>

using namespace std;

#include "tree.h"

void basicTest() {
    RBTree<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(4);
    s.insert(8);
    s.insert(16);

    assert(*s.find_by_order(1) == 2);
    assert(*s.find_by_order(2) == 4);
    assert(*s.find_by_order(4) == 16);
    assert(s.find_by_order(6) == s.end());

    assert(s.order_of_key(-5) == 0);
    assert(s.order_of_key(1) == 0);
    assert(s.order_of_key(400) == 5);

    cout << "Basic correctness OK" << endl;
}

int main() {
    basicTest();
}

