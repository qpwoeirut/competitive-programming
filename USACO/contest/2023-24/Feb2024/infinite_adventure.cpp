#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
using ll=long long;

//const int MN = 100005;
const int MN = 2000;
const int LG = 62;

int N, Q;
int T[MN];
vector<int> C[MN];

const int MK = 50;
const int MMT = 2000;
const int MMNT = 50;

int K;
int MT, MNT;

//vector<vector<int>> inner[LG];
//vector<vector<int>> outer[LG];
int inner[LG][MK][MMT];
int outer[LG][MN][MMNT];

int hub[MN];
bitset<MN> is_hub;
int hub_of[MN];

int dest(int u, ll t, ll dt) {
    if (dt == 0) return u;
    if (is_hub[u]) {
        for (int i = LG-1; i >= 0; --i) {
            if ((1LL << i) <= dt) {
                u = inner[i][hub_of[u]][t % MT];
                dt -= 1LL << i;
                t += 1LL << i;
                break;
            }
        }
    } else {
        for (int i = LG-1; i >= 0; --i) {
            if ((1LL << i) <= dt && outer[i][u][t % MNT] != -1) {
                u = outer[i][u][t % MNT];
                dt -= 1LL << i;
                t += 1LL << i;
                break;
            }
        }
    }
    return dest(u, t, dt);
}

void build_binlift() {
    for (int i=0; i<LG; ++i) {
        for (int u=0; u<K; ++u) {
            for (int t=0; t<MT; ++t) {
                inner[i][u][t] = -1;
            }
        }
        for (int u=0; u<N; ++u) {
            for (int t=0; t<MNT; ++t) {
                outer[i][u][t] = -1;
            }
        }
    }
    for (int u=0; u<K; ++u) {
        for (int t=0; t<MT; ++t) {
            inner[0][u][t] = C[hub[u]][t % T[hub[u]]];
        }
    }
    for (int u=0; u<N; ++u) {
        for (int t=0; t<MNT; ++t) {
            if (!is_hub[u]) {
                outer[0][u][t] = C[u][t % T[u]];
            }
        }
    }

    for (int i=1; i<LG; ++i) {
        for (int u=0; u<N; ++u) {
            for (int t=0; t<MNT; ++t) {
                if (!is_hub[u]) {
                    const int v = outer[i - 1][u][t];
                    if (v != -1) {
                        outer[i][u][t] = outer[i - 1][v][(t + (1LL << (i - 1))) % MNT];
                    }
                }
            }
        }
    }

    for (int i=1; i<LG; ++i) {
        for (int u=0; u<K; ++u) {
            for (int t=0; t<MT; ++t) {
                inner[i][u][t] = dest(inner[i - 1][u][t], t + (1LL << (i - 1)), 1LL << (i - 1));
            }
        }
    }
    
    //cerr << endl;
    //cerr << K << ' ' << MT << ' ' << MNT << endl;
    //for (int i=0; i<3; ++i) {
    //    for (int t=0; t<8; ++t) {
    //        for (int u=0; u<N; ++u) {
    //            if (is_hub[u]) {
    //                cerr << i << ' ' << u << ' ' << t << " i: " << inner[i][hub_of[u]][t] << endl;
    //            } else {
    //                cerr << i << ' ' << u << ' ' << t << " o: " << outer[i][u][t] << endl;
    //            }
    //        }
    //    }
    //}
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;

    for (int i=0; i<N; ++i) {
        cin >> T[i];
    }
    for (int i=0; i<N; ++i) {
        C[i] = vector<int>(T[i]);
        for (int j=0; j<T[i]; ++j) {
            cin >> C[i][j]; --C[i][j];
        }
    }

    vector<pii> t_idx(N);
    for (int i=0; i<N; ++i) {
        t_idx[i] = pii(T[i], i);
    }
    sort(t_idx.begin(), t_idx.end(), greater<pii>());

    K = min(N - 1, MK);
    MT = t_idx[0].first;
    MNT = t_idx[K].first;

    is_hub.reset();
    fill(hub_of, hub_of+N, -1);
    for (int i=0; i<K; ++i) {
        hub[i] = t_idx[i].second;
        is_hub[hub[i]] = true;
        hub_of[hub[i]] = i;
    }

    //for (int i=0; i<LG; ++i) {
    //    inner[i] = vector<vector<int>>(K, vector<int>(MT));
    //    outer[i] = vector<vector<int>>(N, vector<int>(MNT));
    //}
    build_binlift();

    for (int q=0; q<Q; ++q) {
        ll v, t, dt;
        cin >> v >> t >> dt; --v;

        cout << dest(v, t, dt) + 1 << '\n';
    }
}
