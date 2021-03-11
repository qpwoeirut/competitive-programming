//xorsum.cpp created at 03/04/21 10:30:22

#include <bits/stdc++.h>

using namespace std;

#define LB lower_bound

const int MN = 1000000;
const int LG = 24;

int N;
int A[MN];
int val[MN];
int psum[(1 << LG) + 1];

const int p2[31] = {
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7,
    1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15,
    1 << 16, 1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 21, 1 << 22, 1 << 23,
    1 << 24, 1 << 25, 1 << 26, 1 << 27, 1 << 28, 1 << 29, 1 << 30
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);

    int ans = 0;
    for (int i=0; i<LG; ++i) {
        fill(psum, psum + p2[i + 1] + 1, 0);
        for (int j=0; j<N; ++j) {
            ++psum[(A[j] & (p2[i + 1] - 1)) + 1]; // add 1 for easy indexing stuff
        }
        for (int j=1; j<=p2[i + 1]; ++j) {
            psum[j] += psum[j - 1];
        }

        // range [2^i, 2^(i+1)) and [2^(i+1) + 2^i, 2^(i+2))
        int ct = 0;
        for (int j=0; j<N; ++j) {
            const int cur = A[j] & (p2[i + 1] - 1);
            const int lo1 = p2[i] - cur;
            ct += psum[p2[i + 1] - cur] - psum[lo1 < 0 ? 0 : lo1] +
                  psum[min(p2[i + 1], p2[i + 2] - cur)] - psum[min(p2[i + 1], p2[i + 1] + lo1)] +
                  (((A[j] << 1) >> i) & 1);
        }

        ans |= (i == 0) ? ((ct >> 1) & 1) : ((ct & 2) << (i-1));
    }

    for (int i=LG; i<30; ++i) {
        for (int j=0; j<N; ++j) {
            val[j] = A[j] & (p2[i + 1] - 1);
        }
        sort(val, val+N);

        int ct = 0;
        for (int j=0; j<N; ++j) {
            const int cur = A[j] & (p2[i + 1] - 1);
            const int range1 = LB(val, val+N, (p2[i + 1]) - cur) - LB(val, val+N, p2[i] - cur);
            const int range2 = LB(val, val+N, p2[i+1] - cur - (cur == 0) + p2[i+1]) - LB(val, val+N, p2[i + 1] + p2[i] - cur);

            ct += range1 + range2 + ((A[j] >> (i-1)) & 1);
        }

        ans |= (ct & 2) << (i-1);
    }

    cout << ans << '\n';
}

/*
4  
3 9 6 6 

00110   1 1
01100   1 2
01001   1 3
01001   1 4
10010   2 2
01111   2 3
01111   2 4
01100   3 3
01100   3 4
01100   4 4
*/
