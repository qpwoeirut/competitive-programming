#include <bits/stdc++.h>

using namespace std;

constexpr int MN = 7500;

bitset<MN> A;

int cost[MN][MN];

int solve(const int lo, const int hi) {
    const int mid = (hi - lo) / 2;
    vector<int> bad[2];
    for (int i=0; i<mid; ++i) {
        if (A[lo+i] != A[hi-i-1]) {
            bad[A[lo+i]].push_back(i);
        }
    }

    if ((bad[0].size() ^ bad[1].size()) & 1) {
        if (((hi - lo) & 1) == 0) return -1;
        bad[A[lo+mid]].push_back(mid);
    }

    int cost = 0;
    int i = 0, j = 0;
    for (i=0, j=0; i < bad[0].size() && j < bad[1].size(); ++i, ++j) {
        cost += abs(bad[0][i] - bad[1][j]);
    }
    for (; i < bad[0].size(); i+=2) {
        assert(i+1 < bad[0].size());
        const int a = bad[0][i];
        const int b = bad[0][i+1];

        cost += (hi - b - 1) - (lo + a);
    }
    for (; j < bad[1].size(); j+=2) {
        assert(j+1 < bad[1].size());
        const int a = bad[1][j];
        const int b = bad[1][j+1];

        cost += (hi - b - 1) - (lo + a);
    }

    //cerr << lo << ' ' << hi << ' ' << cost << endl;
    return cost;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string S;
    cin >> S;

    const int N = S.size();
    for (int i=0; i<N; ++i) {
        A[i] = S[i] == 'H';
    }

    long long ans = 0;

    // odd
    vector<int> bad[2];
    vector<int> ssum[2];
    for (int mid=0; mid<N; ++mid) {
        bad[0].clear();
        bad[1].clear();
        for (int i=mid-1; i>=0 && mid+mid<N+i; --i) {
            if (A[i] != A[mid+mid-i]) {
                bad[A[i]].push_back(i);
            }
        }
        reverse(bad[0].begin(), bad[0].end());
        reverse(bad[1].begin(), bad[1].end());

        for (int lo = mid-1; lo>=0; --lo) {
            const int hi = mid + mid - lo + 1;
            if (hi > N) continue;

            if (lo + 1 < hi - 1 && A[lo] == A[hi-1]) {
                cost[lo][hi] = cost[lo+1][hi-1];
            } else if (lo + 2 < hi - 2 && A[lo] == A[hi - 2] && A[lo + 1] == A[hi - 1]) {
                cost[lo][hi]
            }
            } else {
                int i = lower_bound(bad[0].begin(), bad[0].end(), lo) - bad[0].begin();
                int j = lower_bound(bad[1].begin(), bad[1].end(), lo) - bad[1].begin();

                bool swap_mid = (bad[0].size() ^ bad[1].size() ^ i ^ j) & 1;

                if (swap_mid) bad[A[mid]].push_back(mid);

                //cerr << lo << ' ' << mid << ' ' << hi << ' ' << i << ' ' << j << endl;
                //for (const int x: bad[0]) cerr << x << ' ';
                //cerr << endl;
                //for (const int x: bad[1]) cerr << x << ' ';
                //cerr << endl << endl << endl;;

                for (; i < bad[0].size() && j < bad[1].size(); ++i, ++j) {
                    cost[lo][hi] += abs(bad[0][i] - bad[1][j]);
                }
                for (; i < bad[0].size(); i+=2) {
                    //assert(i+1 < bad[0].size());
                    const int a = bad[0][i], b = bad[0][i+1];
                    cost[lo][hi] += (hi - (b - lo) - 1) - a;
                }
                for (; j < bad[1].size(); j+=2) {
                    //assert(j+1 < bad[1].size());
                    const int a = bad[1][j], b = bad[1][j+1];
                    cost[lo][hi] += (hi - (b - lo) - 1) - a;
                }

                if (swap_mid) bad[A[mid]].pop_back();
            }

            //assert(cost[lo][hi] == solve(lo, hi));
            ans += cost[lo][hi];
        }
    }
    
    //cerr << ans << endl;

    //even
    for (int mid=0; mid<N; ++mid) {
        bad[0].clear();
        bad[1].clear();
        for (int i=mid-1; i>=0 && mid+mid-i-1 < N; --i) {
            if (A[i] != A[mid+mid-i-1]) {
                bad[A[i]].push_back(i);
            }
        }
        reverse(bad[0].begin(), bad[0].end());
        reverse(bad[1].begin(), bad[1].end());

        for (int lo = mid-1; lo>=0; --lo) {
            const int hi = mid + mid - lo;
            if (hi > N) continue;

            if (lo + 1 < hi - 1 && A[lo] == A[hi-1]) {
                cost[lo][hi] = cost[lo+1][hi-1];
            } else {
                int i = lower_bound(bad[0].begin(), bad[0].end(), lo) - bad[0].begin();
                int j = lower_bound(bad[1].begin(), bad[1].end(), lo) - bad[1].begin();

                //cerr << lo << ' ' << mid << ' ' << hi << ' ' << i << ' ' << j << endl;
                //for (const int x: bad[0]) cerr << x << ' ';
                //cerr << endl;
                //for (const int x: bad[1]) cerr << x << ' ';
                //cerr << endl << endl << endl;;

                if ((bad[0].size() ^ bad[1].size() ^ i ^ j) & 1) {
                    cost[lo][hi] = -1;
                } else {
                    for (; i < bad[0].size() && j < bad[1].size(); ++i, ++j) {
                        cost[lo][hi] += abs(bad[0][i] - bad[1][j]);
                    }
                    for (; i < bad[0].size(); i+=2) {
                        //assert(i+1 < bad[0].size());
                        const int a = bad[0][i], b = bad[0][i+1];
                        cost[lo][hi] += (hi - (b - lo) - 1) - a;
                    }
                    for (; j < bad[1].size(); j+=2) {
                        //assert(j+1 < bad[1].size());
                        const int a = bad[1][j], b = bad[1][j+1];
                        cost[lo][hi] += (hi - (b - lo) - 1) - a;
                    }
                }
            }

            //assert(cost == solve(lo, hi));
            ans += cost[lo][hi];
        }
    }
    
    //long long ans2 = 0;
    //for (int i=0; i<N; ++i) { for (int j=i; j<N; ++j) { ans2 += solve(i, j+1); } }
    //if (ans != ans2) { cerr << ans << ' ' << ans2 << endl; assert(0); }

    cout << ans << '\n';
}
/*
GGH
*/
