//phidias.cpp created at 09/16/23 15:45:06

#include <bits/stdc++.h>

using namespace std;

const int MX = 600;

int W, H;
int N;

int dp[MX + 1][MX + 1];
int recurse(const int w, const int h) {
    if (dp[w][h] != -1) return dp[w][h];

    dp[w][h] = w * h;
    for (int i=1; i<w; ++i) {
        dp[w][h] = min(dp[w][h], recurse(i, h) + recurse(w - i, h));
    }
    for (int i=1; i<h; ++i) {
        dp[w][h] = min(dp[w][h], recurse(w, i) + recurse(w, h - i));
    }
    return dp[w][h];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i=0; i<=MX; ++i) {
        for (int j=0; j<=MX; ++j) {
            dp[i][j] = -1;
        }
    }

    cin >> W >> H;
    cin >> N;

    for (int i=0; i<N; ++i) {
        int w, h;
        cin >> w >> h;
        dp[w][h] = 0;
    }

    const int answer = recurse(W, H);
    cout << answer << '\n';
}

