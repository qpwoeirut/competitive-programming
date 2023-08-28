//fancy_fence.cpp created at 09/07/20 08:40:21

#include <bits/stdc++.h>

using namespace std;

#define h first
#define w second
#define pos second

typedef long long ll;
typedef pair<ll,ll> pll;

const ll MOD = 1e9 + 7;
const ll MN = 100001;

ll N;
pll A[MN];

ll fancy(ll width, ll height) {
    ll sw = ((width * (width + 1)) >> 1) % MOD;
    ll sh = ((height * (height + 1)) >> 1) % MOD;
    ll rects = (sw * sh) % MOD;
    //cerr << "w,h,sw,sh,re:" << width << ' ' << height << ' ' << sw << ' ' << sh << ' ' << rects << endl;
    return rects;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;

    for (int i=0; i<N; i++) {
        cin >> A[i].h;
    }
    for (int i=0; i<N; i++) {
        cin >> A[i].w;
    }
    A[N] = pll(0, 0);
    ++N;

    ll ans = 0;
    vector<pll> prev;
    ll x = 0;
    for (int i=0; i<N; i++) {
        //cerr << i << endl;
        //for (int j=0; j<prev.size(); j++) {
        //    cerr << prev[j].h << ' ' << prev[j].pos << endl;
        //}
        ll ppos = -1;
        while (prev.size() > 0 && prev.back().h > A[i].h) {
            ll width = (x - prev.back().pos) % MOD;
            ll height = prev.back().h;
            ppos = prev.back().pos;
            prev.pop_back();
            //cerr << "popping: " << width << ' ' << height << endl;

            ans += fancy(width, height) - fancy(width, max(prev.empty() ? 0 : prev.back().h, A[i].h));
            ans = (ans + MOD) % MOD;
        }
        if (prev.empty() || prev.back().h < A[i].h) {
            prev.push_back(pll(A[i].h, x));
            if (ppos != -1) {
                prev.back().pos = ppos;
            }
        }
        x += A[i].w;
    }

    cout << ans << endl;
}
/*
5
1 2 3 2 1
1 1 1 1 1
30

2
2 1
1 1
5

4
1 4 2 3
1 1 1 1
32
*/
