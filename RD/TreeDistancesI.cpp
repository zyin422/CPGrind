// #pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define endl "\n"

int INF, MOD;

vector<int> p1, p2;
vector<vector<int>> adj;

void dfs(int p, int u)
{
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        dfs(u, v);
        int cd = p1[v] + 1;
        if (cd >= p1[u])
        {
            p2[u] = p1[u];
            p1[u] = cd;
        }
        else if (cd > p2[u])
            p2[u] = cd;
    }
}

void dfsup(int p, int u)
{
    if (p != 0)
    {
        int path = p1[p];
        if (p1[u] + 1 == path)
            path = p2[p];
        if (path + 1 >= p1[u])
        {
            p2[u] = p1[u];
            p1[u] = path + 1;
        }
        else if (path + 1 > p2[u])
            p2[u] = path + 1;
    }
    for (int v : adj[u]) {
        if (v == p)
            continue;
        dfsup(u, v);
    }
}

signed main()
{
    IOS;

    int n;
    cin >> n;
    p1.resize(n + 1, 0);
    p2.resize(n + 1, 0);
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 1);
    dfsup(0, 1);

    for (int i = 1; i <= n; i++)
        cout << p1[i] << " ";
}