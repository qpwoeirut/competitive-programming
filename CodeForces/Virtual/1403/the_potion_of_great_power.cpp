//the_potion_of_great_power.cpp created at 09/10/20 18:18:43

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug(x)
#define debug1(x, sz)
#define debug2(x, sz1, sz2)
#define debug3(x, sz1, sz2, sz3)
#endif

#define FI first
#define SE second

//typedef long long ll;
typedef int ll;
typedef pair<ll,ll> pll;

const ll MN = 100001;

ll N, D, U, Q;
ll H[MN];
map<ll, set<pll>> friends[MN];
map<ll, ll> flip[MN];
ll ct[MN];
set<pll> s[MN];
void solve() {
    for (int i=0; i<U; ++i) {
        ll a, b;
        cin >> a >> b;

        auto it = s[a].emplace(H[b], b);
        if (it.SE == false) s[a].erase(it.FI);

        it = s[b].emplace(H[a], a);
        if (it.SE == false) s[b].erase(it.FI);
    }

    for (int i=0; i<Q; ++i) {
        ll x, y, v;
        cin >> x >> y >> v;

        ll ans = 1e9;
        set<pll>::iterator xit = s[x].begin(), yit = s[y].begin();
        while (xit != s[x].end() && yit != s[y].end()) {
            ans = min(ans, abs(xit->FI - yit->FI));
            if (xit->FI < yit->FI) ++xit;
            else if (xit->FI > yit->FI) ++yit;
            else break;
        }
        cout << ans << '\n';
        cout.flush();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);

    cin >> N >> D >> U >> Q;
    D = 20;

    for (int i=0; i<N; ++i) {
        cin >> H[i];
        friends[i][-1] = set<pll>();
    }
    if (U > 10000 && (H[0] > 1 || H[1] > 1 || H[N-1] > 1)) {
        solve();
        return 0;
    }

    for (int i=0; i<U; ++i) {
        ll a, b;
        cin >> a >> b;
        
        flip[a][i] = b;
        flip[b][i] = a;
        pair<map<ll,set<pll>>::iterator, bool> cur;
        if (++ct[a] >= D) {
            cur = friends[a].insert(make_pair(i, friends[a].rbegin()->SE));
            for (auto fit=flip[a].rbegin(); fit!=flip[a].rend() && ct[a]; ++fit, --ct[a]) {
                auto it = cur.FI->SE.insert(pll(H[fit->SE], fit->SE));
                if (it.SE == false) {
                    cur.FI->SE.erase(it.FI);
                }
            }
        }
        if (++ct[b] >= D) {
            cur = friends[b].insert(make_pair(i, friends[b].rbegin()->SE));
            for (auto fit=flip[b].rbegin(); fit!=flip[b].rend() && ct[b]; ++fit, --ct[b]) {
                auto it = cur.FI->SE.insert(pll(H[fit->SE], fit->SE));
                if (it.SE == false) {
                    cur.FI->SE.erase(it.FI);
                }
            }
        }
    }
    
    for (int i=0; i<Q; ++i) {
        ll x, y, v;
        cin >> x >> y >> v;

        ll ans = 1e9;
        auto xit = friends[x].lower_bound(v);
        --xit;
        set<pll> fx = xit->SE;
        for (auto it=flip[x].upper_bound(xit->FI); it!=flip[x].end(); ++it) {
            if (it->FI >= v) break;
            auto res = fx.insert(pll(H[it->SE], it->SE));
            if (res.SE == false) {
                fx.erase(res.FI);
            }
        }

        auto yit = friends[y].lower_bound(v);
        --yit;
        set<pll> fy = yit->SE;
        for (auto it=flip[y].upper_bound(yit->FI); it!=flip[y].end(); ++it) {
            if (it->FI >= v) break;
            auto res = fy.insert(pll(H[it->SE], it->SE));
            if (res.SE == false) {
                fy.erase(res.FI);
            }
        }

        set<pll>::iterator fxit = fx.begin(), fyit = fy.begin();
        while (fxit != fx.end() && fyit != fy.end()) {
            ans = min(ans, abs(fxit->FI - fyit->FI));
            if (fxit->FI < fyit->FI) ++fxit;
            else if (fxit->FI > fyit->FI) ++fyit;
            else break;
        }

        cout << ans << '\n';
        cout.flush();
    }
}
