//building_bridges.cpp created at 01/21/21 19:56:54

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;
const int MX = 1000006;
const ll INF = 2e17;

int N;
ll H[MN], W[MN];
ll dp[MN];
ll hc[MX];

ll p1[MN], p2[MN];
ll solve2() {
    fill(p1, p1+N, 0);
    fill(p2, p2+N, 0);
    ll wsum = 0;
    for (int i=0; i<N; ++i) {
        wsum += W[i];
    }
    ll ans = INF;

    for (int i=0; i<N; ++i) {
        p1[i] = W[i] + W[0] + (H[i] - H[0]) * (H[i] - H[0]);
        p2[i] = W[i] + W[N-1] + (H[N-1] - H[i]) * (H[N-1] - H[i]);
        //cerr << i << ' ' << p1[i] << ' ' << p2[i] << endl;
    }
    p1[0] = W[0];
    p2[N-1] = W[N-1];
    map<ll,ll> cur;
    for (int i=0; i<N; ++i) {
        ans = min(ans, p1[i] + p2[i] - W[i] - wsum);
        //cerr << i << ' ' << p1[i] + p2[i] - W[i] - wsum << endl;

        auto it = cur.lower_bound((H[0] + H[i] + 1) >> 1);
        if (it != cur.end()) {
            ans = min(ans, it->second + p2[i] - wsum + (it->first - H[i]) * (it->first - H[i]));
        }
        if (it != cur.begin()) {
            --it;
            ans = min(ans, it->second + p2[i] - wsum + (it->first - H[i]) * (it->first - H[i]));
        }
        if (cur.count(H[i])) {
            cur[H[i]] = min(cur[H[i]], p1[i]);
        } else {
            cur[H[i]] = p1[i];
        }
    }

    return ans;
}

ll solve1() {
    fill(hc, hc+MX, INF);
    fill(dp, dp+N, 0);

    dp[0] = W[0];
    hc[H[0]] = dp[0];
    ll mn = dp[0];
    for (int i=1; i<N; ++i) {
        ll best = min(hc[H[i]], hc[H[0]] + (H[i] - H[0]) * (H[i] - H[0]));
        //cerr << "best=" << best << endl;
        //cerr << "i,H: " << i << ' ' << H[i] << endl;
        for (ll j=1; j<MX && j*j < best - mn; ++j) {
            //cerr << i << ' ' << j << endl;
            if (H[i] >= j) {
                best = min(best, hc[H[i] - j] + (j * j));
            }
            if (H[i] + j < MX) {
                best = min(best, hc[H[i] + j] + (j * j));
            }
        }

        dp[i] = best + W[i];
        //cerr << "W=" << W[i] << endl;
        //cerr << "best=" << best << endl;
        //cerr << "dp=" << dp[i] << endl;
        hc[H[i]] = min(hc[H[i]], dp[i]);
        mn = min(mn, dp[i]);
    }

    ll wsum = 0;
    for (int i=0; i<N; ++i) {
        wsum += W[i];
        //cerr << i << ' ' << dp[i] << ' ' << dp[i] - wsum << endl;
    }
    //cerr << wsum << endl;

    return dp[N-1] - wsum;
}

void test() {
    for (N=2; N<=4; ++N) {
        cerr << N << endl;
        for (int t=0; t<10000000; ++t) {
            for (int i=0; i<N; ++i) {
                H[i] = rand() % 1000001;
                W[i] = (rand() % 41) - 20;
            }
            ll a1 = solve1(), a2 = solve2();
            if (a1 != a2) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << H[i] << ' ';
                } cout << endl;
                for (int i=0; i<N; ++i) {
                    cout << W[i] << ' ';
                } cout << endl;
                cout << endl << a1 << ' ' << a2 << endl;
                assert(0);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    test(); return 0;

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> H[i];
    }
    bool sub2 = N > 1000;
    for (int i=0; i<N; ++i) {
        cin >> W[i];
        W[i] = -W[i];
        if (abs(W[i]) > 20) sub2 = false;
    }

    if (sub2) {
        cout << solve2() << endl;
    } else {
        cout << solve1() << endl;
    }
}

/*
6
3 8 7 1 6 6
0 -1 9 1 2 0

2
16807 648451
-11 -18

5
749432 636218 549261 546549 27011 
-20 16 1 -13 10
*/
