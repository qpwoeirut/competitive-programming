//cf_822e.cpp created at 01/22/21 21:47:16

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;
const int MX = 33;

const int CT = 4;
const ll MOD[CT] = {(ll)1e9 + 7, (ll)1e9 + 9, (ll)1e9 + 21, (ll)1e9 + 33};
const ll BASE = 29;

ll pw[MN][CT];

struct Hash {
    vector<ll> v[CT];

    Hash(const string& s) {
        fill(v, v+CT, vector<ll>(1));
        for (int i=0; i<s.size(); ++i) {
            for (int j=0; j<CT; ++j) {
                v[j].push_back((v[j].back() * BASE + s[i] - 'a' + 1) % MOD[j]);
            }
        }
    }

    bool match(const int len, const int s1, const int s2, const Hash& h) const {
        if (s1 + len >= v[0].size() || s2 + len >= h.v[0].size()) return false;
        for (int j=0; j<CT; ++j) {
            ll h1 = (v[j][s1 + len] - v[j][s1] * pw[len][j]) % MOD[j];
            if (h1 < 0) h1 += MOD[j];
            ll h2 = (h.v[j][s2 + len] - h.v[j][s2] * pw[len][j]) % MOD[j];
            if (h2 < 0) h2 += MOD[j];

            if (h1 != h2) return false;
        }
        return true;
    }

    int lcp(const int s1, const int s2, const Hash& h) const {
        int lo = 0, hi = min(v[0].size(), h.v[0].size());
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (match(mid, s1, s2, h)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        return lo;
    }
};

void chmx(int& a, const int b) {if (a<b) a=b;}

int N, M, X;
string S, T;
int dp[MN][MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i=0; i<MN; ++i) {
        for (int j=0; j<CT; ++j) {
            pw[i][j] = i ? (pw[i-1][j] * BASE) % MOD[j] : 1;
        }
    }

    cin >> N;
    cin >> S;
    const Hash sh(S);
    cin >> M;
    cin >> T;
    const Hash th(T);
    cin >> X;

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=X; ++j) {
            chmx(dp[i+1][j], dp[i][j]);
            if (j < X) {
                chmx(dp[i][j+1], dp[i][j]);
                const int p = sh.lcp(i, dp[i][j], th);
                if (p > 0) {
                    //for (int k=0; k<p; ++k) assert(S[i+k] == T[dp[i][j] + k]);
                    chmx(dp[i+p][j+1], dp[i][j] + p);
                    //assert(i+p <= N);
                    //assert(dp[i][j] + p <= M);
                }
            }
        }
    }

    //cerr << dp[N][X] << endl;
    cout << (dp[N][X] == M ? "YES" : "NO") << endl;
}
