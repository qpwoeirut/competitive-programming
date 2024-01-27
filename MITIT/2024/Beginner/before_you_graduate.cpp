#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

const int MN = 100005;

int N, K;
int A[MN];

struct Trie {
    Trie* zero;
    Trie* one;

    int max_idx;
    const int bits;

    Trie(int _bits): bits(_bits) { 
        zero = nullptr;
        one = nullptr;
        max_idx = -1;
    }

    void add(int x, int idx) {
        max_idx = max(max_idx, idx);

        if (bits == 0) return;
        if ((x >> (bits - 1)) & 1) {
            if (one == nullptr) one = new Trie(bits - 1);
            one->add(x, idx);
        } else {
            if (zero == nullptr) zero = new Trie(bits - 1);
            zero->add(x, idx);
        }
    }

    int idx_of(int x) {
        if (K == 0) return -1;
        if (zero == nullptr) zero = new Trie(bits - 1);
        if (one == nullptr) one = new Trie(bits - 1);

        if (bits == 0) return max_idx;

        int a = (x >> (bits - 1)) & 1;
        int b = ((K - 1) >> (bits - 1)) & 1;
        if (a == 0 && b == 1) {
            return max(zero->max_idx, one->idx_of(x));
        } else if (a == 1 && b == 0) {
            return one->idx_of(x);
        } else if (a == 0 && b == 0) {
            return zero->idx_of(x);
        } else {
            return max(zero->idx_of(x), one->max_idx);
        }
    }
};

Trie* trie = new Trie(30);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    vector<pii> include;
    map<int,int> idxs;
    for (int i=0; i<N; ++i) {
        auto it = idxs.find(A[i] ^ K);
        if (it != idxs.end()) {
            include.emplace_back(it->second, i);
        }
        idxs[A[i]] = i;
    }

    vector<pii> exclude;
    for (int i=0; i<N; ++i) {
        const int j = trie->idx_of(A[i]);
        if (j != -1) {
            exclude.emplace_back(j, i);
        }
        trie->add(A[i], i);
    }
    debug(include, exclude);

    long long ans = 0;
    int i_inc = 0, i_exc = 0;
    int max_inc = -1, max_exc = -1;
    for (int i=0; i<N; ++i) {
        while (i_inc < include.size() && include[i_inc].second <= i) max_inc = max(max_inc, include[i_inc++].first);
        while (i_exc < exclude.size() && exclude[i_exc].second <= i) max_exc = max(max_exc, exclude[i_exc++].first);

        ans += max(0, max_inc - max_exc);
        debug(i, max_inc, max_exc);
    }

    cout << ans << '\n';
}
