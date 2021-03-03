//mobile.cpp created at 02/22/21 22:23:13
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define x real()
#define y imag()
 
#define fi first
#define se second
 
typedef double dbl;
typedef complex<dbl> pt;
typedef pair<dbl,int> pdi;
 
const int MN = 1000006;
const dbl EPS2 = 1e-3;
 
int N;
dbl L;
pt A[MN];
 
pdi pts[MN << 1];

inline const bool cmp(const pdi& a, const pdi& b) {
    if (a.fi == b.fi) return a.se > b.se;
    return a.fi < b.fi;
}

// (x - a)^2 + (y - b)^2 = r^2
// (x - a)^2 = r^2 - b^2
// x - a = sqrt(r^2 - b^2)
// x = sqrt(r^2 - b^2) + a
bool check(const dbl r) {
    int M = 0;
    for (int i=0; i<N; ++i) {
        const dbl s = r*r - (A[i].y * A[i].y);
        if (s < 0) continue;
        const dbl z = sqrt(s);
        pts[M++] = pdi(A[i].x - z, 1);
        pts[M++] = pdi(A[i].x + z, -1);
    }
    sort(pts, pts+M, cmp);
    //for (int i=0; i<M; ++i) { cerr << pts[i].fi << ' ' << pts[i].se << endl; } cerr << endl;
 
    if (M == 0) return false;
    if (pts[0].fi > 0 || pts[M-1].fi <= L) return false;
    int cover = 0;
    for (int i=0; i<M; ++i) {
        cover += pts[i].se;
        if (cover == 0) {
            if (0 <= pts[i].fi && pts[i].fi <= L) return false;
            if (i+1 < M) {
                if (0 <= pts[i+1].fi && pts[i].fi <= L) return false;
            }
        }
    }
    return true;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> N >> L;
    for (int i=0; i<N; ++i) {
        int px, py;
        cin >> px >> py;
        A[i] = pt(px, py);
    }
 
    dbl lo = L / N, hi = 2.3e9;
    while (lo + EPS2 < hi) {
        dbl mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
 
    cout << fixed << setprecision(5);
    cout << (lo + hi) / 2 << endl;
}
 
/*
2 10
0 0
11 1
 
1 10
-100000 100000
 
1 1000000000
-1000000000 1000000000
*/
