//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        map<ll, ll> m;
        set<ll> s;
        for (ll i = 0; i < n; i++) {
            ll a; cin >> a;
            s.insert(a);
            m[a]++;
        }
        vector<ll> nums;
        for (ll num: s) nums.push_back(m[num]);

        sort(nums.begin(), nums.end());

        ll ans = nums.size();
        for (ll num: nums) {
            if (k >= num) {
                k -= num;
                ans--;
            }
            else break;
        }
        if (ans == 0) ans = 1;



        cout << ans << endl;
    }
}