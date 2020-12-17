//factory_machines.cpp created at 12/16/20 19:17:33

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;

int N, T;
int A[MN];

bool check(const ll days) {
    ll total = 0;
    for (int i=0; i<N; ++i) {
        total += days / A[i];
        if (total >= T) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ll lo = 0, hi = 1e18 + 1;
    while (lo < hi) {
        ll mid = (lo + hi) >> 1;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << endl;
}
