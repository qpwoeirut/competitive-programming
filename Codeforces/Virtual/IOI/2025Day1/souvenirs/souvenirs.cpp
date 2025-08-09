#include <bits/stdc++.h>
#include "souvenirs.h"

using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

void buy_souvenirs(int N, long long P0) {
    vi total(N);
    vl cost_lo(N), cost_hi(N);
    cost_lo[0] = P0;
    cost_hi[0] = P0;
    for (int i=1; i<N; ++i) {
        cost_lo[i] = N - i;
        cost_hi[i] = cost_hi[i - 1] - 1;
    }
    for (int i=1; i<N; ++i) {
        while (total[i] < i) {
            const pair<vi, ll> result = transaction(cost_hi[i]);
            const ll cost = cost_hi[i] - result.second;

            const int m = result.first.size();

            cost_lo[result.first[0]] = max(cost_lo[result.first[0]], (cost + m - 1) / m);
            cost_hi[result.first[m-1]] = max(cost_hi[result.first[m-1]], cost / m + 1);

            for (int j=i; j<N; ++j) {
                if (binary_search(result.first.begin(), result.first.end(), j)) {
                    ++total[j];

                    ll other_lo = 0, other_hi = 0;
                    for (int k: result.first) {
                        if (j != k) {
                            other_lo += cost_lo[k];
                            other_hi += cost_hi[k];
                        }
                    }
                    cost_lo[j] = max(cost_lo[j], cost - other_hi);
                    cost_hi[j] = min(cost_hi[j], cost - other_lo);
                }
            }

            ll cur_lo = result.second, cur_hi = result.second;
            for (int j=N-1; j>=i; --j) {
                if (binary_search(result.first.begin(), result.first.end(), j)) {
                    cur_lo += cost_lo[j];
                    cur_hi += cost_hi[j];
                } else {
                    cost_lo[j] = max(cost_lo[j], cur_lo + 1);
                }
            }

            for (int j=i; j<N; ++j) {
                cost_hi[j] = min(cost_hi[j], cost_hi[j - 1] - 1);
                //cost_lo[j] = max(cost_lo[j], cost_lo[j - 1] / 2);
            }
            for (int j=N-2; j>=i; --j) {
                cost_lo[j] = max(cost_lo[j], cost_lo[j + 1] + 1);
            }
        }
    }
}

