//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

string s;

signed main() {
    IOS;

    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> groups, visited(n + 1);
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        int cur = i, gcnt = 0;
        while (!visited[cur]) {
            visited[cur]++;
            cur = a[cur];
            gcnt++;
        }
        groups.push_back(gcnt);
    }

    sort(groups.begin(), groups.end());

    int g = groups.size();
    int minans = 0, maxans = 0;
    if (k <= g) maxans += k * 2;
    else {
        maxans -= g * 2;
        if (n - k >= g) maxans += (k - g);
        else maxans = n;
    }
}