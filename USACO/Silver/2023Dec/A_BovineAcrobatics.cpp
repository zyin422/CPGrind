#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;
    ll n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> cows;
    ll tot = 0;
    for (ll i = 0; i < n; i++) {
        ll w, a; cin >> w >> a;
        cows.push_back({w, a});
        tot += a;
    }

    sort(cows.begin(), cows.end());

    vector<vector<ll>> q;
    ll qi = 0;
    ll toss = 0;
    for (ll i = 0; i < n; i++) {
        ll w = cows[i][0], a = cows[i][1];
        if (m >= a) {
            q.push_back({w, a});
            m -= a;
            continue;
        }
        else if (m > 0) {
            q.push_back({w, m});
            a -= m;
            cows[i][1] -= m;
            m = 0;
        }

        ll u = q[qi][0], cnt = q[qi][1];
        while (u + k <= w && a > 0) {
            if (cnt > a) {
                q[qi][1] -= a;
                a = 0;
            }
            else {
                a -= cnt;
                qi++;
                if (qi == q.size()) break;
                u = q[qi][0], cnt = q[qi][1];
            }
        }
        q.push_back({w, cows[i][1] - a});
        toss += a;
    }

    cout << tot - toss << endl;
}