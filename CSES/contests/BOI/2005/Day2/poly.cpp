#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef long double dbl;
typedef pair<dbl, dbl> point;

const int MN = 1001;
const dbl EPS = 1e-8;
const dbl EPS2 = 0.001;
const dbl PI = 3.14159265358979323;
const bool DEBUG = 0;

int N;
dbl A[MN];
dbl suf[MN];

dbl sqrt2(dbl x) {
    return sqrt(x);
    dbl lo = 0, hi = 1e9;
    while (lo + EPS < hi) {
        dbl mid = (lo + hi) / 2;
        if (mid*mid + EPS < x) {
            lo = mid + EPS;
        } else {
            hi = mid;
        }
    }
    return lo;
}

bool turn(const point& a, const point& b, const point& c) {
    dbl dx1 = a.x - b.x, dy1 = a.y - b.y;
    dbl dx2 = a.x - c.x, dy2 = a.y - c.y;
    return (dx1 * dy2) > (dx2 * dy1) + EPS;
}

vector<point> ans;
bool solve(int idx, const point& a, const point& b) {
    //cerr << idx << ' ';
    if (idx == N-1) {
        dbl dst = sqrt2(b.x * b.x + b.y * b.y);
        //cerr << "dst: " << dst << endl;
        if (DEBUG && abs(A[N-1] - dst) >= EPS2) {
            cerr << "dst: " << dst << endl;
            for (int i=0; i<N; ++i) {
                cout << A[i] << ' ';
            } cout << endl;
        }
        assert(abs(A[N-1] - dst) < EPS2);
        return true;
    }
    dbl mxd = -1;
    dbl ang = -1;
    point best;
    dbl inc = PI/18000;
    if (idx == N-2) inc /= 100;
    for (dbl angle = 0; angle < 4; angle += inc) {
        dbl dy = sin(angle) * A[idx];
        dbl dx = cos(angle) * A[idx];

        point nxt(b.x + dx, b.y + dy);
        dbl dst = sqrt2(nxt.x * nxt.x + nxt.y * nxt.y);
        //cerr << nxt.x << ' ' << nxt.y << ' ' << dst << ' ' << suf[idx] << endl;

        if (!turn(a, b, nxt)) continue;

        if (dst > suf[idx] + EPS2) continue;
        if (mxd < dst) {
            mxd = dst;
            ang = angle;
            best = nxt;
        }
    }
    const int ITERS = 10000;
    inc /= ITERS;
    for (int i=0; i<ITERS; ++i) {
        dbl cang = ang + inc; 
        dbl dy = sin(cang) * A[idx];
        dbl dx = cos(cang) * A[idx];

        point nxt(b.x + dx, b.y + dy);
        dbl dst = sqrt2(nxt.x * nxt.x + nxt.y * nxt.y);
        //cerr << nxt.x << ' ' << nxt.y << ' ' << dst << ' ' << suf[idx] << endl;

        if (!turn(a, b, nxt)) continue;

        if (dst > suf[idx] + EPS2) continue;
        if (mxd < dst) {
            mxd = dst;
            ang = cang;
            best = nxt;
        } else break;
    }
    for (int i=0; i<ITERS; ++i) {
        dbl cang = ang - inc;
        dbl dy = sin(cang) * A[idx];
        dbl dx = cos(cang) * A[idx];

        point nxt(b.x + dx, b.y + dy);
        dbl dst = sqrt2(nxt.x * nxt.x + nxt.y * nxt.y);
        //cerr << nxt.x << ' ' << nxt.y << ' ' << dst << ' ' << suf[idx] << endl;

        if (!turn(a, b, nxt)) continue;

        if (dst > suf[idx] + EPS2) continue;
        if (mxd < dst) {
            mxd = dst;
            ang = cang;
            best = nxt;
        } else break;
    }
    if (DEBUG && mxd < 0) {
        for (int i=0; i<N; ++i) {
            cout << A[i] << ' ';
        } cout << endl;
    }
    assert(mxd >= 0);
    ans.emplace_back(best);
    //cerr << best.x << ' ' << best.y << endl;
    if (solve(idx+1, b, best)) {
        return true;
    }

    return false;
}

void check() {
    for (int i=0; i<N; ++i) {
        dbl dx = ans[i].x - ans[(i+1)%N].x;
        dbl dy = ans[i].y - ans[(i+1)%N].y;
        dbl dist = sqrt2(dx*dx + dy*dy);

        assert(abs(dist - A[i]) < EPS2);

        dbl dx2 = ans[i].x - ans[(i+2)%N].x;
        dbl dy2 = ans[i].y - ans[(i+2)%N].y;
        assert(abs(dx*dy2 - dx2*dy) > EPS);
    }
}


void run() {
    sort(A, A+N);
    int sum = 0;
    suf[N-1] = 0;
    for (int i=N-1; i>=0; --i) {
        if (i) suf[i-1] = suf[i] + A[i];
        sum += A[i];
    }
    if (A[N-1] + A[N-1] >= sum) {
        if (!DEBUG) {
            cout << "NO SOLUTION" << endl;
        }
        return;
    }

    ans.clear();
    ans.push_back(point(0, 0));
    ans.push_back(point(A[0], 0));
    if (solve(1, ans[0], ans[1])) {
        if (DEBUG) {
            check();
        } else {
            for (int i=0; i<N; ++i) {
                cout << ans[i].x << ' ' << ans[i].y << endl;
            }
        }
    } else {
        assert(false);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(16);
    cerr << setprecision(16);

    if (DEBUG) {
        srand(time(0));
        //for (N=1000 - 30; N<=1000; ++N) {
        for (N=3; N<=30; ++N) {
            cout << N << endl;
            for (int t=0; t<1000; ++t) {
                if ((t & ((1 << 6) - 1)) == 0) cout << t << endl;
                for (int i=0; i<N; ++i) {
                    A[i] = rand() % 10000;
                    ++A[i];
                }
                run();
            }
        }
    } else {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        run();
    }

}
/*
4
7 4 5 4

3
74 5250 6808

4
2 2 2 3

3   
879 7545 7924

5
5258 6028 6905 7764 8915
*/
