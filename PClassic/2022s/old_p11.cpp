#include "bits/stdc++.h"

using namespace std;

#define MOD 1000000007
#define ll long long

#define A 0
#define B 1
#define P 2
#define X 3

ll binexp(ll x, ll y, ll m = MOD) {

    if (!y) return 1;
    if (y % 2) return (x * binexp(x, y - 1, m)) % m;
    return binexp((x * x) % m, y / 2);

}

vector<long long> vacation(int n, int q, vector<vector<ll>> trees, vector<vector<ll>> queries) {

    // {pv, l}
    // -> {a * (pv ^ b) * (l ^ x), p * l}

    vector<ll> a(n), b(n), p(n), x(n);

    for (int i = 0; i < n; i++) {

        ll ct = 1;
        ll ov = 1;
        for (ll j = 1; j < trees[i].size(); j++) {
            ct *= trees[i][j];
            ov *= trees[i][j];
            ct %= MOD;
            ov %= (MOD - 1);
        }

        b[i] = ov;
        p[i] = ct;
        x[i] = 0;

        ll cn = 1;
        ll cr = 1;

        for (ll v = 1; v < trees[i].size(); v++) {
            ll j = trees[i][v];

            // cout << "currently " << ct << " leaves and " << cn << " nodes " << endl;

            /*

                there are cn nodes at this level

                each leads to ct * l leaves

                multiply by (ct * l) ^ cn = (ct ^ cn) * (l ^ cn)

            */

            cr *= binexp(ct, cn, MOD);
            cr %= MOD;

            x[i] += cn;
            x[i] %= (MOD - 1);

            cn *= j;
            cn %= (MOD - 1);

            ct *= binexp(j, MOD - 2, MOD);
            ct %= MOD;

        }

        a[i] = cr;

    }

    auto merge = [](array<ll, 4> q, array<ll, 4> p) {

        // a, b, p, x
        // q to left
        // p to right

        if (p[0] == -1)
            return q;

        array<ll, 4> res =
                {(((q[A] * binexp(p[A], q[B], MOD)) % MOD) * binexp(p[P], q[X], MOD)) % MOD,
                 (q[B] * p[B]) % (MOD - 1),
                 (q[P] * p[P]) % (MOD),
                 (p[X] * q[B] + q[X]) % (MOD - 1)};

        return res;

    };

    const int LOG = 17;

    vector<vector<array<ll, 4>>> jump(LOG, vector<array<ll, 4>>(n));
    for (int i = 0; i < n; i++)
        jump[0][i] = {a[i], b[i], p[i], x[i]};

    for (int i = 1; i < LOG; i++) {

        for (int j = 0; j < n; j++) {

            int pv = j - (1 << (i - 1));
            if (pv >= 0)
                jump[i][j] = merge(jump[i - 1][pv], jump[i - 1][j]);
            else
                jump[i][j] = jump[i - 1][j];

        }

    }

    vector<ll> ans;
    for (auto cq: queries) {
        ll l = cq[0], r = cq[1];
        l--;
        r--;

        ll cv = 1, leaf = 1;
        array<ll, 4> ca = {-1, -1, -1, -1};

        int ci = r;

        int td = r - l + 1;
        for (int i = 0; i < LOG; i++) {

            if (td & (1 << i)) {

                ca = merge(jump[i][ci], ca);
                ci -= (1 << (i));

            }

        }

        ll res = ca[0];

        ans.push_back(res % MOD);

    }

    return ans;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<long long>> trees(n);
    vector<vector<long long>> queries(q, vector<long long>(2));

    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        trees[i] = vector<long long>(s);
        for (int j = 0; j < s; j++) {
            cin >> trees[i][j];
        }
    }

    for (int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }

    vector<long long> ret = vacation(n, q, trees, queries);

    for (ll b: ret) {
        cout << b << "\n";
    }
}