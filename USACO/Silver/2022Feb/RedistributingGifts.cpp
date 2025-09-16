// #pragma GCC optimize ("trapv")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    vector<set<int>> ai(n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        if (a[i][j] == i + 1) break;
        ai[i].insert(a[i][j]);
    }

    for (int i = 0; i < n; i++) {
        int pref = i + 1;
        vector<int> visited(n + 1);
        for (int j = 0; j < n; j++) {
            if (a[i][j] == i + 1) break;
            if (visited[a[i][j]]) continue;
            queue<int> q;
            q.push(a[i][j]); visited[a[i][j]]++;
            bool f = false;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (ai[u - 1].find(pref) != ai[u - 1].end()) {
                    f = true;
                    pref = a[i][j];
                    break;
                }
                for (int v: ai[u - 1]) {
                    if (!visited[v]) {
                        q.push(v);
                        visited[v]++;
                    }
                }
            }
            if (f) break;
        }
        cout << pref << endl;
    }

}