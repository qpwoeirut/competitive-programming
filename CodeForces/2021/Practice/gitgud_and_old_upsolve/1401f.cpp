//1401f.cpp created at 01/25/21 12:59:22

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Node {
    ll sum;
    int lo, hi;
    int lvl;
};

const int MN = 1 << 19;

int N, Q;
ll A[MN];
Node tree[MN];
bool flipped[20];

void build() {
    for (int i=0; i<N; ++i) {
        tree[N+i].lo = i;
        tree[N+i].hi = i+1;
        tree[N+i].sum = A[i];
        tree[N+i].lvl = 0;
    }
    for (int i=N-1; i>0; --i) {
        tree[i].lo = tree[i << 1].lo;
        tree[i].hi = tree[(i << 1) + 1].hi;
        tree[i].sum = tree[i << 1].sum + tree[(i << 1) + 1].sum;
        tree[i].lvl = tree[i << 1].lvl + 1;
    }
}

int flip(const int node, const int pos, const int dir) {
    assert(tree[node].lvl > 0);
    const int lo = tree[node].lo;
    const int hi = tree[node].hi;
    const int shf = (hi - lo) >> 1;
    const int ret = pos + (dir * shf);

    //cerr << lo << ' ' << hi << ' ' << pos << ' ' << ret << endl;
    return ret;
}

void update(const int node, int pos, const int val) {
    if (pos + 1 <= tree[node].lo || tree[node].hi <= pos) return;
    if (tree[node].lo == pos && pos + 1 == tree[node].hi) {
        //cerr << tree[node].lo << " set to " << val << endl;
        tree[node].sum = val;
        return;
    }
    if (flipped[tree[node].lvl]) {
        update(node << 1, flip(node, pos, -1), val);
        update((node << 1) + 1, flip(node, pos, +1), val);
    } else {
        update(node << 1, pos, val);
        update((node << 1) + 1, pos, val);
    }

    tree[node].sum = tree[node << 1].sum + tree[(node << 1) + 1].sum;
}

ll query(const int node, int lo, int hi) {
    assert(lo < hi);
    //cerr << tree[node].lo << ' ' << tree[node].hi << ' ' << lo << ' ' << hi << endl;
    //cerr << tree[node].lvl << ' ' << flipped[tree[node].lvl] << endl;
    if (hi <= tree[node].lo || tree[node].hi <= lo) return 0;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].sum;
    if (flipped[tree[node].lvl]) {
        const int llo = flip(node, lo, -1), lhi = flip(node, hi, -1);
        const int hlo = flip(node, lo, +1), hhi = flip(node, hi, +1);
        return query(node << 1, llo, lhi) + query((node << 1) + 1, hlo, hhi);
    }
    
    return query(node << 1, lo, hi) + query((node << 1) + 1, lo, hi);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    N = 1 << N;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    build();
    for (int i=0; i<Q; ++i) {
        int t, x, k, L, R;
        cin >> t;
        if (t == 1) {
            cin >> x >> k;
            --x;
            update(1, x, k);
        } else if (t == 2) {
            cin >> k;
            for (int j=0; j<=k; ++j) {
                flipped[j] = !flipped[j];
            }
        } else if (t == 3) {
            cin >> k;
            ++k;
            flipped[k] = !flipped[k];
        } else if (t == 4) {
            cin >> L >> R;
            --L;
            cout << query(1, L, R) << '\n';
        } else assert(false);
    }
}
/*
3 4
1 2 4 8 16 32 64 128
2 2
4 1 1
4 4 4
4 8 8

3 10
1 2 4 8 16 32 64 128
2 3
3 2
4 1 4
4 5 8
4 1 8
4 1 5
1 4 3
4 1 4
2 2
4 1 4
*/
