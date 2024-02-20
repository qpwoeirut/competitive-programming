#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int MOD = 1e9 + 7;

int N;
int A[MN];
string S;

int dp[MN][4];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> S;
    N = S.size();
    for (int i=0; i<N; ++i) {
        if (S[i] == 'A') A[i] = 0;
        else if (S[i] == 'C') A[i] = 1;
        else if (S[i] == 'G') A[i] = 2;
        else if (S[i] == 'T') A[i] = 3;
        else A[i] = -1;
    }

    for (int i=0; i<4; ++i) {
        dp[0][i] = A[i] == i || A[i] == -1;
    }
    for (int i=1; i<N; ++j) {
        for (int j=0; j<4; ++j) {
            for (int k=i-1; k>=0; --k) {
                if (A[k] == j) {
                    for (int l=k; l<i; ++l) {
                        dp[i][j] += dp[l][j];
                    }
                }
            }
        }
    }
