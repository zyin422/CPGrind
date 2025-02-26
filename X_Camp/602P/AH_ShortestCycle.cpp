//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    ll n; cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> freq(65, 0);
    for (ll i = 0; i < n; i++) {
        for (ll bit = 0; bit < 65; bit++) {
            if (1 & (a[i] >> bit)) freq[bit]++;
        }
    }
    
    ll ans = n + 1;
    for (ll i = 0; i < 65; i++) {
        if (freq[i] >= 3) ans = 3;
    }
    vector<set<ll>> adj(n);
    for (ll bit = 0; bit < 65; bit++) {
        if (freq[bit] != 2) continue; 
        ll u = -1, v;
        for (ll i = 0; i < n; i++) {
            if (1 & (a[i] >> bit)) {
                if (u == -1) u = i;
                else v = i;
            }
        }
        adj[u].insert(v);
        adj[v].insert(u);
    }

    for (ll u = 0; u < n; u++) {
        for (ll v: adj[u]) {
            queue<vector<ll>> bfs;
            vector<ll> visited(n, 0);
            bfs.push({u, 0});
            visited[u]++;
            while (!bfs.empty()) {
                auto data = bfs.front(); bfs.pop();
                ll x = data[0], c = data[1];
                if (x == v) {
                    ans = min(c + 1, ans);
                    break;
                }
                for (ll y: adj[x]) {
                    if (x == u && y == v) continue;
                    if (visited[y]) continue;
                    visited[y]++;
                    bfs.push({y, c + 1});
                }
            }
        }
    }

    if (ans != n + 1) cout << ans << endl;
    else cout << -1 << endl;
}