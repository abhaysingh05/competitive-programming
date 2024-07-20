template <typename T_weight>
struct Dijkstra {
    const T_weight W_INF = numeric_limits<T_weight>::max() / 2;

    struct edge {
        int node = -1;
        T_weight weight = 0;

        edge() {}

        edge(int _node, T_weight _weight) : node(_node), weight(_weight) {}
    };

    struct state {
        T_weight dist;
        int node;

        state() {}

        state(T_weight _dist, int _node) : dist(_dist), node(_node) {}

        bool operator<(const state &other) const {
            return dist > other.dist;
        }
    };

    int n;
    vector<vector<edge>> adj;
    vector<T_weight> dist;
    vector<int> parent;

    Dijkstra(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        adj.assign(n, {});
    }

    void add_directional_edge(int a, int b, T_weight weight) {
        adj[a].emplace_back(b, weight);
    }

    void add_bidirectional_edge(int a, int b, T_weight weight) {
        add_directional_edge(a, b, weight);
        add_directional_edge(b, a, weight);
    }

    void dijkstra_check(priority_queue<state> &pq, int node, int from, T_weight new_dist) {
        if (new_dist < dist[node]) {
            dist[node] = new_dist;
            parent[node] = from;
            pq.emplace(new_dist, node);
        }
    }

    void dijkstra(const vector<int> &source) {
        if (n == 0) return;
        dist.assign(n, W_INF);
        parent.assign(n, -1);
        priority_queue<state> pq;

        for (int src : source)
            dijkstra_check(pq, src, -1, 0);

        while (!pq.empty()) {
            state top = pq.top();
            pq.pop();

            if (top.dist > dist[top.node])
                continue;

            for (edge &e : adj[top.node])
                dijkstra_check(pq, e.node, top.node, top.dist + e.weight);
        }
    }
};