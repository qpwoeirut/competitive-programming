//polygon.cpp created at 09/15/23 17:43:01

#include <bits/stdc++.h>

using namespace std;

using dbl = long double;
using pt=complex<int>;
using fpt=complex<dbl>;
#define x real()
#define y imag()

const dbl EPS = 1e-10;
const dbl PI = atan2(0, -1);

int ccw(const pt& po, const pt& _pa, const pt& _pb) {
    const pt pa = fpt(_pa.x - po.x, _pa.y - po.y);
    const pt pb = fpt(_pb.x - po.x, _pb.y - po.y);
    dbl arg_a = arg(pa - po);
    const dbl arg_b = arg(pb - po);
    if (abs(arg_a - arg_b) < EPS || abs(arg_a - arg_b - PI) < EPS || abs(arg_a - arg_b + PI) < EPS) return 0;
    if (signbit(arg_a) == signbit(arg_b)) {
        return arg_a < arg_b ? 1 : -1;
    } else {
        return arg_b < PI - arg_a ? 1 : -1;
    }
}
vector<pt> minkowski(const vector<pt>& a, const vector<pt>& b) {
    vector<pt> all_pts;
    for (const pt& pa: a) {
        for (const pt& pb: b) {
            all_pts.push_back(pa + pb);
        }
    }

    sort(all_pts.begin(), all_pts.end(), [](const pt& pa, const pt& pb) {
        return pa.x < pb.x || (pa.x == pb.x && pa.y < pb.y);
    });
    const fpt base(all_pts[0].x, all_pts[0].y);
    stable_sort(all_pts.begin() + 1, all_pts.end(), [&](const pt& pa, const pt& pb) {
        return arg(fpt(pa.x, pa.y) - base) < arg(fpt(pb.x, pb.y) - base);
    });

    vector<pt> polygon;
    for (int i=0; i<all_pts.size(); ++i) {
        while (polygon.size() >= 2 && ccw(polygon[polygon.size() - 2], polygon.back(), all_pts[i]) != 1) {
            polygon.pop_back();
        }
        if (polygon.size() < 2 || ccw(polygon[0], polygon.back(), all_pts[i]) == 1) {
            polygon.push_back(all_pts[i]);
        }
    }
    return polygon;
}

bool polygons_match(vector<pt> poly_a, vector<pt> poly_b) {
    if (poly_a.size() != poly_b.size()) return false;

    const auto cmp = [](const pt& a, const pt& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    };
    sort(poly_a.begin(), poly_a.end(), cmp);
    sort(poly_b.begin(), poly_b.end(), cmp);
    int ox = poly_a[0].x - poly_b[0].x;
    int oy = poly_a[0].y - poly_b[0].y;
    for (int i = 0; i<poly_a.size(); ++i) {
        if (poly_a[i].x - poly_b[i].x != ox || poly_a[i].y - poly_b[i].y != oy) return false;
    }
    return true;
}

const int N_ARR[12] = { 0, 5, 5, 10, 4, 6, 4, 118, 908, 119, 82, 121 };
string TEST = "05";
int N = N_ARR[5];
const int MX_ARR[10] = { 0, 3, 2600, 37, 5, 7, 12, 100, 100, 100 };
int MX;
bitset<15> G[15];

vector<pt> ans_a, ans_b;
vector<pt> target;
void recurse(vector<pt>& a, vector<pt>& b) {
    if (polygons_match(minkowski(a, b), target)) {
        if (ans_a.size() < a.size() || (ans_a.size() == a.size() && ans_b.size() > b.size())) {
            ans_a = a;
            ans_b = b;
        }

        cout << a.size() << '\n';
        for (const pt& p: a) cout << p.x << ' ' << p.y << '\n';
        cout << b.size() << '\n';
        for (const pt& p: b) cout << p.x << ' ' << p.y << '\n';
        return;
    }

    for (int px=0; px<MX; ++px) {
        for (int py=0; py<MX; ++py) {
            const pt p(px, py);
            if (a.size() < 4 && find(a.begin(), a.end(), p) == a.end()) {
                a.push_back(p);
                recurse(a, b);
                a.pop_back();
            }
            if (find(b.begin(), b.end(), p) == b.end()) {
                b.push_back(p);
                recurse(a, b);
                b.pop_back();
            }
        }
    }
}

void solve() {
    ifstream fin("tests/" + TEST);
    assert(fin.is_open());

    int _N;
    fin >> _N;
    assert(N == _N);
    target = vector<pt>(N);
    for (int i = 0; i < N; ++i) {
        int px, py;
        fin >> px >> py;
        target[i] = pt(px, py);
        G[py][px] = true;
    }

    for (int r = MX - 1; r >= -1; --r) {
        string s = r == -1 ? string(MX + 1, '-') : G[r].to_string() + "|";
        reverse(s.begin(), s.end());
        cout << s << '\n';
    }

    vector<pt> a, b;
    recurse(a, b);

    ofstream fout("out/" + TEST);
    assert(fout.is_open());
    fout << a.size() << '\n';
    for (const pt& p: a) fout << p.x << ' ' << p.y << '\n';
    fout << b.size() << '\n';
    for (const pt& p: b) fout << p.x << ' ' << p.y << '\n';
}

int main() {
    TEST = "01";
    N = N_ARR[1];
    MX = MX_ARR[1];
    solve();
    TEST = "04";
    N = N_ARR[4];
    MX = MX_ARR[4];
    solve();
    TEST = "05";
    N = N_ARR[5];
    MX = MX_ARR[5];
    solve();
    TEST = "06";
    N = N_ARR[6];
    MX = MX_ARR[6];
    solve();
}

