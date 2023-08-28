//1864e.cpp created at 08/27/23 21:10:32

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 200005;
const int MOD = 998244353;

ll binpow(ll x, int p) {
    x %= MOD;

    ll ret = 1;
    for (; p > 0; p >>= 1) {
        if (p & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
    }
    return ret;
}

int A[MN];

struct TrieNode {
    int p2;
    int val;
    int ct;

    int child[2];

    TrieNode() : TrieNode(-1, 0) {}
    TrieNode(const int _p2, const int _val) : p2(_p2), val(_val) {
        ct = 0;
        child[0] = child[1] = -1;
    }
};

int n_trie;
TrieNode trie[MN * 30];

void create_children(TrieNode& node) {
    if (node.child[0] == -1) {
        node.child[0] = n_trie;
        trie[n_trie++] = TrieNode(node.p2 - 1, 0);
    }
    if (node.child[1] == -1) {
        node.child[1] = n_trie;
        trie[n_trie++] = TrieNode(node.p2 - 1, 1);
    }
}

void inc(TrieNode& node, const int x) {
    ++node.ct;

    if (node.p2 < 0) return;

    create_children(node);

    if (node.p2 == 0) {
        inc(trie[node.child[0]], 0);
    } else {
        inc(trie[node.child[(x >> (node.p2 - 1)) & 1]], x & ((1 << node.p2) - 1));
    }
}
int count_answer(TrieNode& node, const int x, bool alice) {
    if (node.p2 < 0) return node.ct;

    const int alice_val = (x >> node.p2) & 1;

    int ans;
    if (alice_val == node.val) {
        create_children(node);

        const int nxt = x & ((1 << node.p2) - 1);
        ans = count_answer(trie[node.child[0]], nxt, !alice) + count_answer(trie[node.child[1]], nxt, !alice);
        if (node.val == 1) ans += node.ct;
    } else if (alice_val ^ alice) {
        ans = node.ct;
    } else {
        ans = node.ct * 2;
    }
    return ans;
}

void solve() {
    n_trie = 0;
    trie[n_trie++] = TrieNode(30, 0);

    ll N;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<N; ++i) {
        inc(trie[0], A[i]);
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        ans += count_answer(trie[0], A[i], true);
    }

    ans %= MOD;
    ans = (ans * binpow(N * N, MOD - 2)) % MOD;

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) solve();
}

