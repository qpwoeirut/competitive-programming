#include <bits/stdc++.h>

using namespace std;

const int W = 1000;

int A[50][50];
int ans[50][50][4];

void solve(int d, int n) {
    for (int day=0; day<d; ++day) {
        int width = (A[day][0] + W - 1) / W;
        int cur_h = 0;
        int cur_w = 0;
        for (int i=0; i<n; ++i) {
            int height = (A[day][i] + width - 1) / width;
            if (cur_h + height > W) {
                cur_h = 0;
                cur_w += width;
                width = (A[day][i] + W - 1) / W;
                height = (A[day][i] + width - 1) / width;
            }
            ans[day][i][0] = cur_h;
            ans[day][i][1] = min(cur_w, W - (n - i));
            ans[day][i][2] = cur_h + height;
            ans[day][i][3] = min(cur_w + width, W - (n - i - 1));
            cur_h += height;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _W, D, N;
    cin >> _W >> D >> N;
    assert(W == _W);

    for (int day=0; day<D; ++day) {
        for (int i=0; i<N; ++i) {
            cin >> A[day][i];
        }
    }

    solve(D, N);

    for (int day=0; day<D; ++day) {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<4; ++j) {
                cout << ans[day][i][j] << (j < 3 ? ' ' : '\n');
            }
        }
    }
}

/*
Find better fallback method
Set widths to minimize extra space
Mix combinations of stacks
Maintain same stack widths across days
Drop a few units to make widths fit, if necessary
*/
