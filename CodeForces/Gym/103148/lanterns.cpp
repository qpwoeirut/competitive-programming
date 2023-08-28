//lanterns.cpp created at 08/29/21 19:23:12

#include <bits/stdc++.h>

using namespace std;

const int MN = 300;//2000;
const int INIT = 2001001001;

struct Lantern {
    int pos, cost;
    int lo, hi;
};

int N, K;
int A[MN];
Lantern lantern[MN];

int dp[MN][MN][MN];

inline void chmn(int& a, const int b) {
    if (a>b) a=b;
}
// if part of interval 1 is in interval 2
bool overlap(const int lo1, const int hi1, const int lo2, const int hi2) {
    return (lo2 <= lo1 && lo1 <= hi2) || (lo2 <= hi1 && hi1 <= hi2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;

    assert(N <= MN);
    
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        --A[i];
    }
    for (int i=0; i<K; ++i) {
        cin >> lantern[i].pos >> lantern[i].cost >> lantern[i].lo >> lantern[i].hi;
        --lantern[i].pos;
        --lantern[i].lo;
        --lantern[i].hi;
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            for (int k=0; k<N; ++k) {
                dp[i][j][k] = INIT;
            }
        }
    }
    dp[0][N-1][0] = 0;

    for (int lo=0; lo<N; ++lo) {
        for (int hi=N-1; hi>=lo; --hi) {
            for (int i=0; i<N; ++i) {
                if (lo > A[i] || A[i] > hi) continue;
                if (i > 0 && lo <= A[i-1] && A[i-1] <= hi) {
                    dp[lo][hi][i] = dp[lo][hi][i-1];
                    continue;
                }

                int j = i;
                while (j+1 < N && lo <= A[j+1] && A[j+1] <= hi) ++j;

                for (int k=0; k<K; ++k) {
                    if (i <= lantern[k].pos && lantern[k].pos <= j && overlap(lo, hi, lantern[k].lo, lantern[k].hi)) {
                        chmn(dp[lo][hi][i], dp[min(lo, lantern[k].lo)][max(hi, lantern[k].hi)][i] + lantern[k].cost);
                    }
                }
                
                //cerr << lo << ' ' << hi << ' ' << i << ' ' << j << ' ' << dp[lo][hi][i] << endl;
            }
        }
    }

    //for (int lo=0; lo<N; ++lo) { for (int hi=lo; hi<N; ++hi) { for (int i=0; i<N; ++i) {
    //            cerr << "lo,hi,i,dp: " << lo << ' ' << hi << ' ' << i << ' ' << dp[lo][hi][i] << endl; } } }

    for (int i=0; i<K; ++i) {
        const int ans = dp[lantern[i].lo][lantern[i].hi][lantern[i].pos];
        cout << (ans == INIT ? -1 : ans + lantern[i].cost) << '\n';
    }
}
/*
3 2
1 2 3
3 1 1 2
3 2 2 3
*/
