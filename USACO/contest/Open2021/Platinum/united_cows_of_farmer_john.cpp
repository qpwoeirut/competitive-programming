#include <bits/stdc++.h>

using namespace std;

#define pb push_back

#define all(x) (x).begin(), (x).end()

typedef long long ll;

const int MN = 200005;

int N;
int A[MN];

int pref[MN];
vector<int> pos[MN];

struct Node {
    int lo, hi;
    ll sum, val;
    ll ct;
    ll lazy;
};
// sum is total sum, regardless of validity
// val is the value we will use

Node st[MN << 2];

void build() {
    int PN = N - 1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    for (int i=0; i<PN; ++i) {
        st[PN+i].lo = i;
        st[PN+i].hi = i + 1;
        st[PN+i].sum = i < N ? pref[i] : 0;
        st[PN+i].ct = i < N && pos[A[i]][0] == i ? 1 : 0;
        st[PN+i].val = st[PN+i].sum * st[PN+i].ct;
        st[PN+i].lazy = 0;
    }
    for (int i=PN-1; i>0; --i) {
        st[i].lo = st[i << 1].lo;
        st[i].hi = st[(i << 1) + 1].hi;
        st[i].sum = st[i << 1].sum + st[(i << 1) + 1].sum;
        st[i].ct = st[i << 1].ct + st[(i << 1) + 1].ct;
        st[i].val = st[i << 1].val + st[(i << 1) + 1].val;
        st[i].lazy = 0;
    }
}

void prop(const int node) {
    st[node << 1].val += st[node].lazy * st[node << 1].ct;
    st[node << 1].sum += st[node].lazy * (st[node << 1].hi - st[node << 1].lo);
    st[node << 1].lazy += st[node].lazy;

    st[(node << 1) + 1].val += st[node].lazy * st[(node << 1) + 1].ct;
    st[(node << 1) + 1].sum += st[node].lazy * (st[(node << 1) + 1].hi - st[(node << 1) + 1].lo);
    st[(node << 1) + 1].lazy += st[node].lazy;

    st[node].lazy = 0;
}

void upd_val(const int node, const int lo, const int hi, const int val) {
    if (lo >= st[node].hi || st[node].lo >= hi) return;
    if (lo <= st[node].lo && st[node].hi <= hi) {
        st[node].val += val * st[node].ct;
        st[node].sum += val * (st[node].hi - st[node].lo);
        st[node].lazy += val;
        return;
    }

    prop(node);

    upd_val(node << 1, lo, hi, val);
    upd_val((node << 1) + 1, lo, hi, val);

    st[node].val = st[node << 1].val + st[(node << 1) + 1].val;
    st[node].sum = st[node << 1].sum + st[(node << 1) + 1].sum;
}

void upd_ct(const int node, const int pos) {
    if (pos >= st[node].hi || st[node].lo >= pos + 1) return;
    if (pos <= st[node].lo && st[node].hi <= pos + 1) {
        st[node].ct = 1;
        st[node].val = st[node].sum;
        return;
    }

    prop(node);

    upd_ct(node << 1, pos);
    upd_ct((node << 1) + 1, pos);

    st[node].val = st[node << 1].val + st[(node << 1) + 1].val;
    st[node].ct = st[node << 1].ct + st[(node << 1) + 1].ct;
}

ll query_val(const int node, const int lo, const int hi) {
    if (lo >= st[node].hi || st[node].lo >= hi) return 0;
    if (lo <= st[node].lo && st[node].hi <= hi) return st[node].val - st[node].ct;

    prop(node);

    return query_val(node << 1, lo, hi) + query_val((node << 1) + 1, lo, hi);
}

int ct[MN];
ll brute() {
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            for (int k=j+1; k<N; ++k) {
                fill(ct, ct+N+1, 0);
                for (int a=i; a<=k; ++a) {
                    ct[A[a]]++;
                }
                if (ct[A[i]] == 1 && ct[A[j]] == 1 && ct[A[k]] == 1) ++ans;
            }
        }
    }
    return ans;
}

ll solve() {
    fill(ct, ct+N+1, 0);
    fill(pref, pref+N, 0);
    fill(pos, pos+N+1, vector<int>());

    for (int i=0; i<N; ++i) {
        pos[A[i]].pb(i);
        
        pref[i] = i ? pref[i-1] : 0;

        ++ct[A[i]];
        if (ct[A[i]] == 1) {
            ++pref[i];
        } else if (ct[A[i]] == 2) {
            --pref[i];
        }
    }

    for (int i=1; i<=N; ++i) {
        pos[i].pb(N);
        pos[i].pb(N+1);
    }

    build();

    //cerr << "pref: "; for (int i=0; i<N; ++i) { cerr << pref[i] << ' '; } cerr << endl;
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        int nxt = *upper_bound(all(pos[A[i]]), i);
        int nxt_nxt = min(*upper_bound(all(pos[A[i]]), nxt), N);

        if (nxt != N) {
            upd_ct(1, nxt);
        }
        upd_val(1, i+1, nxt, -1);
        upd_val(1, nxt, nxt_nxt,   +1);

        ans += query_val(1, i+2, nxt);

        //cerr << "i,ans,nxt: " << i << ' ' << ans << ' ' << nxt << endl;
        //cerr << "val: "; for (int j=0; j<N; ++j) { cerr << query_val(1, j, j+1) << ' '; } cerr << endl;
    }

    return ans;
}

void test() {
    for (N=1; N<=50; ++N) {
        cerr << N << endl;
        for (int t=0; t<100000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = (rand() % N) + 1;
            }

            ll ans = solve();
            ll bans = brute();

            if (ans != bans) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cout << ' ';
                    cout << A[i];
                }
                cout << endl;
                cout << ans << ' ' << bans << endl;
            }
            assert(ans == bans);
        }
    }
}

int main() {
    //test(); return 0;
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    //cerr << brute() << '\n';
    cout << solve() << '\n';
}

/*
5
5 1 1 1 3

5
5 5 3 5 2
*/

