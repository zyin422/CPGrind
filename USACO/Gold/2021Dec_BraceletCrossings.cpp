#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

bool valid = true;
vector<set<int>> adj;
vector<int> visited;

void dfs(int u) {
    if (visited[u] == 1) {
        valid = false;
        return;
    }
    else if (visited[u] == 2) return;

    visited[u] = 1;
    for (int v: adj[u]) dfs(v);
    visited[u] = 2;
    return;
}

signed main() {
    IOS;

    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;

        vector<vector<int>> chains(m);
        for (int i = 0; i < m; i++) {
            int k; cin >> k;
            while (k--) {
                int c; cin >> c;
                chains[i].push_back(c);
            }
        }

        valid = true;
        set<int> pcolors;
        vector<int> mark(n + 1, 0);
        adj.clear();
        visited.clear();
        adj.resize(n + 1, set<int>());
        visited.resize(n + 1, 0);
        vector<set<int>> ccentric(n + 1);
        for (int i = 0; i < m; i++) {
            map<int, int> cnt;
            vector<int> bcolors; // adj
            set<int> ccolors; // consec
            vector<int> ncolors; // overlap
            map<int, int> nmap;
            for (int c: chains[i]) {
                if (!cnt[c]) {
                    for (int u: bcolors) {
                        if (ccentric[u].find(c) != ccentric[u].end()) {
                            if (!nmap[u]) {
                                valid = false;
                                break;
                            }
                        }
                        adj[u].insert(c);
                    }
                    bcolors.push_back(c);
                    ccolors.insert(c);
                    for (int u: ncolors) ccentric[u].insert(c);
                    ncolors.push_back(c);
                    cnt[c]++;
                    nmap[c]++;
                }
                else {
                    if (ncolors[ncolors.size() - 1] != c) {
                        valid = false;
                        break;
                    }
                    ncolors.pop_back();
                    nmap[c]--;
                }
            }
            if (!valid) break;
            
            for (int c: pcolors) {
                if (ccolors.find(c) == ccolors.end()) {
                    mark[c]++;
                    for (int cc: ccolors) {
                        if (ccentric[c].find(cc) != ccentric[c].end()) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            pcolors = ccolors;
        }

        for (int c: pcolors) mark[c]++;
        for (int i = 1; i <= n; i++) {
            if (mark[i] > 1) {
                valid = false;
                break;
            }
        }

        for (int i = m - 1; i >= 0; i--) {
            map<int, int> cnt;
            vector<int> bcolors; // adj
            set<int> ccolors; // consec
            vector<int> ncolors; // overlap
            map<int, int> nmap;
            for (int c: chains[i]) {
                if (!cnt[c]) {
                    for (int u: bcolors) {
                        if (ccentric[u].find(c) != ccentric[u].end()) {
                            if (!nmap[u]) {
                                valid = false;
                                break;
                            }
                        }
                        adj[u].insert(c);
                    }
                    bcolors.push_back(c);
                    ccolors.insert(c);
                    for (int u: ncolors) ccentric[u].insert(c);
                    ncolors.push_back(c);
                    cnt[c]++;
                    nmap[c]++;
                }
                else {
                    if (ncolors[ncolors.size() - 1] != c) {
                        valid = false;
                        break;
                    }
                    ncolors.pop_back();
                    nmap[c]--;
                }
            }
            if (!valid) break;

            for (int c: pcolors) {
                if (ccolors.find(c) == ccolors.end()) {
                    mark[c]++;
                    for (int cc: ccolors) {
                        if (ccentric[c].find(cc) != ccentric[c].end()) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            pcolors = ccolors;
        }

        for (int i = 1; i <= n; i++) dfs(i);

        if (!valid) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
}