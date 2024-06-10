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

struct boruvka_mst : DSU {

    struct edge {
        int u, v, wt;
    };

    int n;
    vector<vector<edge>> adj;
    vector<edge> T;
    int mst_wt = 0;

    boruvka_mst(int _n) : DSU(_n), n(_n), adj(_n) {}

    void add_edge(int _u, int _v, int _wt) {
        adj[_u].push_back(edge{_u, _v, _wt});
        adj[_v].push_back(edge{_v, _u, _wt});
    }

    int find_mst() {
        while (count() > 1) {
            vector<edge> min_edge(n, {-1, -1, INT_MAX});

            for (int u = 0; u < n; ++u) {
                for (auto &e : adj[u]) {
                    if (!same(e.u, e.v)) {
                        if (e.wt < min_edge[set_u].wt) min_edge[set_u] = e;
                        if (e.wt < min_edge[set_v].wt) min_edge[set_v] = e;
                    }
                }
            }

            for (int i = 0; i < n; ++i) {
                if (min_edge[i].u != -1 && !same(min_edge[i].u, min_edge[i].v)) {
                    merge(min_edge[i].u, min_edge[i].v);
                    T.push_back(min_edge[i]);
                    mst_wt += min_edge[i].wt;
                }
            }
        }
        return mst_wt;
    }

    // Can do some operations of MST, Edges are in T.
};