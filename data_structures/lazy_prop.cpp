struct lazySeg {
    typedef int64_t item;

    // item zeroSum = inf;
    item zeroSum = 0LL;

    // item zeroAdd = 1LL;
    item zeroAdd = 0LL;

    item calc(item a, item b) {
        // return min(a, b);
        return a + b;
    }

    item modify(item a, item b) {
        // return a * b;
        return a + b;
    }

    vector<item> sums;
    vector<item> adds;

    int size;

    void propogate(int n, int len) {
        // len = 1; // for multiplication modify
        sums[n] = modify(len * adds[n], sums[n]);
        if (2 * n + 1 < 2 * size) adds[2 * n + 1] = modify(adds[n], adds[2 * n + 1]);
        if (2 * n + 2 < 2 * size) adds[2 * n + 2] = modify(adds[n], adds[2 * n + 2]);
        adds[n] = zeroAdd;
    }

    void set(int i, item x, int n, int L, int R) {
        if (R == L + 1) {
            sums[n] = x;
            adds[n] = zeroAdd;
            return;
        }
        if (adds[n] != zeroAdd) propogate(n, R - L);
        int M = (L + R) >> 1;
        if (i < M) {
            set(i, x, 2 * n + 1, L, M);
        } else {
            set(i, x, 2 * n + 2, M, R);
        }
        sums[n] = calc(sums[2 * n + 1], sums[2 * n + 2]);
    }

    item get(int i, int n, int L, int R) {
        if (R == L + 1) {
            if (adds[n] != zeroAdd) propogate(n, R - L);
            return sums[n];
        }
        if (adds[n] != zeroAdd) propogate(n, R - L);
        int M = (L + R) >> 1;
        if (i < M) {
            return get(i, 2 * n + 1, L, M);
        } else {
            return get(i, 2 * n + 2, M, R);
        }
    }

    item sum(int l, int r, int n, int L, int R) {
        if (l >= R || L >= r) return zeroSum;
        if (L >= l && R <= r) {
            if (adds[n] != zeroAdd) propogate(n, R - L);
            return sums[n];
        }
        if (adds[n] != zeroAdd) propogate(n, R - L);
        int M = (L + R) >> 1;
        return calc(sum(l, r, 2 * n + 1, L, M), sum(l, r, 2 * n + 2, M, R));
    }

    void add(int l, int r, item v, int n, int L, int R) {
        if (l >= R || L >= r) return;
        if (L >= l && R <= r) {
            adds[n] = modify(adds[n], v);
            if (adds[n] != zeroAdd) propogate(n, R - L);
            return;
        }
        if (adds[n] != zeroAdd) propogate(n, R - L);
        int M = (L + R) >> 1;
        add(l, r, v, 2 * n + 1, L, M);
        add(l, r, v, 2 * n + 2, M, R);
        sums[n] = modify(calc(sums[2 * n + 1], sums[2 * n + 2]), adds[n]);
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, zeroSum);
        adds.assign(2 * size, zeroAdd);
    }

    void init(vector<item> a) {
        int n = a.size();
        init(n);
        for (int i = 0; i < n; i++) {
            sums[size - 1 + i] = a[i];
        }
        for (int i = size - 2; i >= 0; i--) {
            sums[i] = calc(sums[2 * i + 1], sums[2 * i + 2]);
        }
    }

    void set(int i, item x) {
        set(i, x, 0, 0, size);
    }

    item get(int i) {
        return get(i, 0, 0, size);
    }

    item sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    void add(int l, int r, item v) {
        add(l, r, v, 0, 0, size);
    }
};