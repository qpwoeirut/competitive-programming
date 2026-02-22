#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MN = 1000006;
const int MOD = 1e9 + 7;

struct Node {
    int lo, hi;
    ll val;
    ll mult;

    Node() {
        lo = hi = val = 0;
        mult = 1;
    }

    Node(int _lo, int _hi, ll _val, ll _mult) : lo(_lo), hi(_hi), val(_val), mult(_mult) {}
};
const int PN = 1 << 20;
Node st[2 * PN];

void build() {
    for (int i=0; i<PN; ++i) {
        st[PN + i] = Node(i, i+1, 0, 1);
    }
    for (int i=PN-1; i>0; --i) {
        st[i] = Node(st[2*i].lo, st[2*i+1].hi, 0, 1);
    }
}

void upd(int node, int idx, ll val) {
    if (idx < st[node].lo || st[node].hi <= idx) return;
    assert(st[node].mult == 1);

    if (st[node].lo == idx && idx + 1 == st[node].hi) {
        st[node].val = val;
    } else {
        upd(2 * node, idx, val);
        upd(2 * node + 1, idx, val);
        st[node].val = (st[2 * node].val + st[2 * node + 1].val) % MOD;
    }
}
void multiply(int node, int lo, int hi, ll val) {
    if (hi <= st[node].lo || st[node].hi <= lo) return;
    if (lo <= st[node].lo && st[node].hi <= hi) {
        st[node].mult = (st[node].mult * val) % MOD;
    } else {
        multiply(2 * node, lo, hi, val);
        multiply(2 * node + 1, lo, hi, val);
    }
}
ll query(int node, int lo, int hi) {
    if (hi <= st[node].lo || st[node].hi <= lo) return 0;
    if (lo <= st[node].lo && st[node].hi <= hi) {
        return (st[node].val * st[node].mult) % MOD;
    } else {
        st[2 * node].mult = (st[2 * node].mult * st[node].mult) % MOD;
        st[2 * node + 1].mult = (st[2 * node + 1].mult * st[node].mult) % MOD;
        return (query(2 * node, lo, hi) + query(2 * node + 1, lo, hi)) % MOD;
    }
}

int p2[MN];

int N, D;
int P[MN], T[MN];

ll dp[MN];
ll pref[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    build();
    
    p2[0] = 1;
    for (int i=1; i<MN; ++i) {
        p2[i] = (p2[i-1] * 2) % MOD;
    }

    vector<int> coach, camper;
    cin >> N >> D;
    for (int i=0; i<N; ++i) {
        cin >> P[i] >> T[i];
        if (T[i]) coach.push_back(P[i]);
        else camper.push_back(P[i]);
    }

    auto campers = [&camper](const int a, const int b) {
        return upper_bound(camper.begin(), camper.end(), b) - lower_bound(camper.begin(), camper.end(), a);
    };

    dp[0] = 1;
    upd(1, 0, 1);
    pref[0] = dp[0];

    for (int i=0; i<coach.size(); ++i) {
        dp[i+1] = 0;

        int n_full = lower_bound(coach.begin(), coach.end(), coach[i] - D) - coach.begin();
        dp[i+1] += (p2[campers(coach[i], coach[i] + D)] * pref[n_full]) % MOD;

        if (i > 0) {
            multiply(1, n_full + 1, i+1, p2[campers(coach[i-1] + D, coach[i] + D)]);
            dp[i+1] += query(1, n_full + 1, i+1);
        }

        dp[i+1] %= MOD;
        upd(1, i+1, dp[i+1]);
        pref[i+1] = (pref[i] + dp[i+1]) % MOD;
    }

    cout << (pref[coach.size()] + MOD - 1) % MOD << '\n';
}
