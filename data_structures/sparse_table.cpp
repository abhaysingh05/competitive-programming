/*
precalc: O(n*log(n))
query: O(1)
*/
struct sparse {
    int n;
    int k;
    vector<vector<long>> sp;

    int logg(int n) { return n ? __builtin_clz(1) - __builtin_clz(n) : -1; }

    long argmin(long a, long b) { return min(a, b); }

    void precalc() {
        for (int j = 1; j <= k; j++) {
            for (int i = 0; i <= n - (1 << j); i++) {
                sp[i][j] = calc(sp[i][j - 1], sp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    void init(vector<long> a) {
        n = a.size();
        k = logg(n);
        sp.resize(n, vector<long>(k + 1));
        for (int i = 0; i < n; i++) {
            sp[i][0] = a[i];
        }
        precalc();
    }

    long calc(int l, int r) {
        int p = logg(r - l);
        return argmin(sp[l][p], sp[r - (1 << p)][p]);
    }
};