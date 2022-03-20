#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;
using ll=long long;

#define fi first
#define se second

const int MN = 1003;

int N;
int G[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        char c;
        int xi, yi, xj, yj, vi;
        cin >> c >> xi >> yi >> xj >> yj >> vi;

        if (c == 'B') vi = -vi;

        ++xi; ++yi;
        ++xj; ++yj;
        G[xi][yi] += vi;
        G[xi][yj] -= vi;
        G[xj][yi] -= vi;
        G[xj][yj] += vi;
    }

    int mx = -1001001001;
    for (int i=1; i<=1001; ++i) {
        for (int j=1; j<=1001; ++j) {
            G[i][j] += G[i-1][j] + G[i][j-1] - G[i-1][j-1];
            mx = max(mx, G[i][j]);
        }
    }

    int ct = 0;
    for (int i=1; i<=1001; ++i) {
        for (int j=1; j<=1001; ++j) {
            ct += mx == G[i][j];
        }
    }
    cout << mx << ' ' << ct << '\n';
}
