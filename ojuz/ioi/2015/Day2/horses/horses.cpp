#include "horses.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>

using namespace std;

typedef long long ll;

const int MN = 500005;
const ll MOD = 1e9 + 7;

ll binpow(ll x, ll e, const ll mod) {
    x %= mod;
    ll ret = 1;
    for (; e>0; e>>=1) {
        if (e&1) ret = (ret * x) % mod;
        x = (x * x) % mod;
    }
    return ret;
}

struct Node {
    int lo, hi;
    ll mx, pd;
};

int N;
ll A[MN], B[MN];
Node st[MN << 2];

void build() {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    for (int i=0; i<PN; ++i) {
        st[PN+i].lo = i;
        st[PN+i].hi = i+1;
        st[PN+i].mx = (i < N ? B[i] : 0);
        st[PN+i].pd = (i < N ? A[i] : 0);
    }
    for (int i=PN-1; i>0; --i) {
        st[i].lo = st[i << 1].lo;
        st[i].hi = st[(i << 1) + 1].hi;
        st[i].mx = max(st[i << 1].mx, st[(i << 1) + 1].mx);
        st[i].pd = (st[i << 1].pd * st[(i << 1) + 1].pd) % MOD;
    }
}

void upd_pd(const int node, const int pos, const ll val) {
    if (pos >= st[node].hi || st[node].lo >= pos + 1) return;
    if (pos <= st[node].lo && st[node].hi <= pos + 1) {
        st[node].pd = val;
        return;
    }

    upd_pd(node << 1, pos, val);
    upd_pd((node << 1) + 1, pos, val);

    st[node].pd = (st[node << 1].pd * st[(node << 1) + 1].pd) % MOD;
}

void upd_mx(const int node, const int pos, const ll val) {
    if (pos >= st[node].hi || st[node].lo >= pos + 1) return;
    if (pos <= st[node].lo && st[node].hi <= pos + 1) {
        st[node].mx = val;
        return;
    }

    upd_mx(node << 1, pos, val);
    upd_mx((node << 1) + 1, pos, val);

    st[node].mx = max(st[node << 1].mx, st[(node << 1) + 1].mx);
}

ll query_pd(const int node, const int lo, const int hi) {
    if (lo >= st[node].hi || st[node].lo >= hi) return 1;
    if (lo <= st[node].lo && st[node].hi <= hi) return st[node].pd;
    return (query_pd(node << 1, lo, hi) * query_pd((node << 1) + 1, lo, hi)) % MOD;
}

ll query_mx(const int node, const int lo, const int hi) {
    if (lo >= st[node].hi || st[node].lo >= hi) return 0;
    if (lo <= st[node].lo && st[node].hi <= hi) return st[node].mx;
    return max(query_mx(node << 1, lo, hi), query_mx((node << 1) + 1, lo, hi));
}

set<int, greater<int>> idxs;
int get_ans() {
    __int128 suff = 1;
    int idx = 0;
    for (const int i: idxs) {
        suff *= A[i];
        idx = i;
        if (suff >= MOD) break;
    }

    if (suff < MOD) idx = 0;

    ll pref = query_pd(1, 0, idx);
    __int128 best = query_mx(1, 0, N);
    for (const int i: idxs) {
        best = max(best, suff * query_mx(1, i, N));
        suff /= A[i];
        if (idx == i) break;
    }
    assert(suff == 1);
    best %= MOD;

    return (pref * best) % MOD;
}

int init(int n, int X[], int Y[]) {
    N = n;
    copy(X, X+N, A);
    copy(Y, Y+N, B);

    build();
    
    for (int i=0; i<N; ++i) {
        if (A[i] > 1) idxs.insert(i);
    }

    return get_ans();
}

int updateX(int pos, int val) {
    upd_pd(1, pos, val);
    if (A[pos] == 1 && val > 1) {
        idxs.insert(pos);
    } else if (A[pos] > 1 && val == 1) {
        idxs.erase(pos);
    }
    A[pos] = val;
    return get_ans();
}

int updateY(int pos, int val) {
    upd_mx(1, pos, val);
    B[pos] = val;
	return get_ans();
}

/*
pref/suff of X (point update pduct)
max pref[i] * Y[i] (lazy multiply max segtree)

inverse mod p^2 = pow(x, (p*(p-1)) - 1, p^2)
*/
