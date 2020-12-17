//minimizing_coins.cpp created at 12/16/20 22:21:18

#include <bits/stdc++.h>

using namespace std;

const int MN = 105;
const int MX = 1000005;

int N, X;
int A[MN];

int kn[MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    fill(kn, kn+X+1, X+1);

    kn[0] = 0;
    for (int i=1; i<=X; ++i) {
        for (int j=0; j<N; ++j) {
            if (A[j] <= i) {
                kn[i] = min(kn[i], kn[i - A[j]] + 1);
            }
        }
    }

    cout << (kn[X] == X+1 ? -1 : kn[X]) << endl;
}
