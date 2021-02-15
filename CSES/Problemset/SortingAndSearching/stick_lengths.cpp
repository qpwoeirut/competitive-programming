//stick_lengths.cpp created at 10/16/20 22:00:12

#include <bits/stdc++.h>

using namespace std;

int N;
int A[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    nth_element(A, A+N/2, A+N);

    int median = A[N/2];

    long long ans = 0;
    for (int i=0; i<N; ++i) {
        ans += abs(median - A[i]);
    }

    cout << ans << endl;
}

