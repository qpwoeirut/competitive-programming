//radio.cpp created at 11/12/20 18:33:58

#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef pair<int,int> point;

const int MN = 1005;
const int INIT = 1001001001;

void chmn(int& a, const int b) {if (a>b) a=b;}

int N, M;
string f, b;

point fjpos[MN], bpos[MN];

int dp[MN][MN];
int dist(int i, int j) {
    int dx = fjpos[i].x - bpos[j].x;
    int dy = fjpos[i].y - bpos[j].y;
    return dx * dx + dy * dy;
}

int main() {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;

    cin >> fjpos[0].x >> fjpos[0].y;
    cin >> bpos[0].x >> bpos[0].y;

    cin >> f;
    cin >> b;

    for (int i=1; i<=N; ++i) {
        fjpos[i] = fjpos[i-1];
        if (f[i-1] == 'N') {
            ++fjpos[i].y;
        } else if (f[i-1] == 'E') {
            ++fjpos[i].x;
        } else if (f[i-1] == 'S') {
            --fjpos[i].y;
        } else {
            --fjpos[i].x;
        }
    }

    for (int i=1; i<=M; ++i) {
        bpos[i] = bpos[i-1];
        if (b[i-1] == 'N') {
            ++bpos[i].y;
        } else if (b[i-1] == 'E') {
            ++bpos[i].x;
        } else if (b[i-1] == 'S') {
            --bpos[i].y;
        } else {
            --bpos[i].x;
        }
    }

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            dp[i][j] = INIT;
        }
    }

    dp[0][0] = 0;
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            if (i == 0 && j == 0) continue;
            
            if (i > 0) {
                chmn(dp[i][j], dp[i-1][j]);
            }
            if (j > 0) {
                chmn(dp[i][j], dp[i][j-1]);
            }
            if (i > 0 && j > 0) {
                chmn(dp[i][j], dp[i-1][j-1]);
            }
            if (dp[i][j] < INIT) {
                dp[i][j] += dist(i, j);
            }
        }
    }

    //for (int i=0; i<=N; ++i) { for (int j=0; j<=M; ++j) { cerr << dp[i][j] << ' '; } cerr << endl; }

    cout << dp[N][M] << endl;
}

