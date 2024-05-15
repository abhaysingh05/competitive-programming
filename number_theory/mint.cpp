/*
1. Struct mint: This is a custom struct representing an element in a finite field modulo a given value mod. It has a single member value which stores the actual value of the element.
2 .Constructor: There is a constructor that allows creating mint objects from integers. It takes care of normalizing the value to ensure it's within the range [0, mod).
3. Operators: Overloaded operators (==, +, *, +=) are defined to perform arithmetic operations on mint objects.
4. Function power: This function computes the power of a mint object. It uses binary exponentiation to efficiently compute powers.
5. Function inv: This function computes the modular inverse of a mint object using Fermat's little theorem.
6. Precomputation: There are vectors fact_precalc and inv_fact_precalc used for precomputing factorials and their inverses. These are used to speed up factorial computations.
7. Functions ensure_fact, fact, inv_fact: These functions are used to ensure that the precomputed factorials and their inverses are available up to a certain value n. They compute and store these values as needed.
8. Function calc_c: This function computes the binomial coefficient "n choose k" modulo mod using precomputed factorials and their inverses.
*/
#include <bits/stdc++.h>
// https://codeforces.com/contest/1761/problem/D
#define long long long int
using namespace std;

int mod = 1000000007;

struct mint {
    int value = 0;

    constexpr mint() : value() {}

    mint(const long &x) {
        value = normalize(x);
    }

    static long normalize(const long &x) {
        long v = x % mod;
        if (v < 0) v += mod;
        return v;
    }

    bool operator==(const mint &x) { return value == x.value; };

    mint operator+(const mint &x) { return value + x.value; };

    mint operator*(const mint &x) { return (long) value * x.value; };

    void operator+=(const mint &x) { value = normalize(value + x.value); };
};

mint power(mint a, long b) {
    mint res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

mint inv(mint a) {
    return power(a, mod - 2);
}

vector<mint> fact_precalc(1, 1);
vector<mint> inv_fact_precalc(1, 1);

void ensure_fact(int n) {
    while (n >= fact_precalc.size()) {
        fact_precalc.push_back(fact_precalc.back() * fact_precalc.size());
        inv_fact_precalc.push_back(inv(fact_precalc.back()));
    }
}

mint fact(int n) {
    ensure_fact(n);
    return fact_precalc[n];
}

mint inv_fact(int n) {
    ensure_fact(n);
    return inv_fact_precalc[n];
}

mint calc_c(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    mint res = fact(n);
    res = res * inv_fact(k);
    res = res * inv_fact(n - k);
    return res;
}


int main() {
    ios::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    fact_precalc.resize(n + 1);
    fact_precalc[0] = 1;
    for (int i = 1; i < fact_precalc.size(); i++) {
        fact_precalc[i] = fact_precalc[i - 1] * i;
    }
    inv_fact_precalc.resize(n + 1);
    inv_fact_precalc[n] = inv(fact_precalc[n]);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact_precalc[i] = inv_fact_precalc[i + 1] * (i + 1);
    }

    vector<mint> p3(n + 1);
    p3[0] = 1;
    for (int i = 1; i <= n; i++) {
        p3[i] = p3[i - 1] * 3;
    }

    if (k == 0) {
        cout << p3[n].value << "\n";
        return 0;
    }

    mint res = 0;
    for (int i = 1; i <= k; i++) {
        if (i + i <= n) {
            mint r = calc_c(k - 1, i - 1);
            r = r * calc_c(n - k, i);
            r = r * p3[n - 2 * i];
            res += r;
        }
        if (i + i - 1 <= n) {
            mint r = calc_c(k - 1, i - 1);
            r = r * calc_c(n - k, i - 1);
            r = r * p3[n - 2 * i + 1];
            res += r;
        }
    }
    cout << res.value << "\n";

    return 0;
}