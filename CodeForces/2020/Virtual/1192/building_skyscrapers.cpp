//building_skyscrapers.cpp created at 09/13/20 09:09:08

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef pair<ll,ll> pll;

void chmn(ll& a, ll b) {if (a > b) a=b;}
void chmx(ll& a, ll b) {if (a < b) a=b;}

const ll MN = 150001;

ll N, T;
const ll MX = 2005;
ll mark[MX][MX];
ll grid[MX][MX];
bool reach[MN];
bool built[MX][MX];
struct Node {
    ll r, c;
    ll num;

    Node(ll _r, ll _c, ll _num) {
        r = _r;
        c = _c;
        num = _num;
    }
    Node() {
        r = 0;
        c = 0;
        num = -1;
    }

    inline const bool can_reach() const {
        return reach[mark[r+1][c]] || reach[mark[r][c+1]] || reach[mark[r-1][c]] || reach[mark[r][c-1]];
    }
    inline const bool connected() const {
        return built[r+1][c] || built[r][c+1] || built[r-1][c] || built[r][c-1] || built[r+1][c+1] || built[r-1][c+1] || built[r-1][c-1] || built[r+1][c-1];
    }

    inline const bool operator<(const Node& other) const {
        if (connected() != other.connected()) {
            return connected();
        }
        if (can_reach() != other.can_reach()) {
            return can_reach();
        }
        return num > other.num;
    }

    void join() {
        assert(can_reach());
        
        reach[mark[r+1][c]] = reach[mark[r][c+1]] = reach[mark[r-1][c]] = reach[mark[r][c-1]] = true;
        reach[N] = false;
        mark[r][c] = 1;

        built[r][c] = true;
    }

    bool is_adj(const Node& other) {
        return abs(r - other.r) <= 1 && abs(c - other.c) <= 1;
    }
};

bool valid(ll r, ll c) {
    return 0 <= r && r < MX && 0 <= c && c < MX && mark[r][c] == 0 && grid[r][c] == 0;
}

Node nodes[MN];

ll m;
void ffill(ll r, ll c) {
    queue<pll> q;
    q.push(pll(r, c));
    while (q.size() > 0) {
        pll cur = q.front();
        q.pop();
        r = cur.FI;
        c = cur.SE;

        if (valid(r+1, c)) {
            q.push(pll(r+1, c));
            mark[r+1][c] = m;
        }
        if (valid(r, c+1)) {
            q.push(pll(r, c+1));
            mark[r][c+1] = m;
        }
        if (valid(r-1, c)) {
            q.push(pll(r-1, c));
            mark[r-1][c] = m;
        }
        if (valid(r, c-1)) {
            q.push(pll(r, c-1));
            mark[r][c-1] = m;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    cin >> N >> T;

    pll mr(1e9, -1e9), mc(1e9, -1e9);
    for (int i=0; i<N; ++i) {
        cin >> nodes[i].r >> nodes[i].c;
        nodes[i].num = i+1;

        chmn(mr.FI, nodes[i].r);
        chmx(mr.SE, nodes[i].r);
        chmn(mc.FI, nodes[i].c);
        chmx(mc.SE, nodes[i].c);
    }

    if (mr.SE - mr.FI >= N || mc.SE - mc.FI >= N) {
        cout << "NO" << endl;
        return 0;
    }

    for (int i=0; i<N; ++i) {
        nodes[i].r -= mr.FI - 1;
        nodes[i].c -= mc.FI - 1;
        grid[nodes[i].r][nodes[i].c] = nodes[i].num;
    }

    m = 1;
    for (int i=0; i<MX; ++i) {
        for (int j=0; j<MX; ++j) {
            if (mark[i][j] == 0) {
                mark[i][j] = m;
                ffill(i, j);
                ++m;
            }
        }
    }

    deque<Node> q;
    for (int i=0; i<N; ++i) {
        mark[nodes[i].r][nodes[i].c] = N;
    }
    reach[1] = true;
    for (int i=0; i<N; ++i) {
        q.push_back(nodes[i]);
    }

    for (int i=0; i<10; ++i) { for (int j=0; j<10; ++j) { cerr << grid[i][j] << ' '; } cerr << '\n'; }
    for (int i=0; i<10; ++i) { for (int j=0; j<10; ++j) { cerr << mark[i][j] << ' '; } cerr << '\n'; }

    bool start = true;
    vector<ll> ans;
    while (q.size() > 0) {
        sort(q.begin(), q.end());
        Node cur = q[0];

        for (deque<Node>::iterator it=q.begin(); it!=q.end(); ++it) {
            cerr << it->r << ' ' << it->c << ' ' << it->connected() << ' ' << it->can_reach() << endl;
        } cerr << endl;
        for (int i=0; i<=N; ++i) {
            cerr << reach[i] << ' ';
        } cerr << '\n';
        for (int i=0; i<10; ++i) { for (int j=0; j<10; ++j) { cerr << built[i][j] << ' '; } cerr << '\n'; }
        q.pop_front();

        if (!start && (!cur.connected() || !cur.can_reach())) {
            cerr << cur.connected() << ' ' << cur.can_reach() << endl;
            cout << "NO" << endl;
            return 0;
        }

        ans.push_back(cur.num);
        cur.join();
        start = false;
    }

    reverse(ans.begin(), ans.end());

    cout << "YES" << endl;
    for (int i=0; i<ans.size(); ++i) {
        cout << ans[i] << endl;
    }
}

/*
9 1
1 1
1 2
1 3
2 1
2 2
2 3
3 3
3 2
3 1

9 2
1 1
1 2
1 3
2 3
3 3
3 2
3 1
2 1
2 2

10 1
-2 0
-1 1
0 2
1 1
2 0
1 -1
0 -2
-1 -1
0 0
-3 0

5 1
-1 -1
1 -1
-1 1
1 1
0 0

*/
