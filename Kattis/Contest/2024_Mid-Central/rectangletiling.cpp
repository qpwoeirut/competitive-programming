#include <bits/stdc++.h>

using namespace std;

using i128=__int128;
using ll=long long;

const int MN = 53;
const ll INF = 1e18;

ll W, H, N;
ll A[MN];

ll fill_side(ll n, int p) {
    i128 total = n * ((i128)(1) << p);
    cerr << "n p: " << n << ' ' << p << endl;
    ll cost = 0;
    for (int i=p; i>=0; --i) {
        i128 req = total >> (2 * i);

        if (req >= INF) return INF;
        const ll used = min((ll)req, A[i]);
        //cerr << "i n u: " << i << ' ' << n << ' ' << used << endl;
        A[i] -= used;
        cost += used;
        total -= (i128)(used) << (2 * i);
    }
    if (total > 0) return INF;
    return cost;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> W >> H >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ll ans = 0;
    for (int p=0; p<MN; ++p) {
        if (W & (1LL << p)) {
            W -= 1LL << p;
            ans += fill_side(H, p);
        }
        if (H & (1LL << p)) {
            H -= 1LL << p;
            ans += fill_side(W, p);
        }
        if (ans >= INF) {
            cout << "-1\n";
            return 0;
        }
        //cerr << "p: " << p << endl;
        //cerr << "A:";
        //for (int i=0; i<N; ++i) cerr << ' ' << A[i];
        //cerr << endl << W << ' ' << H << endl << endl;
    }
    cout << ans << endl;
}
/*
1099511627776 1099511627776 30
1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776 1099511627776
*/
