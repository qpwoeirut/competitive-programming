//1132g.cpp created at 02/03/21 14:24:32

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 1000006;
const int LG = 20;
const int INIT = 1001001001;

int N, K;
int A[MN];

struct Node {
    int mx;
    int lazy;
    int lo, hi;

    Node() {}
    Node(const int _lo, const int _hi) {
        mx = 1;
        lazy = 0;
        lo = _lo;
        hi = _hi;
    }
};

Node tree[1 << (LG + 1)];

void build() {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    
    for (int i=0; i<PN; ++i) {
        tree[PN + i] = Node(i, i+1);
    }
    for (int i=PN-1; i>0; --i) {
        tree[i] = Node(tree[i << 1].lo, tree[(i << 1) + 1].hi);
    }
}

void prop(const int node) {
    tree[node << 1].mx += tree[node].lazy;
    tree[node << 1].lazy += tree[node].lazy;

    tree[(node << 1) + 1].mx += tree[node].lazy;
    tree[(node << 1) + 1].lazy += tree[node].lazy;

    tree[node].lazy = 0;
}

void inc(const int node, const int lo, const int hi) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        ++tree[node].mx;
        ++tree[node].lazy;
        return;
    }

    if (tree[node].lazy != 0) {
        prop(node);
    }

    inc(node << 1, lo, hi);
    inc((node << 1) + 1, lo, hi);

    tree[node].mx = max(tree[node << 1].mx, tree[(node << 1) + 1].mx);
}

void dec(const int node, const int lo, const int hi) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        --tree[node].mx;
        --tree[node].lazy;
        return;
    }

    if (tree[node].lazy != 0) {
        prop(node);
    }

    dec(node << 1, lo, hi);
    dec((node << 1) + 1, lo, hi);

    tree[node].mx = max(tree[node << 1].mx, tree[(node << 1) + 1].mx);
}

int query(const int node, const int lo, const int hi) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return -INIT;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].mx;

    if (tree[node].lazy > 0) {
        prop(node);
    }

    return max(query(node << 1, lo, hi), query((node << 1) + 1, lo, hi));
}

vector<int> adj[MN];
pii range[MN];
int cur_mark = 0;
void dfs(const int u) {
    range[u].fi = cur_mark++;
    for (const int v: adj[u]) {
        dfs(v);
    }
    range[u].se = cur_mark;
}

int main() {
    cin.tie(0)->sync_with_stdio();

    cin >> N >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    
    stack<int> st;
    for (int i=0; i<N; ++i) {
        while (st.size() > 0 && A[st.top()] < A[i]) {
            adj[i].push_back(st.top());
            st.pop();
        }
        st.push(i);
    }

    while (st.size() > 0) {
        dfs(st.top());
        st.pop();
    }

    build();

    for (int i=0; i<N; ++i) {
        inc(1, range[i].fi + 1, range[i].se);

        if (i+1 >= K) {
            cout << query(1, 0, N) << ' ';

            dec(1, range[i-K+1].fi, range[i-K+1].se);
        }
    }
    cout << endl;
}
/*
5 3
1 2 3 4 5
*/

