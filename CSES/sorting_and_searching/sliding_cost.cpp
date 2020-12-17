//sliding_cost.cpp created at 12/16/20 21:33:24

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;

int N, K;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ll lo_sum = 0, hi_sum = 0;
    multiset<int> lo, hi;
    for (int i=0; i<K; ++i) {
        hi.insert(A[i]);
        hi_sum += A[i];
    }
    while (lo.size() < hi.size()) {
        lo.insert(*hi.begin());
        lo_sum += *hi.begin();
        hi_sum -= *hi.begin();
        hi.erase(hi.begin());
    }
    ll med = *lo.rbegin();
    cout << hi_sum - (med * hi.size()) + (med * lo.size()) - lo_sum;
    for (int i=K; i<N; ++i) {
        if (A[i] <= *lo.rbegin()) {
            lo.insert(A[i]);
            lo_sum += A[i];
        } else {
            hi.insert(A[i]);
            hi_sum += A[i];
        }
        if (A[i - K] <= *lo.rbegin()) {
            lo.erase(lo.find(A[i - K]));
            lo_sum -= A[i - K];
        } else {
            hi.erase(hi.find(A[i - K]));
            hi_sum -= A[i - K];
        }
        if (lo.size() > hi.size() + 1) {
            lo_sum -= *lo.rbegin();
            hi_sum += *lo.rbegin();
            hi.insert(*lo.rbegin());
            auto it = lo.end();
            --it;
            lo.erase(it);
        } else if (lo.size() < hi.size()) {
            lo_sum += *hi.begin();
            hi_sum -= *hi.begin();
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }

        med = *lo.rbegin();
        cout << ' ' << hi_sum - (med * hi.size()) + (med * lo.size()) - lo_sum;
    }
    cout << endl;
}


