template <typename T>
struct lazySeg {

    // T zeroSum = inf;
    T zeroSum = 0LL;

    // T zeroAdd = 1LL;
    T zeroAdd = 0LL;

    T calc(T a, T b) {
        // return min(a, b);
        return a + b;
    }

    T modify(T a, T b) {
        // return a * b;
        return a + b;
    }

    vector<T> sums;
    vector<T> adds;

    int size;

    void propogate(int n, int len) {
        // len = 1; // for multiplication modify
        sums[n] = modify(len * adds[n], sums[n]);
        if (2 * n + 1 < 2 * size) adds[2 * n + 1] = modify(adds[n], adds[2 * n + 1]);
        if (2 * n + 2 < 2 * size) adds[2 * n + 2] = modify(adds[n], adds[2 * n + 2]);
        adds[n] = zeroAdd;
    }

    void set(int i, T x, int n, int L, int R) {
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

    T get(int i, int n, int L, int R) {
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

    T sum(int l, int r, int n, int L, int R) {
        if (l >= R || L >= r) return zeroSum;
        if (L >= l && R <= r) {
            if (adds[n] != zeroAdd) propogate(n, R - L);
            return sums[n];
        }
        if (adds[n] != zeroAdd) propogate(n, R - L);
        int M = (L + R) >> 1;
        return calc(sum(l, r, 2 * n + 1, L, M), sum(l, r, 2 * n + 2, M, R));
    }

    void add(int l, int r, T v, int n, int L, int R) {
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

    void init(vector<T> a) {
        int n = a.size();
        init(n);
        for (int i = 0; i < n; i++) {
            sums[size - 1 + i] = a[i];
        }
        for (int i = size - 2; i >= 0; i--) {
            sums[i] = calc(sums[2 * i + 1], sums[2 * i + 2]);
        }
    }

    void set(int i, T x) {
        set(i, x, 0, 0, size);
    }

    T get(int i) {
        return get(i, 0, 0, size);
    }

    T sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    void add(int l, int r, T v) {
        add(l, r, v, 0, 0, size);
    }
};