//traffic_lights.cpp created at 12/16/20 18:54:33

#include <bits/stdc++.h>

using namespace std;

int X, N;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> X >> N;

    set<int> lights;
    lights.insert(0);
    lights.insert(X);

    multiset<int> dists;
    dists.insert(X);

    for (int i=0; i<N; ++i) {
        int p;
        cin >> p;

        auto lo = lights.insert(p).first;
        auto hi = lo;
        --lo; ++hi;

        dists.erase(dists.find(*hi - *lo));
        dists.insert(p - *lo);
        dists.insert(*hi - p);

        if (i) cout << ' ';
        cout << *dists.rbegin();
    }
    cout << endl;
}

