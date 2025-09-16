#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

vector<int> x_ = {0, 0, 1, -1};
vector<int> y_ = {1, -1, 0, 0};
vector<char> t_ = {'L', 'R', 'U', 'D'};

signed main() {
    IOS;

    int n, q; cin >> n >> q;
    int tot = n * n;
    int goodcells = 0;
    vector<vector<int>> queries;
    vector<vector<char>> grid(n + 2, vector<char>(n + 2, '?'));
    for (int i = 0; i < q; i++) {
        int r, c; char t; cin >> r >> c >> t;
        queries.push_back({r, c, t});
        grid[r][c] = t;
    }
    // for (int i = 0; i <= n + 1; i++) {
    //     for (int j = 0; j <= n + 1; j++) {
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }

    queue<vector<int>> bfs;
    vector<vector<int>> good(n + 2, vector<int>(n + 2, 0));
    for (int i = 1; i <= n; i++) {
        bfs.push({0, i});
        bfs.push({i, 0});
        bfs.push({n + 1, i});
        bfs.push({i, n + 1});
        good[0][i]++;
        good[i][0]++;
        good[n + 1][i]++;
        good[i][n + 1]++;
    }

    while (!bfs.empty()) {
        auto data = bfs.front(); bfs.pop();
        int x = data[0], y = data[1];
        for (int i = 0; i < 4; i++) {
            int x1 = x + x_[i];
            int y1 = y + y_[i];
            if (x1 <= 0 || x1 > n || y1 <= 0 || y > n || good[x1][y1]) continue;
            if (grid[x1][y1] != t_[i] && grid[x1][y1] != '?') continue;
            good[x1][y1]++;
            goodcells++;
            bfs.push({x1, y1});
        }
    }
    vector<int> ans(q);
    for (int i = q - 1; i >= 0; i--) {
        ans[i] = tot - goodcells;
        int r = queries[i][0], c = queries[i][1];
        grid[r][c] = '?';
        if (!good[r][c]) {
            bool gneighbor = false;
            for (int j = 0; j < 4; j++) {
                int x1 = r + x_[j];
                int y1 = c + y_[j];
                if (good[x1][y1]) gneighbor = true;
            }
            if (!gneighbor) continue;
            bfs.push({r, c});
            good[r][c]++;
            goodcells++;
            while (!bfs.empty()) {
                auto data = bfs.front(); bfs.pop();
                int x = data[0], y = data[1];
                for (int j = 0; j < 4; j++) {
                    int x1 = x + x_[j];
                    int y1 = y + y_[j];
                    if (x1 <= 0 || x1 > n || y1 <= 0 || y > n || good[x1][y1]) continue;
                    if (grid[x1][y1] != t_[j] && grid[x1][y1] != '?') continue;
                    good[x1][y1]++;
                    goodcells++;
                    bfs.push({x1, y1});
                }
            }
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
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
