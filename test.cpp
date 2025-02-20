#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    string s, t;
    cin >> s >> t;

    int n = s.size();
    int tn = t.size();

    string ans = "";
    for (int i = 0; i < n; i++) {
        ans += s[i];
        int m = ans.size();
        if (m >= tn) {
            string end = ans.substr(m - tn, tn);
            if (end == t) {
                ans.erase(m - tn);
            }
        }
    }

    cout << ans << endl;
}