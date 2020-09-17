#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

struct func {
    ll m, b;
    func() : m(0), b(0) {}
    func(ll m, ll b) : m(m), b(b) {}
    func operator+(const func &f2) const {
        ll m2 = m * f2.m % MOD;
        ll b2 = (b * f2.m % MOD + f2.b) % MOD;
        return func(m2, b2);
    }
    ll eval(ll x) {
        return ((m * x % MOD) + b % MOD);
    }
};

int n, m;
func val[MAXN];
func st[MAXN];

void build(int v, int l, int r) {
    if (l == r) {
        st[v] = val[l];
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v, m + 1, r);
        st[v] = st[2 * v] + st[2 * v + 1];
    }
}

void upd(int v, int l, int r, int x, func &f) {
    if (l == r) {
        st[v] = f;
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            upd(2 * v, l, m, x, f);
        } else {
            upd(2 * v + 1, m + 1, r, x, f);
        }
        st[v] = st[2 * v] + st[2 * v + 1];
    }
}

func qry(int v, int l, int r, int x, int y) {
    cout << v << ' ' << l << ' ' << r << '\n';
    if (x <= l && r <= y) {
        return st[v];
    } else if (x > r || y < l) {
        return func(1, 0);
    } else {
        int m = (l + r) / 2;
        return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m + 1, r, x, y);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char op; int x; cin >> op >> x;
        switch (op) {
            case '+':
                val[i] = func(1, x);
                break;
            case '-':
                val[i] = func(1, -x);
                break;
            default:
                val[i] = func(x, 0);
        }
    }

    build(1, 1, n);

    for (int i = 1; i <= 3; i++) {
        cout << val[i].m << ' ' << val[i].b << '\n';
    }

    for (int i = 0; i < m; i++) {
        char t; cin >> t;
        if (t == 'q') {
            int x, y; cin >> x >> y;
            func f = qry(1, 1, n, 1, y);
            cout << f.m << ' ' << f.b << '\n';
            /* cout << qry(1, 1, n, 1, y).eval(x) << '\n'; */
        } else {
            int m, n; char op;
            cin >> m >> n >> op;
            switch (op) {
                case '+':
                    val[m] = func(1, n);
                    break;
                case '-':
                    val[m] = func(1, -n);
                    break;
                default:
                    val[m] = func(n, 0);
            }
            upd(1, 1, n, m, val[m]);
        }
    }

    return 0;
}
