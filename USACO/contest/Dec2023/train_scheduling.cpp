#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 500;
const ll INF = 2e18;

int N, T;
ll A[MN];
bool type_of[MN];
int prefix[2][MN];
int idx_of[2][MN];

ll dp[MN][MN][MN];

void chmn(ll& a, const ll b) {
    a = (a < b) ? a : b;
}

pair<bool, ll> arr[MN];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T;
    for (int i=0; i<N; ++i) {
        char c;
        cin >> c >> arr[i].second;
    }
    
    sort(arr, arr+N);
    for (int i=0; i<N; ++i) {
        type_of[i] = arr[i].first == 'B';
        prefix[0][i + 1] = prefix[0][i] + (type_of[i] == false);
        prefix[1][i + 1] = prefix[1][i] + (type_of[i] == true);
        idx_of[arr[i].first == 'B'][prefix[0][i]] = i;
    }

    for (int n=0; n<=N; ++n) {
        for (int last=0; last<N; ++last) {
            for (int mult=0; mult<=N; ++mult) {
                dp[n][last][mult] = INF;
            }
        }
    }
    dp[0][0][0] = 0;
    ll ans = INF;
    for (int n=0; n<=N; ++n) {
        for (int last=0; last<N; ++last) {
            for (int mult=0; mult<=N; ++mult) {
                const ll tm = A[last] + T * mult;
                const bool ltype = type_of[last] ^ (mult & 1) ^ 1;
                const bool otype = ltype ^ 1;

                const ll n_last = prefix[ltype][last];

                if (prefix[otype][N] > n) continue;
                if (prefix[otype][N] == n && n_last == prefix[ltype][N]) {
                    chmn(ans, dp[n][last][mult]);
                }

                ll delay = 0;
                for (int nxt=n + 1; nxt<=prefix[otype][N]; ++nxt) {
                    const int i = idx_of[otype][nxt - 1];
                    const ll ntm = A[i];
                    if (ntm <= tm) {
                        delay += tm - ntm;
                        chmn(dp[n_last][last][mult + 1], dp[n][last][mult] + delay);
                    } else {
                        chmn(dp[n_last][i][1], dp[n][last][mult] + delay);
                    }
                }
            }
        }
    }

    cout << ans << '\n';
}
