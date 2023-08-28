//1485c.cpp created at 02/27/21 11:52:39

#include <bits/stdc++.h>

using namespace std;

void brute() {
    const int a = 200, b = 100;
    map<int,int> ct;
    for (int j=1; j<=b; ++j) {
        int x = 0;
        for (int i=1; i<=a; ++i) {
            if (i / j == i % j) {
                ++x;
            }
        }
        cout << j << ' ' << x << ' ' << min(j-1, a/(j+1)) << endl;
    }
}

void solve() {
    int a, b;
    cin >> a >> b;

    b = min(a-1, b);
    long long ans = 0;
    int i=1;
    for (; i<=b && i-1 <= a/(i+1); ++i) {
        ans += i-1;
    }
    while (i <= b) {
        int hi = min(b+1, a / (a/(i+1)));
        assert(i < hi);
        //cerr << i << ' ' << a/(i+1) << ' ' << hi << endl;
        ans += a/(i+1) * (hi - i);
        i = hi;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //brute();

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) solve();
}

/*
x, x-1

10 4
*/
