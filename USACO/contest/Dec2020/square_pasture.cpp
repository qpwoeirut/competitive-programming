#include <bits/stdc++.h>

using namespace std;

const int MN = 205;

#define x first
#define y second

typedef pair<int,int> pt;

int N;
pt A[MN];
bool used[MN];

inline const bool cmp_y(const pt& a, const pt& b) {
    if (a.y == b.y) return a.x < b.y;
    return a.y < b.y;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
    }
    sort(A, A+N);
    int ans = 1;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            const pt top = A[i];
            const pt bot = A[j];
            if (top.y < bot.y) continue;

            const int sz = top.y - bot.y;
            const int L = min(top.x, bot.x);
            const int R = max(top.x, bot.x);

            map<int,int> in;
            for (int k=0; k<N; ++k) {
                if (A[k].y < bot.y || top.y < A[k].y) {
                    continue;
                }
                in[A[k].x] = k;
            }
            fill(used, used+N, false);
            for (int k=0; k<N; ++k) {
                if (A[k].y < bot.y || top.y < A[k].y) {
                    continue;
                }
                if (R <= A[k].x && A[k].x <= L + sz) { // right side
                    ++ans;
                    const int lft = in.lower_bound(A[k].x - sz)->second;
                    used[lft] = true;
                    cerr << i << ' ' << j << ' '<< k << " 1" << endl;
                    //cerr << R << ' ' << A[k].x << ' ' << L+sz << endl;
                }
            }
            for (int k=0; k<N; ++k) {
                if (A[k].y < bot.y || top.y < A[k].y || used[k]) {
                    continue;
                }
                if (R - sz <= A[k].x && A[k].x <= L) { // left side
                    ++ans;
                    cerr << i << ' ' << j << ' '<< k << " 2" << endl;
                }
            }
        }
    }

    sort(A, A+N, cmp_y);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            const pt lft = A[i];
            const pt rht = A[j];
            if (lft.x > rht.x) continue;

            const int sz = rht.x - lft.x;
            const int B = min(lft.y, rht.y);
            const int T = max(lft.y, rht.y);

            map<int,int> in;
            for (int k=0; k<N; ++k) {
                if (A[k].x < lft.x || rht.x < A[k].x) {
                    continue;
                }
                in[A[k].y] = k;
            }
            fill(used, used+N, false);
            for (int k=0; k<N; ++k) {
                if (A[k].x < lft.x || rht.x < A[k].x) {
                    continue;
                }
                if (T <= A[k].y && A[k].y <= B + sz && in.count(A[k].y - sz) == 0) { // top side
                    ++ans;
                    const int bot = in.lower_bound(A[k].y - sz)->second;
                    used[bot] = true;
                    cerr << i << ' ' << j << ' '<< k << " 3" << endl;
                }
            }
            for (int k=0; k<N; ++k) {
                if (A[k].x < lft.x || rht.x < A[k].x || used[k]) {
                    continue;
                }
                if (T - sz <= A[k].y && A[k].y <= B && in.count(A[k].y + sz) == 0) { // bottom side
                    ++ans;
                    cerr << i << ' ' << j << ' '<< k << " 4" << endl;
                }
            }
        }
    }

    cout << ans << endl;
}
/*
0 0 0 1
0 1 1 1
1 1 1 1
2 1 2 1
2 1 3 1
2 1 1 2
2 2 2 1
2 3 3 1
3 3 3 1
0 1 1 3
2 1 2 3
2 1 1 4
2 3 2 4

0 0 0 1
0 1 1 1
1 1 1 1
2 1 2 1
2 1 3 1
2 1 1 2
2 2 2 1
2 3 3 1
3 3 3 1
0 1 1 3
 0 1 0 4
2 1 2 3
2 1 1 4
 2 3 3 3
2 3 2 4
*/

