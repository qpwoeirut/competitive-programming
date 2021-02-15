//apartments.cpp created at 09/19/20 19:51:05

#include <bits/stdc++.h>

using namespace std;

const int MN = 200001;

int N, M, K;
int A[MN], B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<M; ++i) {
        cin >> B[i];
    }

    sort(A, A+N);
    sort(B, B+M);

    int ans = 0;
    for (int i=0, j=0; i<N && j<M;) {
        if (A[i] < B[j] - K) ++i;
        else if (A[i] > B[j] + K) ++j;
        else {
            ++ans;
            ++i;
            ++j;
        }
    }
    cout << ans << endl;
}
