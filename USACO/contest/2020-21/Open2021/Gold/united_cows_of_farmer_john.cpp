#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;

int N;
int A[MN];
int dupes[MN];

struct Node {
    int lo, hi;
    int sum;
    int lazy;
};

Node st[MN << 2];

void build() {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;

    for (int i=0; i<PN; ++i) {
        st[PN+i].lo = i;
        st[PN+i].hi = i+1;
        st[PN+i].sum = i < N ? dupes[i] : 0;
        st[PN+i].lazy = 0;
    }
    for (int i=PN-1; i>0; --i) {
        st[i].lo = st[i << 1].lo;
        st[i].hi = st[(i << 1) + 1].hi;
        st[i].sum = st[i << 1].sum + st[(i << 1) + 1].sum;
        st[i].lazy = 0;
    }
}

void prop(const int node) {
    st[node << 1].sum += st[node].lazy * (st[node << 1].hi - st[node << 1].lo);
    st[node << 1].lazy += st[node].lazy;

    st[(node << 1) + 1].sum += st[node].lazy * (st[(node << 1) + 1].hi - st[(node << 1) + 1].lo);
    st[(node << 1) + 1].lazy += st[node].lazy;

    st[node].lazy = 0;
}

void update(const int node, const int lo, const int hi) {
    if (lo >= st[node].hi || st[node].lo >= hi) return;
    if (lo <= st[node].lo && st[node].hi <= hi) {
        st[node].sum -= st[node].hi - st[node].lo;
        --st[node].lazy;
        return;
    }

    if (st[node].lazy != 0) prop(node);

    update(node << 1, lo, hi);
    update((node << 1) + 1, lo, hi);

    st[node].sum = st[node << 1].sum + st[(node << 1) + 1].sum;
}

int query(const int node, const int pos) {
    if (pos >= st[node].hi || st[node].lo >= pos + 1) return 0;
    if (pos <= st[node].lo && st[node].hi <= pos + 1) return st[node].sum;

    if (st[node].lazy != 0) prop(node);
    return query(node << 1, pos) + query((node << 1) + 1, pos);
}

int ct[MN];
vector<int> pos[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<N; ++i) {
        dupes[i] = i ? dupes[i-1] : 0;
        if (++ct[A[i]] >= 2) ++dupes[i];
        pos[A[i]].push_back(i);
    }

    for (int i=1; i<=N; ++i) {
        pos[i].push_back(N);
    }

    build();

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        int nxt = *upper_bound(pos[A[i]].begin(), pos[A[i]].end(), i);
        ans += nxt - i - 1 - query(1, nxt-1);
        update(1, nxt, N);
    }

    cout << ans << '\n';
}
