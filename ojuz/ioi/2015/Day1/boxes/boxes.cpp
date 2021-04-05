#include "boxes.h"
#include <bits/stdc++.h>

using namespace std;

#define idx first
#define cost second

typedef long long ll;
typedef pair<ll,ll> pll;

const ll INF = 1e18;

ll delivery(int n, int k, int l, int p[]) {
    const ll N = n, K = k, L = l;
    deque<pll> lft, rht;
    lft.emplace_back(0, 0);
    if (p[0] > L/2) rht.emplace_back(0, 2LL * (L - p[0]));
    for (ll i=1; i<=N; ++i) {
        while (lft.size() > 0 && lft.front().idx + K < i) lft.pop_front();
        while (rht.size() > 0 && rht.front().idx + K < i) rht.pop_front();
        if (p[i-1] <= L/2) {
            assert(lft.size() > 0);

            const ll cur = lft.front().cost + 2LL * p[i-1];
            if (i == N) return cur;

            if (p[i] <= L/2) {
                while (lft.size() > 0 && lft.back().cost >= cur) lft.pop_back();
                lft.emplace_back(i, cur);
            } else {
                const ll new_cost = cur + 2LL * (L - p[i]);
                while (rht.size() > 0 && rht.back().cost >= new_cost) rht.pop_back();
                rht.emplace_back(i, new_cost);
            }
        } else {
            assert(lft.size() + rht.size() > 0);
            const ll from_left = lft.empty() ? INF : lft.front().cost + L;
            const ll from_right = rht.empty() ? INF : rht.front().cost;

            const ll cur = min(from_left, from_right);
            if (i == N) return cur;

            const ll new_cost = cur + 2LL * (L - p[i]);
            while (rht.size() > 0 && rht.back().cost >= new_cost) rht.pop_back();
            rht.emplace_back(i, new_cost);
        }
    }
    assert(0);
}

