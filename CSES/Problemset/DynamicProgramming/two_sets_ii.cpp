//two_sets_ii.cpp created at 12/17/20 20:13:06

#include <bits/stdc++.h>

using namespace std;

const int MV = 501 * 502 >> 1;
const int MOD = 1e9 + 7;

int kn[MV];

int main() {
    int N;
    cin >> N;

    if (((N * (N+1)) >> 1) & 1) {
        cout << 0 << endl;
        return 0;
    }
    const int tar = (N * (N+1)) >> 2;

    kn[1] = 1;
    for (int i=2; i<=N; ++i) {
        for (int j=tar; j>=i; --j) {
            kn[j] += kn[j - i];
            if (kn[j] >= MOD) kn[j] -= MOD;
        }
    }

    cout << kn[tar] << endl;
}

