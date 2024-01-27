//496919g.cpp created at 01/07/24 14:26:01
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace __gnu_pbds;
using namespace std;

using ll = long long;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int MN = 500000;

int N;
ll X[MN];
ll R[MN];

ll ans[MN];
int ans_n = 0;

//int ops;
ordered_map<ll, int> rem;
//set<int> seen;
bool check(const ll first) {
    --rem[first];
    ans_n = 1;
    ans[0] = first;
    ll a = first;
    for (int i=1; i<N; ++i) {
        //++ops;
        //debug(first, i, X[i], a);
        auto it = rem.find(X[i] - X[i - 1] - a);
        if (it != rem.end() && it->second > 0) {
            --it->second;
            a = it->first;
            ans[ans_n++] = a;
            //debug(a);
            //if (seen.count(X[i] + a)) {
            //    debug(N, i, a);
            //    debug1(X, N);
            //    debug1(R, N);
            //    assert(0);
            //}
            //seen.insert(X[i] + a);
        } else {
            return false;
        }
    }
    return true;
}

mt19937 rng(8);
void solve() {
    rem.clear();
    ans_n = 0;
    //seen.clear();

    set<ll> radii;
    for (int i=0; i<N; ++i) {
        radii.insert(R[i]);
        ++rem[R[i]];
    }

    const ll across = X[N - 1] - X[0];
    ll total = 0;
    for (int i=0; i<N; ++i) {
        total += R[i];
    }

    const ll diff = total + total - across;

    vector<ll> shuffled(radii.begin(), radii.end());
    shuffle(shuffled.begin(), shuffled.end(), rng);
    for (const ll x: shuffled) {
        if (radii.count(diff - x) && check(x)) {
            return;
        } else {
            while (ans_n > 0) {
                ++rem[ans[--ans_n]];
            }
        }
    }
}

void test() {
    int maxOps = 0;
    for (N=50; N<=50; ++N) {
        debug(N);
        for (int t=0; t<1000000; ++t) {
            for (int i=0; i<N; ++i) {
                R[i] = i + 1 + (rng() % 3);
            }
            shuffle(R, R+N, rng);
            X[0] = 0;
            for (int i=1; i<N; ++i) {
                X[i] = X[i - 1] + R[i - 1] + R[i];
            }
            shuffle(R, R+N, rng);

            //ops = 0;
            solve();
            sort(R, R+N);
            //if (maxOps < ops) {
            //    maxOps = ops;
            //    debug(ops);
            //    cout << N << endl;
            //    for (int i=0; i<N; ++i) {
            //        cout << X[i] << ' ';
            //    } cout << endl;
            //    for (int i=0; i<N; ++i) {
            //        cout << R[i] << ' ';
            //    } cout << endl;
            //}
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> X[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> R[i];
    }
    solve();
    for (int i=0; i<ans_n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
/*
15
0 20 39 56 71 89 106 126 162 197 218 238 255 276 309 
1 2 3 4 5 6 12 13 14 15 16 17 18 18 20
*/
