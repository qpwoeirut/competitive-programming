/*
ID: zhongbr1
TASK: range
LANG: C++14
*/

//range.cpp created at 12/23/20 13:32:53

#include <bits/stdc++.h>

using namespace std;

const int MN = 255;

int N;
bool G[MN][MN];
int psum[MN][MN];

int main() {
    freopen("range.in", "r", stdin);
    freopen("range.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == '1';
        }
    }

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            psum[i][j] = psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1] + G[i][j];
        }
    }

    for (int sz=2; sz<=N; ++sz) {
        int ct = 0;
        for (int r=sz; r<=N; ++r) {
            for (int c=sz; c<=N; ++c) {
                int sum = psum[r][c] - psum[r-sz][c] - psum[r][c-sz] + psum[r-sz][c-sz];
                if (sum == sz*sz) {
                    ++ct;
                }
            }
        }

        if (ct == 0) break;
        cout << sz << ' ' << ct << '\n';
    }
}
