/*
ID: zhongbr1
TASK: stamps
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

int ct[201 * 10001];
int stamp[51];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("stamps.in", "r", stdin);
    freopen("stamps.out", "w", stdout);

    int K, N;
    cin >> K >> N;

    int mx = 0;
    for (int i=0; i<N; i++) {
        cin >> stamp[i];
        mx = max(mx, stamp[i]);
    }

    const int MX = mx * K;
    fill(ct, ct+MX+1, K+1);
    ct[0] = 0;
    for (int i=0; i<=MX; i++) {
        if (ct[i] > K) {
            cout << i-1 << endl;
            return 0;
        }
        for (int j=0; j<N; j++) {
            if (i + stamp[j] <= MX) {
                ct[i + stamp[j]] = min(ct[i + stamp[j]], ct[i] + 1);
            }
        }
    }
    cout << MX << endl;
}
