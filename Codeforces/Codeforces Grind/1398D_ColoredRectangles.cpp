
Zixuan Yin <yinzixuansz@gmail.com>
Fri, Nov 7, 1:29 PM (3 days ago)
to me

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    int R, G, B; cin >> R >> G >> B;
    vector<int> r(R), g(G), b(B);
    for (int i = 0; i < R; i++) cin >> r[i];
    for (int i = 0; i < G; i++) cin >> g[i];
    for (int i = 0; i < B; i++) cin >> b[i];

    sort(r.rbegin(), r.rend());
    sort(g.rbegin(), g.rend());
    sort(b.rbegin(), b.rend());

    int dp[R + 1][G + 1][B + 1];
    
    for (int i = 0; i <= R; i++) {
        for (int j = 0; j <= G; j++) {
            for (int k = 0; k <= B; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    dp[0][0][0] = 0;
    for (int i = 0; i <= R; i++) {
        for (int j = 0; j <= G; j++) {
            for (int k = 0; k <= B; k++) {
                //cout << i << " " << j << " " << k << endl;
                if (dp[i][j][k] == -1) continue;
                //cout << "passed" << endl;
                if (i < R && j < G) dp[i + 1][j + 1][k] = max(dp[i][j][k] + r[i] * g[j], dp[i + 1][j + 1][k]);
                if (i < R && k < B) dp[i + 1][j][k + 1] = max(dp[i][j][k] + r[i] * b[k], dp[i + 1][j][k + 1]);
                if (j < G && k < B) dp[i][j + 1][k + 1] = max(dp[i][j][k] + g[j] * b[k], dp[i][j + 1][k + 1]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= R; i++) {
        for (int j = 0; j <= G; j++) {
            for (int k = 0; k <= B; k++) {
                ans = max(dp[i][j][k], ans);
            }
        }
    }

    cout << ans << endl;
}