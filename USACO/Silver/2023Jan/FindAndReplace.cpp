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

    int t; cin >> t;
    while (t--) {
        string a, b; cin >> a >> b;
        int n = a.size();
        map<char, int> m;
        int ind = 0;
        set<char> tot_chars;
        for (char c = 'a'; c <= 'z'; c++) {
            m[c] = ind;
            ind++;
        }
        for (char c = 'A'; c <= 'Z'; c++) {
            m[c] = ind;
            ind++;
        }

        vector<set<int>> adj(52);
        for (int i = 0; i < n; i++) adj[m[a[i]]].insert(m[b[i]]);
        
        bool match = true;
        for (int i = 0; i < n; i++) {
            tot_chars.insert(b[i]);
            if (a[i] != b[i]) match = false;
        }
        int strokes = 0;
        bool out = false;
        for (int i = 0; i < 52; i++) {
            if (adj[i].size() > 1) out = true;
            else if (adj[i].size() == 1 && *adj[i].begin() != i) strokes++;
        }

        if (match) {
            cout << 0 << endl;
            continue;
        }
        else if (out || tot_chars.size() == 52) {
            cout << -1 << endl;
            continue;
        }
        vector<set<int>> adj2(52);
        for (int i = 0; i < n; i++) adj2[m[b[i]]].insert(m[a[i]]);

        vector<int> visited(52);
        int cnum = 1;
        set<int> cyclenums;
        for (int i = 0; i < 52; i++) {
            if (visited[i]) continue;
            visited[i] = cnum;
            queue<int> q;
            q.push(i);
            bool outCycle = false;
            bool isCycle = false;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v: adj[u]) {
                    if (u == v) outCycle = true;
                    if (visited[v] == cnum) {
                        isCycle = true;
                        continue;
                    }
                    else if (visited[v]) {
                        if (cyclenums.find(visited[v]) != cyclenums.end()) {
                            strokes--;
                            cyclenums.erase(cyclenums.find(visited[v]));
                        }
                        continue;
                    }
                    visited[v] = cnum;
                    q.push(v);
                }
            }
            if (isCycle && !outCycle) {
                strokes++;
                cyclenums.insert(cnum);
            }
            cnum++;
        }

        cout << strokes << endl;
    }
}