struct LiChaoTree {
    using Int = long long;
    using Func = pair<Int, Int>;

    struct Node {
        Node *left = nullptr, *right = nullptr;
        Int from, to;
        Func cur;

        Node(Int l, Int r, Func f): from(l), to(r), cur(f) {
        }

        void add(Func f) {
            Int mid = (from + to) / 2;
            bool isLeft = isBetterFunc(f, cur, from);
            bool isMid = isBetterFunc(f, cur, mid);
            if (isMid) {
                swap(f, cur);
            }

            if (from < to) {
                if (isLeft != isMid) {
                    if (left == nullptr) {
                        left = new Node(from, mid, f);
                    } else {
                        left->add(f);
                    }
                } else {
                    if (right == nullptr) {
                        right = new Node(mid + 1, to, f);
                    } else {
                        right->add(f);
                    }
                }
            }
        }

        Int query(Int x) {
            Int mine = calc(cur, x);

            Int mid = (from + to) / 2;
            if (x <= mid) {
                if (left) {
                    return best(mine, left->query(x));
                }
            } else {
                if (right) {
                    return best(mine, right->query(x));
                }
            }

            return mine;
        }

        Int calc(Func f, Int x) {
            return f.first * x + f.second;
        }

        bool isBetterFunc(Func f1, Func f2, Int x) {
            return isBetter(calc(f1, x), calc(f2, x));
        }

        Int best(Int v1, Int v2) {
            return isBetter(v1, v2) ? v1 : v2;
        }

        bool isBetter(Int v1, Int v2) {
            return v1 > v2;
        }
    };

    Int mx;
    Node *root = nullptr;

    LiChaoTree(Int mx): mx(mx) {
    }

    // Add a*x + b
    void add(Int a, Int b) {
        Func f = {a, b};
        if (root) {
            root->add(f);
        } else {
            root = new Node(0, mx, f);
        }
    }

    Int query(Int x) {
        return root->query(x);
    }
};
