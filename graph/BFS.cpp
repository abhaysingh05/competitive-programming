
struct BFS {
    struct edge {
        int node = -1, weight = -1;
        edge() {}
        edge(int _node, int _weight) : node(_node), weight(_weight) {}
    };

    int n, INF;
    vector<vector<edge>> adj;
    vector<int> dist;
    vector<int> parent;

    BFS(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        INF = int(1e9) + 5;
        n = _n;
        adj.assign(n, {});
    }

    void add_directional_edge(int a, int b, int weight) {
        assert(0 <= weight && weight <= 1);
        adj[a].emplace_back(b, weight);
    }

    void add_bidirectional_edge(int a, int b, int weight) {
        assert(0 <= weight && weight <= 1);
        adj[a].emplace_back(b, weight);
        adj[b].emplace_back(a, weight);
    }

    void bfs_check(queue<int> &q, queue<int> &next_q, int node, int from, int new_dist, int add) {
        assert(add == 0 || add == 1);

        if (new_dist < dist[node]) {
            dist[node] = new_dist;
            parent[node] = from;
            (add == 0 ? q : next_q).push(node);
        }
    }

    void bfs(const vector<int> &source) {
        if (n == 0) return;

        // Two queues are needed for 0-1 BFS.
        queue<int> q, next_q;
        dist.assign(n, INF);
        parent.assign(n, -1);

        for (int src : source)
            bfs_check(q, next_q, src, -1, 0, 0);

        int level = 0;

        while (!q.empty() || !next_q.empty()) {
            while (!q.empty()) {
                int top = q.front();
                q.pop();

                if (level > dist[top])
                    continue;

                for (edge &e : adj[top])
                    bfs_check(q, next_q, e.node, top, dist[top] + e.weight, e.weight);
            }

            swap(q, next_q);
            level++;
        }
    }
};