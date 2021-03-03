//fire.cpp created at 02/23/21 23:59:50

#include <bits/stdc++.h>

using namespace std;

const int MN = 100000;

int N, S;
int x[MN], y[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> S;
    long long ans = 0;
    for (int i=0; i<N; ++i) {
        cin >> y[i] >> x[i];
        y[i] = abs(y[i]);
        ans += y[i];
    }

    for (int i=0; i<=5000; ++i) {
        long long cur = 0;
        for (int j=0; j<N; ++j) {
            cur += min(abs(x[j] - i) + (y[j] < S ? S - y[j] : 0), y[j] + (abs(x[j] - i) < S ? S - abs(x[j] - i) : 0));
        }
        ans = min(ans, cur);
    }
    cout << ans << '\n';
}

/*
7 2
3 0
0 10
-4 10
-1 6
-2 15
-4 10
1 7
*/
