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

struct minimum_arborescence {
    // Time Complexity - O(m * n)
    struct edge {
        int src, dst, wt, id = -1;
    };

    int n, m = 0;
    DSU uf;
    vector<vector<edge>> adj;
    vector<edge> edges;
    vector<edge> T; // edges from i = 1
    int mst_wt = 0;

    minimum_arborescence(int _n) : n(_n), uf(n), adj(n) {}

    void add_edge(int u, int v, int wt) {
        edges.push_back({u, v, wt, m++});
        adj[v].push_back(edges.back());
    }

    vector<edge> find_min(int r) {
        vector<int> vis(n, -1), mn(n, 1e9);
        vector<edge> par(n);
        DSU tmp = uf;
        vector<int> seq;

        for (int i = 0; i < n; i++) {
            if (uf.find(i) != i) continue;
            int at = i;
            while (at != r && vis[at] == -1) {
                vis[at] = i;
                for (auto &v : adj[at]) {
                    if (v.wt < mn[at] && uf.find(v.src) != at) {
                        mn[at] = v.wt;
                        par[at] = v;
                    }
                }
                if (par[at].id == -1) return {};
                at = uf.find(par[at].src);
            }
            if (at == r || vis[at] != i) continue;
            do {
                seq.push_back(at);
            } while ((at = uf.find(par[at].src)) != seq.front());
            for (auto &v : seq) uf.merge(v, seq[0]);
            int c = uf.find(seq[0]);
            vector<edge> nw;
            for (auto &v : seq) {
                for (auto &w : adj[v]) {
                    nw.push_back({w.src, w.dst, w.wt - mn[v], w.id});
                }
            }
            adj[c] = nw;
            vector<edge> rest = find_min(r);
            if (rest.size() == 0) return {};
            edge use = rest[c];
            rest[at = tmp.find(use.dst)] = use;
            for (auto &v : seq) {
                if (v != at) rest[v] = par[v];
            }
            return rest;
        }
        return par;
    }

    int find_mst(int r) {
        T = find_min(r);
        if (T.empty()) return -1;
        for (int i = 1; i < T.size(); i++) {
            T[i] = edges[T[i].id];
            mst_wt += T[i].wt;
        }
        return mst_wt;
    }
};