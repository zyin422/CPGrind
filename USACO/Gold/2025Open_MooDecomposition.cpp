//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

ll MOD = 1e9 + 7;

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) {
            res *= a;
            res %= MOD;
        }
        a = a * a;
        a %= MOD;
        b >>= 1;
    }
    return res;
}

signed main() {
    IOS;

    ll k, n, l; cin >> k >> n >> l;
    string s; cin >> s;
    ll o = 0;

    vector<ll> fac(n + 1), facinv(n + 1);
    fac[0] = 1;
    for (ll i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }

    facinv[n] = binpow(fac[n], MOD - 2);
    for (ll i = n; i > 0; i--) facinv[i - 1] = facinv[i] * i % MOD;
    
    ll ans = 1;
    ll cnt = 0;
    for (ll i = n - 1; i >= 0; i--) {
        if (s[i] == 'O') o++;
        else {
            ans *= (fac[o] * (facinv[o - k] * facinv[k] % MOD)) % MOD;
            // cout << ans << endl;
            ans %= MOD;
            // if (ans == 0) {
            //     cout << i << endl << endl;
            //     break;
            // }
            o -= k;
            cnt++;
        }
    }
    // cout << cnt << endl;

    ll final = 1;
    for (ll bit = 0; bit <= 60; bit++) {
        if ((l >> bit) & 1) {
            ll cur = ans;
            // cout << bit << endl;
            for (ll i = 0; i < bit; i++) {
                // cout << "cur: " << cur << endl;
                cur *= cur;
                cur %= MOD;
            }
            final *= cur;
            final %= MOD;
        }
    }
    cout << final << endl;
}