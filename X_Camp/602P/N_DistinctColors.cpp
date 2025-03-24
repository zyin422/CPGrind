#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

int timer = 1;
int sum[800005];
vector<vector<int>> c;
vector<vector<int>> adj;
vector<vector<int>> intv; // right, left, node

void dfs(int u, int p) {
    c[u][0] = timer;
    int tin = timer++;
    for (int v: adj[u]) {
        if (v != p) dfs(v, u);
    }
    int tout = timer;
    intv.push_back({tout, tin, u});
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
    c.resize(n + 1, vector<int>(2));
    map<int, int> p;
    for (int i = 1; i <= n; i++) {
        cin >> c[i][1];
        p[c[i][1]] = -1;
    }


    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    sort(c.begin(), c.end());
    sort(intv.begin(), intv.end());

    int j = 1;
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++) {
        int r = intv[i][0], l = intv[i][1], u = intv[i][2];
        while (j < r) {
            if (p[c[j][1]] != -1) update(1, 1, n, p[c[j][1]], 0);
            p[c[j][1]] = j;
            update(1, 1, n, j, 1);
            j++;
        }
        ans[u] = query(1, 1, n, l, r - 1);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
}