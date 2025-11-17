#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

vector<ll> p;
vector<ll> s;

void make_set(ll v) {
    p[v] = v;
    s[v] = 1;
}

ll find_set(ll v) {
    if (v == p[v])
        return v;
    return p[v] = find_set(p[v]);
}

void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (s[a] < s[b])
            swap(a, b);
        p[b] = a;
        s[a] += s[b];
    }
}

signed main() {
    IOS;

    ll n, m; cin >> n >> m;
    vector<vector<ll>> adj(n + 1);
    p.resize(n + 1);
    s.resize(n + 1, 0);
    for (ll i = 0; i < m; i++) {
        ll a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<ll> ecnt(n + 1, 0);
    for (ll i = 1; i <= n; i++) ecnt[i] = adj[i].size();
    
    multiset<vector<ll>> nodes;
    for (ll i = 1; i <= n; i++) nodes.insert({ecnt[i], i});

    map<ll, vector<ll>> on;
    vector<ll> visited(n + 1, 0);
    ll maxe = 0;
    while (!nodes.empty()) {
        auto data = *nodes.begin(); nodes.erase(nodes.begin());
        ll edges = data[0], u = data[1];
        // cout << edges << " " << u << endl;
        maxe = max(edges, maxe);
        on[edges].push_back(u);
        visited[u]++;
        for (ll v: adj[u]) {
            if (visited[v]) continue;
            nodes.erase(nodes.find({ecnt[v], v}));
            if (ecnt[v] != maxe) ecnt[v]--;
            nodes.insert({ecnt[v], v});
        }
    }

    ll ans = 0;

    //for (ll i = 1; i <= n - 1; i++) {
        // cout << "edges: " << i << endl;
        //for (ll v: on[i]) cout << v << " ";
        //cout << endl;
    //}

    ll maxcows = 0;
    for (ll e = n - 1; e >= 1; e--) {
        for (ll u: on[e]) {
            make_set(u);
            for (ll v: adj[u]) {
                if (s[v] != 0) {
                    union_sets(u, v);
                    maxcows = max(s[find_set(u)], maxcows);
                }
            }z
        }

        ans = max(maxcows * e, ans);
    }

    cout << ans << endl;
}