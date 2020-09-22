//ferris_wheel.cpp created at 09/19/20 20:06:48

#include <bits/stdc++.h>

using namespace std;

int N, X;
multiset<int, greater<int>> weights;

int main() {
    cin >> N >> X;

    for (int i=0; i<N; ++i) {
        int p;
        cin >> p;

        weights.insert(p);
    }

    int ans = 0;
    for (auto it=weights.begin(); it!=weights.end(); it=weights.erase(it)) {
        auto other = weights.lower_bound(X - *it);
        if (other == it) ++other;
        if (other != weights.end()) {
            weights.erase(other);
        }
        ++ans;
    }

    cout << ans << endl;
}

