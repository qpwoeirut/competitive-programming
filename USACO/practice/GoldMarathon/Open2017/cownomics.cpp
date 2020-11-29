#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 505;
const ll BASE = 5;
const int MCT = 1;
const ll MOD[MCT] = {(ll)1e9 + 7};//, (ll)1e9 + 9, (ll)1e9 + 21, (ll)1e9 + 33};

typedef array<ll, MCT> subhash;

int N, M;
string A[MN], B[MN];

ll to_int(const char& c) {
    if (c == 'A') return 1;
    if (c == 'C') return 2;
    if (c == 'G') return 3;
    if (c == 'T') return 4;
    assert(false);
}

ll pw[MN][MCT];

struct Hash {
    subhash val[MN];

    Hash() {}
    Hash(const string& s) {
        for (int m=0; m<MCT; ++m) {
            val[0][m] = 0;
            for (int i=0; i<M; ++i) {
                val[i+1][m] = (val[i][m] * BASE + to_int(s[i])) % MOD[m];
            }
        }
    }

    subhash substr(const int start, const int end) {
        subhash ret;
        for (int m=0; m<MCT; ++m) {
            ret[m] = (val[end][m] - ((val[start][m] * pw[end-start][m]) % MOD[m]) + MOD[m]) % MOD[m];
        }
        return ret;
    }

    void print() {
        for (int i=0; i<=M; ++i) {
            for (int m=0; m<MCT; ++m) { cerr << val[i][m] << ' '; }
            cerr << endl;
        }
    }
};

Hash ha[MN], hb[MN];

bool works(const int start, const int end) {
    if (end > M) return true;
    set<subhash> spots;
    for (int i=0; i<N; ++i) {
        spots.insert(ha[i].substr(start, end));
        //cerr << ha[i].substr(start, end)[0] << endl;
    }
    for (int i=0; i<N; ++i) {
        //cerr << hb[i].substr(start, end)[0] << endl;
        if (spots.count(hb[i].substr(start, end))) {
            //cerr << start << ' ' << end << " false\n";
            return false;
        }
    }
    //cerr << start << ' ' << end << " true\n";
    return true;
}

int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        ha[i] = Hash(A[i]);
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
        hb[i] = Hash(B[i]);
    }

    for (int m=0; m<MCT; ++m) {
        pw[0][m] = 1;
        for (int i=1; i<=M; ++i) {
            pw[i][m] = (pw[i-1][m] * BASE) % MOD[m];
        }
    }

    int ans = M;
    for (int i=0; i<M; ++i) {
        int lo = 1, hi = M;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (works(i, i+mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        //cerr << i << ' ' << i+lo << endl;

        if (i+lo <= M) {
            ans = min(ans, lo);
        }
    }

    cout << ans << endl;
}
