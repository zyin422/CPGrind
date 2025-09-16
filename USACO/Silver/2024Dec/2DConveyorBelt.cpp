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
            if (x1 <= 0 || x1 > n || y1 <= 0 || y1 > n || good[x1][y1]) continue;
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
                    if (good[x1][y1]) continue;
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
}