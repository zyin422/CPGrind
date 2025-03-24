//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

ll MOD = 1e9 + 7;
ll dp[3105][101][101]; // total length, last type; last width

signed main() {
    ll n, l; cin >> n >> l;

    vector<vector<ll>> b(n + 1, vector<ll>(2)); 
    for (ll i = 1; i <= n; i++) cin >> b[i][0] >> b[i][1];

    for (ll i = 1; i <= n; i++) {
        ll x = b[i][0], y = b[i][1];
        dp[x][i][y]++;
        dp[x][i][y] %= MOD;
        if (x != y) {
            dp[y][i][x]++;
            dp[y][i][x] %= MOD;
        }
    }
    for (ll i = 1; i <= l; i++) {
        for (ll j = 1; j <= n; j++) {
            ll x = b[j][0], y = b[j][1];
            for (ll k = 1; k <= n; k++) {
                if (j == k) continue;
                dp[i + x][j][y] += dp[i][k][x];
                dp[i + x][j][y] %= MOD;
                if (x != y) {
                    dp[i + y][j][x] += dp[i][k][y];
                    dp[i + y][j][x] %= MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= 100; j++) {
            ans += dp[l][i][j];
            ans %= MOD;
        }
    }

    cout << ans << endl;
}