#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 100005;
const int INF = 1001001001;

struct Pie {
    int idx;
    int from, to;

    Pie() {
        idx = from = to = 0;
    }
    Pie(int _idx, int _from, int _to) {
        idx = _idx;
        from = _from;
        to = _to;
    }

    inline const bool operator<(const Pie& other) const {
        if (to == other.to) {
            if (from == other.from) {
                return idx < other.idx;
            }
            return from < other.from;
        }
        return to < other.to;
    }
    inline const bool operator>(const Pie& other) const {
        if (to == other.to) {
            if (from == other.from) {
                return idx > other.idx;
            }
            return from > other.from;
        }
        return to > other.to;
    }
};

int N, D;
Pie bessie[MN], elsie[MN];

int ans[MN];

int main() {
    freopen("piepie.in", "r", stdin);
    freopen("piepie.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    set<Pie, greater<Pie> > bes, els;
    cin >> N >> D;
    for (int i=0; i<N; ++i) {
        cin >> bessie[i].from >> bessie[i].to;
        bessie[i].idx = i;
        bes.insert(bessie[i]);
    }
    for (int i=0; i<N; ++i) {
        cin >> elsie[i].to >> elsie[i].from;
        elsie[i].idx = i;
        els.insert(elsie[i]);
    }

    queue<pii> q;
    for (int i=0; i<N; ++i) {
        if (bessie[i].to == 0) {
            q.emplace(i, 1);
            bes.erase(bessie[i]);
        }
        if (elsie[i].to == 0) {
            q.emplace(N+i, 1);
            els.erase(elsie[i]);
        }
    }

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();
        const int idx = cur.fi >= N ? cur.fi - N : cur.fi;
        const int dist = cur.se;
        const bool from_bessie = cur.fi < N;

        //cerr << from_bessie << ' ' << idx << ' ' << dist << endl;

        if (from_bessie) {
            ans[idx] = dist;
        }

        if (from_bessie) {
            auto it = els.lower_bound(Pie(INF, INF, bessie[idx].from));
            while (it != els.end() && it->to + D >= bessie[idx].from) {
                q.emplace(N + it->idx, dist + 1);
                it = els.erase(it);
            }
        } else {
            auto it = bes.lower_bound(Pie(INF, INF, elsie[idx].from));
            while (it != bes.end() && it->to + D >= elsie[idx].from) {
                q.emplace(it->idx, dist + 1);
                it = bes.erase(it);
            }
        }
    }

    for (int i=0; i<N; ++i) {
        if (ans[i] == 0) {
            cout << "-1\n";
        } else {
            cout << ans[i] << '\n';
        }
    }
}
