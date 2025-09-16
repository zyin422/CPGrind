#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

	ll tests; cin >> tests;
    while (tests--) {
        ll n, k; cin >> n >> k;
        vector<ll> x(n);
        ordered_set trees;
        map<int, int> cnttrees;
        for (ll i = 0; i < n; i++) {
            cin >> x[i];
            trees.insert(x[i]);
            cnttrees[x[i]]++;
        }

        ll cuttree = 0;
        vector<vector<ll>> laws(k, vector<ll>(4));
        map<ll, ll> initrees;
        for (ll i = 0; i < k; i++) {
            cin >> laws[i][0] >> laws[i][1] >> laws[i][2];
            laws[i][3] = i;
            ll id1 = trees.order_of_key(laws[i][0]);
            ll id2 = trees.order_of_key(laws[i][1] + 1);
            initrees[i] = id2 - id1;
        }
        sort(x.begin(), x.end());
        sort(laws.begin(), laws.end());

        ll lawi = 0;
        set<vector<ll>> endlaws;
        for (ll i = 0; i < n; i++) {
            ll tree = x[i];
            while (lawi < k && laws[lawi][0] <= tree) {
                endlaws.insert({laws[lawi][1], laws[lawi][0], laws[lawi][2], laws[lawi][3]});
                lawi++;
            }

            while (!endlaws.empty() && (*endlaws.begin())[0] < tree) {
                auto data = *endlaws.begin(); endlaws.erase(endlaws.begin());
                ll needcuts = data[2];
                //cout << "needcuts: " << needcuts << endl;
                ll r = data[0], l = data[1], endlawi = data[3];
                ll id1 = trees.order_of_key(l);
                ll id2 = trees.order_of_key(r + 1);
                ll nowtrees = id2 - id1;
                //cout << "nowtrees: " << nowtrees << endl;
                needcuts -= initrees[endlawi] - nowtrees;
                for (ll j = 0; j < needcuts; j++) {
                    auto it = trees.lower_bound(r);
                    if (*it > r) it--;
                    cnttrees[*it]--;
                    if (cnttrees[*it] == 0) trees.erase(it);
                    cuttree++;
                }
            }
        }
        while (!endlaws.empty()) {
            auto data = *endlaws.begin(); endlaws.erase(endlaws.begin());
            ll needcuts = data[2];
            //cout << "needcuts: " << needcuts << endl;
            ll r = data[0], l = data[1], endlawi = data[3];
            ll id1 = trees.order_of_key(l);
            ll id2 = trees.order_of_key(r + 1);
            ll nowtrees = id2 - id1;
            //cout << "nowtrees: " << nowtrees << endl;
            needcuts -= initrees[endlawi] - nowtrees;
            for (ll j = 0; j < needcuts; j++) {
                auto it = trees.lower_bound(r);
                if (*it > r) it--;
                cnttrees[*it]--;
                if (cnttrees[*it] == 0) trees.erase(it);
                cuttree++;
            }
        }

        cout << n - cuttree << endl;
    }
}