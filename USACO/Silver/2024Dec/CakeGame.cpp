#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

signed main() {
    IOS;

	ll t; cin >> t;
	while (t--) {
		ll n; cin >> n;
		vector<ll> a(n);
		ll tot = 0;
		for (ll i = 0; i < n; i++) {
			cin >> a[i];
			tot += a[i];
		}

		vector<ll> psum(n + 1, 0);
		vector<ll> ssum(n + 1, 0);
		for (ll i = 0; i < n; i++) {
			psum[i + 1] = psum[i] + a[i];
		}
		for (ll i = n; i > 0; i--) {
			ssum[i - 1] = ssum[i] + a[i - 1];
		}

		ll ecakes = (n - 2) / 2, j = n;
		ll ans = 0;
		for (ll i = ecakes; i >= 0; i--) {
			ans = max(psum[i] + ssum[j], ans);
			j--;
		}

		cout << tot - ans << " " << ans << endl;
	}
}