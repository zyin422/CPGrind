#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    int n, m, c, r, k; cin >> n >> m >> c >> r >> k;
    vector<vector<vector<int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, l; cin >> u >> v >> l;
        adj[u].push_back({v, l});
        adj[v].push_back({u, l});
    }

    set<vector<int>> dijk;
    for (int i = 1; i <= c; i++) dijk.insert({0, i, i}); // dist cur root

    vector<set<int>> visitors(n + 1);
    while (!dijk.empty()) {
        auto it = dijk.begin();
        int d = (*it)[0], u = (*it)[1], root = (*it)[2];
        dijk.erase(it);
        if (visitors[u].size() > k) continue;
        if (visitors[u].find(root) != visitors[u].end()) continue;
        if (d > r) continue;
        visitors[u].insert(root);
        for (auto data: adj[u]) {
            int v = data[0], l = data[1];
            dijk.insert({d + l, v, root});
        }
    }

    vector<int> ans;
    for (int i = c + 1; i <= n; i++) {
        if ((visitors[i]).size() >= k) ans.push_back(i);
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << endl;
}