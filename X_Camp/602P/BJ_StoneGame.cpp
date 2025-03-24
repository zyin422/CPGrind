//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

string s;

signed main() {
    IOS;

    ll n; cin >> n;
    vector<ll> a(n + 1, 0);
    for (ll i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    ll maxa = a[n];

    ll cnt = 0;

    for (ll x = 1; x <= maxa; x++) {
        ll numt = 0, maxoddt = 0, trange = 0;
        for (ll t = 1; t <= maxa / x; t++) {
            ll l = x * t;
            ll r = x * (t + 1) - 1;
            auto it1 = lower_bound(a.begin(), a.end(), l);
            auto it2 = upper_bound(a.begin(), a.end(), r);

            if ((it2 - it1) % 2) {
                if (maxoddt != 0 && t - 1 != maxoddt) {
                    maxoddt = 0;
                    break;
                }
                maxoddt = t;
                trange = it2 - it1;
                numt++;
            }
        }
        if ((maxoddt != 0 && numt == 2) || (maxoddt == 1)) {
            cnt += trange;
        }
    }

    cout << cnt << endl;
}