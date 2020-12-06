#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef pair<ll,ll> pll;

const int MN = 100005;

int N, n;
bool A[MN << 1];
deque<int> lpos[2], rpos[2];

void calc_pos() {
    lpos[0].clear();
    lpos[1].clear();
    rpos[0].clear();
    rpos[1].clear();

    for (int i=0; i<n; ++i) {
        if (i < N) {
            lpos[A[i]].push_back(i);
        } else {
            rpos[A[i]].push_back(i);
        }
    }
}

ll ct_before(const deque<int>& d, int val) {
    return lower_bound(all(d), val) - d.begin();
}
ll ct_after(const deque<int>& d, int val) {
    return d.size() - ct_before(d, val);
}

pll calc_invs() {
    pll invs(0, 0);
    for (int i=0; i<lpos[0].size(); ++i) {
        invs.fi += ct_before(lpos[1], lpos[0][i]);
    }
    for (int i=0; i<rpos[0].size(); ++i) {
        invs.se += ct_before(rpos[1], rpos[0][i]);
    }
    return invs;
}

int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    n = N << 1;
    for (int i=0; i<n; ++i) {
        cin >> A[i];
    }

    calc_pos();
    //cerr << lpos[0].size() << ' ' << lpos[1].size() << "   " << rpos[0].size() << ' ' << rpos[1].size() << endl;
    pll cur = calc_invs();
    ll ans = abs(cur.fi - cur.se);
    //cerr << cur.fi << ' ' << cur.se << endl;

    ll ct = 0;
    while (lpos[0].size() > 0 && rpos[1].size() > 0) {
        ct += rpos[1].front() - lpos[0].back(); 
        cur.fi -= ct_before(lpos[1], lpos[0].back());
        cur.se -= ct_after(rpos[0], rpos[1].front());
        lpos[0].pop_back();
        rpos[1].pop_front();

        ans = min(ans, abs(cur.fi - cur.se) + ct);
    }
        
    calc_pos();
    cur = calc_invs();

    ct = 0;
    while (lpos[1].size() > 0 && rpos[0].size() > 0) {
        ct += rpos[0].front() - lpos[1].back(); 
        cur.fi -= N - lpos[1].back() - 1;
        cur.se -= rpos[0].front() - N;
        lpos[1].pop_back();
        rpos[0].pop_front();
        cur.fi += lpos[1].size();
        cur.se += rpos[0].size();

        ans = min(ans, abs(cur.fi - cur.se) + ct);
    }

    cout << ans << endl;
}
