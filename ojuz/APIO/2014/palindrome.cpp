#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

string s;
const int CT = 3;
const ll BASE = 29;
const ll MOD[CT] = {(ll)1e9 + 7, (ll)1e9 + 9, (ll)1e9 + 13};


ll binpow(ll x, ll p, const ll mod) {
    x %= mod;
    p %= mod;
    ll res = 1;
    while (p > 0) {
        if (p & 1) {
            res = (res * x) % mod;
        }
        x = (x * x) % mod;
        p >>= 1;
    }
    return res;
}

struct Hash {
    ll val[CT];
    int len;

    Hash() {
        for (int i=0; i<CT; ++i) {
            val[i] = 0;
        }
        len = 0;
    }
    Hash(char c) {
        for (int i=0; i<CT; ++i) {
            val[i] = c - 'a' + 1;
        }
        len = 1;
    }

    void add_left(char c) {
        for (int i=0; i<CT; ++i) { 
            val[i] = (val[i] * BASE) % MOD[i];
            val[i] += c - 'a' + 1;
        }
        ++len;
    }
    void add_right(char c) {
        for (int i=0; i<CT; ++i) {
            val[i] = (val[i] + c * binpow(BASE, len, MOD[i])) % MOD[i];
        }
        ++len;
    }

    inline const bool operator<(const Hash& other) const {
        if (len != other.len) {
            return len < other.len;
        }
        for (int i=0; i<CT; ++i) {
            if (val[i] != other.val[i]) {
                return val[i] < other.val[i];
            }
        }
        return false;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    const int N = s.size();

    map<Hash, ll> ct;
    for (int i=0; i<N; ++i) {
        Hash hash(s[i]);
        ++ct[hash];
        int L = i-1, R = i+1;
        while (L >= 0 && R < N && s[L] == s[R]) {
            hash.add_left(s[L]);
            hash.add_right(s[R]);
            
            ++ct[hash];
            --L; ++R;
        }

        hash = Hash();
        L = i, R = i+1;
        while (L >= 0 && R < N && s[L] == s[R]) {
            hash.add_left(s[L]);
            hash.add_right(s[R]);
            
            ++ct[hash];
            --L; ++R;
        }
    }

    ll ans = 0;
    for (auto it=ct.begin(); it!=ct.end(); ++it) {
        ans = max(ans, it->first.len * it->second);
    }

    cout << ans << endl;
}
