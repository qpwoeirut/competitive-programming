//rain_city.cpp created at 08/29/23 19:29:21

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
using ll=long long;

const int MN = 1000;
const int MOD = 1000000007;

int N;
int G[MN][MN];

bool check_inf() {
    for (int r=0; r<N; ++r) {
        bool ok = false;
        for (int c=0; c<N; ++c) {
            ok |= G[r][c] != -1;
        }
        if (!ok) return true;
    }
    for (int c=0; c<N; ++c) {
        bool ok = false;
        for (int r=0; r<N; ++r) {
            ok |= G[r][c] != -1;
        }
        if (!ok) return true;
    }
    return false;
}

void push_update(const int r, const int c, vector<pii>& updated) {
    updated.emplace_back(r, c);
    for (int d = -min(r, c); d + r < N && d + c < N; ++d) {
        if (d == 0) continue;
        if (G[r + d][c] == -1 && G[r][c + d] != -1 && G[r + d][c + d] != -1) {
            G[r + d][c] = G[r][c] + G[r + d][c + d] - G[r][c + d];
            push_update(r + d, c, updated);
        }
        if (G[r + d][c] != -1 && G[r][c + d] == -1 && G[r + d][c + d] != -1) {
            G[r][c + d] = G[r][c] + G[r + d][c + d] - G[r + d][c];
            push_update(r, c + d, updated);
        }
        if (G[r + d][c] != -1 && G[r][c + d] != -1 && G[r + d][c + d] == -1) {
            G[r + d][c + d] = G[r + d][c] + G[r][c + d] - G[r][c];
            push_update(r + d, c + d, updated);
        }
    }
}

void debug() {
        for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            cerr << G[r][c] << ' ';
        }
        cerr << endl;
    }

}

pii wild[MN * MN];
int n_wild = 0;
ll recurse(int i, const int MAX) {
    if (i == n_wild) {
        //debug();
        for (int r=1; r<N; ++r) {
            for (int c=1; c<N; ++c) {
                if (G[r][c] + G[r-1][c-1] != G[r-1][c] + G[r][c-1]) return 0;
            }
        }
        return 1;
    }

    ll ret = 0;
    vector<pii> updated;
    for (int v=0; v<=MAX; ++v) {
        G[wild[i].first][wild[i].second] = v;
        push_update(wild[i].first, wild[i].second, updated);
        ret += recurse(i + 1, MAX);
        while (updated.size() > 0) {
            G[updated.back().first][updated.back().second] = -1;
            updated.pop_back();
        }

        if (ret >= MOD) ret -= MOD;
    }
    G[wild[i].first][wild[i].second] = -1;

    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> G[i][j];
        }
    }
    if (check_inf()) {
        cout << "-1\n";
        return 0;
    }

    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            if (G[r][c] == -1) {
                for (int d = -min(r, c); d + r < N && d + c < N; ++d) {
                    if (G[r + d][c] != -1 && G[r][c + d] != -1 && G[r + d][c + d] != -1) {  // never passes if d = 0
                        G[r][c] = G[r + d][c] + G[r][c + d] - G[r + d][c + d];
                        vector<pii> vec;
                        push_update(r, c, vec);
                        break;
                    }
                }
            }
        }
    }

    int MAX = 0;
    for (int r=0; r<N; ++r) {
        int mx = 0;
        for (int c=0; c<N; ++c) {
            if (G[r][c] == -1) {
                wild[n_wild++] = pii(r, c);
            }
            mx = max(mx, G[r][c]);

        }
        MAX += mx;
    }
    //cerr << MAX << ' ' << n_wild << endl;

    if (N == 2 && n_wild > 0) {
        if (n_wild == 2) {
            if (G[0][0] != -1 && G[1][1] != -1) {
                cout << G[0][0] + G[1][1] + 1 << '\n';
            } else if (G[0][0] == -1 && G[1][1] == -1) {
                cout << G[0][1] + G[1][0] + 1 << '\n';
            } else {
                cout << "-1\n";
            }
        } else {
            cout << "-1\n";
        }
        return 0;
    }

    ll ans = recurse(0, MAX);
    cout << ans << '\n';
}

