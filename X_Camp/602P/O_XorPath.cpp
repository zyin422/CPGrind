#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

ll grid[20][20];
map<ll, ll> frq[20][20];

signed main() {
    IOS;

    ll n, m, k; cin >> n >> m >> k;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    frq[0][0][grid[0][0]]++;
    
    ll len = ((n - 1) + (m - 1)) / 2;
    for (ll x = 0; x < n; x++) {
        for (ll y = 0; y < m; y++) {
            if (x + y >= len) break;
            for (auto it = frq[x][y].begin(); it != frq[x][y].end(); it++) {
                if (x < n - 1) {
                    frq[x + 1][y][(it->first) ^ grid[x + 1][y]] += it->second;
                }
                if (y < m - 1) {
                    frq[x][y + 1][(it->first) ^ grid[x][y + 1]] += it->second;
                }
            }
        }
    }

    ll ans = 0;
    len++;
    frq[n - 1][m - 1][grid[n - 1][m - 1]]++;
    set<pair<ll, ll>> s;
    for (ll x = n - 1; x >= 0; x--) {
        for (ll y = m - 1; y >= 0; y--) {
            if ((n - 1 + m - 1) - (x + y) + len == n - 1 + m - 1) {
                s.insert({x, y});
                break;
            }
            else if ((n - 1 + m - 1) - (x + y) + len > n - 1 + m - 1) break;
            for (auto it = frq[x][y].begin(); it != frq[x][y].end(); it++) {
                if (x - 1 >= 0) {
                    frq[x - 1][y][(it->first) ^ grid[x - 1][y]] += it->second;
                }
                if (y - 1 >= 0) {
                    frq[x][y - 1][(it->first) ^ grid[x][y - 1]] += it->second;
                }
            }
        }
    }

    for (auto data: s) {
        int x = data.first, y = data.second;
        
        for (auto it1 = frq[x][y].begin(); it1 != frq[x][y].end(); it1++) {
            if (x - 1 >= 0) ans += it1->second * frq[x - 1][y][(it1->first) ^ k];
            if (y - 1 >= 0) ans += it1->second * frq[x][y - 1][(it1->first) ^ k];
        }
    }

    if (grid[0][0] == k && n * m == 1) {
        cout << 1 << endl;
        return 0;
    }

    cout << ans << endl;
}