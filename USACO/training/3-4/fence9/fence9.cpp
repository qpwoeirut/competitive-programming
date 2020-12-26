/*
ID: zhongbr1
TASK: fence9
LANG: C++14
*/

//fence9.cpp created at 12/23/20 20:02:30

#include <bits/stdc++.h>

using namespace std;

int X1, Y1, X2;

int main() {
    freopen("fence9.in", "r", stdin);
    freopen("fence9.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> X1 >> Y1 >> X2;

    int ans = 0;
    const int dx = X1 - X2;
    for (int y=1; y<Y1; ++y) {
        const int L = ((y * X1) / Y1) + 1;
        const int R = (dx >= 0 ? (y * dx + Y1 - 1) / Y1 : (y * dx) / Y1) + X2 - 1;
        ans += R - L + 1;
    }

    cout << ans << endl;
}

