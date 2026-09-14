#include <bits/stdc++.h>

const int MN = 200005;

bitset<MN> used;
vector<array<int, 3>> calculate_triples(int n) {
    int lo = 2, hi = n;
    used.reset();
    vector<array<int, 3>> idxs;
    while (lo < hi - lo && hi - lo < hi) {
        idxs.emplace_back(lo, hi - lo, hi);
        while (lo < hi && used[lo]) ++lo;
        while (lo < hi && used[hi]) --hi;
    }
    for (int i=2; i<n; ++i) {
        if (!used[i] && !used[i+1]) {
            idxs.emplace_back(1, i, i+1);
            break;
        }
    }
    return idxs;
}

bool solve(int N, int K, vector<int>& ans) {
    map<int, int> counts;
    for (int i=0; i<N; ++i) ++counts[A[i]];

    vector<int> pairs;
    vector<int> triples;

    for (const auto& [val, ct]: counts) {
        if (ct == 1) {
            if (N % 2 == 0 || ans[N / 2] != 0) {
                return false;
            }
        } else if (ct % 2 == 0) {
            for (int i=0; i<ct; i+=2) pairs.push_back(val);
        }
    }

    if (triples.size() % 2 == 1) {
        if (N % 2 == 0 || ans[N / 2] != 0) {
            return false;
        }
        int val = triples.back(); triples.pop_back();
        ans[N / 2] = val;
        pairs.push_back(val);
    }

    if (N % 2 == 0 && triples.size() > 0) {
        return false;
    }

    vector<array<int, 3>> triple_idxs = calculate_triples(N / 2);
    if (triple_idxs.size() < triples.size() / 2) {
        return false;
    }

    for (int i=0; i<triples.size(); i+=2) {
        auto [a, b, c] = triple_idxs.back(); triple_idxs.pop_back();
        int center = N / 2;
        ans[center - a] = ans[center - b] = ans[center + c] = triples[i];
        ans[center + a] = ans[center + b] = ans[center - c] = triples[i + 1];
    }
    for (int i=0; i<N/2; ++i) {
        if (ans[i] == 0) {
            assert(ans[N - i - 1] == 0);
            assert(pairs.size() > 0);
            ans[i] = ans[N - i - 1] = pairs.back(); pairs.pop_back();
        }
    }

    return true;
}


