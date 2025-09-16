//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

ll n;
ll a[302];
ll dp[302][20][20][3]; // curInd, left, right, <, =, or >
ll pre[302][302];
void solve(vector<ll> x, ll start, ll m, ll sn) {
    for (ll i = 0; i < 302; i++) {
        for (ll j = 0; j < 20; j++) {
            for (ll k = 0; k < 20; k++) {
                dp[i][j][k][0] = 0;
                dp[i][j][k][1] = 0;
                dp[i][j][k][2] = 0; 
            }
        }
    }

    for (int i = 0; i < 20; i++) {
        dp[start][i][i][1] = 1;
    }

    for (ll i = start; i <= n; i++) {
        for (ll j = 1; j <= 18; j++) {
            for (ll k = j; k <= 18; k++) {
                ll nj = j, nk = k;
                if (j == k) {
                    nj--;
                    nk++;
                }
                
                // ignore
                dp[i + 1][j][k][0] += dp[i][j][k][0];
                dp[i + 1][j][k][1] += dp[i][j][k][1];
                dp[i + 1][j][k][2] += dp[i][j][k][2];

                // top
                if (a[i] < x[j]) {
                    dp[i + 1][j - 1][nk][0] += dp[i][j][k][0];
                    dp[i + 1][j - 1][nk][0] += dp[i][j][k][1];
                    dp[i + 1][j - 1][nk][0] += dp[i][j][k][2];
                }
                else if (a[i] == x[j]) {
                    dp[i + 1][j - 1][nk][0] += dp[i][j][k][0];
                    dp[i + 1][j - 1][nk][1] += dp[i][j][k][1];
                    dp[i + 1][j - 1][nk][2] += dp[i][j][k][2];
                }
                else {
                    dp[i + 1][j - 1][nk][2] += dp[i][j][k][0];
                    dp[i + 1][j - 1][nk][2] += dp[i][j][k][1];
                    dp[i + 1][j - 1][nk][2] += dp[i][j][k][2];
                }

                // bottom
                if (a[i] < x[k]) {
                    dp[i + 1][nj][k + 1][0] += dp[i][j][k][0];
                    dp[i + 1][nj][k + 1][0] += dp[i][j][k][1];
                    dp[i + 1][nj][k + 1][2] += dp[i][j][k][2];
                }
                else if (a[i] == x[k]) {
                    dp[i + 1][nj][k + 1][0] += dp[i][j][k][0];
                    dp[i + 1][nj][k + 1][1] += dp[i][j][k][1];
                    dp[i + 1][nj][k + 1][2] += dp[i][j][k][2];
                }
                else {
                    dp[i + 1][nj][k + 1][0] += dp[i][j][k][0];
                    dp[i + 1][nj][k + 1][2] += dp[i][j][k][1];
                    dp[i + 1][nj][k + 1][2] += dp[i][j][k][2];
                }
            }
        }
    }

    for (ll i = start; i <= n; i++) {
        pre[start][i] += pre[start - 1][i];
        for (ll j = 0; j <= 19; j++) {
            pre[start][i] += dp[i + 1][j][19][0] * m;
            pre[start][i] += dp[i + 1][j][19][1] * m;
            if ((19 - j - 1) < sn) pre[start][i] += dp[i + 1][j][19][2] * m;
        }
    }
}

signed main() {
    IOS;

    ll n1, n2; cin >> n >> n1 >> n2;
    for (ll i = 1; i <= n; i++) cin >> a[i];

    n1--;

    vector<ll> A(19), B(19);
    int an = 0, bn = 0;
    for (ll i = 18; i >= 1; i--) {
        A[i] = n1 % 10, B[i] = n2 % 10;
        if (n1) an++;
        if (n2) bn++;
        n1 /= 10, n2 /= 10;
    }

    for (ll i = 0; i < 302; i++) {
        for (ll j = 0; j < 302; j++) pre[i][j] = 0;
    }

    for (ll i = 1; i <= n; i++) solve(B, i, 1, bn);
    for (ll i = 1; i <= n; i++) solve(A, i, -1, an);

    ll q; cin >> q;
    while (q--) {
        ll l, r; cin >> l >> r;
        cout << pre[l][r] << endl;
    }
}