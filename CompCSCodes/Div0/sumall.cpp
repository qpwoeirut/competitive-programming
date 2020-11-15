//sumall.cpp created at 11/12/20 11:41:41

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N;
ll sum;

int main() {
    freopen("sumall.in", "r", stdin);
    freopen("sumall.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N;

    sum = 0;
    for (int i=0; i<N; ++i) {
        ll x;
        cin >> x;
        sum += x;
    }

    cout << sum << endl;
}

