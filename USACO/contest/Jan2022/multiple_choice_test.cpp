#include <bits/stdc++.h>

using namespace std;

using dbl=float;
using ll=long long;
using pt=complex<ll>;
using pptd=pair<pt,dbl>;

#define x real()
#define y imag()
#define pb push_back
#define eb emplace_back

#define fi first
#define se second

const int MN = 100005;
const dbl EPS = 1e-6;

int N;
vector<pptd> A[MN];

ll solve() {
    //vector<dbl> tied;
    /*
    for (int i=0; i<N; ++i) {
        sort(A[i].begin(), A[i].end(), [](const pptd& a, const pptd& b){return a.se < b.se;});

        for (int j=0; j<A[i].size(); ++j) {
            tied.pb(A[i][j].se - EPS);
            tied.pb(A[i][j].se + EPS);
        }
        if (A[i].size() > 2) tied.pb((A[i][0].se + A[i].back().se) / 2.0);
        for (int j=1; j<A[i].size(); ++j) {
            tied.pb((A[i][j-1].se + A[i][j].se) / 2.0);
        }
    }
    */
    //for (dbl a=-3.1415; a<=3.1415; a+=0.001) tied.pb(a);

    ll ans = 0;
    //for (const dbl tar_angle: tied) {
    for (dbl tar_angle=-3.1415; tar_angle<=3.1415; tar_angle += 0.0005) {
        pt pos(0, 0);
        for (int i=0; i<N; ++i) {
            pt best(0, 0);
            dbl best_val = -1e9;
            for (const pptd& cur: A[i]) {
                const dbl cur_val = norm(cur.fi) * cos(cur.se - tar_angle);
                //cerr << tar_angle << ' ' << cur.fi.x << ',' << cur.fi.y << ' ' << cur.se << ' ' << cur_val << endl;
                if (best_val < cur_val) {
                    best_val = cur_val;
                    best = cur.fi;
                }
            }
            pos += best;
        }
        //cerr << tar_angle << ' ' << pos.x << ',' << pos.y << endl;

        ans = max(ans, norm(pos));
    }

    return ans;
}

ll recurse(const int i, const pt& cur) {
    if (i == N) {
        return norm(cur);
    }
    ll ans = 0;
    for (const pptd& p: A[i]) {
        ans = max(ans, recurse(i+1, cur+p.fi));
    }
    return ans;
}

mt19937 rng(8);

void test() {
    for (N=2; N<=8; ++N) {
        cerr << "N=" << N << endl;
        for (int t=0; t<10000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i].clear();
                const int G = (rng() % 2) + 1;
                for (int j=0; j<G; ++j) {
                    const int xx = (rng() % 21) - 10;
                    const int yy = (rng() % 21) - 10;
                    A[i].eb(pt(xx, yy), arg(complex<dbl>(xx, yy)));
                }
            }
            ll sans = solve();
            ll bans = recurse(0, pt(0,0));
            if (sans != bans) {
                cout << sans << ' ' << bans << endl;
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i].size() << endl;
                    for (const pptd& p: A[i]) {
                        cout << p.fi.x << ' ' << p.fi.y << endl;
                    }
                }
            }
            assert(sans == bans);
        }
    }
}

int main() {
    //test(); return 0;
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;

    for (int i=0; i<N; ++i) {
        int G;
        cin >> G;
        for (int j=0; j<G; ++j) {
            int px, py;
            cin >> px >> py;
            A[i].eb(pt(px, py), arg(complex<dbl>(px, py)));
        }
    }
    const ll ans = solve();
    cout << ans << '\n';
}

/*
2
2
8 -5
9 5
3
4 -10
10 -4
-1 0

2
3
10 -9
10 -8
10 1
4
-9 -1
-5 -3
-9 8
-6 5

2
2
6 -4
10 -6
2
-5 -6
2 5
*/
