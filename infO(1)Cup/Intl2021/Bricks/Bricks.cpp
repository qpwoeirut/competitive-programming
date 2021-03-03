#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;
typedef pair<pii,pii> ppii;

struct Node {
    int mx;
    int lo, hi;
};

const int MN = 6000006;

int N;
Node tree[2][MN << 2];

void build(const bool C[], const int H[]) {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;

    for (int c=0; c<2; ++c) {
        for (int i=0; i<PN; ++i) {
            tree[c][PN+i].mx = (i<N && C[i] == c) ? H[i] : 0;
            tree[c][PN+i].lo = i;
            tree[c][PN+i].hi = i+1;
        }
        for (int i=PN-1; i>0; --i) {
            tree[c][i].mx = max(tree[c][i << 1].mx, tree[c][(i << 1) + 1].mx);
            tree[c][i].lo = tree[c][i << 1].lo;
            tree[c][i].hi = tree[c][(i << 1) + 1].hi;
        }
    }
}

int first_greater(const int c, const int node, const int lo, const int val) {
    //cerr << c << ' ' << node << ' ' << lo << ' ' << val << ' ' << tree[c][node].mx << endl;
    if (tree[c][node].hi <= lo) return N;
    if (tree[c][node].mx <= val) return N;
    if (tree[c][node].lo + 1 == tree[c][node].hi) return tree[c][node].lo;

    int lft = first_greater(c, node << 1, lo, val);
    if (lft != N) return lft;
    return first_greater(c, (node << 1) + 1, lo, val);
}

bool used[MN];
pii pref[2][MN];
int suff[2][MN];
int solve(const int n, bool C[], int H[]) {
    N = n;
    reverse(C, C+N);
    reverse(H, H+N);

    build(C, H);

    for (int c=0; c<2; ++c) {
        pref[c][0] = C[0] == c ? pii(1, H[0]) : pii(0, 0);
        suff[c][N] = 0;
    }

    fill(used, used+N, false);
    used[0] = true;
    for (int i=1; i<N; ++i) {
        for (int c=0; c<2; ++c) {
            pref[c][i] = pref[c][i-1];
            if (C[i] == c && H[i] > pref[c][i].se) {
                used[i] = true;
                ++pref[c][i].fi;
                pref[c][i].se = H[i];
            }
        }
    }

    if (N > 200000) {
        bool sub2 = true;
        for (int i=0; i<N; ++i) {
            sub2 &= C[i];
        }
        if (sub2) {

        }
        return pref[0][N-1].fi + pref[1][N-1].fi;
    }

    for (int i=N-1; i>=0; --i) {
        suff[C[i]][i] = suff[C[i]][first_greater(C[i], 1, i, H[i])] + 1;
        suff[!C[i]][i] = suff[!C[i]][i+1];
    }

    int ans = suff[0][0] + suff[1][0];
    for (int i=0; i<N; ++i) {
        //cerr << "i: " << i << ' ' << C[i] << ' ' << H[i] << endl;
        int cur1, cur2;
        if (used[i]) {
            int val = i ? pref[C[i]][i-1].se : 0;
            int idx = first_greater(C[i], 1, i+1, val);
            cur1 = pref[C[i]][i].fi - 1 + suff[C[i]][idx];
            //cerr << "val,idx1: " << val << ' ' << idx << endl;
            //cerr << pref[C[i]][i].fi << ' ' << suff[C[i]][idx] << endl;
        } else {
            cur1 = suff[C[i]][0];
        }

        if (pref[!C[i]][i].se < H[i]) {
            int idx = first_greater(!C[i], 1, i, H[i]);
            cur2 = pref[!C[i]][i].fi + 1 + suff[!C[i]][idx];
            //cerr << "idx2: " << idx << endl;
        } else {
            cur2 = suff[!C[i]][0];
        }

        ans = max(ans, cur1 + cur2);
        //cerr << i << '\n' << used[i] << endl;
        //cerr << cur1 << ' ' << cur2 << endl << endl;
    }

    return ans;
}

/*
store (len, val) prefixes for both colors
store next 2 larger values for each color
store len suffix for seq that starts at that position
original answer = suff[0]

test brick:
    is interesting
        ans1 = pref[i-1].len + suff[next[prv].se]
    else:
        ans1 = suff[0]

    becomes interesting
        ans2 = pref[i-1].len + 1 + suff[nxt[i].fi]
    else:
        ans2 = suff[0]
*/
/*
6
0 0 1 0 0 1
7 8 6 2 3 5
*/
