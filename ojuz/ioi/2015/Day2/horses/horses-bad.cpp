#include "horses.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

typedef __int128 ll;

const int MN = 500005;
const ll MOD = 1e9 + 7;
const ll MOD2 = MOD * MOD;

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
    ll val;
    ll lazy;
};

#define cval lazy

int N;
ll A[MN], B[MN];
Node pd_st[MN << 2], mx_st[MN << 2];

void build_pd() {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    for (int i=0; i<PN; ++i) {
        pd_st[PN+i].lo = i;
        pd_st[PN+i].hi = i+1;
        pd_st[PN+i].val = pd_st[PN+i].cval = (i < N ? A[i] : 0);
    }
    for (int i=PN-1; i>0; --i) {
        pd_st[i].lo = pd_st[i << 1].lo;
        pd_st[i].hi = pd_st[(i << 1) + 1].hi;
        pd_st[i].val = pd_st[i].cval = (pd_st[i << 1].val * pd_st[(i << 1) + 1].val) % MOD2;
    }
}

void upd_pd(const int node, const int pos, const ll val) {
    if (pos >= pd_st[node].hi || pd_st[node].lo >= pos + 1) return;
    if (pos <= pd_st[node].lo && pd_st[node].hi <= pos + 1) {
        pd_st[node].val = pd_st[node].cval = val;
        return;
    }

    upd_pd(node << 1, pos, val);
    upd_pd((node << 1) + 1, pos, val);

    pd_st[node].val = (pd_st[node << 1].val * pd_st[(node << 1) + 1].val) % MOD2;
    pd_st[node].cval = min(pd_st[node << 1].cval * pd_st[(node << 1) + 1].cval, MOD2);
}

ll query_pd(const int node, const int lo, const int hi) {
    if (lo >= pd_st[node].hi || pd_st[node].lo >= hi) return 1;
    if (lo <= pd_st[node].lo && pd_st[node].hi <= hi) return pd_st[node].val;

    return (query_pd(node << 1, lo, hi) * query_pd((node << 1) + 1, lo, hi)) % MOD2;
}

ll query_cap_pd(const int node, const int lo, const int hi) {
    if (lo >= pd_st[node].hi || pd_st[node].lo >= hi) return 1;
    if (lo <= pd_st[node].lo && pd_st[node].hi <= hi) return pd_st[node].cval;

    return min(query_cap_pd(node << 1, lo, hi) * query_cap_pd((node << 1) + 1, lo, hi), MOD2);
}

#undef cval

void build_mx() {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    for (int i=0; i<PN; ++i) {
        mx_st[PN+i].lo = i;
        mx_st[PN+i].hi = i+1;
        mx_st[PN+i].val = i < N ? (query_pd(1, 0, i+1) * B[i]) % MOD2 : 0;
        mx_st[PN+i].lazy = 1;
    }
    for (int i=PN-1; i>0; --i) {
        mx_st[i].lo = mx_st[i << 1].lo;
        mx_st[i].hi = mx_st[(i << 1) + 1].hi;
        mx_st[i].val = max(mx_st[i << 1].val, mx_st[(i << 1) + 1].val);
        mx_st[i].lazy = 1;
    }
}

void prop_mx(const int node) {
    mx_st[node << 1].lazy = (mx_st[node << 1].lazy * mx_st[node].lazy) % MOD2;
    mx_st[node << 1].val = (mx_st[node << 1].val * mx_st[node].lazy) % MOD2;

    mx_st[(node << 1) + 1].lazy = (mx_st[(node << 1) + 1].lazy * mx_st[node].lazy) % MOD2;
    mx_st[(node << 1) + 1].val = (mx_st[(node << 1) + 1].val * mx_st[node].lazy) % MOD2;

    mx_st[node].lazy = 1;
}

void upd_mx(const int node, const int lo, const int hi, const ll val) {
    if (lo >= mx_st[node].hi || mx_st[node].lo >= hi) return;
    if (lo <= mx_st[node].lo && mx_st[node].hi <= hi) {
        mx_st[node].lazy = (mx_st[node].lazy * val) % MOD2;
        mx_st[node].val = (mx_st[node].val * val) % MOD2;
        return;
    }

    prop_mx(node);

    upd_mx(node << 1, lo, hi, val);
    upd_mx((node << 1) + 1, lo, hi, val);

    mx_st[node].val = max(mx_st[node << 1].val, mx_st[(node << 1) + 1].val);
}

ll query_mx(const int node, const int lo, const int hi) {
    if (lo >= mx_st[node].hi || mx_st[node].lo >= hi) return 0;
    if (lo <= mx_st[node].lo && mx_st[node].hi <= hi) return mx_st[node].val;

    prop_mx(node);

    return max(query_mx(node << 1, lo, hi), query_mx((node << 1) + 1, lo, hi));
}

int get_ans() {
    int lo = 0, hi = N;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (query_cap_pd(1, mid, N) >= MOD) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    ll prefix = query_pd(1, 0, lo);
    //cerr << "pref: " << (long long)prefix << endl;
    upd_mx(1, 0, N, binpow(prefix, MOD * (MOD - 1) - 1, MOD2));
    ll ans = (prefix * query_mx(1, lo, N)) % MOD;
    upd_mx(1, 0, N, prefix);

    assert(ans < MOD);
	return ans;
}

int init(int n, int X[], int Y[]) {
    N = n;
    copy(X, X+N, A);
    copy(Y, Y+N, B);

    build_pd();
    build_mx();

    return get_ans();
}

int updateX(int pos, int val) {
    upd_pd(1, pos, val);
    upd_mx(1, pos, N, val * binpow(A[pos], MOD * (MOD - 1) - 1, MOD2)); 
    A[pos] = val;
    return get_ans();
}

int updateY(int pos, int val) {
    upd_mx(1, pos, pos+1, val * binpow(B[pos], MOD * (MOD - 1) - 1, MOD2)); 
    B[pos] = val;
    //for (int i=0; i<N; ++i) { cerr << (long long )query_mx(1, i, i+1) << ' '; } cerr << endl;
	return get_ans();
}

/*
pref/suff of X (point update pduct)
max pref[i] * Y[i] (lazy multiply max segtree)

inverse mod p^2 = pow(x, (p*(p-1)) - 1, p^2)
*/
