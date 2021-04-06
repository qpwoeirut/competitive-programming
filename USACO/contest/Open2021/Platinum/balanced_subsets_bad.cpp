#include <bits/stdc++.h>

using namespace std;

#define sz first
#define pos second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 152;
const ll MOD = 1e9 + 7;

int N;
bool G[MN * 3][MN * 3];


stack<pii> stk;
int upd_stk(const int h, const int c) {
    int ret = 0;
    const pii cur(h, c);
    while (stk.size() > 0 && stk.top() > cur) {
        const ll width = c - stk.top().pos;
        ret += ((width * (width + 1) >> 1) * stk.top().sz) % MOD;
        if (ret >= MOD) ret -= MOD;

        stk.pop();
    }
    if (stk.empty() || stk.top().sz < h) stk.push(cur);

    return ret;
}

int clear_stk(const int mn, const int mx) {
    int ret = 0;
    while (stk.size() > 0) {
        const ll width = mx - stk.top().pos + 1;
        ret += ((width * (width + 1) >> 1) * stk.top().sz) % MOD;
        if (stk.top().pos == mn) {
            ret -= stk.top().sz;
            if (ret < 0) ret += MOD;
        }
        if (ret >= MOD) ret -= MOD;

        stk.pop();
    }

    return ret;
}

int count_rects(const int r1, const int c1, const int r2, const int c2) {
    cerr << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
    ll top = 1, lft = 1, bot = 1, rht = 1;

    for (int c=c1; c<=c2; ++c) {
        int h = 0;
        for (; h<N && G[r1-h-1][c] == true; ++h);
        top += upd_stk(h, c);
        if (top >= MOD) top -= MOD;
    }
    top += clear_stk(c1, c2);
    if (top >= MOD) top -= MOD;

    for (int c=c1; c<=c2; ++c) {
        int h = 0;
        for (; h<N && G[r2+h+1][c] == true; ++h);
        cerr << h << ' ' << c << endl;
        bot += upd_stk(h, c);
        if (bot >= MOD) bot -= MOD;
    }
    bot += clear_stk(c1, c2);
    if (bot >= MOD) bot -= MOD;

    for (int r=r1; r<=r2; ++r) {
        int w = 0;
        for (; w<N && G[r][c1-w-1] == true; ++w);
        lft += upd_stk(w, r);
        if (lft >= MOD) lft -= MOD;
    }
    lft += clear_stk(r1, r2);
    if (lft >= MOD) lft -= MOD;

    for (int r=r1; r<=r2; ++r) {
        int w = 0;
        for (; w<N && G[r][c2+w+1] == true; ++w);
        rht += upd_stk(w, r);
        if (rht >= MOD) rht -= MOD;
    }
    rht += clear_stk(r1, r2);
    if (rht >= MOD) rht -= MOD;

    int ret = (((top * bot) % MOD) * ((lft * rht) % MOD)) % MOD;
    cerr << top << ' ' << bot << ' ' << lft << ' ' << rht << ' ' << ret << endl;
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=N; i<N+N; ++i) {
        for (int j=N; j<N+N; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == 'G';
        }
    }

    int ans = 0;
    for (int r1=N; r1<N+N; ++r1) {
        for (int c1=N; c1<N+N; ++c1) {
            int mx_col = N+N;
            for (int r2=r1; r2<N+N; ++r2) {
                for (int c2=c1; c2<mx_col; ++c2) {
                    if (G[r2][c2] == false) {
                        mx_col = c2;
                        break;
                    }

                    ans += count_rects(r1, c1, r2, c2);
                    if (ans >= MOD) ans -= MOD;
                }
            }
        }
    }

    cout << ans << '\n';
}
