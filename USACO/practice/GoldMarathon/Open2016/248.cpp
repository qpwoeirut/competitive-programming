#include <bits/stdc++.h>

using namespace std;

const int MN = 255;

int N;
int A[MN];

int dp[MN][MN];

void chmx(int& a, const int b) {if (a<b) a=b;}

int main() {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    int ans = 1;
    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
        dp[i][i+1] = A[i];
        chmx(ans, A[i]);
    }

    for (int len=2; len<=N; ++len) {
        for (int lo=0; lo+len<=N; ++lo) {
            int hi = lo + len;
            for (int mid=lo+1; mid<hi; ++mid) {
                //cerr << lo << ' ' << mid << ' ' << hi << ' ' << dp[lo][mid] << ' ' << dp[mid][hi] << endl;
                if (dp[lo][mid] > 0 && dp[lo][mid] == dp[mid][hi]) {
                    dp[lo][hi] = dp[lo][mid] + 1;
                    chmx(ans, dp[lo][hi]);
                    break;
                }
            }
            //cerr << lo << ' ' << hi << ' ' << dp[lo][hi] << endl;
        }
    }

    cout << ans << endl;
}

