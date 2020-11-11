#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)((x).size())

typedef long long ll;

const int MN = 100001;
const int CT = 1;
//const ll MOD[CT] = {(ll)1e9 + 7, (ll)1e9+9};
const ll MOD[CT] = {(ll)1e9 + 7};
const ll BASE = 11;

int to_int[128];

struct Hash {
    ll h[CT];

    Hash() {
        fill(h, h+CT, 0);
    }
    Hash(const string& s) {
        fill(h, h+CT, 0);
        for (int i=sz(s) - 1; i>=0; --i) {
            for (int j=0; j<CT; ++j) {
                h[j] = ((h[j] * BASE) + to_int[s[i]]) % MOD[j];
            }
        }
    }
    void add(const char& c) {
        for (int i=0; i<CT; ++i) {
            h[i] = ((h[i] * BASE) + to_int[c]) % MOD[i];
        }
    }
    inline const bool operator<(const Hash& other) const {
        for (int i=0; i<CT; ++i) {
            if (h[i] != other.h[i]) {
                return h[i] < other.h[i];
            }
        }
        return false;
    }
    inline const bool operator==(const Hash& other) const {
        for (int i=0; i<CT; ++i) {
            if (h[i] != other.h[i]) return false;
        }
        return true;
    }
};

struct Str {
    string s;
    vector<Hash> h;

    Str() {
        s = "";
        h = vector<Hash>();
    }
    void make_hashes() {
        h = vector<Hash>(sz(s));
        for (int i=0; i<sz(s); ++i) {
            if (i) h[i] = h[i-1];
            h[i].add(s[i]);
        }
    }
    int size() {
        return s.size();
    }
    inline const bool operator<(const Str& other) {
        int mn = min(sz(s), sz(other.s));
        int lo = 0, hi = mn; 
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (h[mid] == other.h[mid]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        if (lo == mn) {
            return sz(s) < sz(other.s);
        }
        return s[lo] < other.s[lo];
    }
};

int N, M;
Str S[MN];
map<Hash, vector<int>> shash;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    to_int['A'] = 1;
    to_int['B'] = 2;
    to_int['C'] = 3;
    to_int['D'] = 4;
    to_int['G'] = 5;
    to_int['H'] = 6;
    to_int['U'] = 7;
    to_int['V'] = 8;

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> S[i].s;
        S[i].make_hashes();
    }
    sort(S, S+N);

    for (int i=0; i<N; ++i) {
        Hash cur;
        for (int j=sz(S[i]) - 1; j>=0; --j) {
            cur.add(S[i].s[j]);
            shash[cur].emplace_back(i);
        }
    }

    for (int i=0; i<M; ++i) {
        Str P;
        string Q;
        cin >> P.s >> Q;
        P.make_hashes();

        int lo = lower_bound(S, S+N, P) - S;
        P.s.back()++;
        P.make_hashes();
        int hi = lower_bound(S+lo, S+N, P) - S;

        Hash suff(Q);
        auto it = shash.find(suff);
        if (it == shash.end()) {
            cout << "0\n";
        } else {
            int ans = lower_bound(it->second.begin(), it->second.end(), hi) - lower_bound(it->second.begin(), it->second.end(), lo);
            cout << ans << '\n';
        }
    }
}
/*
2 3
AUGC
AGC
G C
AU C
A C

3 3
AA
AA AGA
AA AA
AG GA
AG GA

8 7
GCGCUACCCCAACACAAGGCAAGAUAUA
G
GGAC
GCGG
U
GCGCUACCCCAACACAAGGCAAGAUGGUC
GCCG
GCGCUGA
GCGCUACCC A
GCGCUACCCC AC
GCG C
GCGC A
G G
G C
G GGA
*/
