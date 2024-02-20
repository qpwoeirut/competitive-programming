#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back

#define x first
#define y second

#define p1 first
#define p2 second

typedef pair<int,int> pt;
typedef pair<pt,pt> line;

const int MN = 41;
const int MOD = 1e9 + 7;

int N;
pt A[MN];

int ccw(const pt& a, const pt& b, const pt& c) {
    if (a == b || a == c || b == c) return 0;
    int dx1 = b.x - a.x;
    int dy1 = b.y - a.y;
    int dx2 = c.x - a.x;
    int dy2 = c.y - a.y;

    if (dx1 * dy2 > dx2 * dy1) return -1;
    else if (dx1 * dy2 < dx2 * dy1) return 1;
    else assert(0);
}

bool intersects(const line& l1, const line& l2) {
    return ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2) == -1 && 
           ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2) == -1;
}

bool works() {
    vector<line> lines;
    lines.eb(A[0], A[1]);
    lines.eb(A[1], A[2]);
    lines.eb(A[2], A[0]);

    for (int i=3; i<N; ++i) {
        int ct = 0;
        for (int j=0; j<i; ++j) {
            const line cur_line(A[j], A[i]);
            bool ok = true;
            for (const line& ln: lines) {
                if (intersects(ln, cur_line)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ++ct;
                lines.pb(cur_line);
            }
        }
        assert(ct <= 3);
        if (ct < 3) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
    }

    int ans = 0;
    sort(A, A+N);
    do {
        if (works()) {
            //for (int i=0; i<N; ++i) { cerr << A[i].x << ' ' << A[i].y << "   "; } cerr << endl;
            ++ans;
        }
    } while (next_permutation(A, A+N));

    cout << ans << '\n';
}
