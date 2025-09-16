#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

int timer = 1;
int tin[100005], tout[100005];
int sum[400005];
vector<vector<int>> adj;

void dfs(int u) {
    tin[u] = timer++;
    for (int v: adj[u]) dfs(v);
    tout[u] = timer;
}

int query(int p, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return sum[p];

    int m = (l + r) / 2;
    return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m + 1, r, ql, qr);
}

void update(int p, int l, int r, int idx, int val) {
    if (l == r) {
        sum[p] = val;
        return;
    }

    int m = (l + r) / 2;
    if (idx <= m) update(2 * p, l, m, idx, val);
    else update(2 * p + 1, m + 1, r, idx, val);
    sum[p] = sum[2 * p] + sum[2 * p + 1];
}

signed main() {
    IOS;

    int n; cin >> n;
    vector<vector<int>> p(n, vector<int>(2));
    for (int i = 1; i <= n; i++) {
        cin >> p[i - 1][0];
        p[i - 1][1] = i;
    }

    sort(p.rbegin(), p.rend());

    adj.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int u; cin >> u;
        adj[u].push_back(i);
    }

    dfs(1);

    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++) {
        ans[p[i][1]] = query(1, 1, n, tin[p[i][1]], tout[p[i][1]] - 1);
        update(1, 1, n, tin[p[i][1]], 1);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
}