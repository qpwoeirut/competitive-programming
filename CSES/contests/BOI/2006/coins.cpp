#include <bits/stdc++.h>

using namespace std;

const int MN = 500005;
const int LG = 35;
const int INF = 1001001001;

int N, K;
int A[MN], B[MN];
int dp[MN][LG];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i] >> B[i];
    }
    A[N] = K;

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<LG; ++j) {
            dp[i][j] = INF;
        }
    }

    dp[0][0] = 0;
    for (int i=1; i<=N; ++i) {
        for (int x=0; x<LG && x<K; ++x) {
            dp[i][x] = dp[i-1][x];

            const int xx = x - !B[i-1];
            if (dp[i-1][xx] + A[i-1] < A[i]) {
                dp[i][x] = min(dp[i][x], dp[i-1][xx] + A[i-1]);
            }
        }
    }


    int ans1 = 0;
    int ans2 = 0;
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<LG && j<K; ++j) {
            if (dp[i][j] < INF) {
                if (ans1 < j) {
                    ans1 = j;
                    ans2 = 0;
                }
                if (ans1 == j) {
                    ans2 = max(ans2, K - max(dp[i][j], 1));
                }
            }
        }
    }

    //for (int i=0; i<=N; ++i) { for (int j=0; j<LG && j<K; ++j) { cerr << (dp[i][j] == INF ? "XX" : to_string(dp[i][j])) << ' '; } cerr << endl; }
    cout << ans1 << '\n' << ans2 << '\n';
}

/*
dp[n][x] = min change required for x new coins from the first n coins
x is O(log n)
dp[n][x] = dp[n-1][x] + A[n] if dp[n-1][x] < A[n], subtract 1 from x if coin n is new

7 25
1 0
2 0
3 1
5 0
10 0
13 0
20 0
3
6

3 10
1 1
2 1
4 1
0
9

1 1000
1 1
0
999
*/
