struct ModuloNumber {

    long long value() const {
        return val;
    }

    ModuloNumber(const long long val, const long long mod): mod(mod), val(normalize(val, mod)) {
    }

    ModuloNumber pow(const long long &pw) const {
        return ModuloNumber(binPow(val, pw, mod), mod);
    }

    ModuloNumber inv() const {
        return pow(mod-2);
    }

    ModuloNumber& operator*=(const long long &rhs) {
        val = mul(val, rhs, mod);
        return *this;
    }

    ModuloNumber& operator*=(const ModuloNumber &rhs) {
        return *this *= rhs.val;
    }

    ModuloNumber& operator+=(const long long &rhs) {
        val = add(val, rhs, mod);
        return *this;
    }

    ModuloNumber& operator+=(const ModuloNumber &rhs) {
        return *this += rhs.val;
    }

    ModuloNumber& operator-=(const long long &rhs) {
        val = sub(val, rhs, mod);
        return *this;
    }

    ModuloNumber& operator-=(const ModuloNumber &rhs) {
        return *this -= rhs.val;
    }

    ModuloNumber& operator/=(const ModuloNumber &rhs) {
        return *this *= rhs.inv();
    }

    ModuloNumber& operator/=(const long long &rhs) {
        return *this /= ModuloNumber(rhs, mod);
    }

private:
    const long long mod;
    long long val;

    inline static long long normalize(const long long &a, const long long &mod) {
        return (a%mod + mod) % mod;
    }

    static long long binPow(const long long &a, const long long &b, const long long &mod) {
        if (b < 0) {
            throw "invalid op";
        }
        auto ans = 1ll;
        auto cur = a;
        auto mask = 1ll;
        while (b >= mask) {
            if ((b&mask) == mask) {
                ans = (ans*cur)%mod;
            }
            cur = (cur*cur)%mod;
            mask <<= 1;
        }
        return ans;
    }

    static inline long long mul(long long a, long long b, long long mod) {
        return (normalize(a, mod) * normalize(b, mod)) % mod;
    }

    static inline long long add(long long a, long long b, long long mod) {
        return normalize(a + b, mod);
    }

    static inline long long sub(long long a, long long b, long long mod) {
        return normalize(a - b, mod);
    }
};

template<typename T>
ModuloNumber operator*(ModuloNumber lhs, const T& rhs) {
    return lhs *= rhs;
}

ModuloNumber operator*(const long long& lhs, ModuloNumber rhs) {
    return rhs *= lhs;
}

template<typename T>
ModuloNumber operator+(ModuloNumber lhs, const T& rhs) {
    return lhs += rhs;
}

ModuloNumber operator+(const long long& lhs, ModuloNumber rhs) {
    return rhs += lhs;
}

template<typename T>
ModuloNumber operator-(ModuloNumber lhs, const T& rhs) {
    return lhs -= rhs;
}

template<typename T>
ModuloNumber operator/(ModuloNumber lhs, const T& rhs) {
    return lhs /= rhs;
}

class ModuloOps {
public:
    ModuloOps(long long mod): MOD(mod) {
    }

    ModuloNumber number(long long v) {
        return ModuloNumber(v, MOD);
    }

    ModuloNumber fact(int n) {
        while (factMem.size() <= n) {
            long long k = factMem.size();
            factMem.push_back((k * factMem.back()) % MOD);
        }
        return number(factMem[n]);
    }

    ModuloNumber comb(int n, int k) {
        if (k > n) {
            throw "k > n";
        }
        return fact(n) / (fact(k) * fact(n-k));
    }

private:
    long long MOD;
    vector<long long> factMem = {1};
};

