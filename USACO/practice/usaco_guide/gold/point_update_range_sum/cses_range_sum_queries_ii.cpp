//cses_range_sum_queries_ii.cpp created at 12/20/20 12:22:34

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;

struct Node {
    ll sum;
    int start, finish;
};

int N, Q;
ll A[MN];
int PN;
Node tree[MN << 2];

int next_p2(int x) {
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    ++x;
    return x;
}

void build() {
    for (int i=0; i<PN; ++i) {
        if (i < N) {
            tree[PN+i].sum = A[i];
        }
        tree[PN+i].start = i;
        tree[PN+i].finish = i + 1;
    }
    for (int i=PN-1; i>0; --i) {
        tree[i].sum = tree[i << 1].sum + tree[(i << 1) + 1].sum;
        tree[i].start = tree[i << 1].start;
        tree[i].finish = tree[(i << 1) + 1].finish;
    }
}

void update(const int node, const int pos, const ll val) {
    if (tree[node].finish <= pos || pos+1 <= tree[node].start) return;
    if (pos <= tree[node].start && tree[node].finish <= pos+1) {
        tree[node].sum += val;
        return;
    }

    update(node << 1, pos, val);
    update((node << 1) + 1, pos, val);
    tree[node].sum = tree[node << 1].sum + tree[(node << 1) + 1].sum;
}

ll query(const int node, const int lo, const int hi) {
    if (tree[node].finish <= lo || hi <= tree[node].start) return 0;
    if (lo <= tree[node].start && tree[node].finish <= hi) return tree[node].sum;

    return query(node << 1, lo, hi) + query((node << 1) + 1, lo, hi);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    PN = next_p2(N);
    build();

    for (int i=0; i<Q; ++i) {
        int t, a, b;
        cin >> t >> a >> b;

        if (t == 1) {
            --a;
            update(1, a, b - A[a]);
            A[a] = b;
        } else if (t == 2) {
            --a;
            cout << query(1, a, b) << '\n';
        } else assert(false);
    }
}
