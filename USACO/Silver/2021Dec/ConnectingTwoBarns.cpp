// #pragma GCC optimize ("trapv")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<vector<ll>> adj(n + 1);
        for (ll i = 0; i < m; i++) {
            ll u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        set<ll> b1, bn;
        
        vector<ll> visited(n + 1, 0);
        queue<ll> bfs;
        bfs.push(1);
        visited[1]++;
        while (!bfs.empty()) {
            ll u = bfs.front(); bfs.pop();
            b1.insert(u);

            for (ll v: adj[u]) {
                if (visited[v]) continue;
                visited[v]++;
                bfs.push(v);
            }
        }
        if (visited[n]) {
            cout << 0 << endl;
            continue;
        }
        bfs.push(n);
        visited[n]++;
        while (!bfs.empty()) {
            ll u = bfs.front(); bfs.pop();
            bn.insert(u);

            for (ll v: adj[u]) {
                if (visited[v]) continue;
                visited[v]++;
                bfs.push(v);
            }
        }
        b1.insert(-1000000);
        b1.insert(1000000);
        bn.insert(-1000000);
        bn.insert(1000000);

        vector<vector<ll>> dist(n + 1, vector<ll>(2));
        for (ll i = 1; i <= n; i++) {
            auto it1 = b1.upper_bound(i);
            ll r = *it1;
            it1--;
            ll l = *it1;
            dist[i][0] = min(i - l, r - i) * min(i - l, r - i);

            auto it2 = bn.upper_bound(i);
            r = *it2;
            it2--;
            l = *it2;
            dist[i][1] = min(i - l, r - i) * min(i - l, r - i);
        }

        ll ans = 1e15;
        vector<ll> visited2(n + 1, 0);
        for (ll i = 1; i <= n; i++) {
            if (visited2[i]) continue;
            bfs.push(i);
            visited2[i]++;
            ll min1 = 1e15, minn = 1e15;
            while (!bfs.empty()) {
                ll u = bfs.front(); bfs.pop();
                min1 = min(dist[u][0], min1);
                minn = min(dist[u][1], minn);
                for (ll v: adj[u]) {
                    if (visited2[v]) continue;
                    visited2[v]++;
                    bfs.push(v);
                }
            }
            ans = min(min1 + minn, ans);
        }

        cout << ans << endl;
    }
}