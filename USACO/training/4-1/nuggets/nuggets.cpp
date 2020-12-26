/*
ID: zhongbr1
TASK: nuggets
LANG: C++14
*/

//nuggets.cpp created at 12/23/20 22:34:16

#include <bits/stdc++.h>

using namespace std;

const int MN = 12;
const int MX = 300 * 300;

int N;
int A[MN];

inline int gcd(const int a, const int b) {
    return b ? gcd(b, a % b) : a;
}

bool kn[MX + 300];
int main() {
    freopen("nuggets.in", "r", stdin);
    freopen("nuggets.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int g = A[0];
    for (int i=1; i<N; ++i) {
        g = gcd(g, A[i]);
    }

    if (g > 1) {
        cout << 0 << endl;
        return 0;
    }

    kn[0] = true;
    for (int i=0; i<MX; ++i) {
        if (!kn[i]) continue;
        for (int j=0; j<N; ++j) {
            kn[i + A[j]] = true;
        }
    }
    int ans = 0;
    for (int i=MX-1; i>=0; --i) {
        if (!kn[i]) {
            ans = i;
            break;
        }
    }
    cout << ans << endl;
}
