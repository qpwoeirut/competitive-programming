/*
ID: zhongbr1
TASK: ratios
LANG: C++14
*/

#include <bits/stdc++.h>

using namespace std;

const int MX = 200;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("ratios.in", "r", stdin);
    freopen("ratios.out", "w", stdout);

    int tar[3];
    cin >> tar[0] >> tar[1] >> tar[2];

    if (tar[0] + tar[1] + tar[2] == 0) {
        cout << "0 0 0 0" << endl;
        return 0;
    }

    int mix[3][3];
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            cin >> mix[i][j];
        }
    }

    int x = MX, y = MX, z = MX;
    int m = -1;
    for (int i=0; i<=MX; ++i) {
        for (int j=0; j<=MX; ++j) {
            for (int k=0; k<=MX; ++k) {
                bool ok = true;
                int d = -1;
                for (int l=0; l<3; ++l) {
                    const int cur = i * mix[0][l] + j * mix[1][l] + k * mix[2][l];

                    ok &= cur >= tar[l];
                    if (tar[l] == 0) ok &= cur == 0;
                    else {
                        ok &= cur % tar[l] == 0;
                        if (d == -1) {
                            d = cur / tar[l];
                        } else {
                            ok &= cur == tar[l] * d;
                        }
                    }
                }

                if (ok && x + y + z > i + j + k) {
                    x = i;
                    y = j;
                    z = k;
                    assert(d != -1);
                    m = d;
                }
            }
        }
    }

    if (m == -1) {
        cout << "NONE" << endl;
    } else {
        cout << x << ' ' << y << ' ' << z << ' ' << m << endl;
    }
}
