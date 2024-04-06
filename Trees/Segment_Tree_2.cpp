#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int t[4 * MAXN];

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int add) {
    if (l > r)
        return;
    if (l == tl && r == tr) {
        t[v] += add;
    } else {
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), add);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, add);
    }
}

int get(int v, int tl, int tr, int pos) {
    if (tl == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return t[v] + get(v * 2, tl, tm, pos);
    else
        return t[v] + get(v * 2 + 1, tm + 1, tr, pos);
}

int main() {
    // Example usage
    int a[] = {1, 2, 3, 4, 5};
    int n = sizeof(a) / sizeof(a[0]);

    build(a, 1, 0, n - 1);
    update(1, 0, n - 1, 2, 4, 2); // Add 2 to elements in range [2, 4]

    // Query individual elements
    for (int i = 0; i < n; ++i) {
        cout << get(1, 0, n - 1, i) << " ";
    }
    cout << "\n";

    return 0;
}
