//room_allocation.cpp created at 12/16/20 19:04:40

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

struct Point {
    int time;
    bool start;
    int idx;

    Point() {}
    Point(const int _time, const bool _start, const int _idx) {
        time = _time;
        start = _start;
        idx = _idx;
    }
    inline const bool operator<(const Point& other) {
        if (time == other.time) {
            if (start == other.start) {
                return idx < other.idx;
            }
            return start > other.start;
        }
        return time < other.time;
    }
};

int N;
Point A[MN << 1];
int ans[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        int a;
        cin >> a;
        A[i << 1] = Point(a, true, i);
        cin >> a;
        A[(i << 1) + 1] = Point(a, false, i);
    }
    sort(A, A+N+N);

    int K = 0;
    set<int> open;
    for (int i=0; i<N+N; ++i) {
        if (A[i].start) {
            if (open.empty()) {
                ++K;
                ans[A[i].idx] = K;
            } else {
                ans[A[i].idx] = *open.begin();
                open.erase(open.begin());
            }
        } else {
            open.insert(ans[A[i].idx]);
        }
    }

    cout << K << '\n';
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
