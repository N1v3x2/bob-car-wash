#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr char nl = '\n';

int n, m;
vector<int> money, need, patience;
vector<vector<ll>> memo;

ll dp(int i, int t) {
    if (t > m) return INT64_MIN;
    if (i == n) return 0;
    if (memo[i][t] != -1) return memo[i][t];

    memo[i][t] = dp(i + 1, t);
    if (patience[i] >= t) {
        memo[i][t] = max(
            memo[i][t],
            money[i] + dp(i + 1, t + need[i])
        );
    }

    return memo[i][t];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    money.resize(n), need.resize(n), patience.resize(n);
    for (int i = 0; i < n; ++i) cin >> money[i];
    for (int i = 0; i < n; ++i) cin >> need[i];
    for (int i = 0; i < n; ++i) cin >> patience[i];

    memo.resize(n, vector<ll>(m + 1, -1));

    vector<tuple<int, int, int>> tmp(n);
    for (int i = 0; i < n; ++ i) tmp[i] = { patience[i], money[i], need[i] };
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < n; ++i) {
        auto& [x, y, z] = tmp[i];
        patience[i] = x;
        money[i] = y;
        need[i] = z;
    }

    cout << dp(0, 0) << nl;
}
