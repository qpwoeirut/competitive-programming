#include <bits/stdc++.h>

using namespace std;

const int MN = 1001;

int N, K;
int G[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    G[0][0] = 1;

    int ct = K == 1;

    for (int i=1; i<=N; ++i) {
        for (int j=0; j<=i; ++j) {
            G[i][j] = (G[i-1][j] + G[i-1][j-1]) % K;
            ct += G[i][j] == 0;
        }
    }

    cout << ct << '\n';
}
