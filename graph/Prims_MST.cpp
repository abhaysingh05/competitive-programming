struct prims_mst {

    struct Edge {
        int u, v, wt;
    };
    struct edge {
        int wt = INT32_MAX, v = -1;
        bool operator<(edge const &other) const {
            return make_pair(wt, v) < make_pair(other.wt, other.v);
        }
    };

    int n;
    vector<vector<edge>> adj;

    prims_mst(int _n) : n(_n), adj(_n) {}

    vector<Edge> T;
    int mst_wt = 0;

    void add_edge(int _u, int _v, int _wt) {
        adj[_u].push_back(edge{_wt, _v});
        adj[_v].push_back(edge{_wt, _u});
    }

    int find_mst() {
        vector<edge> d(n);
        d[0].wt = 0;
        set<edge> pq;
        pq.insert({0, 0});
        vector<bool> A(n, false);
        for (int i = 0; i < n; i++) {
            int v = pq.begin()->v;
            A[v] = true;
            mst_wt += pq.begin()->wt;
            pq.erase(pq.begin());
            if (d[v].v != -1) T.push_back(Edge{v, d[v].v, d[v].wt});
            for (auto &e : adj[v]) {
                if (!A[e.v] && e.wt < d[e.v].wt) {
                    pq.erase(edge{d[e.v].wt, e.v});
                    d[e.v] = {e.wt, v};
                    pq.insert(e);
                }
            }
        }
        return mst_wt;
    }

    // Can do some operations of MST, Edges are in T.
};