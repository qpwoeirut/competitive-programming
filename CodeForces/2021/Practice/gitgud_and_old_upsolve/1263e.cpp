//1263e.cpp created at 03/03/21 20:34:49

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 1000006;
const int INIT = 1001001001;

struct Node {
    int lo, hi;
    int min, max;
    int lazy;
};

struct Command {
    int time;
    int val;
    int pos;

    inline const bool operator<(const Command& o) const {
        return time < o.time;
    }
};

int N;
int A[MN];
Node tree[MN << 2];

int ans[MN];

void build() {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    for (int i=0; i<PN; ++i) {
        tree[PN+i].lo = i;
        tree[PN+i].hi = i+1;
        tree[PN+i].min = i < N ? 0 : INIT;
        tree[PN+i].max = i < N ? 0 : -INIT;
        tree[PN+i].lazy = 0;
    }
    for (int i=PN-1; i>0; --i) {
        tree[i].lo = tree[i << 1].lo;
        tree[i].hi = tree[(i << 1) + 1].hi;
        tree[i].min = min(tree[i << 1].min, tree[(i << 1) + 1].min);
        tree[i].max = max(tree[i << 1].max, tree[(i << 1) + 1].max);
        tree[i].lazy = 0;
    }
}

void prop(const int node) {
    tree[node << 1].min += tree[node].lazy;
    tree[node << 1].max += tree[node].lazy;
    tree[node << 1].lazy += tree[node].lazy;

    tree[(node << 1) + 1].min += tree[node].lazy;
    tree[(node << 1) + 1].max += tree[node].lazy;
    tree[(node << 1) + 1].lazy += tree[node].lazy;

    tree[node].lazy = 0;
}

void update(const int node, const int lo, const int hi, const int val) {
    if (lo >= tree[node].hi || tree[node].lo >= hi) return;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        tree[node].min += val;
        tree[node].max += val;
        tree[node].lazy += val;
        return;
    }

    if (tree[node].lazy != 0) prop(node);

    update(node << 1, lo, hi, val);
    update((node << 1) + 1, lo, hi, val);

    tree[node].min = min(tree[node << 1].min, tree[(node << 1) + 1].min);
    tree[node].max = max(tree[node << 1].max, tree[(node << 1) + 1].max);
}

int query_min(const int node, const int lo, const int hi) {
    if (lo >= tree[node].hi || tree[node].lo >= hi) return INIT;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].min;

    if (tree[node].lazy != 0) prop(node);

    return min(query_min(node << 1, lo, hi), query_min((node << 1) + 1, lo, hi));
}

int query_max(const int node, const int lo, const int hi) {
    if (lo >= tree[node].hi || tree[node].lo >= hi) return -INIT;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].max;

    if (tree[node].lazy != 0) prop(node);

    return max(query_max(node << 1, lo, hi), query_max((node << 1) + 1, lo, hi));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    string S;
    cin >> S;

    build();
    int balance = 0;
    int pos = 0;
    for (int i=0; i<N; ++i) {
        if (S[i] == 'L') {
            if (pos > 0) --pos;
        } else if (S[i] == 'R') {
            ++pos;
        } else {
            const int val = S[i] == '(' ? 1 : (S[i] == ')' ? -1 : 0);
            balance += val - A[pos];

            update(1, pos, N, val - A[pos]);
            A[pos] = val;
        }
        ans[i] = (query_min(1, 0, N) < 0 || balance != 0) ? -1 : query_max(1, 0, N);
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
