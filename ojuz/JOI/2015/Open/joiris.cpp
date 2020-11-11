#include <bits/stdc++.h>

using namespace std;

#define type first
#define pos second

typedef pair<int,int> pii;

const int MN = 51;

int N, K;
int A[MN];

int get_min() {
    int mn = A[0];
    for (int i=1; i<N; ++i) mn = min(mn, A[i]);
    return mn;
}
int get_max() {
    int mx = A[0];
    for (int i=1; i<N; ++i) mx = max(mx, A[i]);
    return mx;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    vector<pii> ans;

    while (get_max() >= K) {
        for (int i=0; i<N; ++i) {
            if (A[i] < K) {
                A[i] += K;
                ans.emplace_back(1, i);
            }
        }
        int mn = get_min();
        for (int i=0; i<N; ++i) {
            A[i] -= mn;
        }
    }
    for (int i=0; i<N; ++i) { cerr << A[i] << ' '; } cerr << endl;

    int g = gcd(N, K);
    int sum = 0;
    for (int i=0; i<N; ++i) sum += A[i];
    int rem = (((-sum) % N) + N) % N;

    if (rem % g != 0) {
        cout << -1 << endl;
        return 0;
    }


}
