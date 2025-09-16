//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

int smin[400005];
int smax[400005];

int query1(int p, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return smin[p];
    int m = (l + r) / 2;
    return min(query1(2 * p, l, m, ql, qr), query1(2 * p + 1, m + 1, r, ql, qr));
}

int query2(int p, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return smax[p];
    int m = (l + r) / 2;
    return max(query2(2 * p, l, m, ql, qr), query2(2 * p + 1, m + 1, r, ql, qr));
}

void update1(int p, int l, int r, int idx, int val) {
    if (l == r) {
        smin[p] = val;
        return;
    }

    int m = (l + r) / 2;
    if (idx <= m) update1(2 * p, l, m, idx, val);
    else update1(2 * p + 1, m + 1, r, idx, val);
    smin[p] = min(smin[2 * p], smin[2 * p + 1]);
}

void update2(int p, int l, int r, int idx, int val) {
    if (l == r) {
        smax[p] = val;
        return;
    }

    int m = (l + r) / 2;
    if (idx <= m) update2(2 * p, l, m, idx, val);
    else update2(2 * p + 1, m + 1, r, idx, val);
    smax[p] = max(smax[2 * p], smax[2 * p + 1]);
}

signed main() {
    IOS;

    ll t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            int val = a[i] - i;
            update1(1, 1, n, i, val);
            update2(1, 1, n, i, val);
        }

        vector<int> ans(q + 1);
        for (int i = 1; i <= n; i++) {
            int val = a[i] - i;
            int qmin = query1(1, 1, n, 1, i);
            int qmax = query2(1, 1, n, i, n);
            ans[0] = max(max(val - qmin, qmax - val), ans[0]);
        }

        for (int i = 1; i <= q; i++) {
            int p, x; cin >> p >> x;
            int val = x - p;
            update1(1, 1, n, p, val);
            update2(1, 1, n, p, val);
            int qmin = (query1(1, 1, n, 1, p));
            int qmax = (query2(1, 1, n, p, n));
            ans[i] = max(val - qmin, qmax - val);
        }

        for (int i = 0; i <= q; i++) cout << ans[i] << endl;
    }
}