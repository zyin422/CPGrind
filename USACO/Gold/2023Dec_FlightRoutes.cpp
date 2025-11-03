//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    int n; cin >> n;
    vector<vector<int>> adj(n, vector<int>(n, 0));
    for (int i = 0; i < n - 1; i++) {
        string s; cin >> s;
        for (int j = i + 1; j < n; j++) {
            if (s[j - i - 1] == '1') adj[i][j]++;
        }
    }

    vector<vector<int>> adjd(n, vector<int>(n, 0));
    for (int i = 0; i < n - 1; i++) {
        adjd[i][i + 1] = adj[i][i + 1];
    }

    for (int jmp = 2; jmp <= n - 1; jmp++) {
        for (int si = 0; si + jmp < n; si++) {
            int ei = si + jmp;

            int tot = 0;
            for (int i = si + 1; i < ei; i++) {
                tot ^= adjd[si][i] * adj[i][ei];
            }
            if (tot != adj[si][ei]) adjd[si][ei]++;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) ans += adjd[i][j];
    }

    cout << ans << endl;
}