#include <bits/stdc++.h>

using namespace std;

#include "dp.h"

const long long MOD = 1e9 + 7;

struct CombinationsDP : DP2<CombinationsDP, long long> {
	long long impl(int i, int j) {
		if (i == j || j == 0) {
			return 1;
		}
 
		return (calc(i-1, j) + calc(i-1, j-1)) % MOD;
	}
};

long long calcAdHoc(int n, int k) {
    vector<vector<long long>> mem(n+1, vector<long long>(k+1, -1));
    function<long long(int, int)> combinations;
    combinations = [&] (int i, int j) {
        if (j == 0 || j == i) {
            return 1ll;
        }
        auto &res = mem[i][j];
        if (res == -1) {
            res = (combinations(i-1, j) + combinations(i-1, j-1)) % MOD;
        }
        return res;
    };
    return combinations(n, k);
}

void perfTest() {
    int n = 7000;
    int k = 3000;

    auto start = std::chrono::high_resolution_clock::now();
    auto resAdHoc = calcAdHoc(n, k);
    auto finish = std::chrono::high_resolution_clock::now();
    auto totalMs = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    cout << "Ad Hoc: " << resAdHoc << " in " << totalMs << endl;


    start = std::chrono::high_resolution_clock::now();
    auto dp = CombinationsDP::create(n+1, k+1);
    auto resDp = dp->calc(n, k);
    finish = std::chrono::high_resolution_clock::now();
    totalMs = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    cout << "DP:     " << resDp << " in " << totalMs << endl;
}

int main() {
    perfTest();
}
