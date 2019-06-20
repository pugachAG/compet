class Eratosthenes {
public:
    Eratosthenes(int n): mx(n+1) {
        primes.reserve(mx);
        firstDiv.assign(mx, -1);
        firstDiv[1] = 1;
        vector<bool> ps(mx, true);
        for (int p = 2; p < mx; p++) {
            if (!ps[p]) {
                continue;
            }
            primes.push_back(p);

            for (int d = p; d < mx; d += p) {
                ps[d] = false;
                if (firstDiv[d] == -1) {
                    firstDiv[d] = p;
                }
            }
        }
    }

    vector<int> primeFactorizeFlat(int k) {
        auto gr = primeFactorize(k);
        vector<int> res;
        for (auto pr: gr) {
            int p = pr.first;
            for (int c = 0; c < pr.second; c++) {
                res.push_back(p);
            }
        }
        return res;
    }

    vector<pair<int, int>> primeFactorize(int k) {
        assert(k < mx);
        vector<pair<int, int>> res;
        int cur = k;
        while (cur > 1) {
            int p = firstDiv[cur];
            int cnt = 0;
            while (cur % p == 0) {
                cnt++;
                cur /= p;
            }
            res.push_back({p, cnt});
        }
        return res;
    }

    vector<int> allDivs(int k) {
        auto primeFact = primeFactorize(k);
        vector<int> res = {1};
        for (auto pr: primeFact) {
            int sz = res.size();
            int mul = 1;
            for (int c = 0; c < pr.second; c++) {
                mul *= pr.first;
                for (int i = 0; i < sz; i++) {
                    res.push_back(res[i] * mul);
                }
            }
        }
        sort(res.begin(), res.end());
        return res;
    }


    int mobius(int k) {
        auto ps = primeFactorize(k);
        for (auto pr: ps) {
            if (pr.second > 1) {
                return 0;
            }
        }
        return ps.size() % 2 == 0 ? 1 : -1;
    }

    vector<int> allPrimes() {
        return primes;
    }

private:
    int mx;
    vector<int> firstDiv;
    vector<int> primes;
};
