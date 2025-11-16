#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;
    int n, k; cin >> n >> k;
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    vector<vector<int>> adj(k + 1);
    for (int i = 1; i <= k; i++) {
        string s; cin >> s;
        for (int j = 0; j < k; j++) {
            if (s[j] == '1') adj[i].push_back(j + 1);
        }
    }

    vector<vector<int>> breed(k + 1);
    for (int i = 0; i < n; i++) breed[b[i]].push_back(i);

    multiset<vector<int>> nodes;
    nodes.insert({0, 0});
    vector<int> visited(n, 0);

    int ans = -1;
    while (!nodes.empty()) {
        auto data = *nodes.begin(); nodes.erase(nodes.begin());
        int d = data[0], u = data[1];
        if (visited[u]++) continue;
        if (u == n - 1) {
            ans = d;
            break;
        }
        for (int b1: adj[b[u]]) {
            auto it = upper_bound(breed[b1].begin(), breed[b1].end(), u);
            int v1 = -1, v2 = -1;
            if (it != breed[b1].end()) v2 = *it;
            if (it != breed[b1].begin()) {
                it--;
                v1 = *it;
            }
            if (v1 != -1 && !visited[v1]) nodes.insert({d + abs(u - v1), v1});
            if (v2 != -1 && !visited[v2]) nodes.insert({d + abs(u - v2), v2});
            if (breed[b1].size() != 0 && breed[b1][breed[b1].size() - 1] == n - 1) nodes.insert({d + abs(u - (n - 1)), n - 1});
        }
    }

    cout << ans << endl;
}