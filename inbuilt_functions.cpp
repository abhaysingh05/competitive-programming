#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
constexpr int inf = (int)1e18;
constexpr int mod = 1e9 + 7;
/**************************************************************************************/

// // constexpr specifier
// constexpr int factorial(int n) {
//     return n <= 1 ? 1 : (n * factorial(n - 1));
// }
void runCase(int &testCase) {
    // cout << "#Case " << testCase << ": \n";
    {
        // // iota function
        // int arr[100];
        // vector<int> a(100);
        // iota(all(a), 1);
        // iota(all(arr), 1);
        // for (auto &e : a) cout << e << " ";
        // cout << "\n";
        // for (auto e : arr) cout << e << " ";
        // cout << "\n";
    } {
        // // assert function
        // assert(2 * 2 == 4); // true
        // // assert(sizeof(int) == 4); // false
    } {
        // // constexpr specifier
        // constexpr int k = factorial(20LL);
        // cout << k << "\n";
    } {
        // // use at in strings, vector, mp.at(key), ump.at(key) to handle exception
        // vector<int> v(10);
        // v.at(10) = 1;
        // // cout << v.at(10) << "\n"; // exception handling
        // // v[10] = 1;
        // // cout << v[10] << "\n";
        // // cout << v.at(10) << "\n";
    } {
        // // fill function
        // int arr[100];
        // vector<int> a(100);
        // // fill(begin(a), begin(a) + 3, 1024);
        // fill(all(a), 1024);
        // fill(all(arr), 1024);
        // for (auto &e : a) cout << e << " ";
        // cout << "\n";
        // for (auto e : arr) cout << e << " ";
        // cout << "\n";
    } {
        // // assign function
        // vector<vector<int>> dp(m, vector<int>(n));
        // dp.assign(m, vector<int>(n, -1));
    } {
        // // sorting in decreasing order
        // vector<int> v = {5, 4, 2, 6546, 5, 7, 56, 737};
        // sort(v.rbegin(),v.rend()); // but this is slower than using lambda func
    } {
        // // using range loop for vector of pairs
        // vector<pair<int, int>> v(n, {0, 0});
        // for (auto &[x, y] : v) cout << x << " " << y << "\n";
    } {
        // // way to declare binary in decimal
        // long i = 0b10;
    } {
        // // bit magics
        // long n = 0b1010101101;
        // cout << __builtin_clzll(n) << "\n";                   // counts no. of leading zeroes
        // long log2n = __builtin_clzll(1) - __builtin_clzll(n); // calculates log2(n) in constant time
        // cout << log2n << "\n";
    }
}

int32_t main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 1; i <= tests; i++) runCase(i);

    return 0;
}