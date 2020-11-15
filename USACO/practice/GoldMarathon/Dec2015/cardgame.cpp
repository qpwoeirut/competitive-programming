//cardgame.cpp created at 11/12/20 16:45:16

#include <bits/stdc++.h>

using namespace std;

const int MN = 50005;

int N;
set<int> low, high, bessie;

int main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N;

    for (int i=1; i<=2*N; ++i) {
        bessie.insert(i);
    }

    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;

        if (i < N/2) {
            high.insert(x);
        } else {
            low.insert(x);
        }
        bessie.erase(x);
    }

    int ans = 0;
    for (int i=0; i<N/2; ++i) {
        if (*high.rbegin() < *bessie.rbegin()) {
            ++ans;
            auto it = bessie.end(); --it;
            bessie.erase(it);
        }
        auto it = high.end(); --it;
        high.erase(it);
    }
    for (int i=0; i<N/2; ++i) {
        if (*low.begin() > *bessie.begin()) {
            ++ans;
            bessie.erase(bessie.begin());
        }
        low.erase(low.begin());
    }

    cout << ans << endl;
}

