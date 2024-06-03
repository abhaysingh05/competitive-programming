struct undir_graph {

    int n; // 0 - based
    vector<vector<int>> adj;
    vector<int> T_in, label, up, arti_points;
    vector<bool> vis, state, mark;
    map<pair<int, int>, int> arti_label;
    stack<pair<int, int>> arti_buff;
    stack<int> buff;
    int comp = 0, time = 0, arti = 0; // types of edges
    bool cycle = false;

    undir_graph(int n) : n(n), adj(n), vis(n, false), state(n, false), T_in(n), label(n), up(n), mark(n, false) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v) {
        vis[v] = true;
        state[v] = true;
        for (int u : adj[v]) {
            if (!vis[u])
                dfs(u);
            else if (state[u])
                cycle = true;
        }
        state[v] = false;
    }

    void dfs(int v, int p) {
        T_in[v] = time++;
        up[v] = T_in[v];
        mark[v] = true;
        bool ap = false;
        int child = 0;
        buff.push(v);
        for (int &u : adj[v]) {
            if (u == p) continue;
            int a = u, b = v;
            if (a > b) swap(a, b);
            pair<int, int> pr = {a, b};
            arti_buff.push(pr);
            if (mark[u]) {
                up[v] = min(up[v], T_in[u]);
            } else {
                dfs(u, v);
                up[v] = min(up[v], up[u]);
                child++;
                ap = ap || (up[u] >= T_in[v] && p != -1);
                if (up[u] >= T_in[v]) {
                    while (true) {
                        pair<int, int> x = arti_buff.top();
                        arti_buff.pop();
                        arti_label[x] = arti;
                        if (x == pr) break;
                    }
                    arti++;
                }
            }
        }
        if (ap || (p == -1 && child > 1)) {
            arti_points.push_back(v);
        }
        if (p == -1 || (up[v] > T_in[p])) {
            while (true) {
                int u = buff.top();
                buff.pop();
                label[u] = comp;
                if (u == v) break;
            }
            comp++;
        }
    }

    int connected_comp() {
        int res = 0;
        for (int u = 0; u < n; u++) {
            if (!vis[u]) {
                res++;
                dfs(u);
            }
        }
        return res;
    }

    int bi_connectivity() {
        // also for articulation points
        for (int u = 0; u < n; u++) {
            if (!mark[u]) {
                dfs(u, -1);
            }
        }
        return comp;
    }

    int arti_edge(int v, int u) {
        if (v > u) swap(v, u);
        return arti_label[{v, u}];
    }
};