//1299b.cpp created at 02/20/21 21:14:22

#include <bits/stdc++.h>

using namespace std;

#define x real()
#define y imag()

typedef long long ll;
typedef complex<ll> pt;

const int MN = 100005;
const ll INF = 2e18 + 1;

ll N;
pt A[MN];

void chmn(ll& a, const ll b) {if (a>b) a=b;}
void chmx(ll& a, const ll b) {if (a<b) a=b;}

struct cmp {
    inline const bool operator()(const pt& a, const pt& b) const {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll mnx = INF, mny = INF;
    ll mxx = -INF, mxy = -INF;
    cin >> N;
    for (int i=0; i<N; ++i) {
        ll px, py;
        cin >> px >> py;
        px <<= 1;
        py <<= 1;
        A[i] = pt(px, py);
        chmn(mnx, A[i].x);
        chmn(mny, A[i].y);
        chmx(mxx, A[i].x);
        chmx(mxy, A[i].y);
    }
    
    pt mid((mnx + mxx) >> 1, (mny + mxy) >> 1);

    set<pt, cmp> points;
    for (int i=0; i<N; ++i) {
        A[i] -= mid;
        points.insert(A[i]);
    }

    for (int i=0; i<N; ++i) {
        if (points.count(pt(-A[i].x, -A[i].y)) == 0) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}

