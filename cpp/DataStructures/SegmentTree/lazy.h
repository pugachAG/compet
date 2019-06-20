#include "../../Utils/traits.h"

/*
struct LazySegTreeOps {
    static T combine(T a, T b);
    static T apply(T state, UPD upd, int sz);
    static UPD accumulate(UPD cur, UPD val);
};
 */
template<typename OPS>
class LazySegTree {
public:
    using T = typename ReturnType<decltype(&OPS::combine)>::type;
    using UPD = typename ReturnType<decltype(&OPS::accumulate)>::type;

    LazySegTree(int n): data(4*n), n(n) {
    }

    LazySegTree(const vector<T> &a): LazySegTree(a.size()) {
        doBld(a, 1, 0, n-1);
    }

    T get(int l, int r) {
        return doGet(l, r, 1, 0, n-1);
    }

    void upd(int l, int r, UPD val) {
        doUpd(l, r, val, 1, 0, n-1);
    }

private:
    struct NodeState {
        T val;
        UPD upd;
        bool hasUpd = false;
    };

    int n;
    vector<NodeState> data;

    T doBld(const vector<T> &a, int v, int from, int to) {
        T res;
        if (from == to) {
            res = a[from];
        } else {
            int mid = (from+to) / 2;
            res = OPS::combine(doBld(a, 2*v, from, mid), doBld(a, 2*v+1, mid+1, to));
        }
        data[v].val = res;
        return res;
    }

    void doUpd(int l, int r, UPD val, int v, int from, int to) {
        if (l <= from && to <= r) {
            doAccumulate(v, val);
            return;
        }

        doPush(v);

        int mid = (from+to)/2;
        if (l <= mid) {
            doUpd(l, r, val, 2*v, from, mid);
        }
        if (mid+1 <= r) {
            doUpd(l, r, val, 2*v+1, mid+1, to);
        }

        doRecalc(v, from, to);
    }

    T doGet(int l, int r, int v, int from, int to) {
        if (l <= from && to <= r) {
            return doApply(v, from, to);
        }

        doPush(v);
        doRecalc(v, from, to);

        int mid = (from+to)/2;
        if (l > mid) {
            return doGet(l, r, 2*v+1, mid+1, to);
        }
        if (mid+1 > r) {
            return doGet(l, r, 2*v, from, mid);
        }
        return OPS::combine(doGet(l, r, 2*v, from, mid), doGet(l, r, 2*v+1, mid+1, to));
    }


    void doPush(int v) {
        const auto &cur = data[v];
        if (cur.hasUpd) {
            doAccumulate(2*v, cur.upd);
            doAccumulate(2*v+1, cur.upd);
        }
    }

    void doRecalc(int v, int from, int to) {
        auto &cur = data[v];
        int mid = (from+to)/2;
        cur.val = OPS::combine(doApply(2*v, from, mid), doApply(2*v+1, mid+1, to));
        cur.hasUpd = false;
    }

    T doApply(int v, int from, int to) {
        const auto &cur = data[v];
        if (cur.hasUpd) {
            return OPS::apply(cur.val, cur.upd, to-from+1);
        }
        return cur.val;
    }

    void doAccumulate(int v, UPD upd) {
        auto &cur = data[v];
        if (cur.hasUpd) {
            cur.upd = OPS::accumulate(cur.upd, upd);
        } else {
            cur.upd = upd;
            cur.hasUpd = true;
        }
    }
};
