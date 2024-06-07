#include <bits/stdc++.h>

using namespace std;

const int MN = 251;
int G[MN][MN];
int rsum[MN][MN];
int csum[MN][MN];

const int INIT = MN * 10;

struct Rect {
    int r1, c1, r2, c2;
    int cost() {
        return 2 * ((r2 - r1 + 1) + (c2 - c1 + 1));
    }
};
Rect rect[MN * MN * 10];
Rect srect[MN * MN * 10];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int R, C;
    int N, K;
    cin >> R >> C;
    cin >> N >> K;

    for (int i=0; i<N; ++i) {
        int r_i, c_i;
        cin >> r_i >> c_i;
        ++G[r_i][c_i];
    }

    for (int r=1; r<=R; ++r) {
        for (int c=1; c<=C; ++c) {
            rsum[r][c] = rsum[r][c - 1] + G[r][c];
        }
    }
    for (int c=1; c<=C; ++c) {
        for (int r=1; r<=R; ++r) {
            csum[c][r] = csum[c][r - 1] + G[r][c];
        }
    }

    int n_rect = 0;
    for (int c1=1; c1<=C; ++c1) {  // [c1, c2]
        for (int c2=c1; c2<=C; ++c2) {
            int r1 = 1;
            int total = 0;
            for (int r2=1; r2<=R; ++r2) {  // [r1, r2]
                const int row = rsum[r2][c2] - rsum[r2][c1 - 1];
                total += row;

                while (total > K || (r1 < r2 && rsum[r1][c2] - rsum[r1][c1 - 1] == 0)) {
                    total -= rsum[r1][c2] - rsum[r1][c1 - 1];
                    ++r1;
                }
                
                if (total == K && row > 0) {
                    const int col1 = csum[c1][r2] - csum[c1][r1 - 1];
                    const int col2 = csum[c2][r2] - csum[c2][r1 - 1];
                    if (col1 > 0 && col2 > 0) {
                        rect[n_rect].r1 = r1;
                        rect[n_rect].c1 = c1;
                        rect[n_rect].r2 = r2;
                        rect[n_rect].c2 = c2;
                        ++n_rect;
                    }
                }
            }
        }
    }

    int ans = INIT;

    copy(rect, rect+n_rect, srect);
    sort(rect, rect+n_rect, [](const Rect& a, const Rect& b) {
        return a.r1 < b.r1;
    });
    sort(srect, srect+n_rect, [](const Rect& a, const Rect& b) {
        return a.r2 < b.r2;
    });
    int best = INIT;
    int s_i = 0;
    for (int i=0; i<n_rect; ++i) {
        while (s_i < n_rect && srect[s_i].r2 < rect[i].r1) {
            best = min(best, srect[s_i].cost());
            ++s_i;
        }
        ans = min(ans, best + rect[i].cost());
    }

    sort(rect, rect+n_rect, [](const Rect& a, const Rect& b) {
        return a.c1 < b.c1;
    });
    sort(srect, srect+n_rect, [](const Rect& a, const Rect& b) {
        return a.c2 < b.c2;
    });
    best = INIT;
    s_i = 0;
    for (int i=0; i<n_rect; ++i) {
        while (s_i < n_rect && srect[s_i].c2 < rect[i].c1) {
            best = min(best, srect[s_i].cost());
            ++s_i;
        }
        ans = min(ans, best + rect[i].cost());
    }

    if (ans == INIT) {
        cout << "NO\n";
    } else {
        cout << ans << '\n';
    }
}
