#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int MN = 200'000;
const int LG = 19;

void init_sparse(int sparse[LG][MN], const vi& vals, bool is_min) {
    const int n = vals.size();
    for (int i=0; i<n; ++i) {
        sparse[0][i] = vals[i];
    }
    for (int p=0; p+1<LG; ++p) {
        for (int i=0; i<n; ++i) {
            if (is_min) sparse[p+1][i] = min(sparse[p][i], sparse[p][min(i + (1 << p), n - 1)]);
            else sparse[p+1][i] = max(sparse[p][i], sparse[p][min(i + (1 << p), n - 1)]);
        }
    }
}

vector<pii> comp;
int c_idx[MN];
int t_min[LG][MN];
int t_max[LG][MN];
int h_min[LG][MN];
int h_max[LG][MN];
int N;
void initialize(vi T, vi H) {
    N = T.size();
    const int C = H.size();

    comp.clear();
    pii cur(-1, -1);
    for (int c=0; c<=C; ++c) {
        if (c < C && T[0] > H[c]) {
            if (cur.first == -1) cur = {c, c+1};
            else cur.second = c + 1;
        } else {
            if (cur.first != -1) {
                comp.push_back(cur);
                cur = {-1, -1};
            }
        }
    }
    fill(c_idx, c_idx + C, -1);
    for (int i=0; i<comp.size(); ++i) {
        for (int c=comp[i].first; c<comp[i].second; ++c) {
            c_idx[c] = i;
        }
    }
    //cerr << "c_idx: "; for (int c=0; c<C; ++c) { cerr << c_idx[c] << ' '; } cerr << endl;

    init_sparse(t_min, T, true);
    init_sparse(t_max, T, false);
    init_sparse(h_min, H, true);
    init_sparse(h_max, H, false);
}

const int INF = 2'000'000'000;
int query(int sparse[LG][MN], int lo, int hi, bool is_min) {
    int result = is_min ? INF : -INF;
    for (int lg = LG - 1; lg >= 0; --lg) {
        if (lo + (1 << lg) <= hi) {
            result = is_min ? min(result, sparse[lg][lo]) : max(result, sparse[lg][lo]);
            lo += 1 << lg;
        }
    }
    return result;
}

bool ok(int L, int R, int i_s, int i_d) {
    int lo_s = max(comp[i_s].first, L);
    int hi_s = min(comp[i_s].second, R);
    int lo_d = max(comp[i_d].first, L);
    int hi_d = min(comp[i_d].second, R);

    //cerr << "bounds " << lo_s << ',' << hi_s << ' ' << lo_d << ',' << hi_d << endl;

    int h1 = query(h_min, lo_s, hi_s, true);
    int h2 = query(h_min, lo_d, hi_d, true);

    //cerr << "h " << h1 << ' ' << h2 << endl;

    if (h1 == INF || h2 == INF) return false;

    int worst_h = query(h_max, lo_s, hi_d, false);
    //cerr << "worst_h " << worst_h << endl;
    int lo = 0, hi = N;
    while (lo < hi) {
        const int mid = (lo + hi) / 2;
        if (query(t_max, 0, mid+1, false) <= worst_h) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    int target_row = lo;
    //cerr << "target " << target_row << endl;
    if (target_row == N) return false;

    int worst_t = query(t_min, 0, target_row + 1, true);
    //cerr << "worst_t " << worst_t << endl;
    return worst_t > max(h1, h2);
}

bool can_reach(int L, int R, int S, int D) {
    if (S > D) swap(S, D);
    ++R;
    //cerr << "\nL R S D " << L << ' ' << R << ' ' << S << ' ' << D << endl;

    int i_s = c_idx[S];
    if (i_s == -1) return false;

    int i_d = c_idx[D];
    if (i_d == -1) return false;
    
    for (int i=i_s+1; i<=i_d; ++i) {
        if (ok(L, R, i_s, i)) i_s = i;
    }
    return i_s == i_d;
}

const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};
bool brute(const vi& T, const vi& H, int S, int D) {
    if (T[0] <= H[S]) return false;
    set<pii> vis;
    queue<pii> q;
    q.emplace(0, S);
    vis.emplace(0, S);
    while (q.size() > 0) {
        pii p = q.front(); q.pop();
        if (p.first == 0 && p.second == D) return true;

        for (int d=0; d<4; ++d) {
            int nr = p.first + chr[d];
            int nc = p.second + chc[d];
            if (nr < 0 || nr >= T.size() || nc < 0 || nc >= H.size() || T[nr] <= H[nc]) continue;
            if (vis.emplace(nr, nc).second == false) continue;
            q.emplace(nr, nc);
        }
    }
    return false;
}
