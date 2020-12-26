//cses_range_minimum_queries_ii.cpp created at 12/20/20 12:51:53

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;
const int INIT = 1001001001;

struct Node {
    int min;
    int start, finish;
};

int N, Q;
int PN;
int A[MN];

Node tree[MN << 2];

void build() {
    for (int i=0; i<PN; ++i) {
        if (i < N) {
            tree[PN + i].min = A[i];
        } else {
            tree[PN + i].min = INIT;
        }

        tree[PN + i].start = i;
        tree[PN + i].finish = i + 1;
    }

    for (int i=PN-1; i>0; --i) {
        tree[i].min = min(tree[i << 1].min, tree[(i << 1) + 1].min);
        tree[i].start = tree[i << 1].start;
        tree[i].finish = tree[(i << 1) + 1].finish;
    }
}

void update(const int node, const int pos, const int val) {
    if (tree[node].finish <= pos || pos + 1 <= tree[node].start) return;
    if (pos <= tree[node].start && tree[node].finish <= pos + 1) {
        tree[node].min = val;
        return;
    }

    update(node << 1, pos, val);
    update((node << 1) + 1, pos, val);

    tree[node].min = min(tree[node << 1].min, tree[(node << 1) + 1].min);
}

int query(const int node, const int lo, const int hi) {
    if (tree[node].finish <= lo || hi <= tree[node].start) return INIT;
    if (lo <= tree[node].start && tree[node].finish <= hi) return tree[node].min;

    return min(query(node << 1, lo, hi), query((node << 1) + 1, lo, hi));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    PN = N;
    --PN;
    PN |= PN >> 1;
    PN |= PN >> 2;
    PN |= PN >> 4;
    PN |= PN >> 8;
    PN |= PN >> 16;
    ++PN;

    build();

    for (int i=0; i<Q; ++i) {
        int t, a, b;
        cin >> t >> a >> b;
        --a;
        if (t == 1) {
            update(1, a, b);
        } else if (t == 2) {
            cout << query(1, a, b) << '\n';
        } else assert(false);
    }
}

