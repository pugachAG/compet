template<typename Float>
struct FFT {
    static constexpr Float PI = atan(1) * 4;

    using Int = long long;

    struct Complex {
        Float real, img;

        Complex(): Complex(0, 0) {
        }

        Complex(Int real): Complex(real, 0) {
        }

        Complex(Float real, Float img): real(real), img(img) {
        }

        Complex mult(const Complex &b) const {
            return Complex(real*b.real - img*b.img, real*b.img + b.real*img);
        }

        Complex add(const Complex &b) const {
            return Complex(real + b.real, img + b.img);
        }

        Complex sub(const Complex &b) const {
            return Complex(real - b.real, img - b.img);
        }

        bool isZero() const {
            static const double EPS = 0.1;
            return fabs(real) < EPS && fabs(img) < EPS;
        }
    };

    using Vec = vector<Complex>;

    static Vec multVec(const Vec &a, const Vec &b) {
        int n = a.size();
        Vec res(n);
        for (int i = 0; i < n; i++) {
            res[i] = a[i].mult(b[i]);
        }
        return res;
    }

    static vector<Int> sumVec(const Vec &a, const Vec &b) {
        int n = a.size();
        Vec res(n);
        for (int i = 0; i < n; i++) {
            res[i] = a[i].add(b[i]);
        }
        return res;
    }

    static vector<Int> convToIntVec(const vector<Complex> &a) {
        int n = a.size();
        vector<Int> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = a[i].real + 0.5;
        }
        return res;
    }

    static vector<Int> multiply(const vector<Int> &a, const vector<Int> &b) {
        Vec fa(a.begin(), a.end()), fb(b.begin(), b.end());
        auto res = convToIntVec(multiplyFFT(fa, fb));
        truncateZeros(res);
        return res;
    }

    static vector<Int> square(const vector<Int> &a) {
        Vec fa(a.begin(), a.end());
        resizeVecForFFT(fa, fa);
        applyFFT(fa, false);
        auto prod = multVec(fa, fa);
        applyFFT(prod, true);
        auto res = convToIntVec(prod);
        truncateZeros(res);
        return res;
    }

    static void resizeVecForFFT(Vec &a, Vec &b) {
        int sz = max(a.size(), b.size());
        resizeVecForFFT(a, sz);
        resizeVecForFFT(b, sz);
    }

    static void resizeVecForFFT(Vec &a, int sz) {
        int n = 1;
        while (n < sz) {
            n <<= 1;
        }
        n <<= 1;
        a.resize(n);
    }

    static void truncateZeros(vector<Int> &a) {
        while (a.size() > 1 && a.back() == 0) {
            a.pop_back();
        }
    }

    static Vec multiplyFFT(Vec a, Vec b) {
        resizeVecForFFT(a, b);
        applyFFT(a, false);
        applyFFT(b, false);
        auto res = multVec(a, b);
        applyFFT(res, true);
        return res;
    }

    static Complex extract(const Vec &a, int i, int side) {
        int sz = a.size();
        int j = (sz - i) & (sz - 1);
        int sign = side == 0 ? 1 : -1;
        auto multiplier = side == 0 ? Complex(0.5, 0) : Complex(0, -0.5);
        return multiplier.mult(Complex(a[i].real + a[j].real * sign, a[i].img - a[j].img * sign));
    }

    static Vec split(const vector<Int> &a, Int base) {
        int n = a.size();
        Vec res;
        for (int i = 0; i < n; i++) {
            res.emplace_back(a[i] % base, a[i] / base);
        }
        return res;
    }

    static vector<Int> multiplyMod(const vector<Int> &a, const vector<Int> &b, Int mod) {
        Int base = sqrt(mod);
        auto fa = split(a, base);
        auto fb = split(b, base);

        resizeVecForFFT(fa, fb);
        applyFFT(fa, false);
        applyFFT(fb, false);

        int sz = fa.size();
        vector<Int> result(sz);
        for (int exponent = 0; exponent <= 2; exponent++) {
            Int multiplier = 1;
            for (int k = 0; k < exponent; k++) {
                multiplier = multiplier * base % mod;
            }

            Vec product(sz);
            for (int x = 0; x < 2; x++) {
                for (int y = 0; y < 2; y++) {
                    if (x + y == exponent) {
                        for (int i = 0; i < sz; i++) {
                            product[i] = product[i].add(extract(fa, i, x).mult(extract(fb, i, y)));
                        }
                    }
                }
            }

            applyFFT(product, true);

            auto cur = convToIntVec(product);
            for (int i = 0; i < sz; i++) {
                result[i] = (result[i] + cur[i] % mod * multiplier) % mod;
            }
        }

        truncateZeros(result);

        return result;
    }

    static void applyFFT(Vec &a, bool invert) {
        int n = a.size();
    
        int j = 0;
        for (int i = 1; i < n; i++) {
            int bit = n >> 1;
            while (j >= bit) {
                j -= bit;
                bit >>= 1;
            }
            j += bit;
            if (i < j) {
                swap(a[i], a[j]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            vector<Complex> ws;
            for (int j = 0; j < len/2; j++) {
                Float ang = 2 * j * PI / len * (invert ? -1 : 1);
                ws.emplace_back(cos(ang), sin(ang));
            }

            for (int i = 0; i < n; i += len) {
                auto wsIt = ws.begin();
                for (int j = 0; j < len/2; j++) {
                    Complex w = *wsIt;
                    Complex u = a[i+j];
                    Complex v = a[i+j+len/2].mult(w);
                    a[i+j] = u.add(v);
                    a[i+j+len/2] = u.sub(v);
                    ++wsIt;
                }
            }
        }

        if (invert) {
            for (int i = 0; i < n; i++) {
                a[i].real /= n;
                a[i].img /= n;
            }
        }
    }
};
