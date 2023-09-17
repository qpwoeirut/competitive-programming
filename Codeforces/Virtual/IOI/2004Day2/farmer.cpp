//farmer.cpp created at 09/16/23 15:59:01

#include <bits/stdc++.h>

using namespace std;

const int MN = 2000;
const int MX = 150000;
const int X = 150;

int Q, M, K;
int field[MN];
int strip[MN];

bitset<MX + X + 1> kn;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> Q >> M >> K;
    for (int i=0; i<M; ++i) {
        cin >> field[i];
    }
    for (int i=0; i<K; ++i) {
        cin >> strip[i];
    }
    sort(strip, strip+K, greater<int>());

    kn[0] = true;
    for (int i=0; i<M; ++i) {
        kn |= kn << field[i];
    }

    if (kn[Q]) {
        cout << Q << '\n';
        return 0;
    }
    for (int i=1; i<=X; ++i) {
        if (kn[Q+i]) {
            cout << Q - 1 << '\n';
            return 0;
        }
    }

    int mx_field = Q;
    for (; mx_field >= 0 && !kn[mx_field]; --mx_field);

    int remaining = Q - mx_field;
    int waste = 0;
    for (int i=0; i<K && remaining > 0; ++i) {
        remaining -= strip[i];
        ++waste;
    }

    cout << Q - waste << '\n';
}

/*
17 3 3
13 4 8
4 8 6

10 1 3
5
2 3 4
*/
