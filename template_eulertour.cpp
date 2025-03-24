//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

int timer = 1;
int tin[100005], tout[100005];
vector<vector<int>> adj;

void dfs(int u, int p) {
    tin[u] = timer++;
    for (int v: adj[u]) {
        if (p != v) dfs(v, u);
    }
    tout[u] = timer;
}


signed main() {
    IOS;
}