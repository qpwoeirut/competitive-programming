#include <bits/stdc++.h>

using namespace std;

const int MN = 502;

int R, C;
string G[MN];

int h_pal[MN][MN];
int v_pal[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> R >> C;
    for (int r=0; r<R; ++r) {
        cin >> G[r];
    }

    for (int r=0; r<R; ++r) {
        for (int c=0; c<C; ++c) {
            int h_len = 0;
            for (int l=0; l<=c && c+l<C; ++l) {
                if (G[r][c - l] != G[r][c + l]) break;
                h_len = max(h_len, 2 * l + 1);
            }
            for (int l=0; l<=c && c+l+1<C; ++l) {
                if (G[r][c - l] != G[r][c + l + 1]) break;
                h_len = max(h_len, 2 * l + 2);
            }

            int c0 = c - (h_len - 1) / 2;
            for (int i=0; i<h_len; ++i) {
                h_pal[r][c0 + i] = max(h_pal[r][c0 + i], h_len);
            }
        }
        for (int c=0; c<C; ++c) {
            int v_len = 0;
            for (int l=0; l<=r && r+l<R; ++l) {
                if (G[r - l][c] != G[r + l][c]) break;
                v_len = max(v_len, 2 * l + 1);
            }
            for (int l=0; l<=r && r+l+1<R; ++l) {
                if (G[r - l][c] != G[r + l + 1][c]) break;
                v_len = max(v_len, 2 * l + 2);
            }
            int r0 = r - (v_len - 1) / 2;
            for (int i=0; i<v_len; ++i) {
                v_pal[r0 + i][c] = max(v_pal[r0 + i][c], v_len);
            }
        }
    }

    int ans = 0;
    for (int r=0; r<R; ++r) {
        for (int c=0; c<C; ++c) {
            ans = max(ans, h_pal[r][c] * v_pal[r][c]);
        }
    }

    cout << ans << endl;
}
