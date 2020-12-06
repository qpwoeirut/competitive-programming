#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int MM = 30;
const int INIT = 1001001001;

int N, M, K;
int A[MN];
int mat[MM][MM];

int pref[MN][MM];
int dp[MN][MM];

void chmn(int& a, const int b) {if (a>b) a=b;}

int main() {
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for (int i=0; i<N; ++i) {
        char c;
        cin >> c;
        A[i] = c - 'a';
    }
    for (int i=0; i<M; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> mat[i][j];
        }
    }

    for (int k=0; k<M; ++k) {
        for (int i=0; i<M; ++i) {
            for (int j=0; j<M; ++j) {
                chmn(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            pref[i+1][j] = pref[i][j] + mat[A[i]][j];
        }
    }

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<M; ++j) {
            dp[i][j] = INIT;
        }
    }
    for (int i=0; i<=K; ++i) {
        for (int j=0; j<M; ++j) {
            dp[i][j] = pref[i][j];
        }
    }
    for (int i=K; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            chmn(dp[i+1][j], dp[i][j] + mat[A[i]][j]);
            if (i+K <= N) {
                for (int k=0; k<M; ++k) {
                    chmn(dp[i+K][k], dp[i][j] + pref[i+K][k] - pref[i][k]);
                }
            }
        }
    }

    //for (int i=0; i<M; ++i) { for (int j=0; j<M; ++j) { cerr << mat[i][j] << ' '; } cerr << endl; } cerr << endl;
    //for (int i=0; i<=N; ++i) { for (int j=0; j<M; ++j) { cerr << dp[i][j] << ' '; } cerr << endl; }

    int ans = INIT;
    for (int i=0; i<M; ++i) {
        chmn(ans, dp[N][i]);
    }

    cout << ans << endl;
}
