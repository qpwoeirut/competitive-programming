#include <bits/stdc++.h>

using namespace std;

const int MN = 301;
const int INIT = 1001;

int N;
int A[MN];
int rdp[MN][MN];

int dp[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    //N = unique(A, A+N) - A;

    for (int len=1; len<=N; ++len) {
        for (int lo=0; lo+len<=N; ++lo) {
            const int hi = lo + len;

            dp[lo] = 0;
            for (int i=lo+1; i<hi; ++i) {
                if (A[i] != A[lo]) continue;
                dp[i] = INIT;
                for (int j=lo; j<i; ++j) {
                    if (A[j] == A[lo]) dp[i] = min(dp[i], dp[j] + rdp[j+1][i]);
                }
            }
            rdp[lo][hi] = INIT;
            for (int i=lo; i<hi; ++i) {
                if (A[i] == A[lo]) rdp[lo][hi] = min(rdp[lo][hi], 1 + dp[i] + rdp[i+1][hi]);
            }

            //cerr << "lo,hi: " << lo << ' ' << hi << endl;
            //for (int i=lo; i<hi; ++i) { cerr << dp[i] << ' '; } cerr << endl;
        }
    }

    //for (int i=0; i<N; ++i) { for (int j=0; j<=N; ++j) { cerr << rdp[i][j] << ' '; } cerr << endl; }

    cout << rdp[0][N] << endl;
}
/*
3
1 2 1
*/
