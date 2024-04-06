#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define all(x) x.begin(), x.end()
// #define int long long
const int INF = (int)1e9;
const int mod = INF + 7;
/**************************************************************************************/
int value = 0;
void runCase(int &testCase) {
    // cout << "#Case " << testCase << ": \n";
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &e : arr) cin >> e;
    vector<int> segmentTree(4 * n);
    function<void(int, int, int)> buildSegmentTree = [&](int index, int low, int high) {
        value++;
        if (low == high) {
            segmentTree[index] = arr[low];
        } else {
            int mid = (low + high) / 2;
            buildSegmentTree(2 * index + 1, low, mid);
            buildSegmentTree(2 * index + 2, mid + 1, high);
            segmentTree[index] = segmentTree[2 * index + 1] + segmentTree[2 * index + 2];
        }
    };
    function<int(int, int, int, int, int)>
        querySum = [&](int index, int low, int high, int l, int r) {
            value++;
            if (l > r) return 0;
            if (l == low && r == high) return segmentTree[index];
            int mid = (low + high) / 2;
            return (querySum(2 * index + 1, low, mid, l, min(mid, r)) + querySum(2 * index + 2, mid + 1, high, max(l, mid + 1), r));
        };
    function<void(int, int, int, int, int)> updateQuery = [&](int index, int low, int high, int pos, int val) {
        if (low == high) {
            segmentTree[index] = val;
        } else {
            int mid = (low + high) / 2;
            if (pos <= mid)
                updateQuery(index * 2 + 1, low, mid, pos, val);
            else
                updateQuery(index * 2 + 2, mid + 1, high, pos, val);
            segmentTree[index] = segmentTree[index * 2 + 1] + segmentTree[index * 2 + 2];
        }
    };
    buildSegmentTree(0, 0, n - 1);
    cout << value << "\n";
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << querySum(0, 0, n - 1, l - 1, r - 1) << ' ';
    }
    cout << "\n";
    cout << value << "\n";
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int tests = 1;
    cin >> tests;
    for (int i = 1; i <= tests; i++) runCase(i);

    return 0;
}