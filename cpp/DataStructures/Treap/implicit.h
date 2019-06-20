#include "../../Utils/traits.h"

struct NoopTreapOps {
    static int combine(int left, int cur, int right) {
    }
};

/*
struct TreapOps {
    static U combine(U left, T cur, U right);
};
 */
template<typename T, typename OPS=NoopTreapOps>
struct ImplicitTreap {
public:
    using U = typename ReturnType<decltype(&OPS::combine)>::type;

    template <class TP, class OPS_TP>
    struct AggregateMember {
        TP agr;
    };

    template <class TP>
    struct AggregateMember<TP, NoopTreapOps> {
    };

    struct Node: AggregateMember<U, OPS> {
        T data;
        unsigned int prio;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        int size;

        Node(T data, unsigned int prio): data(data), prio(prio) {
        }

        Node* root() {
            return parent == nullptr ? this : parent->root();
        }

        int pos() {
            int res = getSize(left);
            auto cur = this;
            while (cur->parent) {
                auto p = cur->parent;
                if (p == nullptr) {
                    break;
                }
                if (cur == p->right) {
                    res += 1 + getSize(p->left);
                }
                cur = p;
            }
            return res;
        }

        static inline int getSize(Node *cur) {
            return cur ? cur->size : 0;
        }
    };

    ImplicitTreap() {
    }

    ImplicitTreap(Node *node) {
        root = node->root();
    }

    Node* insert(int pos, T val) {
        auto node = createNode(val);
        insertNode(pos, node);
        return node;
    }

    void insertNode(int pos, Node* node) {
        auto pr = doSplit(root, pos);
        auto left = doMerge(pr.first, node);
        root = doMerge(left, pr.second);
    }

    T get(int pos) {
        auto node = getNode(pos);
        if (node == nullptr) {
            return 0;
        }
        return node->data;
    }

    Node* getNode(int pos) {
        return doFind(root, pos);
    }

    U rangeQuery(int l, int r) {
        auto leftPr = doSplit(root, l);
        auto rightPr = doSplit(leftPr.second, r-l+1);
        auto res = rightPr.first->agr;
        root = doMerge(leftPr.first, doMerge(rightPr.first, rightPr.second));
        return res;
    }

    Node* remove(int pos) {
        return removeRange(pos, pos);
    }

    Node* removeRange(int from, int to) {
        auto pr1 = doSplit(root, from);
        auto pr2 = doSplit(pr1.second, to-from+1);
        root = doMerge(pr1.first, pr2.second);
        return pr2.first;
    }

    int size() {
        if (root) {
            return root->size;
        }
        return 0;
    }

private:
    template <class NODE, class OPS_TP>
    struct AggregateLogic {
        static inline void updateAgr(NODE *cur) {
            cur->agr = OPS_TP::combine(getAgr(cur->left), cur->data, getAgr(cur->right));
        }

        static inline U getAgr(NODE *cur) {
            return cur ? cur->agr : U();
        }
    };

    template <class NODE>
    struct AggregateLogic<NODE, NoopTreapOps> {
        static inline void updateAgr(NODE *cur) {
        }
    };

    Node *root = nullptr;

    Node* doFind(Node *cur, int pos) {
        if (cur == nullptr) {
            return nullptr;
        }

        int curPos = Node::getSize(cur->left);
        if (curPos == pos) {
            return cur;
        } else if (curPos < pos) {
            return doFind(cur->right, pos - curPos - 1);
        } else {
            return doFind(cur->left, pos);
        }
    }

    pair<Node*, Node*> doSplit(Node *cur, int pos) {
        if (cur == nullptr) {
            return {nullptr, nullptr};
        }

        int leftSize = Node::getSize(cur->left);
        if (leftSize < pos) {
            auto nxt = doSplit(cur->right, pos - leftSize - 1);
            cur->right = nxt.first;
            doRecalcState(cur);
            return {cur, nxt.second};
        } else {
            auto nxt = doSplit(cur->left, pos);
            cur->left = nxt.second;
            doRecalcState(cur);
            return {nxt.first, cur};
        }
    }

    Node* doMerge(Node *left, Node *right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        if (left->prio > right->prio) {
            left->right = doMerge(left->right, right);
            doRecalcState(left);
            return left;
        } else {
            right->left = doMerge(left, right->left);
            doRecalcState(right);
            return right;
        }
    }

    void doRecalcState(Node *cur) {
        cur->size = Node::getSize(cur->left) + 1 + Node::getSize(cur->right);
        updateParent(cur, cur->left);
        updateParent(cur, cur->right);
        cur->parent = nullptr;
        AggregateLogic<Node, OPS>::updateAgr(cur);
    }

    Node* createNode(const T &val) {
        auto res = new Node(val, generateNextUnique());
        doRecalcState(res);
        return res;
    }

    void updateParent(Node *cur, Node *chld) {
        if (chld) {
            chld->parent = cur;
        }
    }

    // https://preshing.com/20121224/how-to-generate-a-sequence-of-unique-random-integers/
    unsigned int generateNextUnique() {
        static const unsigned int INTERMEDIATE_OFFSET = permuteQPR(permuteQPR(228) + 0x46790905);
        static unsigned int index = permuteQPR(permuteQPR(1377) + 0x682f0161);
        return permuteQPR((permuteQPR(index++) + INTERMEDIATE_OFFSET) ^ 0x5bf03635);
    }

    unsigned int permuteQPR(unsigned int x) {
        static const unsigned int PRIME = 4294967291;
        if (x >= PRIME) {
            return x;  // The 5 integers out of range are mapped to themselves.
        }
        unsigned int residue = ((unsigned long long) x * x) % PRIME;
        return (x <= PRIME / 2) ? residue : PRIME - residue;
    }
};
