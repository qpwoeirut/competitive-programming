//camp.cpp created at 10/01/20 18:52:16

#include <bits/stdc++.h>

using namespace std;

const int MN = 1005;

int R, C, L, W, N;
int height[MN][MN];
int psum[MN][MN];

struct Req {
    int r, c;
    int h, w;
    bool vert, flip;
};

Req req[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> R >> C;
    for (int i=1; i<=R; ++i) {
        for (int j=1; j<=C; ++j) {
            cin >> height[i][j];
            psum[i][j] = height[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
        }
    }

    cin >> L >> W;
    cin >> N;
    for (int i=1; i<=N; ++i) {
        cin >> req[i].r >> req[i].c >> req[i].h >> req[i].w >> req[i].vert >> req[i].flip;
        --req[i].r; --req[i].c; --req[i].h; --req[i].w;
    }

    int ans_r = 0, ans_c = 0, score = 0;
    for (int i=1; i+L-1<=R; ++i) {
        for (int j=1; j+W-1<=C; ++j) {
            int cur = 0;
            for (int k=1; k<=N; ++k) {
                int r1 = req[k].r + i;
                int c1 = req[k].c + j;
                int r2 = r1 + req[k].h, c2 = c1 + req[k].w;
                int r3 = r2, c3 = c2;
                if (req[k].vert) {
                    r3 += req[k].h + 1;
                } else {
                    c3 += req[k].w + 1;
                }

                --r1; --c1;
                //cerr << r1 << ',' << c1 << ' ' << r2 << ',' << c2 << ' ' << r3 << ',' << c3 << endl;
                int s1 = psum[r2][c2] - psum[r2][c1] - psum[r1][c2] + psum[r1][c1];
                int s2 = psum[r3][c3] - psum[r3][c1] - psum[r1][c3] + psum[r1][c1];

                if (((s1 << 1) < s2) ^ req[k].flip) {
                    //cerr << i << ' ' << j << ' ' << k << endl;
                    ++cur;
                } else if (cur + N < k + score) break;
            }
            //cerr << i << ',' << j << ' ' << cur << endl << endl;;
            if (score < cur) {
                score = cur;
                ans_r = i;
                ans_c = j;
            }
        }
    }

    cout << ans_r << ' ' << ans_c << endl;
}
/*
5 6
2 2 2 2 2 2
2 6 6 4 3 2
3 5 8 7 7 4
4 6 8 9 8 6
5 7 8 8 8 7
3 5
3
1 1 1 3 1 0
2 2 2 2 0 0
2 4 1 1 1 1

1,1 -> 100
1,2 -> 100
2,1 -> 110
2,2 -> 100
3,1 -> 111
3,2 -> 101
*/
