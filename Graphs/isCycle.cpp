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
const int N = 2e5 + 10;
vector<vector<int>> graph(N);
vector<bool> vis(N, false);
bool check = false;
void dfs(int vertex, int parent)
{
    vis[vertex] = true;
    for (auto child : graph[vertex])
    {
        if (vis[child] && child == parent)
            continue;
        if (vis[child])
        {
            check = true;
            return;
        }
        dfs(child, vertex);
    }
}
void Solution()
{
    int n, m;
    cin >> n >> m;
    rep(i, 0, m)    
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    rep(i, 1, n + 1)
    {
        if (vis[i])
            continue;
        dfs(i, 0);
        if (check == true)
        {
            break;
        }
    }
    cout << check << endl;
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
 