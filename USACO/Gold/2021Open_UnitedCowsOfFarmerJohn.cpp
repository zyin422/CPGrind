//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

// large static array, stores sum of each segment tree node
// in this implementation, node range [l, r] is calculated when we recurse
ll sum[524288];

// node index, [l, r] for node range, [ql, qr] for query range
ll query(ll p, ll l, ll r, ll ql, ll qr) {
    // no overlap between query and node range
    if (ql > r || qr < l) return 0;
    // node range completely covered by query
    if (ql <= l && r <= qr) return sum[p];
    // keep descending down
    // 2 * p and 2 * p + 1 are left and right child
    ll m = (l + r) / 2;
    return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m + 1, r, ql, qr);
}

// node index, [l, r] for node range, set element at idx to val
void update(ll p, ll l, ll r, ll idx, ll val) {
    if (l == r) { // leaf node
        sum[p] = val;
        return;
    }

    // descend down correct branch that the leaf is under
    ll m = (l + r) / 2;
    if (idx <= m) update(2 * p, l, m, idx, val);
    else update(2 * p + 1, m + 1, r, idx, val);
    sum[p] = sum[2 * p] + sum[2 * p + 1]; // recalculate value
}

signed main() {
    IOS;

    ll n; cin >> n;
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) cin >> b[i];

    vector<ll> prev(n);
    map<ll, ll> ind;
    for (ll i = 1; i <= n; i++) ind[i] = 0;
    for (ll i = 0; i < n; i++) {
        prev[i] = ind[b[i]];
        ind[b[i]] = i + 1;
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        // cout << ans << endl;
        if (prev[i] == 0) {
            ans += query(1, 1, n, 1, i);
            update(1, 1, n, i + 1, 1);
        }
        else {
            ans += query(1, 1, n, prev[i] + 1, i);
            update(1, 1, n, prev[i], 0);
            update(1, 1, n, i + 1, 1);
        }
    }

    cout << ans << endl;
}