//sliding_median.cpp created at 12/16/20 20:55:06

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N, K;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    multiset<int> lo, hi;
    for (int i=0; i<K; ++i) {
        hi.insert(A[i]);
    }
    while (lo.size() < hi.size()) {
        lo.insert(*hi.begin());
        hi.erase(hi.begin());
    }
    cout << *lo.rbegin();
    for (int i=K; i<N; ++i) {
        if (A[i] <= *lo.rbegin()) {
            lo.insert(A[i]);
        } else {
            hi.insert(A[i]);
        }
        if (A[i - K] <= *lo.rbegin()) {
            lo.erase(lo.find(A[i - K]));
        } else {
            hi.erase(hi.find(A[i - K]));
        }
        if (lo.size() > hi.size() + 1) {
            hi.insert(*lo.rbegin());
            auto it = lo.end();
            --it;
            lo.erase(it);
        } else if (lo.size() < hi.size()) {
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }

        cout << ' ' << *lo.rbegin();
    }
    cout << endl;
}

