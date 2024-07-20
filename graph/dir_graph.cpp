struct dir_graph {

    int n; // 0 - based
    vector<vector<int>> adj;
    vector<vector<int>> adj_rev;
    vector<bool> vis, state;
    vector<int> topsort, label;
    bool isCycle = false;
    int st_conn_comp = 0;

    dir_graph(int n) : n(n), adj(n), adj_rev(n), vis(n, false), label(n, -1), state(n, false) {}

    void add_edge(int u, int v) { // u->v
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    void dfs(int v) {
        vis[v] = true;
        state[v] = true;
        for (int &u : adj[v]) {
            if (!vis[u])
                dfs(u);
            else if (state[u])
                isCycle = true;
        }
        state[v] = false;
        topsort.push_back(v);
    }

    bool topological_sort() {
        for (int v = 0; v < n; v++) {
            if (!vis[v]) dfs(v);
        }
        reverse(topsort.begin(), topsort.end());
        return !isCycle;
    }

    int strongly_connected_comp() {
        function<void(int, int)> dfs2 = [&](int v, int lb) -> void {
            label[v] = lb;
            for (int &u : adj_rev[v]) {
                if (label[u] == -1) dfs2(u, lb);
            }
        };
        topological_sort();
        for (int &v : topsort) {
            if (label[v] == -1) {
                dfs2(v, st_conn_comp);
                st_conn_comp++;
            }
        }
        return st_conn_comp;
    }
};