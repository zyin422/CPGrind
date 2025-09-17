//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    ll T; cin >> T;
    while (T--) {
        ll n; cin >> n;
        vector<ll> p(n), s(n), ans(n);
        for (ll i = 0; i < n; i++) cin >> p[i];
        for (ll i = 0; i < n; i++) cin >> s[i];

        vector<ll> l(n), r(n);
        for (ll i = 0; i < n; i++) l[i] = i - 1;
        for (ll i = 0; i < n; i++) r[i] = i + 1;

        multiset<pair<double, pair<ll,ll>>> m_am, am_m;
        set<double> times;
        for (ll i = 0; i < n; i += 2) {
            ll x1 = p[i], x2 = p[i + 1];
            ll v1 = s[i], v2 = s[i + 1];
            double time = (x2 - x1) / (double)(v1 + v2);
            m_am.insert({ceil(time), {i, i + 1}});
            times.insert(ceil(time));
        }
        for (ll i = 1; i < n - 1; i += 2) {
            ll x1 = p[i], x2 = p[i + 1];
            ll v1 = s[i], v2 = s[i + 1];
            double time = (x2 - x1) / (double)(v1 + v2);
            am_m.insert({ceil(time), {i, i + 1}});
            times.insert(ceil(time));
        }
        // for (auto t: times) cout << t << " ";
        // cout << endl;

        while (!times.empty()) {
            // check m_am first
            double time = *times.begin();
            // cout << time << endl;
            while (!m_am.empty()) {
                auto data = *m_am.begin();
                double t = data.first;
                ll i1 = data.second.first, i2 = data.second.second;
                // cout << "t: " << t << endl;
                if (t != time) break;
                else {
                    ll obs = ceil(t) * 2 - 1;
                    ans[i1] = obs;
                    ans[i2] = obs;
                    // cout << time2 << endl;
                }
                // collision: i1 <-> i2
                if (l[i1] != -1) {
                    r[l[i1]] = r[i2];

                    ll x1 = p[l[i1]], x2 = p[i1];
                    ll v1 = s[l[i1]], v2 = s[i1];
                    double time2 = (x2 - x1) / (double)(v1 + v2);
                    auto it = am_m.find({ceil(time2), {l[i1], i1}});
                    if (it != am_m.end()) am_m.erase(it);
                }
                if (r[i2] != n) {
                    l[r[i2]] = l[i1];

                    ll x1 = p[r[i2]], x2 = p[i2];
                    ll v1 = s[r[i2]], v2 = s[i2];
                    double time2 = (x1 - x2) / (double)(v1 + v2);
                    auto it = am_m.find({ceil(time2), {i2, r[i2]}});
                    if (it != am_m.end()) am_m.erase(it);
                }

                if (l[i1] != -1 && r[i2] != n) { // sake of completeness
                    ll x1 = p[l[i1]], x2 = p[r[i2]];
                    ll v1 = s[l[i1]], v2 = s[r[i2]];
                    double time2 = (x2 - x1) / (double)(v1 + v2);
                    am_m.insert({ceil(time2), {l[i1], r[i2]}});
                    times.insert(ceil(time2));
                }

                m_am.erase(m_am.begin());
            }
            // now check am_m
            while (!am_m.empty()) {
                auto data = *am_m.begin();
                double t = data.first;
                // cout << "t: " << t << endl;
                ll i1 = data.second.first, i2 = data.second.second;
                if (t != time) break;
                else {
                    ll obs = ceil(t) * 2;
                    // cout << obs << endl;
                    ans[i1] = obs;
                    ans[i2] = obs;
                }

                if (l[i1] != -1) {
                    r[l[i1]] = r[i2];

                    ll x1 = p[l[i1]], x2 = p[i1];
                    ll v1 = s[l[i1]], v2 = s[i1];
                    double time2 = (x2 - x1) / (double)(v1 + v2);
                    auto it = m_am.find({ceil(time2), {l[i1], i1}});
                    if (it != m_am.end()) m_am.erase(it);
                }
                if (r[i2] != n) {
                    l[r[i2]] = l[i1];

                    ll x1 = p[r[i2]], x2 = p[i2];
                    ll v1 = s[r[i2]], v2 = s[i2];
                    double time2 = (x1 - x2) / (double)(v1 + v2);
                    auto it = m_am.find({ceil(time2), {i2, r[i2]}});
                    if (it != m_am.end()) m_am.erase(it);
                }

                if (l[i1] != -1 && r[i2] != n) {
                    ll x1 = p[l[i1]], x2 = p[r[i2]];
                    ll v1 = s[l[i1]], v2 = s[r[i2]];
                    double time2 = (x2 - x1) / (double)(v1 + v2);
                    m_am.insert({ceil(time2), {l[i1], r[i2]}});
                    // cout << x1 << " " << x2 << endl;
                    // cout << "newtime: " << time2 << endl;
                    times.insert(ceil(time2));
                }

                am_m.erase(am_m.begin());
            }
           times.erase(times.begin());
        }

        for (ll i = 0; i < n - 1; i++) cout << ans[i] << " ";
        cout << ans[n - 1] << endl;
        // cout << endl;
    }
}