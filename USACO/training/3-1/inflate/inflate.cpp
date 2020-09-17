/*
ID: zhongbr1
TASK: inflate
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

int kn[20001];
int pts[10001], mins[10001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("inflate.in", "r", stdin);
    freopen("inflate.out", "w", stdout);

    int N, L;
    cin >> L >> N;

    for (int i=0; i<N; i++) {
        cin >> pts[i] >> mins[i];
    }

    fill(kn, kn+20001, -1);
    kn[0] = 0;
    int ans = 0;
    for (int i=0; i<=L; i++) {
        if (kn[i] == -1) {
            continue;
        }

        for (int j=0; j<N; j++) {
            kn[i+mins[j]] = max(kn[i+mins[j]], kn[i] + pts[j]);
        }

        ans = max(ans, kn[i]);
    }

    cout << ans << endl;
}
