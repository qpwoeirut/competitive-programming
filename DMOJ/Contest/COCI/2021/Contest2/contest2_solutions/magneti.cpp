#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=55;
const int L=1e4+5;
const int MOD=1e9+7;

int n, l;
int r[N];
int dp[2][N][L];
int pas[L+N][N];

int mul(int a, int b) {
    return (ll)a*b%MOD;
}

int add(int a, int b) {
    return (a+b)%MOD;
}

void load() {
    scanf("%d %d", &n, &l);
    for (int i=1; i<=n; ++i) scanf("%d", r+i);
    sort(r+1, r+n+1);
}

void pascal() {
    for (int i=0; i<=l+n; ++i) pas[i][0]=1;
    for (int i=1; i<=l; ++i)
        for (int j=1; j<=min(n, i); ++j)
            pas[i][j]=add(pas[i-1][j], pas[i-1][j-1]);
}

int main() {
    load();
    pascal();

    int x=0;
    dp[0][0][0]=1;
    for (int i=1; i<=n; ++i) {
        x^=1;
        dp[x][0][0]=0;

        int R=r[i];
        for (int j=1; j<=i; ++j) {
            for (int k=1; k<=l; ++k) {
                dp[x][j][k]=dp[!x][j-1][k-1];
                if (k>=R) dp[x][j][k]=add(dp[x][j][k], mul(dp[!x][j][k-R], 2*j));
                if (k>=2*R-1) dp[x][j][k]=add(dp[x][j][k], mul(dp[!x][j+1][k-2*R+1], j*(j+1)));
            }
        }
    }

    int sol=0;
    for (int i=1; i<=l; ++i) sol=add(sol, mul(dp[x][1][i], pas[l-i+n][n]));
    printf("%d", sol);

    return 0;
}
