#### Codeforces interactive problems
```
mkfifo fifo
g++ main.cpp -o a.out
g++ checker.cpp -o b.out
while true; do
    (./a.out < fifo) | (./b.out > fifo)
done                               
```
