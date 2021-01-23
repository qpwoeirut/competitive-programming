//palindromic_partitions.cpp created at 01/21/21 18:16:30

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int CT = 3;
const ll MOD[CT] = {(ll)1e9+7, (ll)1e9+9, (ll)1e9+23};
const ll BASE = 29;

ll binpow(ll x, ll p, const ll mod) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        p >>= 1;
    }
    return ret;
}

struct Hash {
    string str;
    vector<ll> v[CT];

    Hash(const string& s) {
        str = s;
        for (int j=0; j<CT; ++j) v[j] = vector<ll>(1);
        for (int i=0; i<str.size(); ++i) {
            const ll x = str[i] - 'a' + 1;
            for (int j=0; j<CT; ++j) {
                v[j].push_back(((v[j].back() * BASE) + x) % MOD[j]);
            }
        }
    }

    inline bool comp(const int len, const int s1, const int s2) const {
        assert(s1 <= s2);

        for (int j=0; j<CT; ++j) {
            ll h1 = (v[j][s1 + len] - (v[j][s1] * binpow(BASE, len, MOD[j]))) % MOD[j];
            ll h2 = (v[j][s2 + len] - (v[j][s2] * binpow(BASE, len, MOD[j]))) % MOD[j];
            h1 = (h1 + MOD[j]) % MOD[j];
            h2 = (h2 + MOD[j]) % MOD[j];

            if (h1 != h2) {
                return false;
            }
        }

        for (int i=0; i<len; ++i) {
            assert(str[s1 + i] == str[s2 + i]);
        }

        return true;
    }
};

void test() {
    const Hash h("abcdeabcde");
    assert(h.comp(5, 0, 5));
    assert(h.comp(1, 3, 8));
    assert(!h.comp(1, 0, 1));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //test(); return 0;

    int T;
    cin >> T;
    for (int t=0; t<T; ++t) {
        string S;
        cin >> S;
        
        const Hash h(S);

        const int N = S.size();
        int L = 0, R = N;
        int len = 1;
        int ans = 0;
        while (L + len <= R - len) {
            //cerr << L << ' ' << R-len << ' ' << len << endl;
            if (h.comp(len, L, R-len)) {
                ans += 2;
                L += len;
                R -= len;
                len = 1;
            } else {
                ++len;
            }
        }
        //cerr << L << ' ' << R << endl;
        if (L < R) ++ans;

        cout << ans << endl;
    }
}
/*
6
bonobo
deleted
racecar
racecars
abcab
abab
*/
