#include <bits/stdc++.h>
#include "gondola.h"

using namespace std;

typedef long long ll;

const int MN = 250001;
const ll MOD = 1e9 + 9;

bool normalize(int n, int seq[]) {
    for (int i=0; i<n; ++i) {
        if (seq[i] <= n) {
            int val = seq[i];
            int idx = (n + i - val + 1) % n;
            rotate(seq, seq+idx, seq+n);
            return true;
        }
    }
    return false;
}

int valid(int n, int inputSeq[]) {
    normalize(n, inputSeq);
    //for (int i=0; i<n; ++i) { cerr << inputSeq[i] << ' '; } cerr << endl;

    set<int> seen;
    for (int i=0; i<n; ++i) {
        if (inputSeq[i] != i+1 && inputSeq[i] <= n) {
            return 0;
        }
        if (seen.count(inputSeq[i])) {
            return 0;
        }
        seen.insert(inputSeq[i]);
    }

    return 1;
}

//----------------------

bool seen[MN];
int pos[MN];
pair<int,int> process(int n, int seq[]) {
    int mxv = 0;
    int mxi = -1;
    for (int i=0; i<n; ++i) {
        pos[seq[i]] = i;
        seen[seq[i]] = true;
        if (mxv < seq[i]) {
            mxv = seq[i];
            mxi = i;
        }
    }
    return pair<int,int>(mxv, mxi);
}

int replacement(int n, int gondolaSeq[], int replacementSeq[]) {
    fill(seen, seen+n, false);
    normalize(n, gondolaSeq);

    auto mx = process(n, gondolaSeq);
    int mxv = mx.first;
    int cur = mx.second + 1;

    int idx = 0;
    for (int i=n+1; i<=mxv; ++i) {
        if (!seen[i] || i == mxv) {
            replacementSeq[idx++] = cur;
            cur = i;
        } else {
            replacementSeq[idx++] = pos[i] + 1;
        }
    }

    return idx;
}

//----------------------

ll bpow(ll b, ll p) {
    b %= MOD;
    p %= MOD;
    ll ret = 1;
    while (p) {
        if (p & 1) {
            ret = (ret * b) % MOD;
        }
        p >>= 1;
        b = (b * b) % MOD;
    }
    return ret;
}
int countReplacement(int n, int inputSeq[]) {
    bool rotated = normalize(n, inputSeq);
    if (!valid(n, inputSeq)) {
        return 0;
    }

    set<int> nums;
    for (int i=0; i<n; ++i) {
        if (inputSeq[i] > n) {
            nums.insert(inputSeq[i]);
        }
    }

    ll ans = 1;
    ll prev = n+1;
    while (nums.size() > 0) {
        ll cur = *nums.begin();

        ll more = nums.size();
        ans = (ans * bpow(more, cur - prev)) % MOD;

        prev = cur + 1;

        nums.erase(nums.begin());
    }

    if (!rotated) {
        ans = (ans * (ll)n) % MOD;
    }

    return ans;
}
