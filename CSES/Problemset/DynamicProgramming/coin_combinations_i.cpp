//coin_combinations_i.cpp created at 12/16/20 22:25:35

#include <bits/stdc++.h>

using namespace std;

const int MN = 105;
const int MX = 1000005;
const int MOD = 1e9 + 7;

int N, X;
int A[MN];

int kn[MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    kn[0] = 1;
    for (int i=1; i<=X; ++i) {
        for (int j=0; j<N; ++j) {
            if (A[j] <= i) {
                kn[i] += kn[i - A[j]];
                if (kn[i] >= MOD) kn[i] -= MOD;
            }
        }
    }

    cout << kn[X] << endl;
}

