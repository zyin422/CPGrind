//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

vector<ll> p(3e5);
vector<ll> s(3e5);

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

vector<ll> p1(3e5);
vector<ll> s1(3e5);

void make_set1(ll v) {
    p1[v] = v;
    s1[v] = 1;
}

ll find_set1(ll v) {
    if (v == p1[v])
        return v;
    return p1[v] = find_set1(p1[v]);
}

void union_sets1(ll a, ll b) {
    a = find_set1(a);
    b = find_set1(b);
    if (a != b) {
        if (s1[a] < s1[b])
            swap(a, b);
        p1[b] = a;
        s1[a] += s1[b];
    }
}

vector<vector<ll>> padj;
vector<ll> visited;

void dfs(ll pa, ll u) {
    if (visited[u]) return;
    visited[u]++;
    for (ll v: padj[u]) {
        if (v == pa) continue;
        else {
            union_sets(u, v);
            dfs(u, v);
        }
    }
}


signed main() {
    IOS;

    ll n; cin >> n;
    vector<vector<ll>> v(n, vector<ll>(5));
    for (ll i = 0; i < n; i++) cin >> v[i][0] >> v[i][1] >> v[i][2] >> v[i][3] >> v[i][4];

    for (ll i = 1; i <= 2 * n; i++) make_set(i);

    padj.resize(2 * n + 1);
    for (ll i = 0; i < n; i++) {
        ll p1 = v[i][1], p2 = v[i][2], p3 = v[i][3], p4 = v[i][4];
        padj[p1].push_back(p2);
        padj[p2].push_back(p1);
        padj[p3].push_back(p4);
        padj[p4].push_back(p3);
    }

    visited.resize(2 * n + 1, 0);
    for (ll i = 1; i <= 2 * n; i++) dfs(-1, i);
;
    for (ll i = 1; i <= 2 * n; i++) make_set1(find_set(i));

    vector<vector<ll>> edges;
    for (ll i = 0; i < n; i++) {
        ll cost = v[i][0];
        ll p1 = v[i][1], p3 = v[i][3];
        if (find_set(p1) != find_set(p3)) edges.push_back({cost, find_set(p1), find_set(p3)});
    }

    sort(edges.begin(), edges.end());

    ll ans = 0;
    for (auto e: edges) {
        ll cost = e[0], p1 = e[1], p2 = e[2];
        if (find_set(p1) == find_set(p2)) continue;
        union_sets(p1, p2);
        ans += cost;
    }

    cout << ans << endl;
}