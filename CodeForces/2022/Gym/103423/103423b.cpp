#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

const int MN = 100005;
const int MX = 200000;

struct Line {
    int x, y, y2;
};

struct Event {
    int x;
    int type;  // 0 = start pass, 1 = blocker, 2 = end pass
    int idx;

    Event() {
        x = type = idx = 0;
    }
    Event(const int _x, const int _type, const int _idx) {
        x = _x;
        type = _type;
        idx = _idx;
    }
    inline const bool operator<(const Event& o) const {
        return x < o.x || (x == o.x && (type < o.type || (type == o.type && idx < o.idx)));
    }
};

int N, K;
Line pass[MN];
Line block[MN];

bool success[MN];

Event events[MN * 3];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    int M = 0;
    for (int i=0; i<N; ++i) {
        int x2;
        cin >> pass[i].x >> x2 >> pass[i].y;

        events[M++] = Event(pass[i].x, 0, i);
        events[M++] = Event(x2, 2, i);
    }
    for (int i=0; i<K; ++i) {
        cin >> block[i].x >> block[i].y >> block[i].y2;
        events[M++] = Event(block[i].x, 1, i);
    }
    sort(events, events+M);

    fill(success, success+N, true);
    int e_idx = 0;

    set<pii> active;
    for (int x=1; x<=MX; ++x) {
        //cerr << x << ' ' << active.size() << endl;
        //for (const pii a: active) cerr << a.first << ' ' << a.second << endl;
        //cerr << endl;
        while (e_idx < M && events[e_idx].x == x && events[e_idx].type == 0) {
            const int p_idx = events[e_idx].idx;
            const int y = pass[p_idx].y - x;
            active.emplace(y, p_idx);

            ++e_idx;
        }
        while (e_idx < M && events[e_idx].x == x && events[e_idx].type == 1) {
            const int b_idx = events[e_idx].idx;
            const int y1 = block[b_idx].y - x;
            const int y2 = block[b_idx].y2 - x;
            //cerr << b_idx << ' ' << y1 << ' ' << y2 << endl;
            auto it1 = active.lower_bound(pii(y1, 0));
            const auto it2 = active.upper_bound(pii(y2, N));
            for (; it1 != it2; it1 = active.erase(it1)) success[it1->second] = false;

            ++e_idx;
        }
        while (e_idx < M && events[e_idx].x == x && events[e_idx].type == 2) {
            const int p_idx = events[e_idx].idx;
            const int y = pass[p_idx].y - pass[p_idx].x;
            active.erase(pii(y, p_idx));

            ++e_idx;
        }
    }

    for (int i=0; i<N; ++i) {
        cout << success[i] << '\n';
    }
}
/*
1 1
1 6 4
3 6 6
*/

