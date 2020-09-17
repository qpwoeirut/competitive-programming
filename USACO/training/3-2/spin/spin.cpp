/*
ID: zhongbr1
TASK: spin
LANG: C++14
*/

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef pair<int,int> pii;

int speed[5];
vector<pii> wedges[5];
bool open[5][360];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("spin.in", "r", stdin);
    freopen("spin.out", "w", stdout);

    for (int i=0; i<5; i++) {
        int n;
        cin >> speed[i] >> n;
        wedges[i] = vector<pii>(n);
        for (int j=0; j<n; j++) {
            cin >> wedges[i][j].FI >> wedges[i][j].SE;
        }
    }

    for (int i=0; i<360; i++) {
        for (int w=0; w<5; w++) {
            for (int j=0; j<360; j++) {
                open[w][j] = false;
            }
            for (int j=0; j<wedges[w].size(); j++) {
                for (int k=0; k<=wedges[w][j].SE; k++) {
                    open[w][(speed[w] * i + wedges[w][j].FI + k) % 360] = true;
                }
            }
        }
        for (int j=0; j<360; j++) {
            bool ok = true;
            for (int k=0; k<5; k++) {
                ok &= open[k][j];
            }

            if (ok) {
                cout << i << endl;
                return 0;
            }
        }
    }

    cout << "none" << endl;
}
