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

    ll n; cin >> n;
    vector<vector<ll>> cows(n, vector<ll>(2));
    for (ll i = 0; i < n; i++) cin >> cows[i][0] >> cows[i][1];

    sort(cows.begin(), cows.end());

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll y1 = cows[i][1]; 
        ordered_set less;
        ordered_set more;
        for (ll j = i + 1; j < n; j++) {
            ll y2 = cows[j][1];
            ll l, r;
            if (y2 < y1) {
                l = less.order_of_key(y2);
                r = more.size();
                less.insert(y2);
            }
            else {
                l = less.size();
                r = more.size() - more.order_of_key(y2);
                more.insert(y2);
            }
            ans += (l + 1) * (r + 1);
        }
    }
    ans += cows.size() + 1;
    cout << ans << endl;
}