template <typename T>
struct fenwick {
    vector<T> f;

    void init(int n) {
        f.assign(n + 1, 0);
    }

    T sum(int r) { // exclusive
        if (r == 0)
            return 0;
        r--;
        T result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            result += f[r];
        return result;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void inc(int i, T x) {
        for (; i < f.size(); i = (i | (i + 1)))
            f[i] += x;
    }

    void init(vector<T> a) {
        int n = a.size();
        init(n);
        for (int i = 0; i < n; i++) {
            inc(i, a[i]);
        }
    }
};