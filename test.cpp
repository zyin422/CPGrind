    //#pragma GCC optimize ("trapv")
    #include <bits/stdc++.h>
    using namespace std;

    typedef long long ll;
    typedef unsigned long long ull;

    #define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #define endl "\n"

    ll MOD = 1e9 + 7;

    signed main() {
        IOS;
        ll n, d, a1, b; cin >> n >> d >> a1 >> b;
        if (d * (a1 - b) < (ll)1e8) {
            vector<ll> a(n);
            for (ll i = 0; i < n; i++) cin >> a[i];
            sort(a.begin(), a.end());
            for (ll i = 0; i < d; i++) {
                for (ll i = n - (a1); i < n - a1 + (a1 - b); i++) a[i]++;
                sort(a.begin(), a.end());
            }
            ll ans = 0;
            for (ll i = 0; i < n; i++) {
                ans += a[i] * a[i];
                ans %= MOD;
            }
            cout << ans << endl;
            return 0;
        }
        vector<ll> orig(n);
        for (ll i = 0; i < n; i++) cin >> orig[i];
        sort(orig.begin(), orig.end());
        ll c = a1 - b;
        ll on = n;
        
        vector<ll> a(a1);
        for (ll i = n - a1; i < n; i++) a[i - (n - a1)] = orig[i];
        // for (ll i = 0; i < a1; i++) cout << a[i] << " ";
        n = a1;
        deque<ll> s1, s2;
        for (ll i = 0; i < c - 1; i++) {
            s1.push_front(a[i]);
        }
        ll cur = a[c - 1], curc = 1, curinc = 1, nxt = 0;
        for (ll i = c; i < n; i++) {
            s2.push_back(a[i]);
        }

        ll added = 0;
        while (!(s1.empty() && s2.empty()) && d > 0) {
            
            ll s1f = -1, s2f = -1;
            if (!s1.empty()) s1f = s1.front();
            if (!s2.empty()) s2f = s2.front();
            // cout << s1f << " " << s2f << endl;
            ll diff1 = -1, diff2 = -1;
            if (s1f != -1) diff1 = cur - (s1f + added);
            if (s2f != -1) diff2 = ((s2f - (cur + 1)) * curc + (curc - nxt) - 1) / curinc + 1;
            if (diff1 == -1) diff1 = diff2 + 1;
            if (diff2 == -1) diff2 = diff1 + 1;
            if (diff1 < diff2) {
                if (diff1 > d) diff1 = d;
                added += diff1;
                nxt += diff1 * curinc;
                cur += nxt / curc;
                nxt %= curc;
                if (s1f + added == cur) {
                    curc++;
                    curinc++;
                    s1.pop_front();
                }
                d -= diff1;
            }
            else {
                if (diff2 > d) diff2 = d;
                s2.pop_front();
                added += diff2;
                nxt += diff2 * curinc;
                cur += nxt / curc;
                nxt %= curc;
                curc++;
                d -= diff2;
            }
            // cout << endl;
        }
        //assert(0);
        ll ans = 0;
        if (d == 0) {
            while (!s1.empty()) {
                ans += (s1.front() + added) * (s1.front() + added);
                ans %= MOD;
                s1.pop_front();
            }
            while (!s2.empty()) {
                ans += s2.front() * s2.front();
                ans %= MOD;
                s2.pop_front();
            }
        }
        else {
            // cout << "no d" << endl;
            nxt += d * curinc;
            cur += nxt / curc;
            nxt %= curc;
        }
        for (ll i = 0; i < nxt; i++) {
            ans += (cur + 1) * (cur + 1);
            ans %= MOD;
        }
        for (ll i = 0; i < curc - nxt; i++) {
            ans += cur * cur;
            ans %= MOD;
        }
        // cout << added << endl;
        // cout << cur << endl;
        // cout << curc << endl;
        // cout << nxt << endl;
        for (ll i = 0; i < (on - a1); i++) {
            ans += orig[i] * orig[i];
            ans %= MOD;
        }
        cout << ans % MOD << endl;
    }