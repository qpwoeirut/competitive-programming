#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;

const ll INF = 100'000'000'000'000'000LL;

bool chmx(int& a, const int b) {
    return a < b ? a = b, true : false;
}
bool chmx(ll& a, const ll b) {
    return a < b ? a = b, true : false;
}

vi run_dp(ll A, const vi& P, const vi& T) {
    const int N = P.size();

    vector<pii> coupons[5];
    for (int i=0; i<N; ++i) {
        coupons[T[i]].emplace_back(P[i], i);
    }
    for (int k=0; k<=4; ++k) {
        sort(coupons[k].begin(), coupons[k].end());
    }

    vector<vector<vl>> dp(coupons[2].size()+1, vector<vl>(coupons[3].size()+1, vl(coupons[4].size()+1, -1)));
    vector<vector<vl>> used(coupons[2].size()+1, vector<vl>(coupons[3].size()+1, vl(coupons[4].size()+1, -1)));
    dp[0][0][0] = A;

    vl psum(coupons[1].size() + 1);
    for (int i=1; i<=coupons[1].size(); ++i) {
        psum[i] = psum[i-1] + coupons[1][i-1].first;
    }

    int best_ct = 0, best_i = -1, best_j = -1, best_k = -1;
    for (int i=0; i<=coupons[2].size(); ++i) {
        for (int j=0; j<=coupons[3].size(); ++j) {
            for (int k=0; k<=coupons[4].size(); ++k) {
                if (i && chmx(dp[i][j][k], (dp[i - 1][j][k] - coupons[2][i - 1].first) * 2)) {
                    used[i][j][k] = coupons[2][i - 1].second;
                }
                if (j && chmx(dp[i][j][k], (dp[i][j - 1][k] - coupons[3][j - 1].first) * 3)) {
                    used[i][j][k] = coupons[3][j - 1].second;
                }
                if (k && chmx(dp[i][j][k], (dp[i][j][k - 1] - coupons[4][k - 1].first) * 4)) {
                    used[i][j][k] = coupons[4][k - 1].second;
                }
                dp[i][j][k] = min(dp[i][j][k], INF);

                int ct1 = upper_bound(psum.begin(), psum.end(), dp[i][j][k]) - psum.begin() - 1;
                if ((used[i][j][k] != -1 || (i == 0 && j == 0 && k == 0)) && chmx(best_ct, ct1 + i + j + k)) {
                    best_i = i;
                    best_j = j;
                    best_k = k;
                }
            }
        }
    }
    if (best_ct == 0) return vi();
    int a_i = best_i, a_j = best_j, a_k = best_k;
    vi ans;
    ll rem = dp[a_i][a_j][a_k];
    for (int a=0; a<coupons[1].size(); ++a) {
        if (coupons[1][a].first <= rem) {
            rem -= coupons[1][a].first;
            ans.push_back(coupons[1][a].second);
        } else break;
    }

    while (a_i || a_j || a_k) {
        int idx = used[a_i][a_j][a_k];
        if (idx == -1) {
            ans.clear();
            break;
        }
        ans.push_back(idx);
        if (T[idx] == 2) --a_i;
        if (T[idx] == 3) --a_j;
        if (T[idx] == 4) --a_k;
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

vi max_coupons(int A, vi P, vi T) {
    const int N = P.size();
    assert(N == T.size());

    return run_dp(A, P, T);
}
