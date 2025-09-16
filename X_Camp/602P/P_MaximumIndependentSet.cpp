//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    ll n, m; cin >> n >> m;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < m; i++) {
        ll u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll mid = n / 2;
    ll f[(1 << mid)], fbits[(1 << mid)], g[(1 << mid)], gmax[(1 << mid)];
    for (ll mask = 0; mask < (1 << mid); mask++) {
        f[mask] = 0, g[mask] = 0, gmax[mask] = 0;
        ll ind = 1;

        ll bits = 0;
        for (ll bit = 0; bit < mid; bit++) {
            if (!((mask >> bit) & 1)) continue;
            for (ll v: adj[bit]) if ((mask >> v) & 1) ind = 0;
            bits++;
        }
        
        f[mask] = ind;
        if (ind) {
            g[mask] = bits;
            gmax[mask] = mask;
        }
        
        for (ll bit = 0; bit < mid; bit++) {
            if (!((mask >> bit) & 1)) continue;
            if (g[mask] < g[(mask ^ (1 << bit))]) {
                g[mask] = g[(mask ^ (1 << bit))];
                gmax[mask] = gmax[(mask ^ (1 << bit))];
            }
        }
    }

    ll ans = 0, ans1, ans2;
    
    for (ll mask = 0; mask < (1 << (n - mid)); mask++) {
        ll ind = 1;

        ll bits = 0, flip = (1 << mid) - 1; 
        for (ll bit = 0; bit < (n - mid); bit++) {
            if (!((mask >> bit) & 1)) continue;
            for (ll v: adj[mid + bit]) {
                if (v >= mid && ((mask >> (v - mid)) & 1)) ind = 0;
                if (v < mid && ((flip >> v) & 1)) flip ^= (1 << v); 
            }
            bits++;
        }
        

        if (!ind) bits = 0;
        if (g[flip] + bits > ans) {
            ans = g[flip] + bits;
            ans1 = gmax[flip];
            if (bits == 0) ans2 = 0;
            else ans2 = mask;
        }
    }

    
    cout << ans << endl;
    ans1 += (ans2 << mid);
    for (ll bit = 0; bit < n; bit++) {
        if ((ans1 >> bit) & 1) cout << bit << " ";
    }
}