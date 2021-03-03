#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 4100006;
const int INIT = 1001001001;

void chmn(int& a, const int b) {if (a>b) a=b;}

pii merged[MN];
int dp[MN];
int val[MN];

int f(int i, int x) {
    return dp[x] + val[merged[i-1].se - merged[x].fi];
}

int solve(int N, int P[]) {
    fill(val, val+MN, -1);
    val[0] = 0;
    val[1] = 1;
    for (int i=2; i<=N; ++i) {
        if (i <= N/i) {
            val[i*i] = i;
        }
        if (val[i] == -1) val[i] = val[i-1];
    }

    set<pii> intervals;
    for (int i=0; i<N; ++i) {
        --P[i];
        if (i < P[i]) {
            intervals.emplace(i, P[i] + 1);
        } else if (P[i] < i) {
            intervals.emplace(P[i], i + 1);
        }
    }

    int M = 0;
    for (const pii& p: intervals) {
        if (M == 0|| p.fi > merged[M-1].se) {
            merged[M++] = p;
            continue;
        }
        merged[M-1].se = p.se;
    }

    //for (int i=0; i<M; ++i) { cerr << merged[i].fi << ' ' << merged[i].se << endl; } cerr << endl;

    fill(dp, dp+M+1, INIT);
    dp[0] = 0;
    deque<int> d; d.push_back(0);
    for (int i=1; i<=M; ++i) {
        while (d.size() >= 2 && f(i, d[0]) >= f(i, d[1])) {
            d.pop_front();
        }
        chmn(dp[i], f(i, d[0]));
        d.push_back(i);
    }

    //cerr << "dp: "; for (int i=0; i<=M; ++i) { cerr << dp[i] << ' '; } cerr << endl;
    //cerr << "val: "; for (int i=0; i<N; ++i) { cerr << val[i] << ' '; } cerr << endl;

    return dp[M];
}
/*
5
3 1 4 2 5

3
1 2 3
*/
