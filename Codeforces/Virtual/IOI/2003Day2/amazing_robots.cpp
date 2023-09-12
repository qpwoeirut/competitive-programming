//amazing_robots.cpp created at 09/11/23 19:22:34

#include <bits/stdc++.h>

using namespace std;

const int MN = 20 + 2;
const int MG = 10;
const int INF = 1001001001;
const int TMOD = 12;

const int chr[4] = { 1,  0, -1,  0 };
const int chc[4] = { 0,  1,  0, -1 };
const string DIRS = "SENW";

inline int to_idx(char c) {
    if (c == 'S') return 0;
    if (c == 'E') return 1;
    if (c == 'N') return 2;
    if (c == 'W') return 3;
    assert(0);
}

struct Guard {
    int sr, sc;
    int len;
    int dir;
    
    bool catches(int r, int c, int nr, int nc, int t) const {
        int cur_dir = dir;
        int gnr = sr, gnc = sc;
        int gr = t == 0 ? sr : sr + chr[cur_dir], gc = t == 0 ? sc : sc + chc[cur_dir];
        
        t %= (len - 1) * 2;
        while (t > 0) {
            const int jump = min(t, len - 1);
            //cerr << t << ' ' << jump << endl;
            gnr += jump * chr[cur_dir];
            gnc += jump * chc[cur_dir];

            gr = gnr - chr[cur_dir];
            gc = gnc - chc[cur_dir];

            t -= jump;
            cur_dir ^= 0b10;  // flip
        }

        return (gnr == r && gnc == c && gr == nr && gc == nc) || (gnr == nr && gnc == nc);
    }
};

int R[2], C[2];
bitset<MN> G[2][MN];

struct State {
    int r[2];
    int c[2];
    int time;

    State(int r0, int c0, int r1, int c1, int _time) : time(_time) {
        r[0] = r0;
        r[1] = r1;
        c[0] = c0;
        c[1] = c1;
    }

    State move(const int dir) const {
        int nr[2] = {r[0] + chr[dir], r[1] + chr[dir]};
        int nc[2] = {c[0] + chc[dir], c[1] + chc[dir]};
        for (int m = 0; m < 2; ++m) {
            if (escaped(m) || (!escaped(nr[m], nc[m], m) && G[m][nr[m]][nc[m]])) {
                nr[m] = r[m];
                nc[m] = c[m];
            }
        }
        return State(nr[0], nc[0], nr[1], nc[1], time + 1);
    }

    bool escaped(int row, int col, int m) const {
        return row == 0 || row > R[m] || col == 0 || col > C[m];
    }

    bool escaped(const int m) const {
        return escaped(r[m], c[m], m);
    }
};

int dist[MN][MN][MN][MN][TMOD];
pair<int, char> par[MN][MN][MN][MN][TMOD];
Guard guard[2][MG];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N[2];
    int sr[2], sc[2];
    for (int m = 0; m < 2; ++m) {
        cin >> R[m] >> C[m];
        for (int r = 1; r <= R[m]; ++r) {
            for (int c = 1; c <= C[m]; ++c) {
                char ch;
                cin >> ch;
                if (ch == 'X') {
                    sr[m] = r;
                    sc[m] = c;
                }
                G[m][r][c] = ch == '#';
            }
        }

        cin >> N[m];
        for (int i = 0; i < N[m]; ++i) {
            char dir;
            cin >> guard[m][i].sr >> guard[m][i].sc >> guard[m][i].len >> dir;
            guard[m][i].dir = to_idx(dir);
        }
    }

    for (int r0 = 0; r0 < MN; ++r0) {
        for (int c0 = 0; c0 < MN; ++c0) {
            for (int r1 = 0; r1 < MN; ++r1) {
                for (int c1 = 0; c1 < MN; ++c1) {
                    for (int t = 0; t < TMOD; ++t) {
                        dist[r0][c0][r1][c1][t] = INF;
                        par[r0][c0][r1][c1][t] = pair(0, '!');
                    }
                }
            }
        }
    }

    dist[sr[0]][sc[0]][sr[1]][sc[1]][0] = 0;
    queue<State> q;
    q.emplace(sr[0], sc[0], sr[1], sc[1], 0);
    while (q.size() > 0) {
        const State cur = q.front(); q.pop();
        //cerr << cur.time << ' ' << cur.r[0] << ' ' << cur.c[0] << ' ' << cur.r[1] << ' ' << cur.c[1] << endl;

        if (cur.escaped(0) && cur.escaped(1)) {
            string history = "";

            int r0 = cur.r[0], c0 = cur.c[0], r1 = cur.r[1], c1 = cur.c[1];
            int t = cur.time;
            while (par[r0][c0][r1][c1][t % TMOD].second != '!') {
                //cerr << r0 << ' ' << c0 << ' ' << r1 << ' ' << c1 << ' ' << t << endl;
                history += par[r0][c0][r1][c1][t % TMOD].second;

                int val = par[r0][c0][r1][c1][t % TMOD].first;
                c1 = val % MN; val /= MN;
                r1 = val % MN; val /= MN;
                c0 = val % MN; val /= MN;
                r0 = val % MN; val /= MN;
                --t;
            }
            reverse(history.begin(), history.end());
            cout << history.size() << '\n';
            for (char c: history) {
                cout << c << '\n';
            }
            return 0;
        }

        for (int dir = 0; dir < 4; ++dir) {
            State nxt = cur.move(dir);
            //cerr << '\t' << nxt.time << ' ' << nxt.r[0] << ' ' << nxt.c[0] << ' ' << nxt.r[1] << ' ' << nxt.c[1] << ' ' << endl;

            bool bad = false;
            for (int m = 0; m < 2; ++m) {
                for (int i = 0; i < N[m]; ++i) {
                    bad |= guard[m][i].catches(cur.r[m], cur.c[m], nxt.r[m], nxt.c[m], nxt.time);
                }
            }
            if (!bad && dist[nxt.r[0]][nxt.c[0]][nxt.r[1]][nxt.c[1]][nxt.time % TMOD] > nxt.time) {
                dist[nxt.r[0]][nxt.c[0]][nxt.r[1]][nxt.c[1]][nxt.time % TMOD] = nxt.time;
                par[nxt.r[0]][nxt.c[0]][nxt.r[1]][nxt.c[1]][nxt.time % TMOD] = pair(((cur.r[0] * MN + cur.c[0]) * MN + cur.r[1]) * MN + cur.c[1], DIRS[dir]);
                q.push(nxt);
            }
        }
    }

    cout << "-1\n";
}

/*
5 6
##.###
#....#
#....#
#.X..#
######
2
2 2 4 E
3 5 4 W
3 3
###
#X.
###
0

5 6
##.###
#....#
#....#
#.X..#
######
2
2 3 2 E
3 4 2 W
4 4
####
#X.#
#...
####
1
3 2 3 E

3 3
###
#X.
###
0
4 4
####
#X.#
#...
####
1
3 2 3 E
*/
