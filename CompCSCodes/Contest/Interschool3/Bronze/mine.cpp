//mine.cpp created at 02/04/21 19:13:24

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pll;

const int MN = 102;
const ll INIT = 1001001001;

bool chmn(ll& a, const ll b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

ll N, M, K;
char L;
ll r, c, mr, mc;
string G[MN];

bool visited[MN][MN];
ll brute() {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            visited[i][j] = false;
        }
    }

    pll cur(r, c);
    ll k = K;
    ll ans = 0;
    while (k > 0) {
        if (visited[cur.fi][cur.se] && k == K) {
            return -1;
        }
        ++ans;
        if (G[cur.fi][cur.se] == L) {
            --k;
            if (k == 0) break;
        }

        ++ans;
        visited[cur.fi][cur.se] = true;

        cur.fi += mr;
        cur.fi %= N;
        cur.se += mc;
        cur.se %= M;
    }

    //cerr << "brute: " << ans << endl;
    return ans;
}

ll val[MN][MN];
pll nxt[MN][MN];
ll solve() {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            val[i][j] = G[i][j] == L ? 0 : INIT;
            nxt[i][j] = pll(i, j);
        }
    }
    bool change = false;
    for (int k=0; k<N*M; ++k) {
        change = false;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                const int nr = i + mr >= N ? i + mr - N : i + mr;
                const int nc = j + mc >= M ? j + mc - M : j + mc;
                assert(0 <= nr && nr < N);
                assert(0 <= nc && nc < M);
                if (chmn(val[i][j], val[nr][nc] + 1)) {
                    nxt[i][j] = nxt[nr][nc];
                    change = true;
                }
            }
        }
    }
    assert(change == false);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (val[i][j] != INIT) {
                assert(val[i][j] < N*M);
                assert(G[nxt[i][j].fi][nxt[i][j].se] == L);
            }
        }
    }
    //for (int i=0; i<N; ++i) { for (int j=0; j<M; ++j) { cerr << val[i][j] << ' '; } cerr << endl; }
    //for (int i=0; i<N; ++i) { for (int j=0; j<M; ++j) { cerr << nxt[i][j].fi << ' ' << nxt[i][j].se << "   "; } cerr << endl; }

    ll ans = K - 1;
    pll cur(r, c);
    for (int i=0; i<K; ++i) {
        //cerr << cur.fi << ' ' << cur.se << ' ' << ans << endl;
        if (G[cur.fi][cur.se] != L) {
            if (val[cur.fi][cur.se] >= INIT) {
                return -1;
            }
            ans += val[cur.fi][cur.se] * 2;
            cur = nxt[cur.fi][cur.se];
        }
        assert(0 <= cur.fi && cur.fi < N);
        assert(0 <= cur.se && cur.se < M);
        assert(G[cur.fi][cur.se] == L);
        ++ans;
        cur.fi = cur.fi + mr >= N ? cur.fi + mr - N : cur.fi + mr;
        cur.se = cur.se + mc >= M ? cur.se + mc - M : cur.se + mc;
        assert(0 <= cur.fi && cur.fi < N);
        assert(0 <= cur.se && cur.se < M);
    }
    assert(ans <= K*N*M*2);

    return ans;
}

void print_answer(ll ans) {
    if (ans == -1) {
        cout << "-1 -1 -1" << endl;
        return;
    }
    const ll answer = ans;
    const ll seconds = ans % 60;
    ans /= 60;
    const ll minutes = ans % 60;
    ans /= 60;
    const ll hours = ans;

    cout << hours << ' ' << minutes << ' ' << seconds << endl;
    assert((((hours * 60) + minutes) * 60) + seconds == answer);
}

void test() {
    const string chars = "abc";
    for (N=1; N<=10; ++N) {
        for (M=1; M<=10; ++M) {
            for (K=1; K<=50; ++K) {
                cout << N << ' ' << M << ' ' << K << endl;
                for (int t=0; t<10000; ++t) {
                    for (int i=0; i<N; ++i) {
                        G[i] = string(M, '?');
                        for (int j=0; j<M; ++j) {
                            G[i][j] = chars[rand() % chars.size()];
                        }
                    }
                    L = chars[rand() % chars.size()];
                    r = rand() % int(1e5);
                    c = rand() % int(1e5);
                    mr = rand() % int(1e5);
                    mc = rand() % int(1e5);

                    r %= N;
                    c %= M;
                    mr %= N;
                    mc %= M;

                    const ll sans = solve();
                    const ll bans = brute();
                    if (sans != bans) {
                        cout << sans << ' ' << bans << endl;
                        cout << N << ' ' << M << ' ' << K << ' ' << L << endl;
                        cout << r << ' ' << c << ' ' << mr << ' ' << mc << endl;
                        for (int i=0; i<N; ++i) {
                            cout << G[i] << endl;
                        }
                        cout << endl;
                    }
                    assert(sans == bans);
                }
            }
        }
    }
}

int main() {
    //test(); return 0;
    freopen("mine.in", "r", stdin);
    freopen("mine.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K >> L;
    assert(N <= 100);
    assert(M <= 100);
    assert(K <= 1e8);
    assert(isalpha(L) && islower(L));
    cin >> r >> c >> mr >> mc;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
        assert(G[i].size() == M);
    }

    --r; --c;
    r %= N;
    c %= M;
    mr %= N;
    mc %= M;

    ll sans = solve();
    //ll bans = brute();
    //assert(sans == bans);

    print_answer(sans);
    return 0;
}

