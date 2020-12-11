#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    bool start;
    int idx;

    inline const bool operator<(const Point& other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

const int MN = 100005;
const int MP = 200005;

int N, P;
int saved[MN];
int val[MN];
Point point[MP];

int BIT[MP];
void upd(int idx, int val) {
    for (; idx<MP; idx+=(idx & -idx)) BIT[idx] = max(BIT[idx], val);
}
int query(int idx) {
    int ret = 0;
    for (; idx>0; idx-=(idx & -idx)) ret = max(ret, BIT[idx]);
    return ret;
}

int main() {
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> P;

    vector<int> px, py;
    for (int i=0; i<P; ++i) {
        cin >> point[i << 1].x >> point[i << 1].y;
        point[i << 1].start = true;
        point[i << 1].idx = i;

        cin >> point[(i << 1) + 1].x >> point[(i << 1) + 1].y;
        point[(i << 1) + 1].start = false;
        point[(i << 1) + 1].idx = i;

        val[i] = point[(i << 1) + 1].x + point[(i << 1) + 1].y - point[i << 1].x - point[i << 1].y;

        px.push_back(point[i << 1].x);
        px.push_back(point[(i << 1) + 1].x);
        py.push_back(point[i << 1].y);
        py.push_back(point[(i << 1) + 1].y);
    }
    sort(px.begin(), px.end());
    sort(py.begin(), py.end());
    px.resize(unique(px.begin(), px.end()) - px.begin());
    py.resize(unique(py.begin(), py.end()) - py.begin());

    for (int i=0; i<P+P; ++i) {
        point[i].x = lower_bound(px.begin(), px.end(), point[i].x) - px.begin();
        point[i].y = lower_bound(py.begin(), py.end(), point[i].y) - py.begin();
    }

    sort(point, point+P+P);

    for (int i=0; i<P+P; ++i) {
        if (point[i].start) {
            saved[point[i].idx] = query(point[i].y + 1) + val[point[i].idx];
        } else {
            upd(point[i].y + 1, saved[point[i].idx]);
        }
    }

    int best = 0;
    for (int i=0; i<P; ++i) {
        best = max(best, saved[i]);
    }
    //for (int i=0; i<P; ++i) { cerr << saved[i] << ' '; } cerr << endl;
        
    cout << N + N - best << endl;
}
