//1485d.cpp created at 02/27/21 12:44:44

#include <bits/stdc++.h>

using namespace std;

const int MN = 502;
const int MX = 1000000;
const int LCM = 720720;

int N, M;
int G[MN][MN];

int ans[17];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }

    set<int> p4;
    for (int i=1; i<=100 && i*i*i*i<=MX; ++i) {
        p4.insert(i * i * i * i);
    }

    for (int i=1; i<=16; ++i) {
        ans[i] = -1;
        for (int j=i; j<=MX; j+=i) {
            if (p4.count(abs(LCM - j))) {
                ans[i] = j;
                break;
            }
        }
        assert(ans[i] != -1);
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (j) cout << ' ';
            if ((i ^ j) & 1) {
                cout << LCM;
            } else {
                cout << ans[G[i][j]];
            }
        }
        cout << '\n';
    }
}

