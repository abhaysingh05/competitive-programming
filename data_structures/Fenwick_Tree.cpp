struct fenwick {
    vector<int64_t> f;

    void init(int n) {
        f.assign(n + 1, 0);
    }

    int64_t sum(int r) { // exclusive
        if (r == 0)
            return 0;
        r--;
        int64_t result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            result += f[r];
        return result;
    }

    int64_t sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void inc(int i, int64_t x) {
        for (; i < f.size(); i = (i | (i + 1)))
            f[i] += x;
    }

    void init(vector<int64_t> a) {
        int n = a.size();
        init(n);
        for (int i = 0; i < n; i++) {
            inc(i, a[i]);
        }
    }
};