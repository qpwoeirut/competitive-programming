//roads.cpp created at 09/07/20 09:44:35

#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<ll,ll> pll;

const ll MN = 100001;

struct Segment {
    pll a, b;
    Segment() {
        a = pll();
        b = pll();
    }
    Segment(pll ta, pll tb) {
        a = ta;
        b = tb;
    }
    Segment(ll ax, ll ay, ll bx, ll by) {
        a = pll(ax, ay);
        b = pll(bx, by);
    }
    void print() {
        cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << endl;
    }

    bool line(const Segment& o) {
        ll rise = b.y - a.y;
        ll run = b.x - a.x;
        ll orise = o.b.y - a.y;
        ll orun = o.b.x - a.x;

        return rise * orun == orise * run;
    }
};

inline bool cmp_seg(const Segment& a, const Segment& b) {
    if (a.a.x == b.a.x) {
        return a.a.y < b.a.y;
    }
    return a.a.x < b.a.x;
}

ll N;
Segment seg[MN];

int main() {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> seg[i].a.x >> seg[i].a.y >> seg[i].b.x >> seg[i].b.y;
        if (seg[i].a.y > seg[i].b.y) swap(seg[i].a, seg[i].b);
    }

    vector<Segment> segs, ans;
    sort(seg, seg+N, cmp_seg);
    for (int i=0; i<N; ++i) {
        if (segs.size() > 0 && seg[i].line(segs.back())) {
            ans.push_back(Segment(segs.back().b, seg[i].a));
            segs.back().b = seg[i].b;
        } else {
            segs.push_back(seg[i]);
        }
    }

    for (int i=0; i+1<segs.size(); ++i) {
        if (segs[i].line(segs[i+1])) {
            ans.push_back(Segment(segs[i].b, segs[i+1].a));
        } else {
            ans.push_back(Segment(segs[i].a, segs[i+1].a));
        }
    }

    //for (int i=0; i<ans.size(); i++) {
    //    ans[i].print();
    //}

    for (int i=0; i<N-1; i++) {
        ans[i].print();
    }
}

/*
3
1 1 1 2
1 3 1 4
1 5 1 6

5
1 1 1 100
5 3 5 4
3 8 3 12
5 1000 5 2000
-1 -10 -1 40


5
1 1 2 2
3 3 10 10
4 1 7 4
-10 -20 100 90
100 200 200 300

*/
