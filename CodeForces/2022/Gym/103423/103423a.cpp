#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using pll=pair<ll,ll>;

#define fi first
#define se second

const int MN = 1 << 20;
const ll INF = 1e18;

ll N;
ll A[MN];

ll ending[MN];

ll BIT[MN];
void upd(int idx, int val) {
    for (++idx; idx<MN; idx+=(idx&-idx)) BIT[idx] += val;
}
ll query(int idx) {
    ll ret = 0;
    for (++idx; idx>0; idx-=(idx&-idx)) ret += BIT[idx];
    return ret;
}


ll vals[MN];

ll min_BIT[MN];
void min_upd(int idx, ll val) {
    for (++idx; idx<MN; idx+=(idx&-idx)) min_BIT[idx] = min(min_BIT[idx], val);
}
ll min_query(int idx) {
    ll ret = INF;
    for (++idx; idx>0; idx-=(idx&-idx)) ret = min(ret, min_BIT[idx]);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    copy(A, A+N, vals);
    sort(vals, vals+N);
    for (int i=0; i<N; ++i) {
        A[i] = upper_bound(vals, vals+N, A[i]) - vals;
    }

    fill(min_BIT, min_BIT+MN, INF);
    for (int i=N-1; i>=0; --i) {
        //cerr << "i, A: " << i << ' ' << A[i] << endl;
        //for (int j=0; j<10; ++j) { cerr << j << ' ' << query_st(1, 0, j+1) << ' ' << query_st(1, j, j+1) << endl; }

        ending[i] = min_query(A[i] - 1);
        if (ending[i] == INF) ending[i] = N;
        min_upd(A[i], i);
    }
    //for (int i=0; i<N; ++i) { cerr << A[i] << ' '; } cerr << endl;
    //for (int i=0; i<N; ++i) { cerr << ending[i] << ' '; } cerr << endl;

    ll ans = 0;
    set<pll> valid;
    for (int i=N-1; i>=0; --i) {
        upd(i, 1);
        valid.emplace(A[i], i);
        while (valid.begin()->fi < A[i]) {
            upd(valid.begin()->se, -1);
            valid.erase(valid.begin());
        }
        ans += query(ending[i]);
    }

    cout << ans << '\n';
}

