/*
ID: zhongbr1
TASK: rockers
LANG: C++14
*/

//rockers.cpp created at 12/23/20 22:15:11

#include <bits/stdc++.h>

using namespace std;

const int MN = 24;

int N, T, M;
int A[MN];

int main() {
    freopen("rockers.in", "r", stdin);
    freopen("rockers.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int ans = 0;
    for (int i=0; i<(1 << N); ++i) {
        int ct = 0, cur = 0;
        int bit_ct = 0;
        for (int j=0; j<N; ++j) {
            if ((i >> j) & 1) {
                ++bit_ct;
                if (A[j] > T) {
                    bit_ct = -1;
                    break;
                }
                cur += A[j];
                if (cur > T) {
                    ++ct;
                    cur = A[j];
                }
            }
        }
        if (cur > 0) ++ct;

        if (bit_ct != -1 && ct <= M) {
            ans = max(ans, bit_ct);
        }
    }

    cout << ans << endl;
}
