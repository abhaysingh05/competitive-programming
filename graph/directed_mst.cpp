struct Rollback_DSU {
    // Time-Complexity is not Ackermann-Func (No Path Compression)
    vector<int> par;
    vector<pair<int, int>> changes;

    Rollback_DSU(int n) : par(n, -1) {}

    int find(int a) {
        while (par[a] >= 0) a = par[a];
        return a;
    }

    int get_size(int a) { return -par[find(a)]; } // O(log n)

    bool merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return false;
        if (par[pa] > par[pb]) swap(pa, pb);
        changes.push_back({pa, par[pa]});
        changes.push_back({pb, par[pb]});
        // Make smaller pb a child of larger pa.
        par[pa] += par[pb];
        par[pb] = pa;
        return true;
    }

    int save() { return changes.size(); }

    void rollback(int version) {
        while (changes.size() > version) {
            auto &v = changes.back();
            par[v.first] = v.second;
            changes.pop_back();
        }
    }
};

struct edge {
    int src, dst, wt, id;
};

struct skew_heap {
    struct node {
        node *ch[2];
        edge key;
        int delta;
        int id;
    } * root;
    skew_heap() : root(0) {}
    void propagate(node *a) {
        a->key.wt += a->delta;
        if (a->ch[0]) a->ch[0]->delta += a->delta;
        if (a->ch[1]) a->ch[1]->delta += a->delta;
        a->delta = 0;
    }
    node *merge(node *a, node *b) {
        if (!a || !b) return a ? a : b;
        propagate(a);
        propagate(b);
        if (a->key.wt > b->key.wt) swap(a, b);
        a->ch[1] = merge(b, a->ch[1]);
        swap(a->ch[0], a->ch[1]);
        return a;
    }
    void push(edge key) {
        node *n = new node();
        n->ch[0] = n->ch[1] = 0;
        n->id = key.id;
        n->key = key;
        n->delta = 0;
        root = merge(root, n);
    }
    void pop() {
        propagate(root);
        root = merge(root->ch[0], root->ch[1]);
    }
    pair<edge, int> top() {
        propagate(root);
        return {root->key, root->id};
    }
    bool empty() {
        return !root;
    }
    void add(int delta) {
        root->delta += delta;
    }
    void merge(skew_heap x) {
        root = merge(root, x.root);
    }
};

struct minimum_arborescence {

    struct fat_node {
        int node, dsu_ver;
        vector<int> edges_id;
    };

    int n, m = 0;
    vector<edge> edges;
    vector<edge> T;
    int mst_wt = 0;

    minimum_arborescence(int _n) : n(_n) {}

    void add_edge(int src, int dst, int wt) {
        edges.push_back({src, dst, wt, m++});
    }

    int find_mst(int r) {

        vector<skew_heap> heap(n);
        vector<int> seen(n, -1), seq(n, -1);
        Rollback_DSU uf(n);
        vector<fat_node> cycles;

        for (auto e : edges) heap[e.dst].push(e);
        seen[r] = r;

        for (int s = 0; s < n; ++s) {
            vector<int> path;
            for (int u = s; seen[u] < 0;) {
                if (heap[u].empty()) return -1;
                auto [min_e, _id] = heap[u].top();
                heap[u].pop();
                int v = uf.find(edges[_id].src);
                if (v == u) continue; // Self Loop
                if (!heap[u].empty()) heap[u].add(-min_e.wt);
                path.push_back(_id);
                seen[u] = s;
                u = v;
                if (seen[u] == s) {
                    // Contracting Cycles in fatNode
                    int dsu_version = uf.save();
                    vector<int> cycle;
                    skew_heap new_heap;
                    while (true) {
                        int w = path.back();
                        cycle.push_back(w);
                        int v = uf.find(edges[w].dst);
                        if (!uf.merge(u, v)) break;
                        new_heap.merge(heap[v]);
                    }
                    u = uf.find(u);
                    heap[u] = new_heap;
                    seen[u] = -1;
                    cycles.push_back({u, dsu_version, move(cycle)});
                }
            }
            // Found Path from root to s.
            for (int &_id : path) {
                seq[uf.find(edges[_id].dst)] = _id;
            }
        }
        // Decontraction
        while (!cycles.empty()) {
            auto big_node = cycles.back();
            int in_edge = seq[big_node.node];
            uf.rollback(big_node.dsu_ver);
            // Restore in-edges in cycle except for the new in-edge.
            for (int _id : big_node.edges_id) seq[uf.find(edges[_id].dst)] = _id;
            seq[uf.find(edges[in_edge].dst)] = in_edge;
            cycles.pop_back();
        }
        for (int i = 0; i < n; ++i) {
            if (i != r) {
                mst_wt += edges[seq[i]].wt;
            }
        }
        for (auto &_id : seq) T.push_back(edges[_id]);
        return mst_wt;
    }
};