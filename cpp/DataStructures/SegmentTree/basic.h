#include "../../Utils/traits.h"

/*
struct SegTreeOps {
    static T combine(T a, T b);
    static T update(T cur, UPD val);
};
 */
template<typename OPS>
class SegTree {
public:
    using T = typename ReturnType<decltype(&OPS::combine)>::type;
    using UPD = typename SecondArgType<decltype(&OPS::update)>::type;

    SegTree(int n): data(4*n), n(n) {
    }

    SegTree(const vector<T> &a): SegTree(a.size()) {
        doBld(a, 1, 0, n-1);
    }

    T get(int l, int r) {
        return doGet(l, r, 1, 0, n-1);
    }

    void upd(int i, UPD val) {
        doUpd(i, val, 1, 0, n-1);
    }

private:
    int n;
    vector<T> data;

    void doBld(const vector<T> &a, int v, int from, int to) {
        if (from == to) {
            data[v] = a[from];
        } else {
            int mid = (from+to)/2;
            doBld(a, 2*v, from, mid);
            doBld(a, 2*v+1, mid+1, to);
            doRecalc(v);
        }
    }

    void doUpd(int i, UPD val, int v, int from, int to) {
        if (from < to) {
            int mid = (from+to)/2;
            if (i <= mid) {
                doUpd(i, val, 2*v, from, mid);
            } else {
                doUpd(i, val, 2*v+1, mid+1, to);
            }
            doRecalc(v);
        } else {
            data[v] = OPS::update(data[v], val);
        }
    }

    T doGet(int l, int r, int v, int from, int to) {
        if (l <= from && to <= r) {
            return data[v];
        }

        int mid = (from+to)/2;
        if (l > mid) {
            return doGet(l, r, 2*v+1, mid+1, to);
        }
        if (mid+1 > r) {
            return doGet(l, r, 2*v, from, mid);
        }
        return OPS::combine(doGet(l, r, 2*v, from, mid), doGet(l, r, 2*v+1, mid+1, to));
    }

    void doRecalc(int v) {
        data[v] = OPS::combine(data[2*v], data[2*v+1]);
    }
};
