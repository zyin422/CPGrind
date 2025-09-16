// #pragma GCC optimize ("trapv")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    ll k, m, n; cin >> k >> m >> n;
    vector<vector<ll>> grass(k, vector<ll>(2));
    vector<ll> cows(m);
    for (ll i = 0; i < k; i++) cin >> grass[i][0] >> grass[i][1];
    for (ll i = 0; i < m; i++) cin >> cows[i];
    
    sort(grass.begin(), grass.end());
    sort(cows.begin(), cows.end());

    vector<ll> ncows;

    ll t1 = 0, j = 0;
    while (j < k && grass[j][0] < cows[0]) {
        t1 += grass[j][1];
        j++;
    }
    ncows.push_back(t1);
    for (ll i = 1; i < m; i++) {
        ll t2 = 0, mt1 = 0;
        ll cdiff = cows[i] - cows[i - 1];
        ll p1 = j, p2 = j;
        while (j < k && grass[j][0] < cows[i]) {
            t2 += grass[j][1];
            j++;
        }
        t1 = 0;
        while (p1 < j) {
            while (p2 < j && grass[p2][0] - grass[p1][0] < (cdiff + 1) / 2) {
                t1 += grass[p2][1];
                p2++;
            }
            mt1 = max(t1, mt1);
            t1 -= grass[p1][1];
            p1++;
        }
        ncows.push_back(mt1);
        ncows.push_back(t2 - mt1);
    }
    t1 = 0;
    for (j; j < k; j++) t1 += grass[j][1];
    ncows.push_back(t1);

    sort(ncows.rbegin(), ncows.rend());

    ll ans = 0;
    for (ll i = 0; i < min((ll)ncows.size(), n); i++) ans += ncows[i];

    cout << ans << endl;
}