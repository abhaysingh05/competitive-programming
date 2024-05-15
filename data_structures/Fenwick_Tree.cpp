#include <bits/stdc++.h>

#define long long long int
using namespace std;

struct fenwick {
    vector<long> f;

    void init(int n) {
        f.assign(n + 1, 0);
    }

    long sum(int r) { // exclusive
        if (r == 0)
            return 0;
        r--;
        long result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            result += f[r];
        return result;
    }

    long sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void inc(int i, long x) {
        for (; i < f.size(); i = (i | (i + 1)))
            f[i] += x;
    }

    void init(vector<long> a) {
        int n = a.size();
        init(n);
        for (int i = 0; i < n; i++) {
            inc(i, a[i]);
        }
    }
};

struct test {
    void solve() {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> b(n);
        for (int i = 0; i < n; i++) cin >> b[i];
        int m;
        cin >> m;
        vector<int> x(m);
        for (int i = 0; i < m; i++) cin >> x[i];
        sort(x.begin(), x.end());

        map<int, vector<int>> bb;
        for (int i = 0; i < n; i++) {
            bb[b[i]].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            if (a[i] < b[i]) {
                cout << "No\n";
                return;
            }
        }

        fenwick fn;
        fn.init(n);
        for (int i = 0; i < n; i++) fn.inc(i, 1);
        int j = 0;
        for (auto &p : bb) {
            int last = -1;
            int need = false;
            int cn = 0;
            for (int i : p.second) {
                if (last != -1) {
                    if (fn.sum(last + 1, i) > 0) {
                        if (need) {
                            cn++;
                        }
                        need = false;
                    }
                }
                if (a[i] != b[i]) need = true;
                fn.inc(i, -1);
                last = i;
            }
            if (need) cn++;
            //            cout << p.first << " " << cn << "\n";
            while (cn) {
                if (j == m) {
                    cout << "No\n";
                    return;
                }
                if (x[j] == p.first) {
                    cn--;
                }
                j++;
            }
        }
        cout << "Yes\n";
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        test().solve();
    }

    return 0;
}