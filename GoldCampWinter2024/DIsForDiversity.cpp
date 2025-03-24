//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

ll INF, MOD;

signed main() {
    IOS;

    ll n; cin >> n;
    vector<ll> a(n), b(n), c(n), d(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];
    for (ll i = 0; i < n; i++) cin >> c[i];
    for (ll i = 0; i < n; i++) cin >> d[i];

    vector<vector<ll>> e(n, vector<ll>(5));

    for (ll i = 0; i < n; i++) {
        e[i][0] = a[i];
        e[i][1] = b[i];
        e[i][2] = c[i];
        e[i][3] = i;
        e[i][4] = d[i];
    }

    sort(e.begin(), e.end());

    set<vector<ll>> s;
    vector<vector<vector<ll>>> left(n, vector<vector<ll>>(2, vector<ll>(3, 1e17)));
    for (ll i = 0; i < n; i++) {
        if (s.size() == 1) {
            left[i][0][0] = (*s.begin())[0];
            left[i][0][1] = (*s.begin())[2];
            left[i][0][2] = (*s.begin())[1];
        }
        else if (s.size() > 1) {
            auto it = s.begin();
            left[i][0][0] = (*it)[0];
            left[i][0][1] = (*it)[2];
            left[i][0][2] = (*it)[1];
            it++;
            left[i][1][0] = (*it)[0];
            left[i][1][1] = (*it)[2];
            left[i][1][2] = (*it)[1];
        }
        ll cur = e[i][2] - e[i][0];
        s.insert({cur, e[i][3], e[i][4]});
        while (s.size() >= 2) {
            auto it = s.begin();
            ll d1 = (*it)[2];
            it++;
            ll d2 = (*it)[2];
            if (d1 == d2) s.erase(it);
            else break;
        }
    }


    s.clear();
    reverse(e.begin(), e.end());
    vector<vector<vector<ll>>> right(n, vector<vector<ll>>(2, vector<ll>(3, 1e17)));
    for (ll i = 0; i < n; i++) {
        if (s.size() == 1) {
            right[n - i - 1][0][0] = (*s.begin())[0];
            right[n - i - 1][0][1] = (*s.begin())[2];
            right[n - i - 1][0][2] = (*s.begin())[1];
        }
        else if (s.size() > 1) {
            auto it = s.begin();
            right[n - i - 1][0][0] = (*it)[0];
            right[n - i - 1][0][1] = (*it)[2];
            right[n - i - 1][0][2] = (*it)[1];
            it++;
            right[n - i - 1][1][0] = (*it)[0];
            right[n - i - 1][1][1] = (*it)[2];
            right[n - i - 1][1][2] = (*it)[1];
        }
        ll cur = e[i][2] + e[i][0];
        s.insert({cur, e[i][3], e[i][4]});
        while (s.size() >= 2) {
            auto it = s.begin();
            ll d1 = (*it)[2];
            it++;
            ll d2 = (*it)[2];
            if (d1 == d2) s.erase(it);
            else break;
        }
    }

    vector<vector<ll>> ans(n, vector<ll>(3));

    reverse(e.begin(), e.end());
    for (ll i = 0; i < n; i++) {
        ll minv = 1e17, minj = -1;
        if (left[i][0][1] != e[i][4]) {
            if (left[i][0][0] + e[i][0] < minv || (left[i][0][0] + e[i][0] == minv && minj > left[i][0][2])) {
                minv = left[i][0][0] + e[i][0];
                minj = left[i][0][2];
            }
        }
        else {
            if (left[i][1][0] < minv || (left[i][1][0] + e[i][0] == minv && minj > left[i][1][2])) {
                if (left[i][1][0] + e[i][0] < minv) {
                    minv = left[i][1][0] + e[i][0];
                    minj = left[i][1][2];
                }
            }
        }
        if (right[i][0][1] != e[i][4]) {
            if (right[i][0][0] - e[i][0] < minv || (right[i][0][0] - e[i][0] == minv && minj > right[i][0][2])) {
                minv = right[i][0][0] - e[i][0];
                minj = right[i][0][2];
            }
        }
        else {
            if (right[i][1][0] - e[i][0] < minv || (right[i][1][0] - e[i][0] == minv && minj > right[i][1][2])) {
                minv = right[i][1][0] - e[i][0];
                minj = right[i][1][2];
            }
        }

        if (minv > 3e9) {
            ans[i][1] = -1;
            ans[i][2] = -1;
        }
        else {
            ans[i][1] = minv + e[i][1];
            ans[i][2] = minj + 1;
        }
        ans[i][0] = e[i][3];
    }


    sort(ans.begin(), ans.end());

    for (ll i = 0; i < n; i++) {
        cout << ans[i][1] << " " << ans[i][2] << endl;
    }
}