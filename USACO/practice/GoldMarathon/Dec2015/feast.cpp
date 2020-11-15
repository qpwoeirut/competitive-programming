//feast.cpp created at 11/12/20 17:08:28

#include <bits/stdc++.h>

using namespace std;

const int MX = 10000005;

int T;
int A, B;

bool kn[MX][2];
int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    cin >> T >> A >> B;

    kn[0][0] = kn[0][1] = true;
    for (int i=0; i<T; ++i) {
        if (kn[i][0]) {
            kn[i+A][0] = true;
            kn[i+B][0] = true;
            kn[i/2][1] = true;
        }
    }

    int ans = 0;
    for (int i=0; i<T; ++i) {
        if (kn[i][1]) {
            kn[i+A][1] = true;
            kn[i+B][1] = true;
            ans = i;
        }
    }

    if (kn[T][1]) ans = T;
    cout << ans << endl;
}

