//spiralprint.cpp created at 11/12/20 11:59:26

#include <bits/stdc++.h>

using namespace std;

const int MN = 501;

int N;
int G[MN][MN];

int main() {
    freopen("spiralprint.in", "r", stdin);
    freopen("spiralprint.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> G[i][j];
        }
    }

    for (int i=0; i<N/2; ++i) {
        for (int j=i; j<N-i; ++j) {
            cout << G[i][j] << '\n';
        }
        for (int j=i+1; j<N-i-1; ++j) {
            cout << G[j][N-i-1] << '\n';
        }
        for (int j=N-i-1; j>=i+1; --j) {
            cout << G[N-i-1][j] << '\n';
        }
        for (int j=N-i-1; j>=i+1; --j) {
            cout << G[j][i]<< '\n';
        }
    }

    if (N&1) {
        cout << G[N/2][N/2] << endl;
    }
}

