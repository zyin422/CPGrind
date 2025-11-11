#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    int n; cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<vector<int>> dp(n, vector<int>(n));

    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int jmp = 1; jmp < n; jmp++) {
        for (int si = 0; si + jmp < n; si++) {
            int ei = si + jmp;
            int best = n;
            for (int i = si; i < ei; i++) {
                int cur = dp[si][i] + dp[i + 1][ei];
                if (c[si] == c[i + 1]) cur--;
                best = min(cur, best);
            }
            dp[si][ei] = best;
        }
    }

    cout << dp[0][n - 1] << endl;
}