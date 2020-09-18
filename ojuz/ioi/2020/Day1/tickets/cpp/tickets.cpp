#include "tickets.h"
#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef vector<vector<int>> vvi;
typedef pair<ll,ll> pll;

ll N, M;

ll sub1(int K, const vvi& x) {
    vvi ans(N, vector<int>(M, -1));
    vector<int> nums(N);
    for (int i=0; i<N; ++i) {
        nums[i] = x[i][0];
        ans[i][0] = 0;
    }
    sort(nums.begin(), nums.end());
    int med = (nums.size()) / 2;
    ll sum = 0;
    for (int i=0; i<N; ++i) {
        sum += abs(nums[i] - nums[med]);
    }

    allocate_tickets(ans);
    return sum;
}

ll score(const vector<pll>& v1, const vector<pll>& v2) {
    vector<ll> nums;
    for (int i=0; i<v1.size(); ++i) nums.push_back(v1[i].FI);
    for (int i=0; i<v2.size(); ++i) nums.push_back(v2[i].FI);
    sort(nums.begin(), nums.end());

    assert(nums.size() == N);
    int med = nums.size() / 2;
    ll sum = 0;
    for (int i=0; i<N; ++i) {
        sum += abs(nums[i] - nums[med]);
    }
    return sum;
}

ll sub2(int K, const vvi& x) {
    vvi ans(N, vector<int>(M, -1));
    vector<pll> left;
    for (int i=0; i<N; ++i) {
        left.push_back(pll(x[i][0], i));
    }
    sort(left.begin(), left.end());

    vector<pll> right;
    pll best(score(left, right), left.back().FI);
    while (left.size() > 0) {
        int color = left.back().SE;
        left.pop_back();

        right.push_back(pll(x[color][M-1], color));

        best = max(best, pll(score(left, right), left.back().FI));
    }

    for (int i=0; i<N; ++i) {
        if (x[i][0] <= best.SE) {
            ans[i][0] = 0;
        } else {
            ans[i][M-1] = 0;
        }
    }

    allocate_tickets(ans);
    return best.FI;
}

long long find_maximum(int K, std::vector<std::vector<int>> x) {
	N = x.size();
	M = x[0].size();

    if (M == 1) {
        return sub1(K, x);
    }
    if (K == 1) {
        return sub2(K, x);
    }

    set<int> vals;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            vals.insert(x[i][j]);
        }
    }

    return 0;
}
