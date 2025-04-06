#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 100005;
ll A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    sort(A, A+N);

    ll cur = 0;
    ll extra = 0;
    ll score = 0;
    for (int i=0; i<N; ++i) {
        if (A[i] >= cur) {
            score += cur * (A[i] - cur);
            A[i] = cur;
            ++cur;
        }
        else {
            extra += A[i];
            A[i] = 0;
        }
        //cerr << i << ' ' << A[i] << ' ' << score << ' ' << cur << ' ' << extra << endl;
    }

    const ll x = cur - 1;
    score += (extra + 1) * cur + (x * (x + 1) * (2*x + 1) / 6) - 1;
    cout << score << '\n';
}
