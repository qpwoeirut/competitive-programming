//fibonacci.cpp created at 11/12/20 12:10:29

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;

int main() {
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);

    cin >> N;
    ll a = 0, b = 1, c = 1;
    for (int i=0; i<N; ++i) {
        a = b;
        b = c;
        c = a+b;
    }

    cout << a << endl;
}

