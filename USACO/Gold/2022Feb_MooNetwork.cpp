//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

vector<ll> p(2e5);
vector<ll> s(2e5);

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

    ll n; cin >> n;
    vector<ll> x(n), y(n);
    for (ll i = 0; i < n; i++) cin >> x[i] >> y[i];

    vector<vector<ll>> y_x(11);
    for (ll i = 0; i < n; i++) y_x[y[i]].push_back(x[i]);

    map<vector<ll>, ll> pmap;
    for (ll i = 0; i < n; i++) {
        pmap[{x[i], y[i]}] = i;
    }

    for (ll i = 0; i <= 10; i++) {
        sort(y_x[i].begin(), y_x[i].end());
    }

    vector<vector<ll>> edges;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j <= 10; j++) {
            auto it = y_x[j].begin();
            if (y[i] == j) it = upper_bound(y_x[j].begin(), y_x[j].end(), x[i]);
            else it = lower_bound(y_x[j].begin(), y_x[j].end(), x[i]);
            if (it != y_x[j].end()) {
                ll p1 = pmap[{*it, j}];
                ll x1 = x[i], y1 = y[i], x2 = x[p1], y2 = y[p1];
                ll cost = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
                edges.push_back({cost, i, p1});
            }
        }
    }

    sort(edges.begin(), edges.end());

    for (ll i = 0; i < n; i++) make_set(i);

    ll ans = 0;
    for (ll i = 0; i < edges.size(); i++) {
        ll cost = edges[i][0];
        ll p1 = edges[i][1], p2 = edges[i][2];
        if (find_set(p1) == find_set(p2)) continue;
        union_sets(p1, p2);
        ans += cost;
    }

    cout << ans << endl;
}