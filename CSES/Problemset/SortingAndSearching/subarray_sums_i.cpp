//subarray_sums_i.cpp created at 12/16/20 20:36:02

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N, X;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int ans = 0;
    int sum = 0;
    int slow = 0;
    for (int i=0; i<N; ++i) {
        sum += A[i];
        while (sum > X) {
            sum -= A[slow++];
        }
        if (sum == X) {
            ++ans;
        }
    }

    cout << ans << endl;
}
