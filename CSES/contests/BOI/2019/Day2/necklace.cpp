#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int M = 5;
const ll X = 29;
const ll MOD[M] = {(ll)1e9+7, (ll)1e9+9, (ll)1e9+23, (ll)1e9+33, (ll)1e9+87};

ll binpow(ll n, ll p, ll mod) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = (ans * n) % mod;
        p >>= 1;
        n = (n * n) % mod;
    }
    return ans;
}

struct Hash {
    ll h[M];
    int start, len;
    inline const bool operator<(const Hash& other)const {
        for (int i=0; i<M; ++i) {
            if (h[i] != other.h[i]) return h[i] < other.h[i];
        }
        return false;
    }

    Hash(int _start) {
        fill(h, h+M, 0);
        start = _start;
        len = 0;
    }

    Hash(const Hash& base, int c, bool rev) {
        start = base.start;
        len = base.len + 1;
        if (!rev) {
            for (int i=0; i<M; ++i) {
                h[i] = (base.h[i] + c * binpow(X, len - 1, MOD[i])) % MOD[i];
            }
        } else {
            for (int i=0; i<M; ++i) {
                h[i] = (base.h[i] * X + c) % MOD[i];
            }
        }
    }
    void rotate(ll c) {
        for (int i=0; i<M; ++i) {
            ll shorter = (h[i] - (c * binpow(X, len-1, MOD[i]))) % MOD[i];
            h[i] = (((shorter * X + c) % MOD[i]) + MOD[i]) % MOD[i];
        }
    }

    inline const string str() const {
        string s = "";
        for (int i=0; i<M; ++i) {
            s += i ? " " : "[";
            s += to_string(h[i]);
        }
        return s + "]";
    }
};

const int MN = 3001;

string s, t;
set<Hash> hashes[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> s >> t;

    for (int i=0; i<s.size(); ++i) {
        Hash h1(i), h2(i);
        for (int j=0; i+j<s.size(); ++j) {
            h1 = Hash(h1, s[i+j] - 'a' + 1, false);
            h2 = Hash(h2, s[i+j] - 'a' + 1, true);

            hashes[j].insert(h1);
            hashes[j].insert(h2);
            //cerr << i << ' ' << j << ": " << h1.str() << ' ' << h2.str() << endl;
        }
    }
    //for (int i=0; i<s.size(); ++i) { cerr << i << endl; for (auto it=hashes[i].begin(); it!=hashes[i].end(); ++it) { cerr << it->str() << endl; } }

    int ans = 0;
    int p1 = -1, p2 = -1;
    for (int i=0; i<t.size(); ++i) {
        Hash h1(i), h2(i);
        for (int j=0; i+j<t.size(); ++j) {
            h1 = Hash(h1, t[i+j] - 'a' + 1, false);
            h2 = Hash(h2, t[i+j] - 'a' + 1, true);

            //cerr << i << ' ' << j << ": " << h1.str() << ' ' << h2.str() << endl;
            //cerr << hashes[j].count(h1) << ' ' << hashes[j].count(h2) << endl;
            //cerr << "ans: " << ans << endl;

            if (ans <= j) {
                auto it = hashes[j].find(h1);
                if (it != hashes[j].end()) {
                    ans = j + 1;
                    p1 = it->start;
                    p2 = h1.start;
                }
                it = hashes[j].find(h2);
                if (it != hashes[j].end()) {
                    ans = j + 1;
                    p1 = it->start;
                    p2 = h2.start;
                }
                for (int k=0; k<j; ++k) {
                    it = hashes[j].find(h1);
                    if (it != hashes[j].end()) {
                        ans = j + 1;
                        p1 = it->start;
                        p2 = h1.start;
                    }
                    h1.rotate(t[i+k] - 'a' + 1);

                    it = hashes[j].find(h2);
                    if (it != hashes[j].end()) {
                        ans = j + 1;
                        p1 = it->start;
                        p2 = h2.start;
                    }
                    h2.rotate(t[i+j-k-1] - 'a' + 1);
                }
            }
            //cerr << i << ' ' << j << ": " << h1.str() << ' ' << h2.str() << endl << endl;
        }
    }

    cout << ans << endl;
    cout << p1 << ' ' << p2 << endl;
}
/*
zxyabcd
yxbadctz
*/
