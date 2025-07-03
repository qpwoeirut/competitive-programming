#include <bits/stdc++.h>

using namespace std;

using ll = long long;

inline void chmn(ll& a, ll b) {
    a = a <= b ? a : b;
}

const int MN = 1005;
const ll INF = 1e18;

string config[MN];
ll dp[MN][MN][2];

void solve() {
    ll N, M;
    cin >> N >> M;

    for (int i=0; i<M; ++i) {
        cin >> config[i];
        config[i] = '0' + config[i];
    }
    
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<M; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }
    for (int j=0; j<M; ++j) {
        dp[0][j][0] = j > 0;
    }
    for (int i=1; i<=N; ++i) {
        vector<pair<ll,ll>> opts[2];
        for (int j=0; j<M; ++j) {
            opts[0].emplace_back(dp[i-1][j][0], j);
            opts[1].emplace_back(dp[i-1][j][1], j);
        }
        opts[0].emplace_back(INF, INF);
        opts[0].emplace_back(INF, INF);
        opts[1].emplace_back(INF, INF);
        opts[1].emplace_back(INF, INF);

        sort(opts[0].begin(), opts[0].end());
        sort(opts[1].begin(), opts[1].end());
        for (int j=0; j<M; ++j) {
            if (config[j][i] == '1') continue;
            if (config[j][i - 1] == '0') {
                chmn(dp[i][j][0], opts[0][0].first + (opts[0][0].second != j));
                chmn(dp[i][j][0], opts[0][1].first + (opts[0][1].second != j));
            }
            chmn(dp[i][j][0], opts[1][0].first + (opts[1][0].second != j));
            chmn(dp[i][j][0], opts[1][1].first + (opts[1][1].second != j));
        }
        for (int j=0; j<M; ++j) {
            if (config[j][i - 1] == '0') {
                chmn(dp[i][j][1], opts[0][0].first + (opts[0][0].second != j) + 1);
                chmn(dp[i][j][1], opts[0][1].first + (opts[0][1].second != j) + 1);
            }
            chmn(dp[i][j][1], opts[1][0].first + (opts[1][0].second != j) + 1);
            chmn(dp[i][j][1], opts[1][1].first + (opts[1][1].second != j) + 1);
        }
    }

    ll ans = INF;
    for (int j=0; j<M; ++j) ans = min(ans, min(dp[N][j][0], dp[N][j][1]));

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--> 0) {
        solve();
    }
}

/*
4 2
1010
0101

15 3
000111111111000
111000111000111
111111000111111

17 3
00011111111111000
11100011111000111
11111100000111111

17 3
00001111111111000
11100001111000111
11111100000111111

1 1
0

5 1
10010

3 4
111
111
000
111

3 4
100
111
111
111
*/
