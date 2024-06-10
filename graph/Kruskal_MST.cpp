struct DSU {
    vector<int> par, rnk, sz;
    int c;
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
        for (int i = 1; i <= n; ++i) par[i] = i;
    }
    int find(int i) {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(int i, int j) {
        return find(i) == find(j);
    }
    int get_size(int i) {
        return sz[find(i)];
    }
    int count() {
        return c; // connected components
    }
    int merge(int i, int j) {
        if ((i = find(i)) == (j = find(j)))
            return -1;
        else
            --c;
        if (rnk[i] > rnk[j]) swap(i, j);
        par[i] = j;
        sz[j] += sz[i];
        if (rnk[i] == rnk[j]) rnk[j]++;
        return j;
    }
};

struct kruskal_mst : DSU {

    int n;

    kruskal_mst(int _n) : DSU(_n), n(_n) {}

    struct edge {
        int u, v, wt;
    };

    vector<edge> E;
    vector<edge> T;
    int mst_wt = 0;

    void add_edge(int _u, int _v, int _wt) {
        E.push_back(edge{_u, _v, _wt});
    }

    int find_mst() {
        sort(E.begin(), E.end(), [](edge A, edge B) { return A.wt < B.wt; });
        for (auto &[u, v, wt] : E) {
            if (!same(u, v)) {
                merge(u, v);
                T.push_back(edge{u, v, wt});
                mst_wt += wt;
            }
        }
        return mst_wt;
    }

    // Can do some operations of MST, Edges are in T.
};