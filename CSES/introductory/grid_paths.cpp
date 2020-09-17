//grid_paths.cpp created at 09/05/20 21:02:24

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

#define PB push_back
#define INS insert

#define FI first
#define SE second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

void setIO(const string& filename = "") {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const int N = 7;
int A[N*N];
//ll G[MN][MN];
//set<ll> adj[MN];

bool V[N+2][N+2];

inline bool check_row(int c) {
    for (++c; c<=N; ++c) {
        if (!V[N][c]) return true;
    }
    return false;
}
inline bool check_col(int r) {
    for (--r; r>0; --r) {
        if (!V[r][N]) return true;
    }
    return false;
}
int vr[N+1], vc[N+1];
inline bool reachable(int r, int c) {
    if (V[r][c] || (r == N && c == 1)) return true;
    return !V[r-1][c] || !V[r+1][c] || !V[r][c-1] || !V[r][c+1];
}
inline bool check_neighbors(int r, int c) {
    return !reachable(r-1, c) || !reachable(r+1, c) || !reachable(r, c-1) || !reachable(r, c+1);
}
inline bool trapped(int r, int c) {
    return (V[r+1][c] && V[r-1][c] && !V[r][c+1] && !V[r][c-1]) || (!V[r+1][c] && !V[r-1][c] && V[r][c+1] && V[r][c-1]);
}

int recurse(int idx, int r, int c) {
    if (48 - idx < N-r + c-1 ||  V[r][c]) {
        return 0;
    }
    if (idx == 48) {
        return 1;
    }
    if (r == N && c == 1) {
        return 0;
    }

    V[r][c] = true;
    ++vr[r];++vc[c];
    int ret = 0;
    if ((r == N && (vc[N] < N || check_row(c))) || (c == N && (vr[1] < N || check_col(r))) || trapped(r, c) || check_neighbors(r, c)) {
        // do nothing
    } else if (A[idx] != -1) {
        if ((r != N || A[idx] != 1) && (c != N || A[idx] != 0)) {
            ret += recurse(idx+1, r + chr[A[idx]], c + chc[A[idx]]);
        }
    } else {
        if (c < N) ret += recurse(idx+1, r-1, c);
        if (r < N) ret += recurse(idx+1, r, c+1);
        ret += recurse(idx+1, r+1, c) + recurse(idx+1, r, c-1);
    }
    V[r][c] = false;
    --vr[r];--vc[c];

    return ret;
}
        
int main() {
    setIO();
    
    string s;
    cin >> s;
    for (int i=0; i<sz(s); ++i) {
        if (s[i] == 'U') {
            A[i] = 0;
        } else if (s[i] == 'R') {
            A[i] = 1;
        } else if (s[i] == 'D') {
            A[i] = 2;
        } else if (s[i] == 'L') {
            A[i] = 3;
        } else A[i] = -1;
    }
    for (int i=0; i<=N+1; i++) {
        V[i][0] = V[i][N+1] = V[0][i] = V[N+1][i] = true;
    }

    cout << recurse(0, 1, 1) << endl;
}
