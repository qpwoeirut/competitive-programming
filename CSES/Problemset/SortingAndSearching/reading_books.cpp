//reading_books.cpp created at 12/16/20 19:38:18

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    ll sum = 0, mx = 0;
    for (int i=0; i<N; ++i) {
        ll x;
        cin >> x;
        sum += x;
        mx = max(mx, x);
    }

    cout << max(sum, mx << 1) << endl;
}

