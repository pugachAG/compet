class ModuloOps {
public:
    ModuloOps(long long mod): MOD(mod) {
    }

    long long binPow(long long a, long long b) {
        if (b == 0) {
            return 1;
        }
        auto prev = binPow(a, b/2);
        return mul(mul(prev, prev), b % 2 == 1 ? a : 1);
    }

    long long inv(long long a) {
        return binPow(a, MOD - 2);
    }

    inline long long add(long long a, long long b) {
        return (a + b) % MOD;
    }

    inline long long sub(long long a, long long b) {
        return (a - b + MOD) % MOD;
    }

    inline void inc(long long &a, long long b) {
        a = add(a, b);
    }

    inline long long mul(long long a, long long b) {
        return (a * b) % MOD;
    }

    inline long long div(long long a, long long b) {
        return mul(a, inv(b));
    }

private:
    long long MOD;
};
