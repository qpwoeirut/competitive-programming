//concert_tickets.cpp created at 09/19/20 20:13:13

#include <bits/stdc++.h>

using namespace std;

int N, M;
multiset<int, greater<int>> prices;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    cin >> N >> M;

    for (int i=0; i<N; ++i) {
        int h;
        cin >> h;
        prices.insert(h);
    }

    for (int i=0; i<M; ++i) {
        int p;
        cin >> p;

        auto it=prices.lower_bound(p);
        if (it == prices.end()) {
            cout << -1 << '\n';
        } else {
            cout << *it << '\n';
            prices.erase(it);
        }
    }
}
