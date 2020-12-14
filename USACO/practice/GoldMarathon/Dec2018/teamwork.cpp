#include <bits/stdc++.h>

using namespace std;

const int MN = 10001;
const int MK = 1001;

const int LG = 16;

int N, K;
int A[MN];
int sparse[LG][MN];
int lg[MN];

int dp[MN];

void chmx(int& a, const int b) {if (a<b) a=b;}

int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        sparse[0][i] = A[i];
    }
    lg[1] = 0;
    for (int i=2; i<=N; ++i) {
        lg[i] = lg[i >> 1] + 1;
    }

    for (int i=1; i<LG; ++i) {
        for (int j=0; j + (1 << i) <= N; ++j) {
            sparse[i][j] = max(sparse[i-1][j], sparse[i-1][j + (1 << (i-1))]);
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=1; j<=K && i+j <= N; ++j) {
            const int L = i;
            const int R = i + j;
            const int sz = R - L;
            chmx(dp[i+j], dp[i] + sz * max(sparse[lg[sz]][L], sparse[lg[sz]][R - (1 << lg[sz])]));
        }
    }

    cout << dp[N] << endl;
}
