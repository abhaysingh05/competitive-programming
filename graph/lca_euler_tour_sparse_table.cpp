// https://codeforces.com/contest/342/problem/E

/*
precalc: O(n*log(n))
query: O(1)
*/

struct tree {
    int n;
    vector<vector<int>> adj;
    vector<int> pos, tour, depth;
    vector<vector<int>> table;

    int logg(int n) { return n ? __builtin_clz(1) - __builtin_clz(n) : -1; }

    tree(int n) : n(n), adj(n) {}

    void add_edge(int s, int t) {
        adj[s].push_back(t);
        adj[t].push_back(s);
    }

    int argmin(int i, int j) { return depth[i] < depth[j] ? i : j; }

    void rootify(int r) {
        pos.resize(n);

        function<void(int, int, int)> dfs = [&](int u, int p, int d) {
            pos[u] = depth.size();
            tour.push_back(u);
            depth.push_back(d);
            for (int v : adj[u]) {
                if (v != p) {
                    dfs(v, u, d + 1);
                    tour.push_back(u);
                    depth.push_back(d);
                }
            }
        };

        dfs(r, r, 0);
        int k = logg(tour.size());
        table.resize(k + 1, vector<int>(tour.size()));
        iota(table[0].begin(), table[0].end(), 0);
        for (int h = 0; h < k; ++h)
            for (int i = 0; i + (1 << h) < tour.size(); ++i)
                table[h + 1][i] = argmin(table[h][i], table[h][i + (1 << h)]);
    }

    int lca(int u, int v) {
        int i = pos[u], j = pos[v];
        if (i > j) swap(i, j);
        int h = logg(j - i);
        return i == j ? u : tour[argmin(table[h][i], table[h][j - (1 << h)])];
    }

    int dep(int v) { return depth[pos[v]]; }

    int dist(int u, int v) {
        int l = lca(u, v);
        return dep(u) + dep(v) - (dep(l) << 1);
    }
};
