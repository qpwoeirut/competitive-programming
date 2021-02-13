//robotcount.cpp created at 02/05/21 22:45:31
// reeeeeeeeee 3d psums
// solved in 17 mins

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int MX = 255;

int N, Q;
int psum[MX][MX][MX];

int main() {
    freopen("robotcount.in", "r", stdin);
    freopen("robotcount.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        ++psum[x][y][z];
    }
    for (int x=1; x<MX; ++x) {
        for (int y=1; y<MX; ++y) {
            for (int z=1; z<MX; ++z) {
                psum[x][y][z] += psum[x-1][y][z] + psum[x][y-1][z] + psum[x][y][z-1]
                               - psum[x-1][y-1][z] - psum[x-1][y][z-1] - psum[x][y-1][z-1]
                               + psum[x-1][y-1][z-1];
            }
        }
    }

    for (int i=0; i<Q; ++i) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

        const int ans = psum[x2][y2][z2]
                      - psum[x1-1][y2][z2] - psum[x2][y1-1][z2] - psum[x2][y2][z1-1]
                      + psum[x1-1][y1-1][z2] + psum[x1-1][y2][z1-1] + psum[x2][y1-1][z1-1]
                      - psum[x1-1][y1-1][z1-1];
        cout << ans << '\n';
    }
}

