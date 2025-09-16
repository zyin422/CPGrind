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
        ll l, r; cin >> l >> r;

        ll ans = 0;
        ll c10 = 0, first = -1, fmask = 0;
        vector<ll> c01;
        for (ll bit = 30; bit >= 0; bit--) {
            ll mask = (1 << bit);
            ll rb = (r & mask), lb = (l & mask);
            if (rb > lb) {
                c10++;
                if (c10 != 1 && first == -1) {
                    first = 1;
                    ans ^= fmask;
                }
                if (first == -1) fmask = mask;
                else if (!first) ans ^= mask;
            }
            if (rb == lb) {
                if (!c10) ans ^= rb;
                else if (first == -1){
                    if (rb) {
                        first = 1;
                        ans ^= fmask;
                    }
                    else first = 0;
                    if (!rb) ans ^= mask;
                }
                else {
                    if (!rb) ans ^= mask;
                }
            }
            else if (rb < lb) c01.push_back(mask);
        }
        if (first == -1) {
            ans ^= fmask;
        }
        else if (first == 0) {
            for (ll mask: c01) ans ^= mask;
        }
        cout << l << " " << ans << " " << r << endl;
    }
}