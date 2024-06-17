// https://codeforces.com/contest/1657/submission/265618963

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

struct Hash {

    int b, n; // b = number of hashes
    const int mod = 1e9 + 7;
    vector<vector<int>> fw, bc, pb, ib;
    vector<int> bases;

    int power(int x, int y) {
        if (y == 0) {
            return 1;
        }

        int v = power(x, y / 2);
        v = 1LL * v * v % mod;
        if (y & 1)
            return 1LL * v * x % mod;
        else
            return v;
    }

    void init(int nn, int bb, string str) {
        // 1 - indexed
        n = nn;
        b = bb;
        fw = vector<vector<int>>(b, vector<int>(n + 2, 0));
        bc = vector<vector<int>>(b, vector<int>(n + 2, 0));
        pb = vector<vector<int>>(b, vector<int>(n + 2, 1));
        ib = vector<vector<int>>(b, vector<int>(n + 2, 1));
        bases = vector<int>(b);
        str = "0" + str;

        for (auto &x : bases) x = RNG() % (mod / 10);

        for (int i = 0; i < b; i++) {
            for (int j = 1; j <= n + 1; j++) {
                pb[i][j] = 1LL * pb[i][j - 1] * bases[i] % mod;
            }
            ib[i][n + 1] = power(pb[i][n + 1], mod - 2);
            for (int j = n; j >= 1; j--) {
                ib[i][j] = 1LL * ib[i][j + 1] * bases[i] % mod;
            }

            for (int j = 1; j <= n; j++) {
                fw[i][j] = (fw[i][j - 1] + 1LL * (str[j] - 'a' + 1) * pb[i][j]) % mod;
            }
            for (int j = n; j >= 1; j--) {
                bc[i][j] = (bc[i][j + 1] + 1LL * (str[j] - 'a' + 1) * pb[i][n + 1 - j]) % mod;
            }
        }
    }

    int getfwhash(int l, int r, int i) {
        int ans = fw[i][r] - fw[i][l - 1];
        ans = 1LL * ans * ib[i][l - 1] % mod;

        if (ans < 0) ans += mod;

        return ans;
    }

    int getbchash(int l, int r, int i) {
        int ans = bc[i][l] - bc[i][r + 1];
        ans = 1LL * ans * ib[i][n - r] % mod;

        if (ans < 0) ans += mod;

        return ans;
    }

    bool equal(int l1, int r1, int l2, int r2) {
        for (int i = 0; i < b; i++) {
            int v1, v2;
            if (l1 <= r1)
                v1 = getfwhash(l1, r1, i);
            else
                v1 = getbchash(r1, l1, i);

            if (l2 <= r2)
                v2 = getfwhash(l2, r2, i);
            else
                v2 = getbchash(r2, l2, i);

            if (v1 != v2) return false;
        }
        return true;
    }

    bool pal(int l, int r) {
        return equal(l, r, r, l);
    }
};