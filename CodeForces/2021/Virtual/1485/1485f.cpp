//1485f.cpp created at 02/27/21 13:18:29

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;
const ll MOD = 1e9 + 7;

void add(ll& a, const ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

int N;
ll B[MN];

ll pref[MN];
map<ll, vector<int>> pos;
ll dp[MN];
ll invalid[MN];
void solve() {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }
    pos.clear();
    fill(dp, dp+N+1, 0);
    fill(invalid, invalid+N+1, 0);

    pref[0] = 0;
    for (int i=0; i<N; ++i) {
        pref[i+1] = pref[i] + B[i];
        pos[pref[i+1]].push_back(i);
    }

    ll sum = 0;

    for (int i=0; i<N; ++i) {
        dp[i] = i == 0 ? 1 : sum;
        int idx = lower_bound(pos[pref[i]].begin(), pos[pref[i]].end(), i) - pos[pref[i]].begin();
        if (idx < pos[pref[i]].size()) {
            add(invalid[pos[pref[i]][idx] + 1], dp[i]);
        }

        add(sum, dp[i] - invalid[i]);
    }
    //for (int i=0; i<N; ++i) { cerr << dp[i] << ' '; } cerr << endl;
    //for (int i=0; i<N; ++i) { cerr << invalid[i] << ' '; } cerr << endl;


    cout << sum << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) solve();
}

