struct Rollback_DSU {
    // Time-Complexity is not Ackermann-Func (No Path Compression)
    vector<int> par;
    vector<pair<int, int>> changes;

    Rollback_DSU(int n) : par(n, -1) {}

    int find(int a) {
        while (par[a] >= 0) a = par[a];
        return a;
    }

    int get_size(int a) return -par[find(a)]; // O(log n)

    bool merge(int a, int b) {
        int pa = get(a), pb = get(b);
        if (pa == pb) return false;
        if (par[pa] > par[pb]) swap(pa, pb);
        changes.push_back(pa, par[pa]);
        changes.push_back(pb, par[pb]);
        // Make smaller pb a child of larger pa.
        par[pa] += par[pb];
        par[pb] = pa;
        return true;
    }

    int save() return changes.size();

    void rollback(int version) {
        while (changes.size() > version) {
            auto &v = changes.back();
            par[v.first] = v.second;
            changes.pop_back();
        }
    }
};