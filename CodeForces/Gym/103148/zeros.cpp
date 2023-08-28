//zeros.cpp created at 08/29/21 16:27:43

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

int main() {
    ll a, b;
    cin >> a >> b;

    ll five, f=0;
    for (five=5; five<=b; five*=5) {
        if (b / five == (a-1) / five) break;
        ++f;
    }
    ll two, t=0;
    for (two=2; two<=b; two*=2) {
        if (b / two == (a-1) / two) break;
        ++t;
    }

    cout << min(f, t) << '\n';
}

