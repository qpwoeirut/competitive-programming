//chess_rush.cpp created at 09/10/20 19:58:46

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

typedef long long ll;
typedef pair<ll,ll> pll;

const ll MOD = 1e9 + 7;

ll R, C;

pll solve_pawn(ll start, ll finish) {
    if (start != finish) return pll(0,0);
    return pll(R-1, 1);
}
pll solve_rook(ll start, ll finish) {
    if (start == finish) return pll(1, 1);
    return pll(2, 2);
}
pll solve_queen(ll start, ll finish) {
    if ((start == 1 && finish == R) || (start == R && finish == 1) || start == finish) {
        return pll(1, 1);
    }
    ll ways = 4;
    if ((((1+start) % 2) == ((R + finish) % 2)) && R < C+C) {
        ll right = 1 + (C - start);
        ll rleft = C - (R - right);
        if (rleft >= finish) ++ways;

        ll left = start;
        ll lright = 1 + (R - left);
        if (lright <= finish) ++ways;
    }
    if (R == C && (finish == C || finish == 1 || start == C || start == 1)) {
        ++ways;
    }
    return pll(2, ways);
}

struct Square {
    ll r, c;
    ll dist;

    Square(ll _r, ll _c, ll _dist) {
        r = _r;
        c = _c;
        dist = _dist;
    }
};

ll dp[1005][1005];
ll dist[1005][1005];
pll solve_bishop(ll start, ll finish) {
    if (((1+start) % 2) != ((R + finish) % 2)) {
        return pll(0, 0);
    }
    if (R <= 1000) {
        for (int i=0; i<=R+1; ++i) {
            for (int j=0; j<=C+1; ++j) {
                dp[i][j] = 0;
                dist[i][j] = R * C;
            }
        }

        queue<Square> q;
        for (int r=2, c=start+1; r<=R && c<=C; ++r, ++c) {
            q.push(Square(r, c, 1));
            dist[r][c] = 1;
            dp[r][c] = 1;
        }
        for (int r=2, c=start-1; r<=R && c>0; ++r, --c) {
            q.push(Square(r, c, 1));
            dist[r][c] = 1;
            dp[r][c] = 1;
        }

        while (q.size() > 0) {
            Square cur = q.front(); q.pop();

            if (cur.dist >= dist[R][finish]) break;
            assert(cur.dist == dist[cur.r][cur.c]);

            for (int r=cur.r+1, c=cur.c+1; r<=R && c<=C; ++r, ++c) {
                if (dist[r][c] > cur.dist + 1) {
                    dist[r][c] = cur.dist + 1;
                    q.push(Square(r, c, cur.dist + 1));
                }
                if (dist[r][c] == cur.dist + 1) {
                    dp[r][c] += dp[cur.r][cur.c];
                }
            }
            for (int r=cur.r+1, c=cur.c-1; r<=R && c>0; ++r, --c) {
                if (dist[r][c] > cur.dist + 1) {
                    dist[r][c] = cur.dist + 1;
                    q.push(Square(r, c, cur.dist + 1));
                }
                if (dist[r][c] == cur.dist + 1) {
                    dp[r][c] += dp[cur.r][cur.c];
                }
            }
        }
        
        return pll(dist[R][finish], dp[R][finish]);
    } else {
        return pll(0,0);
    }
}
pll solve_king(ll start, ll finish) {
    ll total = R - 1; 

    if (R <= 1000) {
        for (int i=0; i<=R+1; ++i) {
            for (int j=0; j<=C+1; ++j) {
                dp[i][j] = 0;
            }
        }
        dp[1][start] = 1;
        for (int i=2; i<=R; ++i) {
            for (int j=1; j<=C; ++j) {
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1]) % MOD;
            }
        }
        debug2(dp, R+2, C+2);
        return pll(total, dp[R][finish]);
    } else {
        return pll(total, 1);
    }
}

ll Q;
int main() {
    cin >> R >> C >> Q;

    for (int i=0; i<Q; ++i) {
        char c;
        ll start, finish;
        cin >> c >> start >> finish;

        pll ans;
        if (c == 'P') {
            ans = solve_pawn(start, finish);
        } else if (c == 'R') {
            ans = solve_rook(start, finish);
        } else if (c == 'Q') {
            ans = solve_queen(start, finish);
        } else if (c == 'B') {
            ans = solve_bishop(start, finish);
        } else if (c == 'K') {
            ans = solve_king(start, finish);
        } else assert(false);

        cout << ans.first << ' ' << ans.second << endl;
    }
}
