struct segtree {
    typedef int64_t item;

    item zeroSum = 0;

    item calc(item a, item b) {
        return a + b;
    }

    vector<item> sums;

    int size;

    void set(int i, item x, int n, int L, int R) {
        if (R == L + 1) {
            sums[n] = x;
            return;
        }
        int M = (L + R) >> 1;
        if (i < M) {
            set(i, x, 2 * n + 1, L, M);
        } else {
            set(i, x, 2 * n + 2, M, R);
        }
        sums[n] = calc(sums[2 * n + 1], sums[2 * n + 2]);
    }

    item sum(int l, int r, int n, int L, int R) {
        if (l >= R || L >= r) return zeroSum;
        if (L >= l && R <= r) return sums[n];
        int M = (L + R) >> 1;
        return calc(sum(l, r, 2 * n + 1, L, M), sum(l, r, 2 * n + 2, M, R));
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, zeroSum);
    }

    void init(vector<item> a) {
        int n = a.size();
        init(n);
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, zeroSum);
        for (int i = 0; i < n; i++) {
            sums[size - 1 + i] = a[i];
        }
        for (int i = size - 2; i >= 0; i--) {
            sums[i] = calc(sums[2 * i + 1], sums[2 * i + 2]);
        }
    }

    void set(int i, item x) { set(i, x, 0, 0, size); }

    item sum(int l, int r) { return sum(l, r, 0, 0, size); }
};