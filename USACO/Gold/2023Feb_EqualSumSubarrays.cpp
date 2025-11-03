//#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

vector<ll> p(2e5);
vector<ll> s(2e5);

void make_set(ll v) {
    p[v] = v;
    s[v] = 1;
}

ll find_set(ll v) {
    if (v == p[v])
        return v;
    return p[v] = find_set(p[v]);
}

void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (s[a] < s[b])
            swap(a, b);
        p[b] = a;
        s[a] += s[b];
    }
}

signed main() {
    IOS;

    /*
    Input
    for each index i:
        make vector of sums, sort
        for each sum w/ i, count distance from closest, output running minimum
    */

    ll n; cin >> n;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    vector<ll> psum(n + 1);
    for (ll i = 1; i <= n; i++) psum[i] = psum[i - 1] + a[i];

    multiset<ll> s0, s1;
    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j <= n; j++) {
            ll diff = psum[j] - psum[i];
            if (i == 0) s1.insert(diff);
            else s0.insert(diff);
        }
    }
    /*cout << "without sum: ";
    for (int s: s0) cout << s << " ";
    cout << endl << "with sum: ";
    for (int s: s1) cout << s << " ";
    cout << endl;Z*/
    
    for (ll i = 1; i <= n; i++) {
        if (i != 1) {
            for (ll j = 0; j < i - 1; j++) {
                //cout << "diff1: ";
                ll diff = psum[i - 1] - psum[j];
                //cout << diff << endl;
                s1.erase(s1.find(diff));
                s0.insert(diff);
            }
            for (ll j = i; j <= n; j++) {
                //cout << "diff2: ";
                ll diff = psum[j] - psum[i - 1];
                //cout << diff << endl;
                s0.erase(s0.find(diff));
                s1.insert(diff);
            }
        }

        ll mindiff = 1e18;
        
        auto it1 = s0.begin(), it2 = s1.begin();
        while (it1 != s0.end() && it2 != s1.end()) {
            mindiff = min(abs(*it2 - *it1), mindiff);
            if (*it1 < *it2 || it2 == s1.end()) it1++;
            else it2++;
        }

        cout << mindiff << endl;
    }
    
}