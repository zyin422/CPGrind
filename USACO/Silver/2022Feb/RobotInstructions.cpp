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

    ll n; cin >> n;
    ll xg, yg; cin >> xg >> yg;

    vector<vector<ll>> a(n, vector<ll>(2));
    for (ll i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];

    vector<vector<ll>> m;
    for (ll bit = 0; bit < (1 << ((n + 1) / 2)); bit++) {
        ll x = 0, y = 0, cnt = 0;
        for (ll i = 0; i < (n + 1) / 2; i++) {
            if (1 & (bit >> i)) {
                x += a[i][0];
                y += a[i][1];
                cnt++;
            }
        }
        m.push_back({x, y, cnt});
    }

    vector<vector<int>> v;
    vector<int> prev = m[0];
    int prevc = 1;
    for (int i = 1; i < m.size(); i++) {
        if (prev[0] == m[i][0] && prev[1] == m[i][1] && prev[2] == m[i][2]) prevc++;
        else {
            prev.push_back(prevc);
            v.push_back(prev)
            prev = m[i];
            prevc = 1;
        }
    }
    prev.push_back(prevc);
    v.push_back(prev);

    vector<ll> ans(n + 1, 0);
    for (ll bit = 0; bit < (1 << (n - ((n + 1) / 2))); bit++) {
        ll x = xg, y = yg, cnt = 0;
        for (ll i = 0; i < (n - (n + 1) / 2); i++) {
            if (1 & (bit >> i)) {
                x -= a[i + (n + 1) / 2][0];
                y -= a[i + (n + 1) / 2][1];
                cnt++;
            }
        }
        for (ll i = 1; i <= n; i++) {
            if (i >= cnt) ans[i] += lower_bound(v.begin(), v.end(), {x, y, cnt});
        }
    }

    for (ll i = 1; i <= n; i++) cout << ans[i] << endl;
}