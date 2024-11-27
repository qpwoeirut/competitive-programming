#include <bits/stdc++.h>

using namespace std;

using ll=long long;

int N;
ll D, L;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> D >> L;

    multiset<ll> vals;
    for (int i=0; i<N; ++i) {
        ll x;
        cin >> x;
        vals.insert(x);
    }

    while (vals.size() > 1) {
        ll a = *vals.begin(); vals.erase(vals.begin());
        ll b = *vals.begin(); vals.erase(vals.begin());
        vals.insert(max(a, b) + D);
    }

    cout << *vals.begin() + L << endl;
}
