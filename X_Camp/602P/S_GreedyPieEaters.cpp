//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);

    ll n, m; cin >> n >> m;
    vector<vector<ll>> cows(m, vector<ll>(3));
    for (ll i = 0; i < m; i++) cin >> cows[i][0] >> cows[i][1] >> cows[i][2];

    ll maxw[n + 1][n + 1][n + 1];
    ll dp[n + 1][n + 1];
    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j <= n; j++) {
            for (ll k = 0; k <= n; k++) {
                maxw[i][j][k] = 0;
            }
            dp[i][j] = 0;
        }
    }
    for (ll i = 0; i < m; i++) {
        ll w = cows[i][0], l = cows[i][1], r = cows[i][2];
        for (ll k = l; k <= r; k++) {
            maxw[l][r][k] = w;
        }
    }

    for (ll len = 1; len <= n - 1; len++) {
        for (ll i = 1; i <= n - len; i++) {
            ll j = i + len;
            for (ll k = i; k <= j; k++) {
                ll cur = maxw[i][j][k];
                if (k != i) cur = max(maxw[i + 1][j][k], cur);
                if (k != j) cur = max(maxw[i][j - 1][k], cur);
                maxw[i][j][k] = cur;
            }
        }
    }

    for (ll len = 0; len <= n - 1; len++) {
        for (ll i = 1; i <= n - len; i++) {
            ll j = i + len;
            for (ll k = i; k <= j; k++) {
                ll cur = maxw[i][j][k];
                if (k != i) cur += dp[i][k - 1];
                if (k != j) cur += dp[k + 1][j];
                dp[i][j] = max(cur, dp[i][j]);
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            for (int k = i; k <= j; k++) {
                //cout << i << " " << j << " " << k << " " << maxw[i][j][k] << endl;
            }
        }
    }

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = i; j <= n; j++) {
            //cout << i << " " << j << " " << dp[i][j] << endl;
            ans = max(dp[i][j], ans);
        }
    }

    cout << ans << endl;
}