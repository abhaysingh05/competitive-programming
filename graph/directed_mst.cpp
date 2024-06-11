struct RollbackUF {
    vector<int> e;
    vector<pair<int, int>> st;

    RollbackUF(int n) : e(n, -1) {}

    int get_size(int x) { return -e[find(x)]; }

    int find(int x) { return e[x] < 0 ? x : find(e[x]); }

    int time() { return st.size(); }

    void rollback(int t) {
        for (int i = time(); i-- > t;)
            e[st[i].first] = st[i].second;
        st.resize(t);
    }

    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        st.push_back({a, e[a]});
        st.push_back({b, e[b]});
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};

struct DMST {
    // Time Complexity : O(m * log(n))
    struct Edge {
        int a, b;
        int64_t wt;
    };

    int n;
    vector<Edge> Edges;

    DMST(int n) : n(n) {}

    void add_edge(int a, int b, int64_t wt) {
        Edges.push_back({a, b, wt});
    }

    struct Node { /// lazy skew heap node
        int key;
        int id;
        Node *l, *r;
        int64_t delta;
        void prop() {
            key += delta;
            if (l) l->delta += delta;
            if (r) r->delta += delta;
            delta = 0;
        }
        pair<int, int> top() {
            prop();
            return {key, id};
        }
    };

    Node *merge(Node *a, Node *b) {
        if (!a || !b) return a ?: b;
        a->prop(), b->prop();
        if (a->key > b->key) swap(a, b);
        swap(a->l, (a->r = merge(b, a->r)));
        return a;
    }

    void pop(Node *&a) {
        a->prop();
        a = merge(a->l, a->r);
    }

    pair<int64_t, vector<int>> dmst(int n, int root, vector<Edge> &E) {
        vector<Node *> heap(n);
        vector<int> seen(n, -1), pe(n, -1);
        seen[root] = root;
        RollbackUF uf(n);
        vector<tuple<int, int, vector<int>>> cycles; // (merged vertex, uf time, cycle eids)

        for (int i = 0; i < E.size(); ++i) {
            int u = E[i].b;
            heap[u] = merge(heap[u], new Node{E[i].wt, i});
        }

        for (int s = 0; s < n; ++s) {
            vector<int> path;

            for (int u = s; seen[u] < 0;) {
                if (!heap[u]) return {-1, {}};
                auto [w, eid] = heap[u]->top();
                pop(heap[u]);
                int pu = uf.find(E[eid].a);
                if (pu == u) continue; // Self-loop, ignore.
                if (heap[u]) heap[u]->delta -= w;
                path.push_back(eid);
                seen[u] = s;
                u = pu;
                if (seen[u] == s) { // Found a cycle of >= 2 vertices, contract!
                    int dsuTime = uf.time();
                    vector<int> cycle;
                    while (true) {
                        cycle.push_back(path.back());
                        int v = uf.find(E[path.back()].b);
                        path.pop_back();
                        if (!uf.join(u, v)) break;
                        heap[u] = merge(heap[u], heap[v]);
                    }
                    u = uf.find(u);
                    seen[u] = -1;
                    cycles.emplace_back(u, dsuTime, move(cycle));
                }
            }
            // Found path from root to s.
            for (int eid : path) pe[uf.find(E[eid].b)] = eid;
        }
        // Expand the cycles backwards to resolve the in-edges in original graph.
        while (!cycles.empty()) {
            auto &[u, t, cycle] = cycles.back();
            int newInEdge = pe[u];
            uf.rollback(t);
            // Restore in-edges in cycle except for the new in-edge.
            for (int eid : cycle) pe[uf.find(E[eid].b)] = eid;
            pe[uf.find(E[newInEdge].b)] = newInEdge;
            cycles.pop_back();
        }
        int64_t cost = 0;
        for (int i = 0; i < n; ++i) {
            if (i != root) {
                cost += E[pe[i]].wt;
            }
        }
        return {cost, pe};
    }

    pair<int64_t, vector<int>> find_mst(int r) {
        return dmst(n, r, Edges);
    }
};