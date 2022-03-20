#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

const int MN = 1000006;

int N;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        --A[i];
    }
    sort(A, A+N);

    for (int i=1; i<N; ++i) {
        if (A[i-1] == A[i]) {
            ++A[i];
        } else if (A[i-1] > A[i]) {
            A[i] += 2;
        }
    }
    N = unique(A, A+N) - A;
    cout << N << '\n';
}
