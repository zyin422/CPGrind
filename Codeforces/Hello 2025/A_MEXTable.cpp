//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
 
signed main() {
    IOS;
 
    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        cout << max(n, m) + 1 << endl;
    }
}