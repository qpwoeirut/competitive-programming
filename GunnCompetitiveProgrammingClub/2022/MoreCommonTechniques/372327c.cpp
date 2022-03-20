#include <bits/stdc++.h>

using namespace std;

const int MN = 1003;
const int MOD = 998244353;

int A[MN], B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }

    long long inv = 0;
    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            inv += A[i] > A[j];
            inv += A[i] > B[j];
            inv += B[i] > A[j];
            inv += B[i] > B[j];
        }
    }

    inv = (inv * 748683265) % MOD;
    cout << inv << '\n';
}

