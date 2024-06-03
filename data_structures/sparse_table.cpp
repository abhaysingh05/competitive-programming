/*
precalc: O(n*log(n))
query: O(1)
*/

struct sparse {
    int n;
    int k;
    vector<vector<int64_t>> sp;

    int logg(int n) { return n ? __builtin_clz(1) - __builtin_clz(n) : -1; }

    int64_t argmin(int64_t a, int64_t b) { return min(a, b); }

    void precalc() {
        for (int j = 1; j <= k; j++) {
            for (int i = 0; i <= n - (1 << j); i++) {
                sp[i][j] = argmin(sp[i][j - 1], sp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    void init(vector<int64_t> a) {
        n = a.size();
        k = logg(n);
        sp.resize(n, vector<int64_t>(k + 1));
        for (int i = 0; i < n; i++) {
            sp[i][0] = a[i];
        }
        precalc();
    }

    int64_t calc(int l, int r) {
        int p = logg(r - l);
        return argmin(sp[l][p], sp[r - (1 << p)][p]);
    }
};