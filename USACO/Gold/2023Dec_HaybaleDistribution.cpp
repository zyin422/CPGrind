//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    ll N, q; cin >> N;
    vector<ll> y(N);
    for (ll i = 0; i < N; i++) cin >> y[i];
    cin >> q;

    sort(y.begin(), y.end());

    vector<ll> x;
    map<ll, ll> cnt;
    x.push_back(y[0]);
    for (ll i = 0; i < N; i++) {
        cnt[y[i]]++;
        if(y[i] > x.back()) x.push_back(y[i]);
    }
    int n = x.size();

    vector<ll> l(n), r(n);
    ll lcows = 0, rcows = N;
    ll lcnt = 0, rcnt = 0, lprev = x[0];
    for (ll i = 1; i < n; i++) rcnt += (x[i] - x[0]) * cnt[x[i]];
    for (ll i = 0; i < n; i++) {
        rcnt -= (x[i] - lprev) * rcows;
        rcows -= (cnt[x[i]]);
        lcnt += (x[i] - lprev) * lcows;
        lcows += (cnt[x[i]]);
        l[i] = lcnt;
        r[i] = rcnt;

        lprev = x[i];
    }

    // for (ll i = 0; i < n; i++) cout << l[i] << " " << r[i] << endl;

    while (q--) {
        ll a, b; cin >> a >> b;
        // ll idx = n * b / (a + b);
        // cout << l[idx] * a + r[idx] * b << endl;
        ll left = 0, right = n - 1;
        while (left < right) {
            ll mid = left + (right - left) / 2;
            if (l[mid] * a + r[mid] * b > l[mid + 1] * a + r[mid + 1] * b) left = mid + 1;
            else right = mid;
        }

        cout << l[left] * a + r[left] * b << endl;
    }
}