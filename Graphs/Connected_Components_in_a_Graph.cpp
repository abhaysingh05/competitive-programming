#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
typedef long long ll;
#define endl '\n'
#define rep(i, l, r) for (ll i = l; i < (ll)(r); i++)
#define rrep(i, r, l) for (ll i = r; i > (ll)(l); i--)
#pragma GCC optimize("Ofast,no-stack-protector,fast-math", 3)
#define all(x) x.begin(), x.end()
// find_by_order, order_of_key
template <typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <typename Key, typename Value>
using ordered_map = __gnu_pbds::tree<Key, Value, std::less<Key>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
#define ff first
#define ss second
using namespace std;
// const int M = 1e9 + 7;
const int N = 1e5 + 10;
bool vis[N];
int ans = 0;
vector<int> graphs[N];
void dfs(int vertex)
{
    vis[vertex] = true;
    for (auto child : graphs[vertex])
    {
        if (vis[child])
            continue;
        dfs(child);
    }
}
void Solution()
{
    int n, e;
    cin >> n >> e;
    for (int i = 1; i <= e; i++)
    {
        int x, y;
        cin >> x >> y;
        graphs[x].push_back(y);
        graphs[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        dfs(i);
        ans++;
    }
    cout << ans << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        Solution();
    }
    return 0;
}