#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool valid(const ll x, const ll y) {
    for (ll d=1; d <= x || d <= y; d *= 3) {
        if ((((x / d) % 3) & 1) != (((y / d) % 3) & 1)) return false;
    }
    return true;
}

void brute() {
    const int X = 3*3*3;
    const int N = 10000;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            assert(valid(i, j) == valid(i + X, j + X) || valid(i, j) == valid(i + X, j - X) || valid(i, j) == valid(i - X, j + X) || valid(i, j) == valid(i - X, j - X));
        }
    }
}

ll p3[50];

bool check(const ll x, const ll y, const ll k, const int i, const int j) {
    return (((x / p3[k]) % 3) == i) && (((y / p3[k]) % 3) == j);
}

const ll mult[9] = {9, 0, 3, 0, 1, 0, 3, 0, 1};

void solve(int asdf) {
    ll X, Y, D;
    //cin >> D >> X >> Y;
    Y = 0;
    X = asdf;
    D = 242 - X;

    if (X == Y) {
        cout << D+1 << '\n';
    } else if (D <= 1000) {
        int ans = 0;
        for (int i=0; i<=D; ++i) {
            ans += valid(X+i, Y+i);
        }
        const ll tmp = X;
        int a = 243 / 3;
        while (X > 2) {
            if ((X % 3) != 0) a /= 3;
            X /= 3;
        }
        if ((tmp & 1) == 0) cout << tmp << ' ' << ans << ' ' << a << '\n';
    } else if (X + D == p3[2] - 1 && Y == 0) {

    } else assert(false);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //const int P = 27; for (int i=0; i<P; ++i) { for (int j=0; j<P; ++j) { cerr << valid(i, j); } cerr << endl; } cerr << endl;
    
    p3[0] = 1;
    for (ll i=1; i<40; ++i) {
        p3[i] = p3[i-1] * 3;
    }

    int Q;
    cin >> Q;
    for (int q=1; q<=Q; ++q) solve(q - 1);
}
/*
9
8 0 0
7 1 0
6 2 0
5 3 0
4 4 0
3 5 0
2 6 0
1 7 0
0 8 0
*/
