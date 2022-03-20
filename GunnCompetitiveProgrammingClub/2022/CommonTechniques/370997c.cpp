#include <bits/stdc++.h>

using namespace std;

pair<int,int> A[1001001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i].first;
            A[i].second = i;
        }
        sort(A, A+N);
        long long sum = 0;
        for (long long i=0; i<N; ++i) {
            if (A[i].second & 1) {
                sum += i;
            } else {
                sum -= i;
            }
        }
        cout << sum << '\n';
    }
}
