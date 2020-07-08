#### DP
```
#include "../Algo/DP/dp.h"

struct DP: DP2<DP, long long> {
	long long impl(int i, int j) {
		return 0;
	}
};

auto dp = DP::create(n, m);
auto ans = dp->calc(...);
```


#### Codeforces interactive problems
```
mkfifo fifo
g++ main.cpp -o a.out
g++ checker.cpp -o b.out
while true; do
    (./a.out < fifo) | (./b.out > fifo)
done                               
```
