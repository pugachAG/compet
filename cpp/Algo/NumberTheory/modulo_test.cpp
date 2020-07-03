#include <bits/stdc++.h>

using namespace std;

#include "modulo.h"

ModuloOps ops(7);

void testAdd() {
    auto v = ops.number(2);
    auto v2 = v;
    v2 += 6;
    assert(v2.value() == 1);
    v2 += ops.number(6);
    assert(v2.value() == 0);
    assert((v + 6).value() == 1);
    assert((v + ops.number(6)).value() == 1);
}

void testMult() {
    auto v = ops.number(2);
    auto v1 = v;
    v1 *= 5;
    assert(v1.value() == 3);
    v1 *= ops.number(2);
    assert(v1.value() == 6);
    assert((v * 5).value() == 3);
    assert((v * ops.number(5)).value() == 3);
}

void testSub() {
    auto v = ops.number(2);
    auto v3 = v;
    v3 -= 3;
    assert(v3.value() == 6);
    v3 -= ops.number(1);
    assert(v3.value() == 5);
    assert((v - 3).value() == 6);
    assert((v - ops.number(3)).value() == 6);
}

void testDiv() {
    auto v4 = ops.number(4);
    v4 /= 2;
    assert(v4.value() == 2);
    v4 /= ops.number(2);
    assert(v4.value() == 1);
    auto v = ops.number(2);
    assert((v/2).value() == 1);
    assert((v / ops.number(2)).value() == 1);
}

void testFact() {
    assert(ops.fact(0).value() == 1);
    assert(ops.fact(1).value() == 1);
    assert(ops.fact(2).value() == 2);
    assert(ops.fact(4).value() == 3);
}

void testComb() {
    assert(ops.comb(3, 1).value() == 3);
    assert(ops.comb(4, 2).value() == 6);
    assert(ops.comb(5, 3).value() == 3);
}

int main() {
    testAdd();
    testSub();
    testMult();
    testDiv();
    testFact();
    testComb();
}
