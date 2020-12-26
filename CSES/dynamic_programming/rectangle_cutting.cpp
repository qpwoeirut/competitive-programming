//rectangle_cutting.cpp created at 12/17/20 19:19:58
 
#include <bits/stdc++.h>
 
using namespace std;
 
int bad_solve(const int a, const int b) {
    if (a == b) return 0;
    if (a >= b) return 1 + bad_solve(a-b, b);
    else return 1 + bad_solve(a, b-a);
}
 
const int MN = 505;
const int INIT = 1001001001;
 
int dp[MN][MN];
 
void chmn(int& a, const int b) {if (a>b) a=b;}
 
int solve(const int a, const int b) {
    if (dp[a][b] != INIT) return dp[a][b];
    if (a == b) return 0;
 
    for (int i=1; i<a; ++i) {
        chmn(dp[a][b], solve(i, b) + solve(a - i, b) + 1);
    }
    for (int i=1; i<b; ++i) {
        chmn(dp[a][b], solve(a, i) + solve(a, b - i) + 1);
    }
    
    return dp[a][b];
}
 
int main() {
    int a, b;
    cin >> a >> b;
 
    for (int i=0; i<=a; ++i) {
        for (int j=0; j<=b; ++j) {
            dp[i][j] = INIT;
        }
    }
 
    cout << solve(a, b) << endl;
}

