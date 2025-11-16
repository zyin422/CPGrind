#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

int curi;
vector<int> p;
vector<int> s;
vector<int> active;
vector<vector<int>> component;
vector<int> ans;

void make_set(int v) {
    p[v] = v;
    s[v] = 1;
    active[v] = 1;
    component[v].push_back(v);
}

int find_set(int v) {
    if (v == p[v])
        return v;
    return p[v] = find_set(p[v]);
}

void union_sets(int a, int b, int act) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (s[a] < s[b])
            swap(a, b);
        if (act) {
            if (!active[a]) {
                for (int v: component[a]) ans[v] = curi;
                active[a]++;
            }
            if (!active[b]) {
                for (int v: component[b]) ans[v] = curi;
            }
        }
        p[b] = a;
        s[a] += s[b];
        for (int v: component[b]) component[a].push_back(v);
    }
}

signed main() {
    IOS;

    int n, q; cin >> n >> q;
    p.resize(n + 1);
    s.resize(n + 1);
    active.resize(n + 1);
    component.resize(n + 1);
    ans.resize(n + 1, -1);
    vector<vector<int>> q1(q);
    for (int i = 0; i < q; i++) {
        char op; cin >> op;
        if (op == 'D') {
            int x; cin >> x;
            q1[i].push_back(0);
            q1[i].push_back(x);
        }
        else if (op == 'A') {
            int a, b; cin >> a >> b;
            q1[i].push_back(1);
            q1[i].push_back(a);
            q1[i].push_back(b);
        }
        else {
            int e; cin >> e;
            q1[i].push_back(2);
            q1[i].push_back(e);
        }
    }

    for (int i = 1; i <= n; i++) make_set(i);

    vector<vector<int>> edges;
    vector<int> off_edge;
    edges.push_back({0, 0});
    off_edge.push_back(1);
    vector<vector<int>> q2;
    for (int i = 0; i < q; i++) {
        int op = q1[i][0];
        if (op == 0) {
            int x = q1[i][1];
            active[x]--;
            q2.push_back({op, x});
        }
        else if (op == 1) {
            int a = q1[i][1], b = q1[i][2];
            edges.push_back({a, b});
            off_edge.push_back(0);
            q2.push_back({op});
        }
        else {
            int e = q1[i][1];
            off_edge[e]++;
            q2.push_back({op, edges[e][0], edges[e][1]});
        }
    }

    curi = q;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < edges.size(); i++) {
        if (off_edge[i]) continue;
        int a = edges[i][0], b = edges[i][1];
        //cout << a << " " << b << endl;
        union_sets(a, b, max(active[find_set(a)], active[find_set(b)]));
    }
    for (int i = 1; i <= n; i++) {
        if (active[i]) ans[i] = curi;
    }
    //for (int i = 1; i <= n; i++) cout << active[i] << " ";
    //cout << endl;


    for (curi = q - 1; curi >= 0; curi--) {
        int op = q2[curi][0];
        if (op == 0) {
            int x = q2[curi][1];
            if (!active[find_set(x)]) {
                active[find_set(x)]++;
                for (int v: component[find_set(x)]) ans[v] = curi;
            }
        }
        else if (op == 2) {
            int a = q2[curi][1], b = q2[curi][2];
            union_sets(a, b, max(active[find_set(a)], active[find_set(b)]));
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
}