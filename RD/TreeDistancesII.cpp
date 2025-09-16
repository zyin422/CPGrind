// #pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define endl "\n"

ll n;

vector<ll> tree, d, dist;
vector<vector<ll>> adj;

void subtree(ll p, ll u)
{
    for (ll v : adj[u])
    {
        if (v == p)
            continue;
        subtree(u, v);
        tree[u] += tree[v];
        d[u] += d[v] + tree[v];
    }
}

void reroot(ll p, ll u, ll pdist, ll ptree)
{
    dist[u] = pdist + ptree + d[u];
    for (ll v : adj[u])
    {
        if (v == p)
            continue;
        reroot(u, v, dist[u] - d[v] - tree[v], n - tree[v]);
    }
}

signed main()
{
    IOS;

    cin >> n;
    tree.resize(n + 1, 1);
    d.resize(n + 1, 0);
    adj.resize(n + 1);
    dist.resize(n + 1);
    for (ll i = 0; i < n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    subtree(0, 1);
    reroot(0, 1, 0, 0);

    for (ll i = 1; i <= n; i++)
        cout << dist[i] << " ";
}