
using Graph = vector<vector<int>>;

struct TreeOps {
public:
    TreeOps(const Graph &g, int root = 0): g(g), n(g.size()), root(root) {
    }

    void lcaInit() {
        doInitLca();
    }

    int lca(int u, int v) {
        if (checkAncestor(u, v)) {
            return v;
        }
        if (checkAncestor(v, u)) {
            return u;
        }

        int cur = v;
        for (int i = ln-1; i >= 0; i--) {
            int nxt = up[cur][i];
            if (nxt != -1 && !checkAncestor(u, nxt)) {
                cur = nxt;
            }
        }

        return up[cur][0];
    }

    int getParent(int v) {
        return up[v][0];
    }

    bool checkAncestor(int v, int p) {
        return tin[p] <= tin[v] && tout[v] <= tout[p];
    }

private:
    int n;
    Graph g;
    vector<int> tin, tout, depth;
    int root;
    int ln;
    vector<vector<int>> up;

    void doInitLca() {
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);

        for (ln = 1; (1<<ln) < n; ln++) {
        }
        up.assign(n, vector<int>(ln, -1));

        int timer = 0;
        doLcaDfs(root, -1, timer);
    }

    void doLcaDfs(int v, int p, int &timer) {
        tin[v] = timer++;
        depth[v] = depth[p] + 1;

        up[v][0] = p;
        for (int i = 1; i < ln; i++) {
            int prev = up[v][i-1];
            if (prev != -1) {
                up[v][i] = up[prev][i-1];
            }
        }

        for (int u: g[v]) {
            if (u != p) {
                doLcaDfs(u, v, timer);
            }
        }

        tout[v] = timer++;
    }
};

