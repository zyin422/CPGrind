//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    ll n; cin >> n;
    vector<ll> a(n + 1), c(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];
    for (ll i = 1; i <= n; i++) cin >> c[i];

    vector<ll> cr(n + 1, 0); // cost reduced

    for (ll i = 1; i <= n; i++) {
        if (i == a[i]) c[i] = 0;
        cr[a[i]] += c[i];
    }

    set<vector<ll>> s;
    
    for (ll i = 1; i <= n; i++) s.insert({cr[i] - c[i], i});

    vector<int> changed(n + 1, 0);

    ll ans = 0;
    while (!s.empty()) {
        auto it = s.end(); it--;
        ll sum = (*it)[0], ind = (*it)[1];
        s.erase(it);
        if (sum >= 0) {
            //cout << ind << endl;
            ans += c[ind];
            changed[ind]++;

            ll chg = a[ind];
            if (!changed[ind]) {
                s.erase({cr[chg] - c[chg], chg});
                cr[chg] -= c[ind];
                s.insert({cr[chg] - c[chg], chg});
            }

            c[ind] = 0;
            a[ind] = ind;
        }
    }
    
    for (ll i = 1; i <= n; i++) {
        if (a[i] != a[a[i]]) ans += c[i];
    }
    
    cout << ans << endl;
}    