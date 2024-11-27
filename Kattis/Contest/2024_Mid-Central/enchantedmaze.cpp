#include <bits/stdc++.h>

using namespace std;

const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};

const int MN = 15;
const int STATES = 2 * 2 * 2 * 2 * MN * MN * MN * MN;

struct State {
    bool a, b, c, d;
    int m_r, m_c;
    int l_r, l_c;

    State(bool _a, bool _b, bool _c, bool _d, int _m_r, int _m_c, int _l_r, int _l_c) : a(_a), b(_b), c(_c), d(_d), m_r(_m_r), m_c(_m_c), l_r(_l_r), l_c(_l_c) {}
    State(int val) {
        l_c = val % MN; val /= MN;
        l_r = val % MN; val /= MN;
        m_c = val % MN; val /= MN;
        m_r = val % MN; val /= MN;
        d = val & 1; val >>= 1;
        c = val & 1; val >>= 1;
        b = val & 1; val >>= 1;
        a = val & 1; val >>= 1;
        assert(val == 0);
    }
    bool move(int dir, const char G[MN][MN]) {
        m_r += chr[dir];
        m_c += chc[dir];
        l_r += chr[dir];
        l_c += chc[dir];

        bool m_moved = true;
        bool l_moved = true;

        if (obstacle(G[m_r][m_c])) {
            m_r -= chr[dir];
            m_c -= chc[dir];
            m_moved = false;
        }
        if (obstacle(G[l_r][l_c])) {
            l_r -= chr[dir];
            l_c -= chc[dir];
            l_moved = false;
        }

        if (m_moved) apply_switch(m_r, m_c, G);
        if (l_moved) apply_switch(l_r, l_c, G);

        return !invalid(m_r, m_c, G) && !invalid(l_r, l_c, G) && (m_r != l_r || m_c != l_c);
    }

    bool obstacle(char ch) const {
        return ch == '#' || 
            ((a && ch == 'a') || (!a && ch == 'A')) ||
            ((b && ch == 'b') || (!b && ch == 'B')) ||
            ((c && ch == 'c') || (!c && ch == 'C')) || 
            ((d && ch == 'd') || (!d && ch == 'D'));
    }

    void apply_switch(int row, int col, const char G[MN][MN]) {
        if (G[row][col] == '1') a = !a;
        if (G[row][col] == '2') b = !b;
        if (G[row][col] == '3') c = !c;
        if (G[row][col] == '4') d = !d;
    }

    bool invalid(int row, int col, const char G[MN][MN]) const {
        return obstacle(G[row][col]) || G[row][col] == '*';
    }

    int pack() const {
        int val = a;
        val = (val << 1) | b;
        val = (val << 1) | c;
        val = (val << 1) | d;

        val = (val * MN) + m_r;
        val = (val * MN) + m_c;
        val = (val * MN) + l_r;
        val = (val * MN) + l_c;
        return val;
    }

    bool done(const char G[MN][MN]) const {
        return G[l_r][l_c] == 'E' && G[m_r][m_c] == 'E';
    }
};

bitset<STATES> seen;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int R, C;
    cin >> R >> C;

    char G[MN][MN];

    for (int r=0; r<=R+1; ++r) {
        for (int c=0; c<=C+1; ++c) {
            G[r][c] = '*';
        }
    }

    int m_r = -1, m_c = -1, l_r = -1, l_c = -1;
    for (int r=1; r<=R; ++r) {
        for (int c=1; c<=C; ++c) {
            cin >> G[r][c];

            if (G[r][c] == 'S') {
                if (m_r == -1) {
                    m_r = r;
                    m_c = c;
                } else {
                    l_r = r;
                    l_c = c;
                }
            }
        }
    }
    assert(m_r != -1 && m_c != -1 && l_r != -1 && l_c != -1);

    State start(false, false, false, false, m_r, m_c, l_r, l_c);
    queue<pair<State, int>> q;
    q.emplace(start, 0);
    while (q.size() > 0) {
        const State state = q.front().first;
        const int cost = q.front().second;
        q.pop();

        cerr << state.m_r << ' '<< state.m_c << ' ' << state.l_r << ' ' << state.l_c << ' ' << cost << endl;

        if (state.done(G)) {
            cout << cost << '\n';
            return 0;
        }

        for (int d=0; d<4; ++d) {
            State nstate = state;
            if (nstate.move(d, G)) {
                if (seen[nstate.pack()]) continue;
                seen[nstate.pack()] = true;
                q.emplace(nstate, cost + 1);
            }
        }
    }

    assert(false);
}
/*
3 4
.SS.
.##.
EE..

4 4
.SS.
.##.
EE..
..#.

4 4
S.aE
Aaa.
AAA.
S1.E

5 6
S1A2B.
*****E
*****.
S3C4DE
######
*/
